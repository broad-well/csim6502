//
// Created by Michael Peng on 4/26/18.
//

#include "CPU.hh"
#include "Util.hh"

void StatusFlags::LoadFromByte(const byte &data) {
  memcpy(this, &data, sizeof(StatusFlags));
}
byte StatusFlags::ToByte() const {
  byte out;
  memcpy(&out, this, sizeof(StatusFlags));
  return out;
}
void StatusFlags::Clear() {
  memset(this, 0, sizeof(StatusFlags));
}
std::string StatusFlags::ToString() const {
  using namespace std;

  stringstream stream;
  stream
      << (negative_result ? 'N' : 'n')
      << (overflow ? 'V' : 'v')
      << '_'
      << (break_command ? 'B' : 'b')
      << (decimal_mode ? 'D' : 'd')
      << (irq_disable ? 'I' : 'i')
      << (zero_result ? 'Z' : 'z')
      << (carry ? 'C' : 'c');
  return stream.str();
}

CPU::CPU(RAM* memory) :
    x(0), y(0), ac(0), sp(0), pc_low(0), pc_high(0),
    decoder(), status(), memory(memory) {

  status.Clear();
}

byte *CPU::MemoryPtrTo(byte lo, byte hi) const {
  return memory->PtrTo(lo, hi);
}

void CPU::UpdateFlagsFor(const byte &new_value) {
  status.zero_result = new_value==0;
  status.negative_result = new_value >= 0b10000000;
}

void CPU::JumpRelative(const byte &offset) {
  const signed_byte rel(offset);
  const byte prev_low(pc_low);

  pc_low += rel;
  if (rel > 0 && pc_low < prev_low)
    ++pc_high;
  else if (rel < 0 && pc_low > prev_low)
    --pc_high;
}

void CPU::DumpRegisterInfo(std::ostream &out) const {
  char out_str[38];

  sprintf(out_str, "X=%02X Y=%02X A=%02X\nSP=%02X PC=%02X%02X\n%s",
      x, y, ac, sp, pc_high, pc_low, status.ToString().c_str());

  out << out_str;
}
