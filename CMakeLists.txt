cmake_minimum_required(VERSION 2.8)
include(CMakeCommon.txt)

project(csim6502)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Werror -pedantic -Wall -Wextra")

add_library(csim6502_base CPU.cc CPU.hh RAM.cc RAM.hh Util.hh)
#add_executable(csim6502)

add_subdirectory(test/)
add_subdirectory(opcode/)

target_link_libraries(csim6502_base csim6502_opcode)