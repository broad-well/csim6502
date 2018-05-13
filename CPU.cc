//
// Created by Michael Peng on 4/26/18.
//

#include "CPU.hh"
#include <cstring>
#include "Util.hh"

using std::cout;
using std::ostream;
using std::overflow_error;
using std::string;
using std::underflow_error;

constexpr byte kStackFirst(0xFF);
constexpr byte kStackLast(0x00);

void StatusFlags::LoadFromByte(const byte &data) {
  memcpy(this, &data, sizeof(StatusFlags));
}
byte StatusFlags::ToByte() const {
  byte out;
  memcpy(&out, this, sizeof(StatusFlags));
  return out;
}

void StatusFlags::Clear() { memset(this, 0, sizeof(StatusFlags)); }

string StatusFlags::ToString() const {
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

CPU::CPU(RAM *memory)
    : x(0), y(0), ac(0), sp(kStackFirst), pc(0), status(), memory(memory) {
  status.Clear();
}

void CPU::UpdateFlagsFor(const byte new_value) {
  status.zero_result = new_value == 0;
  status.negative_result = new_value >= 0b10000000;
}

void CPU::JumpRelative(const signed_byte offset) { pc += offset; }

void CPU::DumpRegisterInfo(ostream &out) const {
  char out_str[38];

  sprintf(out_str, "X=%02X Y=%02X A=%02X\nSP=%02X PC=%04X\n%s", x, y, ac, sp,
          pc, status.ToString().c_str());

  out << out_str;
}

void CPU::IncrementProgramCounter() {
  if (pc == 0xffff)
    throw overflow_error(
        "Incrementing Program Counter (PC) at 0xffff causes overflow");
  ++pc;
}

byte CPU::NextCodeByte() {
  byte opcode(memory->Read(pc));
  IncrementProgramCounter();
  return opcode;
}

word CPU::NextOperandWord() {
  byte low(NextCodeByte()), high(NextCodeByte());

  return bit::AsWord(low, high);
}

word AddressAtStackPtr(const byte ptr_value) { return 0x100 + ptr_value; }

void CPU::PushByteToStack(byte value) {
  if (sp == kStackLast)
    throw overflow_error("Attempt to push byte onto full stack");

  memory->Write(AddressAtStackPtr(sp--), value);
}

void CPU::PushWordToStack(word value) {
  byte low(bit::LowByte(value)), high(bit::HighByte(value));

  PushByteToStack(high);
  PushByteToStack(low);
}

byte CPU::PullByteFromStack() {
  if (sp == kStackFirst)
    throw underflow_error("Attempt to pull byte from empty stack");

  return memory->Read(AddressAtStackPtr(++sp));
}
word CPU::PullWordFromStack() {
  byte low(PullByteFromStack()), high(PullByteFromStack());

  return bit::AsWord(low, high);
}

void CPU::Reset() {
  pc = 0x00;
  sp = kStackFirst;
  x = y = ac = 0;
  status.Clear();
}
