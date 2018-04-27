//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_CPU_HH
#define CSIM6502_CPU_HH

#include <ostream>
#include <iostream>
#include "types.hh"
#include "opcode/Decoder.hh"
#include "Bitset.hh"

enum StatusPos {
  CARRY,
  ZERO_RESULT,
  IRQ_DISABLE,
  DECIMAL_MODE,
  BREAK_CMD,
  _EXPANSION,
  OVERFLOW,
  NEGATIVE_RESULT,
};

struct CPU {
  // Registers
  word
      x,
      y,
      ac, // Accumulator
      sp, // Stack pointer
      pc; // Program counter
  Bitset status;

  Decoder decoder;

  public:
  CPU();
  ~CPU();

  void UpdateFlagsFor(const word& new_value);
  void JumpRelative(const word& offset);

  void DumpRegisterInfo(const std::ostream& out = std::cout) const;
};

#endif //CSIM6502_CPU_HH
