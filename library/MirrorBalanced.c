/* *************************************************
 * Copyright 2019 IAR Systems. All rights reserved.
 *
 * $Revision$
 *
 * A simple implementation of reflection/mirroring
 *
 * Reflection/mirroring is the process of reversing the bit pattern in a byte (or word)
 * rev(00000001) = 10000000
 * rev(00100001) = 10000100
 *
 * Refelction is used in some crc-calculations. If they are used they
 * should mirror/reflect the input byte (the acutally used byte is
 * created by dereferencing the pointer and then feeding that byte
 * into the mirroring function, the returned value is then used as if
 * it was the result of the dereferencing the pointer). The final
 * result is typically also mirrored/reflected (the entire word, not
 * the individual bytes).
 *
 * The Balanced version uses a table of nibbles and constructs larger
 * reflections/mirrors using that.
 *
 * Example of usage:
 *
 * ... (inside some CRC-function)
 * uint8_t byte = *(p++);
 * ...
 *
 * This will become:
 * ...
 * uint8_t byte = BalancedMirror8(*(p++), 1);
 * ...
 *
 * and finally:
 *
 * crc = BalancedMirror16(crc);  // if crc16)
 * or
 * crc = BalancedMirror32(crc);  // if crc32
 *
 *
 ************************************************* */

#include <stdint.h>
#include <stdlib.h>

static uint8_t t_rev[] =
{
  0, // 0  = 0000 = 0000 = 0
  8, // 1  = 0001 = 1000 = 8
  4, // 2  = 0010 = 0100 = 4
 12, // 3  = 0011 = 1100 = C
  2, // 4  = 0100 = 0010 = 2
 10, // 5  = 0101 = 1010 = A
  6, // 6  = 0110 = 0110 = 6
 14, // 7  = 0111 = 1110 = E
  1, // 8  = 1000 = 0001 = 1
  9, // 9  = 1001 = 1001 = 9
  5, // 10 = 1010 = 0101 = 5
 13, // 11 = 1011 = 1101 = D
  3, // 12 = 1100 = 0011 = 3
 11, // 13 = 1101 = 1011 = E
  7, // 14 = 1110 = 0111 = 7
 15  // 15 = 1111 = 1111 = F
};

uint8_t MirrorBalanced8(uint8_t byte)
{
 return (t_rev[byte & 0xF] << 4) | (t_rev[byte >> 4]);
}

uint16_t MirrorBalanced16(uint16_t hw)
{
  uint8_t hi = MirrorBalanced8(hw & 0xFF);
  uint8_t lo = MirrorBalanced8(hw >> 8);
  return (hi << 8) | lo;
}

uint32_t MirrorBalanced32(uint32_t hw)
{
  uint8_t hihi = MirrorBalanced8((hw >> 0)  & 0xFF);
  uint8_t hilo = MirrorBalanced8((hw >> 8)  & 0xFF);
  uint8_t lohi = MirrorBalanced8((hw >> 16) & 0xFF);
  uint8_t lolo = MirrorBalanced8((hw >> 24) & 0xFF);
  return (hihi << 24) | (hilo << 16) | (lohi << 8) | lolo;
}
