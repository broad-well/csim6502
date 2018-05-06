//
// Created by Michael Peng on 5/4/18.
//

#ifndef CSIM6502_MOCKADDRESSINGMODE_HH
#define CSIM6502_MOCKADDRESSINGMODE_HH

#include "opcode/AddressingModes.hh"
#include <iostream>

struct MockAddressingMode : public AddressingMode {
  byte value;
  bool called = false;

  MockAddressingMode(byte val) : value(val) {
    Read = [this](CPU &) -> byte {
      if (called)
        std::cout << "Read called twice" << std::endl;
      else
        called = true;

      return value;
    };
    Write = [this](CPU &, byte new_value) mutable {
      if (called)
        std::cout << "Write called twice" << std::endl;
      else
        value = new_value;
      called = true;
    };
    Modify = [this](CPU &, auto func) {
      if (called)
        std::cout << "Modify called twice" << std::endl;
      else
        value = func(value);
      called = true;
    };
  }
};

#endif //CSIM6502_MOCKADDRESSINGMODE_HH
