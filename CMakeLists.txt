cmake_minimum_required(VERSION 3.5)
include(CMakeCommon.txt)

project(csim6502 CXX)

add_library(csim6502_base CPU.cc CPU.hh RAM.cc RAM.hh Util.hh types.hh)
#add_executable(csim6502)

add_subdirectory(test/)
add_subdirectory(opcode/)

target_link_libraries(csim6502_base csim6502_opcode)