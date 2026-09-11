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

    const char *input_file    = argv[1];
    const char *encoding = argv[2];
    const char *output_file   = argv[3];

    if (strcmp(encoding, "cp1251") != 0 && strcmp(encoding, "CP-1251") != 0) {
        fprintf(stderr, "Error: unsupported encoding '%s'\n", encoding);
        return 1;
    }

    FILE *input_stream = fopen(input_file, "rb");
    if (input_stream == NULL) {
        fprintf(stderr, "Error: file reading error\n");
        return 1;
    }

    FILE *output_stream = fopen(output_file, "wb");
    if (output_stream == NULL) {
        fprintf(stderr, "Error: file writing error\n");
        fclose(input_stream);
        return 1;
    }

    int result = convert_file(input_stream, output_stream);

    fclose(input_stream);
    fclose(output_stream);

    if (result != 0) {
        fprintf(stderr, "Error: conversion failed\n");
        return 1;
    }

    return 0;
}

