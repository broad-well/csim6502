//
// Created by Michael Peng on 5/2/18.
//

#ifndef CSIM6502_EXECUTOR_HH
#define CSIM6502_EXECUTOR_HH

#include "../types.hh"

#define OPCODE_SET namespace opcode
#define NILADIC_OPCODE(name) void name(CPU& cpu)
#define STATIC_OPCODE(name) void name(CPU&)
#define MONADIC_OPCODE(name) void name(CPU& cpu, const AddressingMode& mode)

#endif //CSIM6502_EXECUTOR_HH
