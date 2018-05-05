//
// Created by michael on 5/4/18.
//

#include <gtest/gtest.h>
#include "CPU.hh"
#include "MockAddressingMode.hh"
#include "test/MockRAM.hh"

#include "opcode/Arithmetic.hh"

MockAddressingMode mode(0x66);
MockRAM ram {
  0x1d, 0x42, 0xaf, 0x4b, 0xc6, 0x92, 0x17, 0xa4
};
CPU cpu(&ram);

#define ASSERT_OPERATION(initial_ac, initial_carry, code, result_ac) do { \
  cpu.Reset(); \
  cpu.ac = initial_ac; \
  cpu.status.carry = initial_carry; \
\
  opcode::code(cpu, mode); \
\
  ASSERT_EQ(cpu.ac, result_ac); \
} while (0)

TEST(ArithmeticOpcode, ADC_OverflowNoCarry) {
  ASSERT_OPERATION(0x24, false, ADC, 0x8a);

  ASSERT_FALSE(cpu.status.zero_result);
  ASSERT_FALSE(cpu.status.carry);
  ASSERT_TRUE(cpu.status.overflow);
  ASSERT_TRUE(cpu.status.negative_result);
}

TEST(ArithmeticOpcode, ADC_NoOverflowNoCarry) {
  ASSERT_OPERATION(0x0d, false, ADC, 0x73);

  ASSERT_FALSE(cpu.status.zero_result);
  ASSERT_FALSE(cpu.status.carry);
  ASSERT_FALSE(cpu.status.overflow);
  ASSERT_FALSE(cpu.status.negative_result);
}

TEST(ArithmeticOpcode, ADC_OverflowCarry) {
  ASSERT_OPERATION(0xd2, true, ADC, 0x39);

  ASSERT_FALSE(cpu.status.zero_result);
  ASSERT_TRUE(cpu.status.carry);
  ASSERT_FALSE(cpu.status.overflow);
  ASSERT_FALSE(cpu.status.negative_result);
}

TEST(ArithmeticOpcode, SBC_OverflowCarry) {
  ASSERT_OPERATION(0x92, false, SBC, 0x2b);

  ASSERT_FALSE(cpu.status.zero_result);
  ASSERT_TRUE(cpu.status.carry);
  ASSERT_TRUE(cpu.status.overflow);
  ASSERT_FALSE(cpu.status.negative_result);
}

TEST(ArithmeticOpcode, SBC_NoOverflowNoCarry) {
  ASSERT_OPERATION(0x13, true, SBC, 0xad);

  ASSERT_FALSE(cpu.status.zero_result);
  ASSERT_FALSE(cpu.status.carry);
  ASSERT_FALSE(cpu.status.overflow);
  ASSERT_TRUE(cpu.status.negative_result);
}

TEST(ArithmeticOpcode, SBC_NoOverflowCarry) {
  ASSERT_OPERATION(0xff, false, SBC, 0x98);

  ASSERT_FALSE(cpu.status.zero_result);
  ASSERT_TRUE(cpu.status.carry);
  ASSERT_FALSE(cpu.status.overflow);
  ASSERT_TRUE(cpu.status.negative_result);
}