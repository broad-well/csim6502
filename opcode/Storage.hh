//
// Created by Michael Peng on 4/25/18.
//

#ifndef CSIM6502_STORAGE_HH
#define CSIM6502_STORAGE_HH

#include "../CPU.hh"
#include "AddressingModes.hh"
#include "Executor.hh"

OPCODE_SET {

NILADIC_OPCODE(CLC);
NILADIC_OPCODE(SEC);
NILADIC_OPCODE(CLI);
NILADIC_OPCODE(SEI);
NILADIC_OPCODE(CLV);
NILADIC_OPCODE(CLD);
NILADIC_OPCODE(SED);

MONADIC_OPCODE(LDA);
MONADIC_OPCODE(LDX);
MONADIC_OPCODE(LDY);
MONADIC_OPCODE(STA);
MONADIC_OPCODE(STX);
MONADIC_OPCODE(STY);

NILADIC_OPCODE(TAX);
NILADIC_OPCODE(TAY);
NILADIC_OPCODE(TSX);
NILADIC_OPCODE(TXA);
NILADIC_OPCODE(TXS);
NILADIC_OPCODE(TYA);

}

#endif //CSIM6502_STORAGE_HH
