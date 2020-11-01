//
// Created by Michael Peng on 4/25/18.
//

#include "System.hh"
#include "Executor.hh"
#include <cstdlib>

OPCODE_SET {
  STATIC_OPCODE(NOP) {}

  NILADIC_OPCODE(BRK) {
    cpu.IncrementProgramCounter();
    cpu.PushWordToStack(cpu.pc);
    cpu.PushByteToStack(static_cast<byte>(cpu.status.ToByte() | 0b00010000U));
    cpu.pc = cpu.memory->ReadWord(0xfffe);
  }

  NILADIC_OPCODE(DMP) {
    cpu.DumpRegisterInfo();
  }

  NILADIC_OPCODE(PTA) {
    printf("%i\n", cpu.ac);
  }

  [[noreturn]]
  STATIC_OPCODE(Illegal) { throw std::invalid_argument("Illegal instruction"); }

  [[noreturn]]
  STATIC_OPCODE(EXIT) { std::exit(0); }

}  // namespace opcode
