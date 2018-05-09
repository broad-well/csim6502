//
// Created by Michael Peng on 5/4/18.
//

#ifndef CSIM6502_MOCKADDRESSINGMODE_HH
#define CSIM6502_MOCKADDRESSINGMODE_HH

#include "opcode/AddressingModes.hh"
#include <iostream>

extern AddressingMode kMockAddressMode;

void SetMockAddressValue(const byte value);
byte MockAddressValue();

#endif //CSIM6502_MOCKADDRESSINGMODE_HH
