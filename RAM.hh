//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_RAM_HH
#define CSIM6502_RAM_HH

#include <cstddef>
#include "types.hh"

class RAM {
  public:

  byte* PtrTo(byte lo, byte hi = 0x00) const;
  byte Read(byte lo, byte hi = 0x00) const;
  void Write(byte value, byte lo, byte hi = 0x00);

  private:

  virtual byte* ptrTo(byte lo, byte hi) const = 0;
};

class HeapRAM : public RAM {
  public:

  explicit HeapRAM(size_t size);
  HeapRAM(const byte* src, size_t size);
  ~HeapRAM();

  private:

  byte* pool;
  size_t size;

  byte* ptrTo(byte lo, byte hi) const override;
  void checkAddress(uint16_t address) const;
};
#endif //CSIM6502_RAM_HH
