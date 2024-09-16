add_library(crc)

target_sources(crc PRIVATE
  BalancedCrc16.c
  BalancedCrc32.c
  FastCrc16.c
  FastCrc32.c
  MirrorBalanced.c
  MirrorFast.c
  MirrorSmall.c
  slow_crc16.c
  SmallCrc16.c
  SmallCrc32.c
)

target_include_directories(crc PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)