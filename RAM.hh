//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_RAM_HH
#define CSIM6502_RAM_HH

#include <cstddef>
#include <unordered_set>
#include <memory>
#include "types.hh"

class RAM;

class Hook {
  public:

  virtual bool ShouldAddressAccessRedirect(word) const {
    return false;
  }

  virtual byte OnRead(RAM &caller, word address) const = 0;
  virtual void OnWrite(RAM &caller, word address, byte value) const = 0;
};

class RAM {
  public:

  byte Read(word address);
  word ReadWord(word address);
  void Write(word address, byte value);

  byte ReadIndirectTarget(word given_address);
  void WriteIndirectTarget(word given_address, byte value);

  void AddHook(Hook *newHook);
  void ClearHooks();

  private:
  std::unordered_set<std::unique_ptr<Hook>> hooks;

  const std::unique_ptr<Hook> * FindHook(word address);
  virtual byte *ptrTo(word address) = 0;
  virtual void checkAddress(word) const {}
};

class HeapRAM : public RAM {
  public:

  explicit HeapRAM(size_t size);
  HeapRAM(const byte *src, size_t size);
  ~HeapRAM();

  private:

  byte *pool;
  size_t size;

  byte *ptrTo(word address) override;
  void checkAddress(word address) const override;
};
#endif //CSIM6502_RAM_HH
