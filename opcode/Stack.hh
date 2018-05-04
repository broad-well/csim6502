//
// Created by Michael Peng on 4/25/18.
//

#ifndef CSIM6502_STACK_HH
#define CSIM6502_STACK_HH

#include "../CPU.hh"
#include "Executor.hh"

namespace opcode {

NILADIC_OPCODE(PHA);
NILADIC_OPCODE(PLA);
NILADIC_OPCODE(PHP);
NILADIC_OPCODE(PLP);

}

#endif //CSIM6502_STACK_HH
