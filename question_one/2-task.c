#include "../blockchain.h"

int main() {
    Blockchain *blockchain = initBlockchain();

    addBlock(blockchain, "Transactions:\n\tSender: John\n\tReceiver: James\n\tAmount: 2btc");
    addBlock(blockchain, "Transactions:\n\tSender: Oliver\n\tReceiver: Kirk\n\tAmount: 5.2btc");
    addBlock(blockchain, "Transactions:\n\tSender: SchumPeter\n\tReceiver: Mark\n\tAmount: 12btc");

    printf("\t\tBLOCKCHAIN CONTENTS:\n\n");
    printBlockchain(blockchain);

    freeBlockchain(blockchain);

    return 0;
}

