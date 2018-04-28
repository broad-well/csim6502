//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_RAM_HH
#define CSIM6502_RAM_HH

#include <cstddef>
#include "types.hh"

class RAM {
  public:

  byte* PtrTo(word address) const;
  byte Read(word address) const;
  void Write(byte value, word address);

  private:

  virtual byte* ptrTo(word address) const = 0;
  virtual void checkAddress(word) const {}
};

class HeapRAM : public RAM {
  public:

  explicit HeapRAM(size_t size);
  HeapRAM(const byte* src, size_t size);
  ~HeapRAM();

  private:

  byte* pool;
  size_t size;

  byte* ptrTo(word address) const override;
  void checkAddress(word address) const override;
};
#endif //CSIM6502_RAM_HH
