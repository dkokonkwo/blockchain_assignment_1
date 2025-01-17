#ifndef BLOCKCHAIN2_H
#define BLOCKCHAIN2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include <openssl/evp.h>
#include <stdint.h>

#define DATASIZE_MAX 1024

typedef struct transaction_s {
    int index;
    char sender[DATASIZE_MAX];
    char receiver[DATASIZE_MAX];
    char amount[512];
    struct transaction_s *next;
} transaction_t;

typedef struct data_s {
    transaction_t *head;
    transaction_t *tail;
    int nb_transactions;
} data_t;

typedef struct block_s {
    int index;
    uint64_t timestamp;
    data_t *data;
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    unsigned char currHash[SHA256_DIGEST_LENGTH];
    struct block_s *next;
} block_t;

typedef struct Blockchain {
    block_t *head;
    block_t *tail;
    int length;
} Blockchain;

/* FUNCTIONS */
void calculateHash(block_t *block, unsigned char *hash);
block_t *createBlock(int index, const char *data, unsigned char *prevHash);
Blockchain *initBlockchain(void);
void addBlock(Blockchain *blockchain, const char *data);
void printBlockchain(Blockchain *blockchain);
void freeBlockchain(Blockchain *blockchain);

#endif /* blockchain.h */
