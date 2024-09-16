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
 * The Fast version is really just a lookup table built using the Small version.
 *
 * Example of usage:
 *
 * The table needs 256 bytes, this can be gathered in many ways, stack
 * allocated, malloc, static memory, etc.
 * The table is built by calling MirrorFast and then the reflected/mirrored
 * byte can be looked up by indexing the table with the byte.
 *
 * Before the first call to the crc function
 *
 * uint8_t * table = ...; // get memory somehow
 * MirrorFast(table);
 *
 * Inside the crc function:
 *
 * uint8_t byte = *(p++);
 * byte = table[byte];
 *
 * The final result is still mirrored using MirrorSmall
 *
 ************************************************* */

#include <stdint.h>
#include <stdlib.h>

extern uint32_t MirrorSmall(uint32_t, uint8_t);

void MirrorFast(uint8_t * table)
{
  for (uint32_t i = 0 ; i < 256 ; ++i)
  {
    table[i] = MirrorSmall(i, 1);
  }
}
