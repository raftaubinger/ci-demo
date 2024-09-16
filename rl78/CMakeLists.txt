add_executable(app-rl78)

target_sources(app-rl78 PRIVATE
  main.c
)

set(TOOLKIT_DIR /opt/iarsystems/bxrl78fs/rl78)

target_link_options(app-rl78 PRIVATE
  "SHELL:
  --config_def _NEAR_HEAP_SIZE=0
  --config_def _FAR_HEAP_SIZE=0
  --config_def _HUGE_HEAP_SIZE=0
  --config_def _STACK_SIZE=128
  --config_def _NEAR_CONST_LOCATION_START=0x2000
  --config_def _NEAR_CONST_LOCATION_SIZE=0xC000"
  --define_symbol _NEAR_CONST_LOCATION=0
  --config ${TOOLKIT_DIR}/config/lnkrl78_s3.icf
  --debug_lib
)

target_link_libraries(app-rl78 crc)
