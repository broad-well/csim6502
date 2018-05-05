//
// Created by Michael Peng on 4/25/18.
//

#include "Decoder.hh"

using namespace opcode;
using namespace address;

#define ADDR(code, mode) std::bind(code, std::placeholders::_1, mode)

/*
static const OpcodeExecutor kInstructionTable[] {
    // 0            1            2            3            4            5            6            7            8            9            A
    BRK
};*/