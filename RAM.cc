//
// Created by Michael Peng on 4/26/18.
//

#include <cstdint>
#include <clocale>
#include <stdexcept>
#include <string>
#include "RAM.hh"
word *RAM::PtrTo(const word lo, const uint8_t hi) const {
  return ptrTo(lo, hi);
}

word RAM::Read(const word lo, const word hi) const {
  return *PtrTo(lo, hi);
}
void RAM::Write(const word value, const word lo, const word hi) {
  *ptrTo(lo, hi) = value;
}



HeapRAM::HeapRAM(size_t size) : size(size) {
  pool = new uint8_t[size];
}

HeapRAM::HeapRAM(const word *src, size_t size) : HeapRAM(size)
{
  memcpy(pool, src, size);
}

HeapRAM::~HeapRAM() {
  delete[] pool;
}

uint16_t ComposeLittleEndianAddress(const word& lo, const word& hi) {
  return (hi << 8) + lo;
}

void HeapRAM::checkAddress(const uint16_t address) const {
  if (address >= size) {
    throw std::out_of_range("Address out of range: " + std::to_string(address));
  }
}

word *HeapRAM::ptrTo(word lo, word hi) const {
  uint16_t address = ComposeLittleEndianAddress(lo, hi);
  checkAddress(address);
  return &pool[address];
}
