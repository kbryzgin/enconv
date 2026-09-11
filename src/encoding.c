/*
 * mapping and encoding core definitions
 */

#include "encoding.h"

#define ASCII_RANGE         0x0080
#define UTF8_2BYTE_MAX      0x07FF

#define CP1251_OFFSET       128
#define CP1251_MAP_SIZE     128

#define UTF8_1BYTE_MASK     0x00
#define UTF8_2BYTE_PREFIX   0xC0
#define UTF8_3BYTE_PREFIX   0xE0
#define UTF8_CONT_PREFIX    0x80

#define UTF8_6BIT_MASK      0x3F

#define CP1251_UNDEF_BYTE   0x98
#define UNICODE_NULL        0x0000
#define FALLBACK_CHAR       '?'

#define UTF8_BUFFER_SIZE    3

static const uint16_t cp1251_unicode_map[CP1251_MAP_SIZE] = {
    0x0402, 0x0403, 0x201A, 0x0453, 0x201E, 0x2026, 0x2020, 0x2021,
    0x20AC, 0x2030, 0x0409, 0x2039, 0x040A, 0x040C, 0x040B, 0x040F,
    0x0452, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
    0x0000, 0x2122, 0x0459, 0x203A, 0x045A, 0x045C, 0x045B, 0x045F,
    0x00A0, 0x040E, 0x045E, 0x0408, 0x00A4, 0x0442, 0x00A6, 0x00A7,
    0x0401, 0x00A9, 0x0404, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x0407,
    0x00B0, 0x00B1, 0x0406, 0x0456, 0x0454, 0x00B5, 0x00B6, 0x00B7,
    0x0451, 0x2116, 0x0458, 0x00BB, 0x0457, 0x0405, 0x0455, 0x045F,
    0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417,
    0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F,
    0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427,
    0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F,
    0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437,
    0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F,
    0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447,
    0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F
};

uint16_t cp1251_to_unicode_mapping(uint8_t byte) {
    if (byte < ASCII_RANGE)
        return (uint16_t)byte;

    return cp1251_unicode_map[byte - CP1251_OFFSET];
}

int unicode_to_utf8_encoding(uint16_t code_point, uint8_t* buffer) {
    if (code_point < ASCII_RANGE) {
        buffer[0] = (uint8_t)code_point;      
        return 1;
    }
    else if (code_point <= UTF8_2BYTE_MAX) {
        buffer[0] = (uint8_t)(UTF8_2BYTE_PREFIX | (code_point >> 6));
        buffer[1] = (uint8_t)(UTF8_CONT_PREFIX  | (code_point & UTF8_6BIT_MASK));
        return 2;
    }
    else {
        buffer[0] = (uint8_t)(UTF8_3BYTE_PREFIX | (code_point >> 12)); 
        buffer[1] = (uint8_t)(UTF8_CONT_PREFIX  | ((code_point >> 6) & UTF8_6BIT_MASK));
        buffer[2] = (uint8_t)(UTF8_CONT_PREFIX  | (code_point & UTF8_6BIT_MASK));
        return 3;
    }
}

int convert_file(FILE *input, FILE *output) {
    if (input == NULL || output == NULL)
        return 1;

    int c;
    uint8_t buffer[UTF8_BUFFER_SIZE];

    while ((c = fgetc(input)) != EOF) {
        uint16_t code_point = cp1251_to_unicode_mapping((uint8_t)c);

        if (code_point == UNICODE_NULL && (uint8_t)c == CP1251_UNDEF_BYTE)
            code_point = FALLBACK_CHAR;

        int bytes_encoded = unicode_to_utf8_encoding(code_point, buffer);
        size_t written = fwrite(buffer, 1, (size_t)bytes_encoded, output);

        if (written != (size_t)bytes_encoded)
            return 1;
    }

    return 0;
}

