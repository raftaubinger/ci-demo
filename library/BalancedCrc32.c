/**************************************************
 * Copyright 2019 IAR Systems. All rights reserved.
 *
 * $Revision$
 *
 * A simple implementation of the crc-32 checksum algorithm.
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
 * uint32_t init = 0x12345678; 
 * uint32_t calc = FastCrc32(init, p, size);
 * // Test the checksum
 * if (calc != the_checksum)
 * {
 *   // Some error handling...
 * }
 *
 **************************************************/

#include <stdint.h>
#include <stdlib.h>

#include "crc-lib.h"

extern uint32_t FastCrcInit32(uint32_t init);

static const uint32_t t32_nib[16] = {
 0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9,
 0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
 0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
};

uint32_t BalancedCrc32(uint32_t sum, code_ptr p, size_t len)
{
 while (len--)
 {
   /* hi nibble */
   sum = t32_nib[(sum >> 28) ^ (*p >> 4)] ^ (sum << 4);
  /* lo nibble */
   sum = t32_nib[(sum >> 28) ^ (*p++ & 0xF)] ^ (sum << 4);
 }

 return sum;
}

/*
   If the initial value is non zero and indirect/prefixed, this
   function must be called with the initial value before the first
   call to BalancedCrc32. The result of this function must be used as
   the input sum to the first call
*/

// uint32_t FastCrcInit32(uint32_t init)
// {
  // uint8_t tmp[4];
  // for (uint8_t i = 0 ; i < 4 ; ++i,init >>= 8)
    // tmp[3-i] = init & 0xFF;
  // return BalancedCrc32(0, tmp, 4);
// }
