#include "blockchain2.h"


int main(void) {
    /* initializing blockchain */
    Blockchain *blockchain = initBlockchain();
    if (!blockchain) {
        fprintf(stderr, "Failed to initialize blockchain\n");
        return EXIT_FAILURE;
    }

    /* Adding blocks with one transaction each */
    char *senders[] = {"Alice", "Bob", "Charlie", "David"};
    char *receivers[] = {"Eve", "Frank", "Grace", "Hank"};
    char *amounts[] = {"100", "200", "300", "400"};

    for (int i = 0; i < 4; i++) {
        /* Creating data for each block */
        data_t *data = createData(senders[i], receivers[i], amounts[i]);
        if (!data) {
            fprintf(stderr, "Failed to create data for block %d\n", i + 1);
            freeBlockchain(blockchain);
            return EXIT_FAILURE;
        }

        /* Adding block to blockchain */
        addBlock(blockchain, data);
    }

    /* Printing the Blockchain */
    printf("Blockchain after adding 4 blocks with one transaction each:\n");
    printBlockchain(blockchain);

    /* Validating the blockchain */
    if (validateBlockchain(blockchain)) {
        printf("Blockchain is valid\n");
    } else {
        printf("Blockchain is invalid\n");
    }

    freeBlockchain(blockchain);

    return EXIT_SUCCESS;
}

