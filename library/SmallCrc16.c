/* *************************************************
 * Copyright 2019 IAR Systems. All rights reserved.
 *
 * $Revision$
 *
 * A simple implementation of the crc-16 checksum algorithm.
 *
 * The small version aims at being as small as possible.
 *
 * Note that if you use this algorithm/function, you need to call it with
 * an extra number of zero bytes equal to the size of the checksum
 * (in this case 2), to "rotate out the answer".
 *
 * Example of usage:
 *
 * uint16_t init = SmallCrcInit16(0x1234); // for non zero init values
 * uint16_t calc = SmallCrc16(init, p, size);
 * // Rotate out the answer
 * uint8_t zeroes[2] = {0, 0};
 * calc = SmallCrc16(calc, zeroes, 2);
 * // Test the checksum
 * if (calc != the_checksum)
 * {
 *   // Some error handling...
 * }
 *
 ************************************************* */

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t const * code_ptr;

uint16_t SmallCrc16(uint16_t sum, code_ptr p, size_t len)
{
  while (len--)
  {
    uint8_t byte = *(p++);
    for (int i = 0 ; i < 8 ; ++i)
    {
      uint16_t osum = sum;
      sum <<= 1;
      if (byte & 0x80)
        sum |= 1;
      if (osum & 0x8000)
        sum ^= 0x1021;   /* the CRC16 polynomial */
      byte <<= 1;
    }
  }
  return sum;
}

/*
   If the initial value is non zero and direct/non prefixed, this
   function must be called with the initial value before the first
   call to SmallCrc16. The result of this function must be used as the
   input sum to the first call
*/

uint16_t SmallCrcInit16(uint16_t init)
{
  for (uint16_t i = 0 ; i < 16 ; ++i)
  {
    uint16_t bit = init & 1;
    if (bit)
      init ^= 0x1021; /* the CRC16 polynomial */
    init >>= 1;

    if (bit)
      init |= 0x8000;
  }

  return init;
}
