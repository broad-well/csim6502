//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_RAM_HH
#define CSIM6502_RAM_HH

#include <cstddef>
#include "types.hh"

class RAM {
  public:

  word* PtrTo(word lo, word hi = 0x00) const;
  word Read(word lo, word hi = 0x00) const;
  void Write(word value, word lo, word hi = 0x00);

  private:

  virtual word* ptrTo(word lo, word hi) const = 0;
};

class HeapRAM : public RAM {
  public:

  explicit HeapRAM(size_t size);
  HeapRAM(const word* src, size_t size);
  ~HeapRAM();

  private:

  word* pool;
  size_t size;

  word* ptrTo(word lo, word hi) const override;
  void checkAddress(uint16_t address) const;
};
#endif //CSIM6502_RAM_HH
