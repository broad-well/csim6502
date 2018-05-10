#include "HeapRAM.hh"
#include <cstring>

using namespace std;

HeapRAM::HeapRAM(size_t size) : size(size) {
  pool = new uint8_t[size];
}

HeapRAM::HeapRAM(const byte *src, size_t size) : HeapRAM(size) {
  memcpy(pool, src, size);
}

HeapRAM::~HeapRAM() {
  delete[] pool;
}

void HeapRAM::checkAddress(const uint16_t address) const {
  if (address >= size) {
    throw out_of_range("Address out of range: " + to_string(address));
  }
}
byte HeapRAM::readStoredValue(word address) {
  return pool[address];
}
void HeapRAM::storeValue(word address, byte value) {
  pool[address] = value;
}
void HeapRAM::Load(const byte *source) {
  memcpy(pool, source, size);
}
