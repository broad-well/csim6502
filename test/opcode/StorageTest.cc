//
// Created by Michael Peng on 5/4/18.
//

#include <gtest/gtest.h>
#include "test/MockRAM.hh"
#include "CPU.hh"

#include "opcode/Storage.hh"

MockRAM ram {
  0x14, 0xfa, 0xbd, 0xdc
};
CPU cpu(&ram);

#define ASSERT_OPCODE_MAKES(code, flag, condition) TEST(StorageOpcode, code) { \
  cpu.status.flag = !(condition); \
  opcode::code(cpu); \
  ASSERT_EQ(cpu.status.flag, (condition)); \
}

ASSERT_OPCODE_MAKES(CLC, carry, false);
ASSERT_OPCODE_MAKES(SEC, carry, true);
ASSERT_OPCODE_MAKES(CLI, irq_disable, false);
ASSERT_OPCODE_MAKES(SEI, irq_disable, true);
ASSERT_OPCODE_MAKES(CLV, overflow, false);
ASSERT_OPCODE_MAKES(CLD, decimal_mode, false);
ASSERT_OPCODE_MAKES(SED, decimal_mode, true);
