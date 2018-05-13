//
// Created by michael on 5/4/18.
//

#include <gtest/gtest.h>
#include "CPU.hh"
#include "MockAddressingMode.hh"
#include "test/MockRAM.hh"

#include "opcode/Arithmetic.hh"

static MockRAM ram{0x1d, 0x42, 0xaf, 0x4b, 0xc6, 0x92, 0x17, 0xa4};
static CPU cpu(&ram);

#define ASSERT_OPERATION(initial_ac, initial_carry, code, result_ac) \
  do {                                                               \
    SetMockAddressValue(0x66);                                       \
    cpu.Reset();                                                     \
    cpu.ac = initial_ac;                                             \
    cpu.status.carry = initial_carry;                                \
                                                                     \
    opcode::code(cpu, kMockAddressMode);                             \
                                                                     \
    ASSERT_EQ(cpu.ac, result_ac);                                    \
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

TEST(ArithmeticOpcode, INC) {
  cpu.Reset();
  SetMockAddressValue(0x7f);

  opcode::INC(cpu, kMockAddressMode);

  ASSERT_EQ(MockAddressValue(), 0x80);
  ASSERT_TRUE(cpu.status.negative_result);
}

TEST(ArithmeticOpcode, DEC) {
  cpu.Reset();
  SetMockAddressValue(0xf2);

  opcode::DEC(cpu, kMockAddressMode);

  ASSERT_EQ(MockAddressValue(), 0xf1);
  ASSERT_TRUE(cpu.status.negative_result);
}

TEST(ArithmeticOpcode, DEX_DEY) {
  cpu.Reset();
  cpu.x = 0x9f;

  opcode::DEX(cpu);

  ASSERT_EQ(cpu.x, 0x9e);
  ASSERT_TRUE(cpu.status.negative_result);

  cpu.y = 0x01;

  opcode::DEY(cpu);

  ASSERT_EQ(cpu.y, 0x00);
  ASSERT_TRUE(cpu.status.zero_result);
}

TEST(ArithmeticOpcode, INX_INY) {
  cpu.Reset();
  cpu.x = 0x7f;

  opcode::INX(cpu);

  ASSERT_EQ(cpu.x, 0x80);
  ASSERT_TRUE(cpu.status.negative_result);
  cpu.y = 0xff;

  opcode::INY(cpu);

  ASSERT_EQ(cpu.y, 0x00);
  ASSERT_TRUE(cpu.status.zero_result);
}

#define ASSERT_OPCODE_SETS_ACCUMULATOR(code, prev_ac, result) \
  do {                                                        \
    SetMockAddressValue(0x66);                                \
    cpu.Reset();                                              \
    cpu.ac = prev_ac;                                         \
                                                              \
    opcode::code(cpu, kMockAddressMode);                      \
                                                              \
    ASSERT_EQ(cpu.ac, (result));                              \
  } while (0)

TEST(ArithmeticOpcode, AND) {
  ASSERT_OPCODE_SETS_ACCUMULATOR(AND, 0x24U, 0x24U & 0x66U);
  ASSERT_OPCODE_SETS_ACCUMULATOR(AND, 0x80U, 0x0);
  ASSERT_TRUE(cpu.status.zero_result);
}
TEST(ArithmeticOpcode, EOR) {
  ASSERT_OPCODE_SETS_ACCUMULATOR(EOR, 0x8eU, 0x8eU ^ 0x66U);
  ASSERT_OPCODE_SETS_ACCUMULATOR(EOR, 0xdaU, 0x66U ^ 0xdaU);
  ASSERT_TRUE(cpu.status.negative_result);
}
TEST(ArithmeticOpcode, ORA) {
  ASSERT_OPCODE_SETS_ACCUMULATOR(ORA, 0x93U, 0x93U | 0x66U);
  ASSERT_TRUE(cpu.status.negative_result);
  ASSERT_OPCODE_SETS_ACCUMULATOR(ORA, 0xedU, 0xedU | 0x66U);
  ASSERT_TRUE(cpu.status.negative_result);
}

TEST(ArithmeticOpcode, BIT) {
  cpu.Reset();
  cpu.ac = 0x5f;

  SetMockAddressValue(0b10010100U);
  opcode::BIT(cpu, kMockAddressMode);
  ASSERT_TRUE(cpu.status.negative_result);
  ASSERT_FALSE(cpu.status.overflow);
  ASSERT_FALSE(cpu.status.zero_result);

  SetMockAddressValue(0b01001001U);
  opcode::BIT(cpu, kMockAddressMode);
  ASSERT_FALSE(cpu.status.negative_result);
  ASSERT_TRUE(cpu.status.overflow);
  ASSERT_FALSE(cpu.status.zero_result);

  SetMockAddressValue(0x0);
  opcode::BIT(cpu, kMockAddressMode);
  ASSERT_FALSE(cpu.status.negative_result);
  ASSERT_FALSE(cpu.status.overflow);
  ASSERT_TRUE(cpu.status.zero_result);
}

TEST(ArithmeticOpcode, ASL) {
  cpu.Reset();
  SetMockAddressValue(0b10010100U);

  opcode::ASL(cpu, kMockAddressMode);

  ASSERT_EQ(MockAddressValue(), 0b00101000U);
  ASSERT_TRUE(cpu.status.carry);
  ASSERT_FALSE(cpu.status.negative_result);

  cpu.Reset();
  cpu.ac = 0b01101101;

  opcode::ASL(cpu, address::Accum);

  ASSERT_EQ(cpu.ac, 0b11011010);
  ASSERT_FALSE(cpu.status.carry);
  ASSERT_TRUE(cpu.status.negative_result);
}

TEST(ArithmeticOpcode, LSR) {
  cpu.Reset();
  SetMockAddressValue(0b11100101U);

  opcode::LSR(cpu, kMockAddressMode);

  ASSERT_EQ(MockAddressValue(), 0b01110010U);
  ASSERT_TRUE(cpu.status.carry);

  cpu.Reset();
  cpu.ac = 0b00101110;

  opcode::LSR(cpu, address::Accum);

  ASSERT_EQ(cpu.ac, 0b00010111);
  ASSERT_FALSE(cpu.status.carry);
}

TEST(ArithmeticOpcode, ROL) {
  cpu.Reset();
  cpu.status.carry = true;
  SetMockAddressValue(0b01001110U);

  opcode::ROL(cpu, kMockAddressMode);

  ASSERT_EQ(MockAddressValue(), 0b10011101U);
  ASSERT_TRUE(cpu.status.negative_result);
  ASSERT_FALSE(cpu.status.carry);

  cpu.Reset();
  cpu.ac = 0b11001100;

  opcode::ROL(cpu, address::Accum);

  ASSERT_EQ(cpu.ac, 0b10011000);
  ASSERT_TRUE(cpu.status.carry);
}

TEST(ArithmeticOpcode, ROR) {
  cpu.Reset();
  cpu.status.carry = true;
  SetMockAddressValue(0b11010101);

  opcode::ROR(cpu, kMockAddressMode);

  ASSERT_EQ(MockAddressValue(), 0b11101010);
  ASSERT_TRUE(cpu.status.carry);
  ASSERT_TRUE(cpu.status.negative_result);

  cpu.Reset();
  cpu.ac = 0b00110100;

  opcode::ROR(cpu, address::Accum);

  ASSERT_EQ(cpu.ac, 0b00011010);
  ASSERT_FALSE(cpu.status.carry);
}

#define GIVEN_REG_MEM_VALUES_WHEN_CODE_CALLED(reg_name, reg_value, mem_value, \
                                              code)                           \
  cpu.Reset();                                                                \
  SetMockAddressValue((mem_value));                                           \
  cpu.reg_name = (reg_value);                                                 \
                                                                              \
  opcode::code(cpu, kMockAddressMode);

#define ASSERT_FLAGS_FOR_GREATER_REGISTER_AFTER_OPCODE(reg_name, reg_value,   \
                                                       mem_value, code)       \
  GIVEN_REG_MEM_VALUES_WHEN_CODE_CALLED(reg_name, reg_value, mem_value, code) \
  ASSERT_FALSE(cpu.status.zero_result);                                       \
  ASSERT_FALSE(cpu.status.negative_result);                                   \
  ASSERT_TRUE(cpu.status.carry);

#define ASSERT_FLAGS_FOR_EQUALITY_AFTER_OPCODE(reg_name, reg_value, mem_value, \
                                               code)                           \
  GIVEN_REG_MEM_VALUES_WHEN_CODE_CALLED(reg_name, reg_value, mem_value, code)  \
  ASSERT_TRUE(cpu.status.zero_result);                                         \
  ASSERT_FALSE(cpu.status.negative_result);                                    \
  ASSERT_TRUE(cpu.status.carry);

#define ASSERT_FLAGS_FOR_LOWER_REGISTER_AFTER_OPCODE(reg_name, reg_value,     \
                                                     mem_value, code)         \
  GIVEN_REG_MEM_VALUES_WHEN_CODE_CALLED(reg_name, reg_value, mem_value, code) \
  ASSERT_FALSE(cpu.status.zero_result);                                       \
  ASSERT_TRUE(cpu.status.negative_result);                                    \
  ASSERT_FALSE(cpu.status.carry);

#define TEST_FOR_ALL_CONDITIONS_WITH_OPCODE_COMPARING_BETWEEN_MEMORY_AND(     \
    code, reg_name)                                                           \
  TEST(ArithmeticOpcode, _##code##_Greater_Register) {                        \
    ASSERT_FLAGS_FOR_GREATER_REGISTER_AFTER_OPCODE(reg_name, 0x81, 0x5F,      \
                                                   code);                     \
  }                                                                           \
  TEST(ArithmeticOpcode, _##code##_Equal) {                                   \
    ASSERT_FLAGS_FOR_EQUALITY_AFTER_OPCODE(reg_name, 0x91, 0x91, code);       \
  }                                                                           \
  TEST(ArithmeticOpcode, _##code##_Less_Register) {                           \
    ASSERT_FLAGS_FOR_LOWER_REGISTER_AFTER_OPCODE(reg_name, 0x52, 0x61, code); \
  }

TEST_FOR_ALL_CONDITIONS_WITH_OPCODE_COMPARING_BETWEEN_MEMORY_AND(CMP, ac)
TEST_FOR_ALL_CONDITIONS_WITH_OPCODE_COMPARING_BETWEEN_MEMORY_AND(CPX, x)
TEST_FOR_ALL_CONDITIONS_WITH_OPCODE_COMPARING_BETWEEN_MEMORY_AND(CPY, y)
