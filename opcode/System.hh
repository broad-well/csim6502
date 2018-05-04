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
NILADIC_OPCODE(Illegal);

}

#endif //CSIM6502_SYSTEM_HH
