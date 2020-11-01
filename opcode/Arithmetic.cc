//
// Created by Michael Peng on 4/25/18.
//

#include "Arithmetic.hh"

#define IS_POSITIVE(n) ((n) >> 7U == 0)

// http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
OPCODE_SET {
  MONADIC_OPCODE(ADC) {
    auto prev_ac(cpu.ac);
    auto operand(mode.Read(cpu));

    cpu.ac = cpu.ac + operand + cpu.status.carry;
    cpu.UpdateFlagsFor(cpu.ac);

    cpu.status.carry = (cpu.ac - cpu.status.carry) < prev_ac;
    cpu.status.overflow = IS_POSITIVE(prev_ac) == IS_POSITIVE(operand) &&
                          IS_POSITIVE(prev_ac) != IS_POSITIVE(cpu.ac);
  }

  MONADIC_OPCODE(SBC) {
    const auto prev_ac(cpu.ac);
    const auto operand(mode.Read(cpu));

    cpu.ac = cpu.ac - operand - !cpu.status.carry;
    cpu.UpdateFlagsFor(cpu.ac);

    cpu.status.carry = cpu.ac < prev_ac;
    cpu.status.overflow = IS_POSITIVE(prev_ac) != IS_POSITIVE(operand) &&
                          IS_POSITIVE(prev_ac) != IS_POSITIVE(cpu.ac);
  }

  MONADIC_OPCODE(INC) {
    byte result;
    mode.Modify(cpu, [&](byte value) {
      result = static_cast<byte>(value + 1U);
      cpu.UpdateFlagsFor(result);
      return result;
    });
  }

  MONADIC_OPCODE(DEC) {
    byte result;
    mode.Modify(cpu, [&](byte value) {
      result = static_cast<byte>(value - 1U);
      cpu.UpdateFlagsFor(result);
      return result;
    });
  }

  NILADIC_OPCODE(INX) { cpu.UpdateFlagsFor(++cpu.x); }
  NILADIC_OPCODE(INY) { cpu.UpdateFlagsFor(++cpu.y); }
  NILADIC_OPCODE(DEX) { cpu.UpdateFlagsFor(--cpu.x); }
  NILADIC_OPCODE(DEY) { cpu.UpdateFlagsFor(--cpu.y); }

#define OPCODE_UPDATES_FLAGS_AND_MAKES_ACCUMULATOR(code, new_ac) \
  MONADIC_OPCODE(code) {                                         \
    cpu.ac = (new_ac);                                           \
    cpu.UpdateFlagsFor(cpu.ac);                                  \
  }

  OPCODE_UPDATES_FLAGS_AND_MAKES_ACCUMULATOR(AND, cpu.ac & mode.Read(cpu))
  OPCODE_UPDATES_FLAGS_AND_MAKES_ACCUMULATOR(EOR, cpu.ac ^ mode.Read(cpu))
  OPCODE_UPDATES_FLAGS_AND_MAKES_ACCUMULATOR(ORA, cpu.ac | mode.Read(cpu))

#undef OPCODE_UPDATES_FLAGS_AND_MAKES_ACCUMULATOR

  MONADIC_OPCODE(BIT) {
    const auto mem_value(mode.Read(cpu));

    cpu.status.overflow = bit::IsNthBitSet(mem_value, 6);
    cpu.status.negative_result = bit::IsNthBitSet(mem_value, 7);

    cpu.status.zero_result = (cpu.ac & mem_value) == 0;
  }

#define OPCODE_MODIFIES_VALUE_AND_SETS_CARRY(code, carry_value, result_value) \
  MONADIC_OPCODE(code) {                                                      \
    mode.Modify(cpu, [&](byte value) {                                        \
      const auto result = static_cast<byte>(result_value);                    \
                                                                              \
      cpu.status.carry = (carry_value);                                       \
      cpu.UpdateFlagsFor(result);                                             \
      return result;                                                          \
    });                                                                       \
  }

  OPCODE_MODIFIES_VALUE_AND_SETS_CARRY(ASL, bit::IsNthBitSet(value, 7),
                                       value << 1U)
  OPCODE_MODIFIES_VALUE_AND_SETS_CARRY(LSR, bit::IsNthBitSet(value, 0),
                                       value >> 1U)
  OPCODE_MODIFIES_VALUE_AND_SETS_CARRY(ROL, bit::IsNthBitSet(value, 7),
                                       (value << 1U) | cpu.status.carry)
  OPCODE_MODIFIES_VALUE_AND_SETS_CARRY(ROR, bit::IsNthBitSet(value, 0),
                                       (value >> 1U) | (cpu.status.carry << 7U))

#undef OPCODE_MODIFIES_VALUE_AND_SETS_CARRY

#define OPCODE_COMPARES_THIS_WITH_MEMORY(code, register_name)                \
  MONADIC_OPCODE(code) {                                                     \
    const auto operand(mode.Read(cpu));                                      \
    const auto result(static_cast<byte>(cpu.register_name - operand)); \
                                                                             \
    cpu.UpdateFlagsFor(result);                                              \
    cpu.status.carry = operand <= cpu.register_name;                         \
  }

  OPCODE_COMPARES_THIS_WITH_MEMORY(CMP, ac)
  OPCODE_COMPARES_THIS_WITH_MEMORY(CPX, x)
  OPCODE_COMPARES_THIS_WITH_MEMORY(CPY, y)

#undef OPCODE_COMPARES_THIS_WITH_MEMORY
}

#undef IS_POSITIVE
