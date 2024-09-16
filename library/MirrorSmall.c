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
 * The Small version is a single function that does everything.
 *
 * Example of usage:
 *
 * ... (inside some CRC-function)
 * uint8_t byte = *(p++);
 * ...
 *
 * This will become:
 * ...
 * uint8_t byte = MirrorSmall(*(p++), 1);
 * ...
 *
 * The caller of the CRC also needs to be updated
 *
 * crc = crc16(...);
 *
 * This needs to be updated with:
 *
 * crc = MirrorSmall(crc, 2); (2 if crc16, 4 if crc32) 
 *
 *
 ************************************************* */

#include <stdint.h>
#include <stdlib.h>

uint32_t MirrorSmall(uint32_t orig, uint8_t size)
{
  uint32_t r = 0, limit = 8*size;
  for (uint32_t d = 0 ; d < limit ; d++)
  {
    if (orig & (1 << d))
      r |= ((1 << (limit - 1)) >> d);
  }

  return r;
}
