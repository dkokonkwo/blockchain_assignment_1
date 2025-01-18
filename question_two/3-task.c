#include "blockchain2.h"

int main() {
    /* initializing blockchain */
    Blockchain *blockchain = initBlockchain();

    /* Adding blocks with one transaction each */
    data_t *data1 = createData("Alice", "Bob", "50btc");
    addBlock(blockchain, data1);

    data_t *data2 = createData("Bob", "Charlie", "30btc");
    addBlock(blockchain, data2);

    data_t *data3 = createData("Charlie", "Dave", "20btc");
    addBlock(blockchain, data3);

    /* Printing the Blockchain */
    printf("Initial Blockchain:\n");
    printBlockchain(blockchain);

    /* Validating the blockchain */
    if (validateBlockchain(blockchain)) {
        printf("Blockchain is valid.\n\n");
    } else {
        printf("Blockchain is invalid.\n\n");
    }

    /* adding new transactions to the last block */
    block_t *lastBlock = blockchain->tail;

    addTransaction(blockchain, lastBlock, "Eve", "Frank", "40btc");
    addTransaction(blockchain, lastBlock, "Grace", "Hank", "25btc");
    /* Recalculating block's hash with after adding transcactions*/
    calculateHash(lastBlock, lastBlock->currHash);

    /* Printing updated transactions*/
    printf("Updated Blockchain:\n");
    printBlockchain(blockchain);

    freeBlockchain(blockchain);

    return 0;
}

