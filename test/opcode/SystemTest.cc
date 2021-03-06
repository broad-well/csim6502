//
// Created by Michael Peng on 5/3/18.
//

#include "../MockRAM.hh"
#include "opcode/System.hh"

#include <gtest/gtest.h>

static MockRAM ram{0xfa, 0x1d, 0xad, 0x14, 0xca, 0xb6, 0xbf, 0x3a};
static CPU cpu(&ram);

TEST(SystemOpcode, BRK) {
  ram.WriteWord(0xfffe, 0xface);
  opcode::BRK(cpu);
  ASSERT_EQ(cpu.pc, 0xface);
  ASSERT_EQ(cpu.PullByteFromStack(), cpu.status.ToByte() | 0x10U);
  ASSERT_EQ(cpu.PullWordFromStack(), 0x0001);
}

TEST(SystemOpcode, Illegal) {
  ASSERT_THROW(opcode::Illegal(cpu), std::invalid_argument);
}
