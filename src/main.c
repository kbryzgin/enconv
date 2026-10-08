#include <stdio.h>
#include <stdlib.h>

#include "codepages.h"
#include "utf8.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Error: Usage: %s <input_file> <encoding> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    encodings name = define_encoding(argv[2]);
    if (name == UNDEFINED) {
        printf("Error: Undefined encoding\n");
        return EXIT_FAILURE;
    }

    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL) {
        printf("Error: File openinig error\n");
        return EXIT_FAILURE;
    }

    FILE *output_file = fopen(argv[3], "wb");
    if (output_file == NULL) {
        fclose(input_file);
        printf("Error: File writing error\n");
        return EXIT_FAILURE;
    }

    int byte;

    while ((byte = fgetc(input_file)) != EOF) {
        byte = (unsigned char)byte;
        uint32_t code_point = decode_to_unicode(byte, name);
        encode_to_utf8(code_point, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}