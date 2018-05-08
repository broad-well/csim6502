cmake_minimum_required(VERSION 2.8)
include(../CMakeCommon.txt)

include_directories(../)
add_library(csim6502_opcode
        Arithmetic.cc Arithmetic.hh
        Jump.cc Jump.hh
        Storage.cc Storage.hh
        Stack.cc Stack.hh
        System.cc System.hh
        Decoder.cc Decoder.hh
        Executor.hh AddressingModes.hh AddressingModes.cc)
