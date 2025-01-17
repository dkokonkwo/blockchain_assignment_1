#include "blockchain2.h"

/**
 * createData: create data_t structure for a new block
 * @sender: sender details
 * @receiver: receiver details
 * @amount: transaction amount
 */
data_t *createData(char sender[DATASIZE_MAX], char receiver[DATASIZE_MAX], char amount[512]) {
    transaction_t *new_trans;
    data_t *new_data;
    new_trans = (transaction_t *)malloc(sizeof(transaction_t));
    if (!new_trans)
    {
        perror("Could not allocate memory for transaction");
        free(new_trans);
        exit(EXIT_FAILURE);
    }
    memcpy(new_trans->sender, sender, sizeof(new_trans->sender) - 1);
    memcpy(new_trans->receiver, receiver, sizeof(new_trans->receiver) - 1);
    memcpy(new_trans->amount, amount, sizeof(new_trans-amount) - 1);
    new_trans->next = NULL;
    new_trans->index = 0;
    new_data = (data_t *)malloc(sizeof(data_t));
    if (!new_data)
    {
        perror("Could not allocate memory for data");
        free(new_trans);
        free(new_data);
        exit(EXIT_FAILURE);
    }
    new_data->head = new_trans;
    new_data->tail = new_trans;
    new_data->nb_transactions = 1;
    return new_data;
}

/**
 * createBlock - creates new block
 * @data: pointer to data to add to block
 * @prevHash: previous block hash
 */
block_t *createBlock(int index, data_t *data, unsigned char *prevHash) {
    block_t *newBlock = (block_t *)malloc(sizeof(block_t));
    if (!newBlock) {
        perror("Failed to allocate memory for block");
        exit(EXIT_FAILURE);
    }

    newBlock->index = index;
    newBlock->timestamp = (uint64_t)time(NULL);
    newBlock->data = data;
    memcpy(newBlock->prevHash, prevHash, SHA256_DIGEST_LENGTH);
    calculateHash(newBlock, newBlock->currHash);
    newBlock->next = NULL;
    return newBlock;
}

/**
 * calculateHash - calculates the hash of a block
 * @block: pointer to block to calculate hash of
 * @hash: pointer to address to store hash
 * Return: Nothing
 */
void calculateHash(block_t *block, unsigned char *hash) {
    char input[DATASIZE_MAX];
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

/**
 * addBlock - adds block to blockchain
 * @blockchain: pointer to blockchain
 * @data: pointer to new data
 * Return: Nothing
 */
void addBlock(Blockchain *blockchain, data_t *data) {
    block_t *newBlock = createBlock(blockchain->length, data, blockchain->tail->currHash);

    blockchain->tail->next = newBlock;
    blockchain->tail = newBlock;
    blockchain->length++;
}

/**
 * addTransaction - adds transaction to a block if its tail else new block
 * @blockchain: pointer to blockchain
 * @block: pointer to block to add transaction to
 * @sender: sender details
 * @receiver: receiver details
 * @amount: amount of transaction
 * Return: 1 on success or 0 on failure
 */
int addTransaction(Blockchain *blockchain, block_t *block, char sender[DATASIZE_MAX], char receiver[DATASIZE_MAX], char amount[512]) {
    if (!block || !blockchain)
    {
        printf("Blockchain or block not valid\n");
        return 0;
    }
    if (blockchain->length - 1 == block->index)
    {
        transaction_t *new_trans = (transaction_t *)malloc(sizeof(transaction_t));
        if (!new_trans)
        {
            printf("Could not allocated memory for new transaction");
            return 0;
        }
        new_trans->index = block->data->nb_transactions++;
        new_trans->next = NULL;
        memcpy(new_trans->sender, sender, sizeof(new_trans->sender) - 1);
        memcpy(new_trans->receiver, receiver, sizeof(new_trans->receiver) - 1);
        memcpy(new_trans->amount, amount, sizeof(new_trans-amount) - 1);
        block->data->tail->next = new_trans;
        block->data->tail = new_trans;
        return 1;
    }
    else if (blockchain->length - 1 < block->index)
    {
        printf("Your block index seems to be wrong\n");
    return 0;
    }
    printf("Creating new block for transaction.....\n");
    data_t *new_data = createData(sender, receiver, amount);
    if (!new_data)
    {
        printf("Could not create new data\n");
        return 0;
    }
    addBlock(blockchain, new_data);
    printf("Added new block to blockchain\n");
    return 1;
}

/**
 * initBlockchain - initializes new blockchain with genesis block
 * Return: pointer to blockchain
 */
Blockchain *initBlockchain() {
    Blockchain *blockchain = (Blockchain *)malloc(sizeof(Blockchain));
    if (!blockchain) {
        perror("Failed to allocate memory for blockchain");
        exit(EXIT_FAILURE);
    }

    // Create the genesis block
    unsigned char genesisHash[SHA256_DIGEST_LENGTH] = {0};
    block_t *genesisBlock = createBlock(0, "Genesis Block", genesisHash);

    blockchain->head = blockchain->tail = genesisBlock;
    blockchain->length = 1;

    return blockchain;
}

/**
 * validateBlockchain - ensures that previous block's hash matches with new block's hash
 * @blockchain: pointer to blockchain to validate
 * Return: 1 if valid, or 0 if invalid
 */
int validateBlockchain(Blockchain *blockchain) {
    if (!blockchain)
        return 0;
    unsigned char genesisHash[SHA256_DIGEST_LENGTH] = {0};
    unsigned char tmpHash[SHA256_DIGEST_LENGTH];
    block_t *current = blockchain->head;

    memcpy(tmpHash, genesisHash, SHA256_DIGEST_LENGTH);

    while (current->next)
    {
        if (memcmp(current->prevHash, tmpHash, SHA256_DIGEST_LENGTH) != 0)
            return 0;
        memcpy(tmpHash, current->currHash, SHA256_DIGEST_LENGTH);
        current = current->next;
    }
    return 1;
}

/**
 * printBlockchain: prints blocks in blockchain
 * @blockchain: pointer to blockchain
 * Return: Nothing
 */
void printBlockchain(Blockchain *blockchain) {
    block_t *current = blockchain->head;
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

/**
 * freeBlockchain - free block in blockchain and then the blockchain itself
 * @blockchain: pointer to blockchain
 * Return: Nothing
 */
void freeBlockchain(Blockchain *blockchain) {
    block_t *current = blockchain->head;
    while (current) {
        block_t *next = current->next;
        free(current);
        current = next;
    }
    free(blockchain);
}


