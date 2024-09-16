#include <stdint.h>
#include <stdbool.h>

#include "crc-lib.h"

const uint8_t data[1024] = { 0 };

int main(void)
{
  uint32_t init = 0x12345678;
  code_ptr p = data;
  uint32_t calc = FastCrc32(init, p, sizeof(data));

  return calc;
}
