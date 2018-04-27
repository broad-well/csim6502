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
#include "RAM.hh"

// C Z I D B _ V N
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
  byte
      x,
      y,
      ac, // Accumulator
      sp, // Stack pointer
      pc; // Program counter

  Bitset status;
  Decoder decoder;
  RAM* memory;

  public:
  CPU(RAM* memory);
  ~CPU() = default;

  byte* MemoryPtrTo(byte lo, byte hi = 0x00);
  void UpdateFlagsFor(const byte& new_value);
  void JumpRelative(const byte& offset);

  void DumpRegisterInfo(const std::ostream& out = std::cout) const;
};

#endif //CSIM6502_CPU_HH
