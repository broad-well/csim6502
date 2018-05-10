//
// Created by Michael Peng on 4/26/18.
//

#include <cstdint>
#include <clocale>
#include <stdexcept>
#include <cstring>
#include <string>
#include "RAM.hh"
#include "Util.hh"

using std::unique_ptr;
using std::memcpy;
using std::out_of_range;
using std::to_string;

byte Hook::loadFrom(RAM &src, word address) const {
  return src.readStoredValue(address);
}
void Hook::storeTo(RAM &src, word address, byte value) const {
  src.storeValue(address, value);
}

byte RAM::Read(const word address) {

  auto hook = FindHook(address);
  if (hook != nullptr)
    return (*hook)->OnRead(*this, address);

  checkAddress(address);
  return readStoredValue(address);
}

void RAM::Write(const word address, const byte value) {

  auto hook = FindHook(address);
  if (hook != nullptr) {
    (*hook)->OnWrite(*this, address, value);
    return;
  }

  checkAddress(address);
  storeValue(address, value);
}
word RAM::ReadWord(word address) {
  // Little endian
  byte low(Read(address)),
      high(Read(address + sizeof(byte)));

  return bit::AsWord(low, high);
}
void RAM::WriteWord(word address, word value) {
  Write(address, bit::LowByte(value));
  Write(address + static_cast<word>(sizeof(byte)), bit::HighByte(value));
}
void RAM::AddHook(Hook *newHook) {
  hooks.emplace(newHook);
}

void RAM::ClearHooks() {
  hooks.clear();
}

const unique_ptr<Hook> *RAM::FindHook(word address) {
  for (auto &hook : hooks)
    if (hook->ShouldAddressAccessRedirect(address))
      return &hook;
  return nullptr;
}
