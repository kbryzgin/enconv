// mapping tables header

#pragma once

#include <stdint.h>

typedef enum {
    CP1251,
    KOI8R,
    ISO8859_5,
    UNDEFINED
} encodings;

encodings define_encoding(const char *str);

uint32_t decode_to_unicode(unsigned char byte, encodings name);
