#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main() {
    const char *input = "Blockchain Cryptography";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char *)input, strlen(input), hash);

    printf("SHA256 hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}

