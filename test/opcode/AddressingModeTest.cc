//
// Created by Michael Peng on 5/2/18.
//

#include "opcode/AddressingModes.hh"
#include "CPU.hh"
#include "../MockRAM.hh"
#include <exception>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;
using namespace address;

static MockRAM ram {
  0x41, 0x13, 0x53, 0xfc, 0xc2, 0x00, 0x9f, 0x3b
};
static CPU cpu(&ram);

TEST(AddressingMode, Immediate) {
  ASSERT_THROW(Immediate.Write(cpu, 0x00), std::bad_function_call);

  ASSERT_EQ(Immediate.Read(cpu), ram.Read(0x00));
  ASSERT_EQ(Immediate.Read(cpu), ram.Read(0x01));
  cpu.pc = 0x00;
}

TEST(AddressingMode, Accumulator) {
  cpu.ac = 0x3d;
  ASSERT_EQ(Accumulator.Read(cpu), 0x3d);

  Accumulator.Write(cpu, 0xda);
  ASSERT_EQ(cpu.ac, 0xda);
}

TEST(AddressingMode, Absolute) {
  ram.Write(0x1341, 0xcc);
  ram.Write(0xfc53, 0xff);
  ram.Write(0x00c2, 0xea);

  ASSERT_EQ(Absolute.Read(cpu), 0xcc);
  ASSERT_EQ(Absolute.Read(cpu), 0xff);
  ASSERT_EQ(Absolute.Read(cpu), 0xea);

  cpu.pc = 0x00;

  Absolute.Write(cpu, 0xda);
  ASSERT_EQ(ram.Read(0x1341), 0xda);
  Absolute.Write(cpu, 0xac);
  ASSERT_EQ(ram.Read(0xfc53), 0xac);

  cpu.pc = 0x00;
}

TEST(AddressingMode, ZeroPage) {
  ram.Write(0x41, 0x1d);
  ASSERT_EQ(ZeroPage.Read(cpu), 0x1d);
  ram.Write(0x13, 0xfc);
  ASSERT_EQ(ZeroPage.Read(cpu), 0xfc);

  cpu.pc = 0x00;

  ZeroPage.Write(cpu, 0x1a);
  ASSERT_EQ(ram.Read(0x41), 0x1a);
  ZeroPage.Write(cpu, 0xa2);
  ASSERT_EQ(ram.Read(0x13), 0xa2);

  cpu.pc = 0x00;
}

TEST(AddressingMode, Indirect) {
  ram.Write(0x1341, 0x06);
  ASSERT_EQ(Indirect.Read(cpu), 0x9f);
  ram.Write(0xfc53, 0x00);
  ASSERT_EQ(Indirect.Read(cpu), 0x41);

  cpu.pc = 0x00;

  ram.Write(0x1341, 0x55);
  Indirect.Write(cpu, 0x13);
  ASSERT_EQ(ram.Read(0x55), 0x13);

  ram.Write(0xfc53, 0x56);
  Indirect.Write(cpu, 0x7d);
  ASSERT_EQ(ram.Read(0x56), 0x7d);

  cpu.pc = 0x00;
}

TEST(AddressingMode, AbsoluteIndexed) {
  cpu.x = 0x02;
  ram.Write(0x1343, 0x5c);
  ASSERT_EQ(AbsoluteIndexedX.Read(cpu), 0x5c);
  cpu.y = 0xff;
  ram.Write(0xfd52, 0xec);
  ASSERT_EQ(AbsoluteIndexedY.Read(cpu), 0xec);

  cpu.pc = 0x00;

  cpu.x = 0x08;
  AbsoluteIndexedX.Write(cpu, 0x5e);
  ASSERT_EQ(ram.Read(0x1349), 0x5e);
  cpu.y = 0x09;
  AbsoluteIndexedY.Write(cpu, 0x1a);
  ASSERT_EQ(ram.Read(0xfc5c), 0x1a);

  cpu.pc = 0x00;
  cpu.x = 0x00;
  cpu.y = 0x00;
}

TEST(AddressingMode, ZeroPageIndexed) {
  cpu.x = 0x02;
  ram.Write(0x43, 0xda);
  ASSERT_EQ(ZeroPageIndexedX.Read(cpu), 0xda);
  cpu.y = 0x05;
  ram.Write(0x18, 0xcf);
  ASSERT_EQ(ZeroPageIndexedY.Read(cpu), 0xcf);

  // Well known bug: zero page indexed will not cross the page boundary when PC+X or PC+Y overflows
  cpu.x = 0xff;
  ZeroPageIndexedX.Write(cpu, 0xae);
  ASSERT_EQ(ram.Read(0x52), 0xae);
  cpu.y = 0xf9;
  ZeroPageIndexedY.Write(cpu, 0xd9);
  ASSERT_EQ(ram.Read(0xf5), 0xd9);

  cpu.pc = 0x00;
  cpu.x = 0x00;
  cpu.y = 0x00;
}

TEST(AddressingMode, XIndexedIndirect) {
  cpu.x = 0x03;
  ram.WriteWord(0x44, 0x2dac);
  ram.Write(0x2dac, 0xfd);
  ASSERT_EQ(XIndexedIndirect.Read(cpu), 0xfd);
  ram.WriteWord(0x16, 0xff3a);
  ram.Write(0xff3a, 0xe2);
  ASSERT_EQ(XIndexedIndirect.Read(cpu), 0xe2);

  cpu.pc = 0x00;
  cpu.x = 0x1d;
  ram.WriteWord(word {0x41 + 0x1d}, 0x1441);
  XIndexedIndirect.Write(cpu, 0xd8);
  ASSERT_EQ(ram.Read(0x1441), 0xd8);

  cpu.pc = 0x4f;
  cpu.x = 0xff;
  ram.Write(0x4f, 0x00);
  ram.WriteWord(0xff, 0xac23); // Across page boundaries
  XIndexedIndirect.Write(cpu, 0x89);
  ASSERT_EQ(ram.Read(0xac23), 0x89);

  cpu.pc = 0x00;
  cpu.x = 0x00;
}

TEST(AddressingMode, IndirectYIndexed) {
  ram.WriteWord(0x41, 0x13fa);
  ram.Write(0x13fc, 0xdc);
  cpu.y = 0x02;
  ASSERT_EQ(IndirectYIndexed.Read(cpu), 0xdc);

  ++cpu.y;
  ram.WriteWord(0x13, 0x614f);
  IndirectYIndexed.Write(cpu, 0x69);
  ASSERT_EQ(ram.Read(word {0x614f + 0x03}), 0x69);

  cpu.pc = 0x00;
  cpu.y = 0x00;
}