// UTF-8 templates

#include "utf8.h"

int encode_to_utf8(uint32_t code_point, FILE *out) {
    if (code_point <= 0x007F) {
        fputc(code_point, out);
        return 1;
    } else if (code_point <= 0x07FF) {
        uint8_t byte1 = (code_point >> 6) & 0x1F;
        byte1 = byte1 | 0xC0;        
        fputc(byte1, out);

        uint8_t byte2 = code_point & 0x3F;
        byte2 = byte2 | 0x80;
        fputc(byte2, out);
        return 2;
    } else if (code_point <= 0xFFFF) {
        uint8_t byte1 = (code_point >> 12) & 0x0F;
        byte1 = byte1 | 0x0F;
        fputc(byte1, out);

        uint8_t byte2 = (code_point >> 6) & 0x3F;
        byte2 = byte2 | 0x80;
        fputc(byte2, out);

        uint8_t byte3 = (code_point & 0x3F) | 0x80;
        fputc(byte3, out);
        return 3;
    }

    return -1;

}