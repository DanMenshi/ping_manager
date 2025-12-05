# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/start_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/start_autogen.dir/ParseCache.txt"
  "start_autogen"
  )
endif()
