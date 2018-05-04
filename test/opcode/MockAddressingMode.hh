//
// Created by Michael Peng on 5/4/18.
//

#ifndef CSIM6502_MOCKADDRESSINGMODE_HH
#define CSIM6502_MOCKADDRESSINGMODE_HH

#include "opcode/AddressingModes.hh"

struct MockAddressingMode : public AddressingMode {
  byte value;

  MockAddressingMode(byte val) : value(val) {
    Read = [this](CPU&) -> byte {
      return value;
    };
    Write = [this](CPU&, byte new_value) mutable {
      value = new_value;
    };
  }
};

#endif //CSIM6502_MOCKADDRESSINGMODE_HH
