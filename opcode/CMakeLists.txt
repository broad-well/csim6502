cmake_minimum_required(VERSION 2.8)
include(../CMakeCommon.txt)

include_directories(../)
add_library(csim6502_opcode
        Arithmetic.cc
        Jump.cc
        Storage.cc
        Stack.cc
        System.cc
        Decoder.cc
        AddressingModes.cc)
