#ifndef HEAPRAM_HH
#define HEAPRAM_HH

#include "RAM.hh"

class HeapRAM : public RAM {
  public:

  explicit HeapRAM(size_t size);
  HeapRAM(const byte* src, size_t size);
  ~HeapRAM();

  void Load(const byte* source);

  private:

  byte *pool;
  size_t size;

  byte readStoredValue(word address) override;
  void storeValue(word address, byte value) override;
  void checkAddress(word address) const override;
};

#endif // HEAPRAM_HH
