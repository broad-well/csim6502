//
// Created by Michael Peng on 4/26/18.
//

#include <cstdint>
#include <clocale>
#include <stdexcept>
#include <cstring>
#include "RAM.hh"

byte *RAM::PtrTo(const byte lo, const uint8_t hi) const {
  return ptrTo(lo, hi);
}

byte RAM::Read(const byte lo, const byte hi) const {
  return *PtrTo(lo, hi);
}
void RAM::Write(const byte value, const byte lo, const byte hi) {
  *ptrTo(lo, hi) = value;
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

uint16_t ComposeLittleEndianAddress(const byte& lo, const byte& hi) {
  return (hi << 8) + lo;
}

void HeapRAM::checkAddress(const uint16_t address) const {
  if (address >= size) {
    throw std::out_of_range("Address out of range: " + std::to_string(address));
  }
}

byte *HeapRAM::ptrTo(byte lo, byte hi) const {
  uint16_t address = ComposeLittleEndianAddress(lo, hi);
  checkAddress(address);
  return &pool[address];
}
