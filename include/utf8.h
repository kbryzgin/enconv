// UTF-8 templates header

#pragma once

#include <stdint.h>
#include <stdio.h>

int encode_to_utf8(uint32_t code_point, FILE *out);
