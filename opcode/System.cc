//
// Created by Michael Peng on 4/25/18.
//

#include "System.hh"

namespace opcode {

EMPTY_OPCODE(NOP);

NILADIC_OPCODE(BRK) {
  cpu.IncrementProgramCounter();
  cpu.PushWordToStack(cpu.pc);
  cpu.PushByteToStack(static_cast<byte>(cpu.status.ToByte() | 0b00010000U));
  cpu.pc = cpu.memory->ReadWord(0xfffe);
}

}