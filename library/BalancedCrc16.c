/**************************************************
 * Copyright 2019 IAR Systems. All rights reserved.
 *
 * $Revision$
 *
 * A simple implementation of the crc-16 checksum algorithm.
 *
 * The balanced version attempts to be almost as small as the small
 * version while simultaneosly being almost as fast as the fast
 * version.
 *
 * Note that the balanced version does not the additional zeroes or
 * the initial processing of the initial value that the SmallCrc
 * version require.
 *
 * Example of usage:
 *
 * uint16_t init = 0x1234;
 * uint16_t calc = FastCrc16(init, p, size);
 * // Test the checksum
 * if (calc != the_checksum)
 * {
 *   // Some error handling...
 * }
 *
 **************************************************/

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t const * code_ptr;

static const uint16_t t16_nib[] = {
 0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
 0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
};

uint16_t BalancedCrc16(uint16_t sum, code_ptr p, size_t len)
{
 while (len--)
 {
   /* hi nibble */
  sum = t16_nib[(sum >> 12) ^ (*p >> 4)] ^ (sum << 4);
  /* lo nibble */
  sum = t16_nib[(sum >> 12) ^ (*p++ & 0xF)] ^ (sum << 4);
 }

 return sum;
}

/*
   If the initial value is non zero and indirect/prefixed, this
   function must be called with the initial value before the first
   call to BalancedCrc16. The result of this function must be used as the
   input sum to the first call
*/

uint16_t BalancedCrcInit16(uint16_t init)
{
  uint8_t tmp[2];
  for (uint8_t i = 0 ; i < 2 ; ++i,init >>= 8)
    tmp[1-i] = init & 0xFF;
  return BalancedCrc16(0, tmp, 2);
}
