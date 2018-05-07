//
// Created by Michael Peng on 4/25/18.
//

#include "Jump.hh"

#define OPCODE_BRANCHES_IF(code, condition) NILADIC_OPCODE(code) { \
  if (condition) \
    cpu.JumpRelative(cpu.NextCodeByte()); \
}
#define OPCODE_BRANCHES_IF_FLAG_SET(code, flag) OPCODE_BRANCHES_IF(code, cpu.status.flag)
#define OPCODE_BRANCHES_IF_FLAG_CLEAR(code, flag) OPCODE_BRANCHES_IF(code, !cpu.status.flag)

OPCODE_SET {

OPCODE_BRANCHES_IF_FLAG_SET(BCS, carry)
OPCODE_BRANCHES_IF_FLAG_CLEAR(BCC, carry)

OPCODE_BRANCHES_IF_FLAG_SET(BEQ, zero_result)
OPCODE_BRANCHES_IF_FLAG_CLEAR(BNE, zero_result)

OPCODE_BRANCHES_IF_FLAG_SET(BMI, negative_result)
OPCODE_BRANCHES_IF_FLAG_CLEAR(BPL, negative_result)

OPCODE_BRANCHES_IF_FLAG_SET(BVS, overflow)
OPCODE_BRANCHES_IF_FLAG_CLEAR(BVC, overflow)

NILADIC_OPCODE(JMP_Abs) {
  cpu.pc = cpu.NextOperandWord();
}
NILADIC_OPCODE(JMP_Ind) {
  cpu.pc = cpu.memory->ReadWord(cpu.NextOperandWord());
}

NILADIC_OPCODE(JSR) {
  cpu.PushWordToStack(static_cast<word>(cpu.pc + 1));
  cpu.pc = cpu.NextOperandWord();
}
NILADIC_OPCODE(RTS) {
  cpu.pc = static_cast<word>(cpu.PullWordFromStack() + 1);
}

NILADIC_OPCODE(RTI) {
  cpu.status.LoadFromByte(cpu.PullByteFromStack());
  cpu.pc = cpu.PullWordFromStack();
}

}