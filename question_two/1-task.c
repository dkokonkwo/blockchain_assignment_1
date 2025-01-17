#include "../blockchain.h"

block_t *block_create(int index, const char *data, unsigned char *prevHash);
void calculateNewHash(block_t *block, unsigned char *hash);
void print_block(block_t *block);

int main()
{
    unsigned char oldHash[SHA256_DIGEST_LENGTH];
    char const *data = "\tTRANSACTIONS:\n1. Sender: Charles George\n   Receiver: John Doe\n   Amount: 2btc\n2. Sender: Jane Foster\n   Receiver: Blaise Pascal\n   Amount: 34btc";
    const char *input = "Old hash for new block";
    SHA256((unsigned char *)input, strlen(input), oldHash);
    block_t *new_block = block_create(0, data, oldHash);
    if (!new_block)
    {
        perror("Failed to create new block");
        exit(EXIT_FAILURE);
    }
    print_block(new_block);
    free(new_block);
    return (0);
}

 block_t *block_create(int index, const char *data, unsigned char *prevHash)
{
    block_t *newBlock = (block_t *)malloc(sizeof(block_t));
    if (!newBlock) {
        perror("Failed to allocate memory for block");
        free(newBlock);
        exit(EXIT_FAILURE);
    }

    newBlock->index = index;
    newBlock->timestamp = (uint64_t)time(NULL);
    strncpy(newBlock->data, data, sizeof(newBlock->data) - 1);
    newBlock->data[sizeof(newBlock->data) - 1] = '\0';
    memcpy(newBlock->prevHash, prevHash, SHA256_DIGEST_LENGTH);
    calculateNewHash(newBlock, newBlock->currHash);

    return newBlock;
}


void calculateNewHash(block_t *block, unsigned char *hash) {
    char input[1024];
    snprintf(input, sizeof(input), "%d%lu%.*s", 
         block->index, 
         block->timestamp, 
         (int)(sizeof(input) - 1 - snprintf(NULL, 0, "%d%lu", block->index, block->timestamp)), 
         block->data);

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

void print_block(block_t *block)
{
    if (!block)
    {
		printf("No blocks\n");
		return;
	}

	printf("Block: {\n");
	printf("index: %u,\n", block->index);
	printf("timestamp: %lu,\n", block->timestamp);
	printf("prev_hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
         printf("%02x", block->prevHash[i]);
    }
    printf("\n},\n");
	printf("data: {\n");
	printf("%s\n", block->data);
	printf("},\n");

	printf("hash: ");
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
         printf("%02x", block->currHash[i]);
    }

	printf("\n}\n");
}
