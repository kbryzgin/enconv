/*
 * entry point
 */

#include <stdio.h> 
#include <string.h>
#include "encoding.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Error: incorrect number of arguments\n");
        fprintf(stderr, "Usage: %s <input> <encoding> <output>\n", argv[0]);
        return 1;
    }

    const char *input    = argv[1];
    const char *encoding = argv[2];
    const char *output   = argv[3];

    if (strcmp(encoding, "cp1251") != 0 && strcmp(encoding, "CP-1251") != 0) {
        fprintf(stderr, "Error: unsupported encoding '%s'\n", encoding);
        return 1;
    }

    FILE *input = fopen(input, "rb");
    if (input == NULL) {
        fprintf(stderr, "Error: file reading error\n");
        return 1;
    }

    FILE *output = fopen(output, "wb");
    if (output == NULL) {
        fprintf(stderr, "Error: file writing error\n");
        return 1;
    }
}
