cmake_minimum_required(VERSION 2.8)
include(../CMakeCommon.txt)

add_library(csim6502_opcode Bitwise.cc Bitwise.hh Arithmetic.cc Arithmetic.hh Jump.cc Jump.hh Branch.cc Branch.hh Storage.cc Storage.hh Stack.cc Stack.hh System.cc System.hh Decoder.cc Decoder.hh)