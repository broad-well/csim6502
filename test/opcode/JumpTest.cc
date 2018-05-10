//
// Created by michael on 5/4/18.
//

#include <gtest/gtest.h>
#include "MockAddressingMode.hh"
#include "test/MockRAM.hh"

#include "opcode/Jump.hh"

static MockRAM ram {
  0x02, 0x00, 0xda, 0x2c, 0x63, 0x8b, 0xaf, 0xf5
};
static CPU cpu(&ram);

static constexpr word kStartPc(0x2121);

#define ASSERT_OPCODE_BRANCHES_ON_FLAG_BEING(code, flag, branch_condition) TEST(JumpOpcode, code) { \
  cpu.Reset(); \
  cpu.pc = kStartPc; \
  ram.Write(kStartPc, 0xa4); \
\
  cpu.status.flag = branch_condition; \
  opcode::code(cpu); \
  ASSERT_EQ(cpu.pc, kStartPc - 91); \
\
  cpu.pc = kStartPc; \
  cpu.status.flag = !(branch_condition); \
  opcode::code(cpu); \
  ASSERT_EQ(cpu.pc, kStartPc); \
}

ASSERT_OPCODE_BRANCHES_ON_FLAG_BEING(BCS, carry, true)
ASSERT_OPCODE_BRANCHES_ON_FLAG_BEING(BCC, carry, false)

ASSERT_OPCODE_BRANCHES_ON_FLAG_BEING(BEQ, zero_result, true)
ASSERT_OPCODE_BRANCHES_ON_FLAG_BEING(BNE, zero_result, false)

ASSERT_OPCODE_BRANCHES_ON_FLAG_BEING(BMI, negative_result, true)
ASSERT_OPCODE_BRANCHES_ON_FLAG_BEING(BPL, negative_result, false)

ASSERT_OPCODE_BRANCHES_ON_FLAG_BEING(BVS, overflow, true)
ASSERT_OPCODE_BRANCHES_ON_FLAG_BEING(BVC, overflow, false)

TEST(JumpOpcode, JMP_Abs) {
  cpu.Reset();
  opcode::JMP_Abs(cpu);
  ASSERT_EQ(cpu.pc, 0x0002);
}

TEST(JumpOpcode, JMP_Ind) {
  cpu.Reset();
  opcode::JMP_Ind(cpu);
  ASSERT_EQ(cpu.pc, 0x2cda);
}

TEST(JumpOpcode, JSR) {
  cpu.Reset();
  opcode::JSR(cpu);
  ASSERT_EQ(cpu.pc, 0x0002);
  ASSERT_EQ(cpu.PullWordFromStack(), 0x0001);

  opcode::JSR(cpu);
  ASSERT_EQ(cpu.pc, 0x2cda);
  ASSERT_EQ(cpu.PullWordFromStack(), 0x0003);
}

TEST(JumpOpcode, RTS) {
  cpu.Reset();
  cpu.PushWordToStack(0x4641);

  opcode::RTS(cpu);

  ASSERT_EQ(cpu.pc, 0x4642);
}

TEST(JumpOpcode, RTI) {
  cpu.Reset();
  cpu.PushWordToStack(0x5858);
  cpu.PushByteToStack(0b01001010);

  opcode::RTI(cpu);

  ASSERT_EQ(cpu.pc, 0x5858);
  ASSERT_EQ(cpu.status.ToByte(), 0b01001010);
}
