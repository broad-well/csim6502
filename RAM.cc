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
byte RAM::ReadIndirectTarget(word given_address) {
  return Read(ReadWord(given_address));
}

void RAM::WriteIndirectTarget(word given_address, byte value) {
  Write(ReadWord(given_address), value);
}

word RAM::ReadWord(word address) {
  // Little endian
  byte low(Read(address)),
      high(Read(address + (word) sizeof(byte)));

  return bit::AsWord(low, high);
}
void RAM::AddHook(Hook *newHook) {
  hooks.emplace(newHook);
}
void RAM::ClearHooks() {
  hooks.clear();
}

const std::unique_ptr<Hook> *RAM::FindHook(word address) {
  for (auto& hook : hooks)
    if (hook->ShouldAddressAccessRedirect(address))
      return &hook;
  return nullptr;
}

HeapRAM::HeapRAM(size_t size) : size(size) {
  pool = new uint8_t[size];
}

HeapRAM::HeapRAM(const byte *src, size_t size) : HeapRAM(size) {
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
byte HeapRAM::readStoredValue(word address) {
  return pool[address];
}
void HeapRAM::storeValue(word address, byte value) {
  pool[address] = value;
}
