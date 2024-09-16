/**************************************************
 * Copyright 2019 IAR Systems. All rights reserved.
 *
 * $Revision$
 *
 * A simple implementation of the crc-32 checksum algorithm.
 *
 * The small version aims at being as small as possible.
 *
 * Note that if you use this algorithm/function, you need to call it with
 * an extra number of zero bytes equal to the size of the checksum
 * (in this case 4), to "rotate out the answer".
 *
 * Example of usage:
 *
 * uint32_t init = SmallCrcInit32(0x12345678); // for non zero init values
 * uint32_t calc = SmallCrc32(init, p, size);
 * // Rotate out the answer
 * uint8_t zeroes[4] = {0, 0, 0, 0};
 * calc = SmallCrc32(calc, zeroes, 4);
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

uint32_t SmallCrc32(uint32_t sum, code_ptr p, size_t len)
{
  while (len--)
  {
    uint8_t byte = *(p++);
    for (int i = 0 ; i < 8 ; ++i)
    {
      uint32_t osum = sum;
      sum <<= 1;
      if (byte & 0x80)
        sum |= 1;
      if (osum & 0x80000000)
        sum ^= 0x4c11db7;    /* the CRC32 polynomial */
      byte <<= 1;
    }
  }
  return sum;
}

/*
   If the initial value is non zero and direct/non prefixed, this
   function must be called with the initial value before the first
   call to SmallCrc32. The result of this function must be used as the
   input sum to the first call
*/

uint32_t SmallCrcInit32(uint32_t init)
{
  for (uint32_t i = 0 ; i < 32 ; ++i)
  {
    uint32_t bit = init & 1;
    if (bit)
      init ^= 0x4c11db7; /* the CRC16 polynomial */
    init >>= 1;

    if (bit)
      init |= 0x80000000;
  }

  return init;
}
