/*
 * encoding.h - mapping and encoding core
 */

#pragma once

#include <stdint.h>

uint16_t cp1251_to_unicode_mapping(uint8_t byte);

int unicode_to_utf8_encoding(uint16_t code_point, uint8_t* buffer);

