//
// Created by Michael Peng on 4/27/18.
//

#ifndef CSIM6502_MOCKRAM_HH
#define CSIM6502_MOCKRAM_HH

#include <cstddef>
#include <cstdlib>
#include <map>
#include "RAM.hh"
#include "types.hh"

class MockRAM : public RAM {
  public:

  MockRAM(const std::initializer_list<byte>& list): size(list.size()) {
    data = new byte[size];
    std::copy(list.begin(), list.end(), data);
  }
  ~MockRAM() {
    delete[] data;
  }

  private:

  byte* data;
  std::map<word, byte> written_data;
  const size_t size;

  byte readStoredValue(word address) override {
    if (address >= size)
      return written_data[address];
    else
      return data[address];
  }
  void storeValue(word address, byte value) override {
    if (address >= size)
      written_data[address] = value;
    else
      data[address] = value;
  }

  void checkAddress(word) const override {}
};

#endif //CSIM6502_MOCKRAM_HH
