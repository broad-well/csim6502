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

  protected:

  byte loadFrom(RAM &src, word address) const;
  void storeTo(RAM &src, word address, byte value) const;
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

  const std::unique_ptr<Hook> *FindHook(word address);

  virtual byte readStoredValue(word address) = 0;
  virtual void storeValue(word address, byte value) = 0;
  virtual void checkAddress(word) const {}

  friend class Hook;
};

class HeapRAM : public RAM {
  public:

  explicit HeapRAM(size_t size);
  HeapRAM(const byte *src, size_t size);
  ~HeapRAM();

  private:

  byte *pool;
  size_t size;

  byte readStoredValue(word address) override;
  void storeValue(word address, byte value) override;
  void checkAddress(word address) const override;
};
#endif //CSIM6502_RAM_HH
