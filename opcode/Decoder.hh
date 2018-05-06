//
// Created by Michael Peng on 4/25/18.
//

#ifndef CSIM6502_DECODER_HH
#define CSIM6502_DECODER_HH

#include <cstdint>
#include "../types.hh"

#include "System.hh"
#include "Stack.hh"
#include "Storage.hh"
#include "Jump.hh"
#include "Arithmetic.hh"

Executor Decode(byte opcode);

#endif //CSIM6502_DECODER_HH
