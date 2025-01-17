#include "../blockchain.h"

void calculateHash(Block *block, unsigned char *hash) {
    char input[512];
    snprintf(input, sizeof(input), "%d%ld%s", block->index, block->timestamp, block->data);

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Failed to create EVP_MD_CTX\n");
        exit(EXIT_FAILURE);
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1 ||
        EVP_DigestUpdate(ctx, input, strlen(input)) != 1 ||
        EVP_DigestUpdate(ctx, block->prevHash, SHA256_DIGEST_LENGTH) != 1 ||
        EVP_DigestFinal_ex(ctx, hash, NULL) != 1) {
        fprintf(stderr, "Failed to calculate hash\n");
        EVP_MD_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(ctx);
}

Block *createBlock(int index, const char *data, unsigned char *prevHash) {
    Block *newBlock = (Block *)malloc(sizeof(Block));
    if (!newBlock) {
        perror("Failed to allocate memory for block");
        exit(EXIT_FAILURE);
    }

    newBlock->index = index;
    newBlock->timestamp = (uint64_t)time(NULL);
    strncpy(newBlock->data, data, sizeof(newBlock->data) - 1);
    newBlock->data[sizeof(newBlock->data) - 1] = '\0';
    memcpy(newBlock->prevHash, prevHash, SHA256_DIGEST_LENGTH);
    calculateHash(newBlock, newBlock->currHash);
    newBlock->next = NULL;

    return newBlock;
}

Blockchain *initBlockchain() {
    Blockchain *blockchain = (Blockchain *)malloc(sizeof(Blockchain));
    if (!blockchain) {
        perror("Failed to allocate memory for blockchain");
        exit(EXIT_FAILURE);
    }

    // Create the genesis block
    unsigned char genesisHash[SHA256_DIGEST_LENGTH] = {0};
    Block *genesisBlock = createBlock(0, "Genesis Block", genesisHash);

    blockchain->head = blockchain->tail = genesisBlock;
    blockchain->length = 1;

    return blockchain;
}

void addBlock(Blockchain *blockchain, const char *data) {
    Block *newBlock = createBlock(blockchain->length, data, blockchain->tail->currHash);

    blockchain->tail->next = newBlock;
    blockchain->tail = newBlock;
    blockchain->length++;
}

void printBlockchain(Blockchain *blockchain) {
    Block *current = blockchain->head;
    while (current) {
        printf("Block %d\n", current->index);
        printf("Timestamp: %lu\n", current->timestamp);
        printf("Data: %s\n", current->data);

        printf("Previous Hash: ");
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            printf("%02x", current->prevHash[i]);
        }
        printf("\n");

        printf("Current Hash: ");
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            printf("%02x", current->currHash[i]);
        }
        printf("\n\n");

        current = current->next;
    }
}

void freeBlockchain(Blockchain *blockchain) {
    Block *current = blockchain->head;
    while (current) {
        Block *next = current->next;
        free(current);
        current = next;
    }
    free(blockchain);
}


