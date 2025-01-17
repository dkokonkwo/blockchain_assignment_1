#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include <openssl/evp.h>
#include <stdint.h>

#define DATASIZE_MAX 1024

typedef struct Block {
    int index;
    uint64_t timestamp;
    char data[DATASIZE_MAX];
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    unsigned char currHash[SHA256_DIGEST_LENGTH];
    struct Block *next;
} Block;

typedef struct block_s {
    int index;
    uint64_t timestamp;
    char data[DATASIZE_MAX];
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    unsigned char currHash[SHA256_DIGEST_LENGTH];
} block_t;

typedef struct Blockchain {
    Block *head;
    Block *tail;
    int length;
} Blockchain;

/* FUNCTIONS */
void calculateHash(Block *block, unsigned char *hash);
Block *createBlock(int index, const char *data, unsigned char *prevHash);
Blockchain *initBlockchain(void);
void addBlock(Blockchain *blockchain, const char *data);
void printBlockchain(Blockchain *blockchain);
void freeBlockchain(Blockchain *blockchain);

#endif /* blockchain.h */
