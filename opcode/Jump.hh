//
// Created by Michael Peng on 4/25/18.
//

#ifndef CSIM6502_JUMP_HH
#define CSIM6502_JUMP_HH

#include <CPU.hh>
#include "Executor.hh"
#include "AddressingModes.hh"

OPCODE_SET {

  // Relative addressing mode uses cpu.JumpRelative
  NILADIC_OPCODE(BCC);
  NILADIC_OPCODE(BCS);
  NILADIC_OPCODE(BEQ);
  NILADIC_OPCODE(BMI);
  NILADIC_OPCODE(BNE);
  NILADIC_OPCODE(BPL);
  NILADIC_OPCODE(BVC);
  NILADIC_OPCODE(BVS);

  // JMP and JSR are special. They don't care about the memory to which the address points, it works with the address (operand) itself
  NILADIC_OPCODE(JMP_Absolute);
  NILADIC_OPCODE(JMP_Indirect);
  NILADIC_OPCODE(JSR);

  NILADIC_OPCODE(RTI);
  NILADIC_OPCODE(RTS);

}

#endif //CSIM6502_JUMP_HH
