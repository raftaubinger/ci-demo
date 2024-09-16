#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t const * code_ptr;

uint16_t BalancedCrc16(uint16_t sum, code_ptr p, size_t len);
uint16_t BalancedCrcInit16(uint16_t init);

uint32_t BalancedCrc32(uint32_t sum, code_ptr p, size_t len);
uint32_t FastCrcInit32(uint32_t init);

uint16_t FastCrc16(uint16_t sum, code_ptr p, size_t len);
uint16_t FastCrcInit16(uint16_t init);

uint32_t FastCrc32(uint32_t sum, code_ptr p, size_t len);
uint32_t FastCrcInit32(uint32_t init);

uint8_t MirrorBalanced8(uint8_t byte);
uint16_t MirrorBalanced16(uint16_t hw);
uint32_t MirrorBalanced32(uint32_t hw);

void MirrorFast(uint8_t * table);

uint32_t MirrorSmall(uint32_t orig, uint8_t size);

unsigned short slow_crc16(unsigned short sum, unsigned char *p, unsigned int len);

uint16_t SmallCrc16(uint16_t sum, code_ptr p, size_t len);
uint16_t SmallCrcInit16(uint16_t init);

uint32_t SmallCrc32(uint32_t sum, code_ptr p, size_t len);
uint32_t SmallCrcInit32(uint32_t init);