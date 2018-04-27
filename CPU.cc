//
// Created by Michael Peng on 4/26/18.
//

#include "CPU.hh"
CPU::CPU() : x(0), y(0), ac(0), sp(0), pc(0), status(0b00000000) {

}
CPU::~CPU() {

}
void CPU::UpdateFlagsFor(const word &new_value) {

}
void CPU::JumpRelative(const word &offset) {

}
word CPU::FetchOpCodeAtCounter() const {
  return 0;
}
word &CPU::StatusFlag(const StatusPos &&position) const {
  return
}
void CPU::DumpRegisterInfo(const std::ostream &out) const {

}
