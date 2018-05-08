//
// Created by Michael Peng on 4/25/18.
//

#include "System.hh"
#include <cstdlib>

namespace opcode {

STATIC_OPCODE(NOP) {}

NILADIC_OPCODE(BRK) {
  cpu.IncrementProgramCounter();
  cpu.PushWordToStack(cpu.pc);
  cpu.PushByteToStack(static_cast<byte>(cpu.status.ToByte() | 0b00010000U));
  cpu.pc = cpu.memory->ReadWord(0xfffe);
}

STATIC_OPCODE(Illegal) {
  throw std::invalid_argument("Illegal instruction");
}

STATIC_OPCODE(EXIT) {
  std::exit(0);
}

}