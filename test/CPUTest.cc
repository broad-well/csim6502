//
// Created by michael on 4/26/18.
//

#include <gtest/gtest.h>
#include "CPU.hh"
#include "MockRAM.hh"
#include "Util.hh"

static MockRAM ram{0x13, 0x79, 0xac, 0xde};
static CPU cpu(&ram);

TEST(StatusFlags, ToFromByte) {
  StatusFlags flags{true, false, false, true, false, true, true, false};
  ASSERT_EQ(flags.ToByte(), 0b01101001);

  StatusFlags clone;
  clone.LoadFromByte(flags.ToByte());
  ASSERT_EQ(clone.ToByte(), flags.ToByte());
}

TEST(StatusFlags, ToString) {
  StatusFlags flags;
  flags.LoadFromByte(0b01110001);
  ASSERT_EQ(flags.ToString(), "nV_BdizC");
  flags.LoadFromByte(0b10001110);
  ASSERT_EQ(flags.ToString(), "Nv_bDIZc");
}

TEST(CPU, UpdateFlagsForNegative) {
  cpu.UpdateFlagsFor(0b10001000);

  ASSERT_FALSE(cpu.status.zero_result);
  ASSERT_TRUE(cpu.status.negative_result);
}

TEST(CPU, UpdateFlagsForZero) {
  cpu.UpdateFlagsFor(0);

  ASSERT_TRUE(cpu.status.zero_result);
  ASSERT_FALSE(cpu.status.negative_result);
}

TEST(CPU, UpdateFlagsForPositive) {
  cpu.UpdateFlagsFor(0b00111010);

  ASSERT_FALSE(cpu.status.zero_result);
  ASSERT_FALSE(cpu.status.negative_result);
}

TEST(CPU, JumpRelativeForward) {
  auto prev_pc(cpu.pc);

  cpu.JumpRelative(0b00001101);

  ASSERT_EQ(cpu.pc, prev_pc + 0b00001101);
}

TEST(CPU, JumpRelativeZero) {
  auto prev_pc(cpu.pc);

  cpu.JumpRelative(0);

  ASSERT_EQ(cpu.pc, prev_pc);
}

TEST(CPU, JumpRelativeBackward) {
  cpu.pc = 0x3a3a;

  cpu.JumpRelative(static_cast<signed_byte>(0xe6));

  ASSERT_EQ(cpu.pc, 0x3a3a - 0x1a);
}

TEST(CPU, JumpRelativeOverflow) {
  cpu.pc = 0xf2f2;

  cpu.JumpRelative(0x56);

  ASSERT_EQ(cpu.pc, 0xf348);
}

TEST(CPU, JumpRelativeUnderflow) {
  cpu.pc = 0x0505;

  cpu.JumpRelative(-106);

  ASSERT_EQ(cpu.pc, 0x0505 - 106);
}

TEST(CPU, DumpRegisterInfo) {
  cpu.JumpRelative(static_cast<signed_byte>(0x9e));

  char expected[39];
  sprintf(expected, "X=%02X Y=%02X A=%02X\nSP=%02X PC=%04X\n%s", cpu.x, cpu.y,
          cpu.ac, cpu.sp, cpu.pc, cpu.status.ToString().c_str());

  std::stringstream stream;
  cpu.DumpRegisterInfo(stream);

  ASSERT_EQ(stream.str(), expected);
}

TEST(CPU, IncrementProgramCounterNoOverflow) {
  auto prev_pc(cpu.pc);
  cpu.IncrementProgramCounter();
  ASSERT_EQ(cpu.pc - 1, prev_pc);
}

TEST(CPU, IncrementProgramCounterOverflow) {
  cpu.pc = 0xffff;
  ASSERT_THROW(cpu.IncrementProgramCounter(), std::overflow_error);
}

TEST(CPU, NextCodeByte) {
  cpu.pc = 0x00;
  ASSERT_EQ(cpu.NextCodeByte(), ram.Read(0x00));
  ASSERT_EQ(cpu.NextCodeByte(), ram.Read(0x01));
  cpu.JumpRelative(1);
  ASSERT_EQ(cpu.NextCodeByte(), ram.Read(0x03));
  cpu.JumpRelative(-2);
  ASSERT_EQ(cpu.NextCodeByte(), ram.Read(0x02));
}

TEST(CPU, NextOperandWord) {
  auto expected(bit::AsWord(ram.Read(0x01), ram.Read(0x02)));
  cpu.pc = 0x01;
  ASSERT_EQ(cpu.NextOperandWord(), expected);
}

TEST(CPU, StackPushPull) {
  cpu.PushByteToStack(0x4a);
  cpu.PushWordToStack(0xfb);
  cpu.PushWordToStack(0xf3ca);

  ASSERT_EQ(cpu.PullWordFromStack(), 0xf3ca);
  ASSERT_EQ(cpu.PullWordFromStack(), 0xfb);
  ASSERT_EQ(cpu.PullByteFromStack(), 0x4a);
}

TEST(CPU, StackOverflow) {
  for (size_t i = 0; i < 0xFF; ++i) {
    cpu.PushByteToStack(0x4d);
  }
  ASSERT_THROW(cpu.PushByteToStack(0x2d), std::overflow_error);

  for (size_t i = 0; i < 0xFF; ++i) {
    ASSERT_EQ(cpu.PullByteFromStack(), 0x4d);
  }
}

TEST(CPU, StackUnderflow) {
  ASSERT_THROW(cpu.PullByteFromStack(), std::underflow_error);
}

TEST(CPU, Reset) {
  cpu.pc = 0xDAEB;
  cpu.sp = 0x51;
  cpu.x = 0xAE;
  cpu.y = 0xB8;
  cpu.ac = 0x1D;
  cpu.status.decimal_mode = true;

  cpu.Reset();

  ASSERT_EQ(cpu.pc, 0x0000);
  ASSERT_NE(cpu.sp, 0x51);
  ASSERT_EQ(cpu.x, 0x00);
  ASSERT_EQ(cpu.y, 0x00);
  ASSERT_EQ(cpu.ac, 0x00);
  ASSERT_EQ(cpu.status.ToByte(), 0b00000000);
}
