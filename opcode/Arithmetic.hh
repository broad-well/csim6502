//
// Created by Michael Peng on 4/25/18.
//

#ifndef CSIM6502_ARITHMETIC_HH
#define CSIM6502_ARITHMETIC_HH

#include "../CPU.hh"
#include "Executor.hh"
#include "AddressingModes.hh"

OPCODE_SET {

MONADIC_OPCODE(ADC);
MONADIC_OPCODE(SBC);

MONADIC_OPCODE(INC);
MONADIC_OPCODE(DEC);

NILADIC_OPCODE(INX);
NILADIC_OPCODE(INY);
NILADIC_OPCODE(DEX);
NILADIC_OPCODE(DEY);

MONADIC_OPCODE(AND);
MONADIC_OPCODE(EOR);
MONADIC_OPCODE(ORA);
MONADIC_OPCODE(BIT);

MONADIC_OPCODE(ASL);
MONADIC_OPCODE(LSR);
MONADIC_OPCODE(ROL);
MONADIC_OPCODE(ROR);

MONADIC_OPCODE(CMP);
MONADIC_OPCODE(CPX);
MONADIC_OPCODE(CPY);

}
#endif //CSIM6502_ARITHMETIC_HH
