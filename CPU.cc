//
// Created by Michael Peng on 4/26/18.
//

#include "CPU.hh"
CPU::CPU(RAM* memory) :
    x(0), y(0), ac(0), sp(0), pc(0),
    status(0b00000000), decoder(), memory(memory) {
}

byte *CPU::MemoryPtrTo(byte lo, byte hi) {
  return memory->PtrTo(lo, hi);
}

void CPU::UpdateFlagsFor(const byte &new_value) {
  status.Change(ZERO_RESULT, new_value==0);
  status.Change(NEGATIVE_RESULT, new_value >= 0b10000000);
}

/*void CPU::JumpRelative(const byte &offset) {

}

void CPU::DumpRegisterInfo(const std::ostream &out) const {

}*/
