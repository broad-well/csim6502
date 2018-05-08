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

  MockAddressingMode(byte val) : value(val) {}

  byte Read(CPU &) const override {
    return value;
  }
  void Write(CPU &, byte writing) const override {
    value = writing;
  }
  void Modify(CPU &, const std::function<byte(byte)> & func) const override {
    value = func(value);
  }
};

#endif //CSIM6502_MOCKADDRESSINGMODE_HH
