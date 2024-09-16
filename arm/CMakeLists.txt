add_executable(application)

target_sources(application PRIVATE
  main.c
)

target_link_libraries(application crc)
