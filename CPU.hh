//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_CPU_HH
#define CSIM6502_CPU_HH

#include <ostream>
#include <iostream>
#include "types.hh"
#include "opcode/Decoder.hh"
#include "RAM.hh"

// C Z I D B _ V N
struct StatusFlags {
  bool carry : 1,
      zero_result : 1,
      irq_disable : 1,
      decimal_mode : 1,
      break_command : 1,
      _expansion : 1,
      overflow : 1,
      negative_result : 1;

  void LoadFromByte(const byte& data);
  void Clear();
  byte ToByte() const;
  std::string ToString() const;
};

struct CPU {
  // Registers
  byte
      x,
      y,
      ac, // Accumulator
      sp; // Stack pointer
  word pc; // Program counter

  Decoder decoder;
  StatusFlags status;
  RAM* memory;

  public:
  explicit CPU(RAM* memory);
  ~CPU() = default;

  byte* MemoryPtrTo(word address) const;
  void UpdateFlagsFor(const byte& new_value);
  void JumpRelative(const byte& offset);

  byte& NextOpcode();
  byte& NextOperand();
  void IncrementProgramCounter();

  void DumpRegisterInfo(std::ostream& out = std::cout) const;
};

#endif //CSIM6502_CPU_HH
