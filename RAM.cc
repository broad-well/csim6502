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

byte *RAM::PtrTo(const word address) const {
  checkAddress(address);
  return ptrTo(address);
}

byte RAM::Read(const word address) const {
  return *PtrTo(address);
}
void RAM::Write(const byte value, const word address) {
  *PtrTo(address) = value;
}
byte *RAM::PtrToIndirectTarget(word given_address) const {
  return PtrTo(ReadWord(given_address));
}
word RAM::ReadWord(word address) const {
  // Little endian
  byte low(Read(address)),
      high(Read(address + (word)sizeof(byte)));

  return bit::AsWord(low, high);
}

HeapRAM::HeapRAM(size_t size) : size(size) {
  pool = new uint8_t[size];
}

HeapRAM::HeapRAM(const byte *src, size_t size) : HeapRAM(size)
{
  std::memcpy(pool, src, size);
}

HeapRAM::~HeapRAM() {
  delete[] pool;
}

void HeapRAM::checkAddress(const uint16_t address) const {
  if (address >= size) {
    throw std::out_of_range("Address out of range: " + std::to_string(address));
  }
}

byte *HeapRAM::ptrTo(const uint16_t address) const {
  return &pool[address];
}
