//
// Created by Michael Peng on 4/25/18.
//

#ifndef CSIM6502_SYSTEM_HH
#define CSIM6502_SYSTEM_HH

#include "../CPU.hh"
#include "Executor.hh"

OPCODE_SET {

NILADIC_OPCODE(NOP);
NILADIC_OPCODE(BRK);
NILADIC_OPCODE(DMP);
NILADIC_OPCODE(PTA);

[[noreturn]]
NILADIC_OPCODE(Illegal);

[[noreturn]]
NILADIC_OPCODE(EXIT);

}

#endif //CSIM6502_SYSTEM_HH
