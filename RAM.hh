//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_RAM_HH
#define CSIM6502_RAM_HH

#include <cstddef>
#include "types.hh"

class RAM {
  public:

  byte* PtrTo(word address);
  byte Read(word address);
  word ReadWord(word address);
  void Write(word address, byte value);
  byte* PtrToIndirectTarget(word given_address);

  private:

  virtual byte* ptrTo(word address) = 0;
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

  byte* ptrTo(word address) override;
  void checkAddress(word address) const override;
};
#endif //CSIM6502_RAM_HH
