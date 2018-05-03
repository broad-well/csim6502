//
// Created by Michael Peng on 5/2/18.
//

#ifndef CSIM6502_EXECUTOR_HH
#define CSIM6502_EXECUTOR_HH

#include "../types.hh"
#include "../CPU.hh"

#define NILADIC_OPCODE(name) void name(CPU& cpu)
#define EMPTY_OPCODE(name) void name(CPU&) {}
#define DECLARE_MONADIC_OPCODE(name) template<const AddressingMode&> void name(CPU&)
#define DEFINE_MONADIC_OPCODE(name) template<const AddressingMode& operand> void name(CPU& cpu)

#endif //CSIM6502_EXECUTOR_HH
