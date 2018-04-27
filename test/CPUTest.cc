//
// Created by michael on 4/26/18.
//

#include <gtest/gtest.h>
#include "../CPU.hh"
#include "../Util.hh"

HeapRAM ram(0x10000);
CPU cpu(&ram);

TEST(StatusFlags, ToFromByte) {
  StatusFlags flags {
      true, false, false, true, false, true, true, false
  };
  ASSERT_EQ(flags.ToByte(), 0b01101001);

  StatusFlags clone;
  clone.LoadFromByte(flags.ToByte());
  ASSERT_EQ(clone.ToByte(), flags.ToByte());
}

TEST(StatusFlags, ToString) {
  StatusFlags flags;
  flags.LoadFromByte(0b01110001);
  ASSERT_EQ(flags.ToString(), "nV_BdizC");
}

TEST(CPU, MemoryPtr) {
  ASSERT_EQ(cpu.MemoryPtrTo(0x02), ram.PtrTo(0x02));
  ASSERT_EQ(cpu.MemoryPtrTo(0x05, 0x02), ram.PtrTo(0x05, 0x02));
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
  auto prev_pc = bit::AsWord(cpu.pc_low, cpu.pc_high);

  cpu.JumpRelative(0b00001101);

  ASSERT_EQ(bit::AsWord(cpu.pc_low, cpu.pc_high), prev_pc + 0b00001101);
}

TEST(CPU, JumpRelativeZero) {
  auto prev_pc = bit::AsWord(cpu.pc_low, cpu.pc_high);

  cpu.JumpRelative(0);

  ASSERT_EQ(bit::AsWord(cpu.pc_low, cpu.pc_high), prev_pc);
}

TEST(CPU, JumpRelativeBackward) {
  cpu.pc_low = cpu.pc_high = 0x3a;

  cpu.JumpRelative(0xe6);

  ASSERT_EQ(cpu.pc_low, 0x3a - 0x1a);
  ASSERT_EQ(cpu.pc_high, 0x3a);
}

TEST(CPU, JumpRelativeOverflow) {
  cpu.pc_low = cpu.pc_high = 0xf2;

  cpu.JumpRelative(0x56);

  ASSERT_EQ(cpu.pc_low, 0x48);
  ASSERT_EQ(cpu.pc_high, 0xf3);
  ASSERT_EQ(bit::AsWord(cpu.pc_low, cpu.pc_high), 0xf348);
}

TEST(CPU, JumpRelativeUnderflow) {
  cpu.pc_low = cpu.pc_high = 0x05;

  cpu.JumpRelative(0x96); // -106

  ASSERT_EQ(cpu.pc_low, 0x9b);
  ASSERT_EQ(cpu.pc_high, 0x04);
  ASSERT_EQ(bit::AsWord(cpu.pc_low, cpu.pc_high), 0x0505 - 106);
}

TEST(CPU, DumpRegisterInfo) {
  cpu.JumpRelative(0x9e);

  char expected[39];
  sprintf(expected, "X=%02X Y=%02X A=%02X\nSP=%02X PC=%04X\n%s",
      cpu.x, cpu.y, cpu.ac, cpu.sp, bit::AsWord(cpu.pc_low, cpu.pc_high),
          cpu.status.ToString().c_str());

  std::stringstream stream;
  cpu.DumpRegisterInfo(stream);

  ASSERT_EQ(stream.str(), expected);
}