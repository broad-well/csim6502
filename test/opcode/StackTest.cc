//
// Created by michael on 5/3/18.
//

#include <gtest/gtest.h>
#include "test/MockRAM.hh"

#include "CPU.hh"
#include "opcode/Stack.hh"

static MockRAM ram{0x1d, 0x4a, 0x1d, 0xbf, 0x57, 0xaf, 0xf4, 0x01};
static CPU cpu(&ram);

TEST(StackOpcode, PHA) {
  cpu.ac = 0xce;

  opcode::PHA(cpu);

  ASSERT_EQ(cpu.PullByteFromStack(), 0xce);
}

TEST(StackOpcode, PLA) {
  cpu.PushByteToStack(0x7d);

  opcode::PLA(cpu);

  ASSERT_EQ(cpu.ac, 0x7d);
  ASSERT_ANY_THROW(cpu.PullByteFromStack());
}

TEST(StackOpcode, PHP) {
  opcode::PHP(cpu);

  ASSERT_EQ(cpu.PullByteFromStack(), cpu.status.ToByte());
  ASSERT_ANY_THROW(cpu.PullByteFromStack());
}

TEST(StackOpcode, PLP) {
  cpu.status.Clear();
  cpu.PushByteToStack(0x49);

  opcode::PLP(cpu);

  ASSERT_EQ(cpu.status.ToByte(), 0x49);
  cpu.status.Clear();
}
