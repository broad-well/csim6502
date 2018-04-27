//
// Created by Michael Peng on 4/26/18.
//

#include <stdexcept>
#include "Bitset.hh"

void CheckByteIndexRange(const std::size_t index) {
  if (index > 7)
    throw std::out_of_range("Bitset indexed by value greater than 7");
}

Bitset::Bitset(): data(0) {
}
Bitset::Bitset(const std::uint8_t data): data(data) {
}

void Bitset::Set(const std::size_t index) {
  CheckByteIndexRange(index);
  data |= 1U << index;
}
void Bitset::Clear(const std::size_t index) {
  CheckByteIndexRange(index);
  data &= ~(1U << index);
}

bool Bitset::IsSet(const std::size_t index) const {
  CheckByteIndexRange(index);
  return ((data >> index) & 1U) != 0;
}

bool Bitset::IsCleared(const std::size_t index) const {
  CheckByteIndexRange(index);
  return !IsSet(index);
}

std::uint8_t Bitset::Data() const {
  return data;
}
