//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_BITSET_HH
#define CSIM6502_BITSET_HH

#include <cstddef>
#include <cstdint>

// LITTLE-ENDIAN, 8-BIT
class Bitset {
  public:

  Bitset();
  explicit Bitset(std::uint8_t data);

  void Set(std::size_t index);
  void Clear(std::size_t index);

  bool IsSet(std::size_t index) const;
  bool IsCleared(std::size_t index) const;

  std::uint8_t Data() const;

  private:

  std::uint8_t data;

};

#endif //CSIM6502_BITSET_HH
