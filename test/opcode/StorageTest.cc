//
// Created by Michael Peng on 5/4/18.
//

#include <gtest/gtest.h>
#include "test/MockRAM.hh"
#include "MockAddressingMode.hh"
#include "CPU.hh"

#include "opcode/Storage.hh"

static MockRAM ram {
  0x14, 0xfa, 0xbd, 0xdc
};
static CPU cpu(&ram);

#define ASSERT_OPCODE_MAKES(code, flag, condition) TEST(StorageOpcode, code) { \
  cpu.status.flag = !(condition); \
  opcode::code(cpu); \
  ASSERT_EQ(cpu.status.flag, (condition)); \
}
#define ASSERT_OPCODE_LOADS_MEMORY_TO(code, reg) TEST(StorageOpcode, code) { \
  cpu.reg = 0x02; \
  SetMockAddressValue(0x9a); \
\
  opcode::code(cpu, kMockAddressMode); \
\
  ASSERT_EQ(cpu.reg, 0x9a); \
\
  ASSERT_TRUE(cpu.status.negative_result); \
  cpu.status.negative_result = false; \
}
#define ASSERT_OPCODE_STORES_TO_MEMORY_FROM(code, reg) TEST(StorageOpcode, code) { \
  SetMockAddressValue(0xf2); \
  cpu.Reset(); \
  cpu.reg = 0x2d; \
\
  opcode::code(cpu, kMockAddressMode); \
\
  ASSERT_EQ(MockAddressValue(), 0x2d); \
}
#define ASSERT_OPCODE_TRANFERS(code, src, dest) TEST(StorageOpcode, code) { \
  cpu.Reset(); \
  cpu.src = 0x9a; \
\
  opcode::code(cpu); \
\
  ASSERT_EQ(cpu.dest, cpu.src); \
  ASSERT_TRUE(cpu.status.negative_result); \
}

ASSERT_OPCODE_MAKES(CLC, carry, false)
ASSERT_OPCODE_MAKES(SEC, carry, true)
ASSERT_OPCODE_MAKES(CLI, irq_disable, false)
ASSERT_OPCODE_MAKES(SEI, irq_disable, true)
ASSERT_OPCODE_MAKES(CLV, overflow, false)
ASSERT_OPCODE_MAKES(CLD, decimal_mode, false)
ASSERT_OPCODE_MAKES(SED, decimal_mode, true)

ASSERT_OPCODE_LOADS_MEMORY_TO(LDA, ac)
ASSERT_OPCODE_LOADS_MEMORY_TO(LDX, x)
ASSERT_OPCODE_LOADS_MEMORY_TO(LDY, y)

ASSERT_OPCODE_STORES_TO_MEMORY_FROM(STA, ac)
ASSERT_OPCODE_STORES_TO_MEMORY_FROM(STX, x)
ASSERT_OPCODE_STORES_TO_MEMORY_FROM(STY, y)

ASSERT_OPCODE_TRANFERS(TAX, ac, x)
ASSERT_OPCODE_TRANFERS(TAY, ac, y)
ASSERT_OPCODE_TRANFERS(TSX, sp, x)
ASSERT_OPCODE_TRANFERS(TXA, x, ac)
ASSERT_OPCODE_TRANFERS(TXS, x, sp)
ASSERT_OPCODE_TRANFERS(TYA, y, ac)
