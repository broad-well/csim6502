//
// Created by Michael Peng on 4/26/18.
//

#include <cstdint>
#include <clocale>
#include <stdexcept>
#include <cstring>
#include <string>
#include "RAM.hh"

byte *RAM::PtrTo(const word address) const {
  return ptrTo(address);
}

byte RAM::Read(const word address) const {
  return *PtrTo(address);
}
void RAM::Write(const byte value, const word address) {
  *ptrTo(address) = value;
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
  checkAddress(address);
  return &pool[address];
}
