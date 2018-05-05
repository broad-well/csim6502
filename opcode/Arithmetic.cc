//
// Created by Michael Peng on 4/25/18.
//

#include "Arithmetic.hh"

#define IS_POSITIVE(n) (n >> 7U == 0)

// http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
OPCODE_SET {
  MONADIC_OPCODE(ADC) {
    auto prev_ac(cpu.ac);
    auto operand(mode.Read(cpu));

    cpu.ac = cpu.ac + operand + cpu.status.carry;
    cpu.UpdateFlagsFor(cpu.ac);

    cpu.status.carry = (cpu.ac - cpu.status.carry) < prev_ac;
    cpu.status.overflow =
        IS_POSITIVE(prev_ac) == IS_POSITIVE(operand) &&
            IS_POSITIVE(prev_ac) != IS_POSITIVE(cpu.ac);

  }

  MONADIC_OPCODE(SBC) {
    const auto prev_ac(cpu.ac);
    const auto operand(mode.Read(cpu));

    cpu.ac = cpu.ac - operand - !cpu.status.carry;
    cpu.UpdateFlagsFor(cpu.ac);

    cpu.status.carry = cpu.ac < prev_ac;
    cpu.status.overflow =
        IS_POSITIVE(prev_ac) != IS_POSITIVE(operand) &&
            IS_POSITIVE(prev_ac) != IS_POSITIVE(cpu.ac);
  }
}