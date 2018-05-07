//
// Created by Michael Peng on 5/2/18.
//

#ifndef CSIM6502_ADDRESSINGMODES_HH
#define CSIM6502_ADDRESSINGMODES_HH

#include <functional>
#include <exception>
#include <stdexcept>
#include "../CPU.hh"
#include "../types.hh"
#include "../Util.hh"

struct AddressingMode {
  virtual byte Read(CPU &) const = 0;
  virtual void Write(CPU &, byte) const = 0;
  virtual void Modify(CPU &, const std::function<byte(byte)> &) const = 0;
};

namespace address {

#define DECLARE_MEMORY_MODE(name, operation) struct name : public AddressingMode { \
  byte Read(CPU &cpu) const override { \
    return cpu.memory->Read((operation)); \
  } \
  void Write(CPU &cpu, byte value) const override { \
    cpu.memory->Write((operation), value); \
  } \
  void Modify(CPU &cpu, const std::function<byte(byte)>& func) const override { \
    const auto addr = (operation); \
    cpu.memory->Write(addr, func(cpu.memory->Read(addr))); \
  } \
};

DECLARE_MEMORY_MODE(Abs, cpu.NextOperandWord())
DECLARE_MEMORY_MODE(AbsX, cpu.NextOperandWord() + cpu.x)
DECLARE_MEMORY_MODE(AbsY, cpu.NextOperandWord() + cpu.y)

DECLARE_MEMORY_MODE(Zpg, cpu.NextCodeByte())
DECLARE_MEMORY_MODE(ZpgX, bit::LowByte(cpu.NextCodeByte() + cpu.x))
DECLARE_MEMORY_MODE(ZpgY, bit::LowByte(cpu.NextCodeByte() + cpu.y))

DECLARE_MEMORY_MODE(Ind, cpu.memory->ReadWord(cpu.NextOperandWord()))
DECLARE_MEMORY_MODE(XInd, cpu.memory->ReadWord(bit::LowByte(cpu.NextCodeByte() + cpu.x)))
DECLARE_MEMORY_MODE(IndY, cpu.memory->ReadWord(cpu.NextCodeByte()) + cpu.y)

// Immediate
struct Immed : public AddressingMode {
  byte Read(CPU &cpu) const override {
    return cpu.NextCodeByte();
  }
  void Write(CPU &, byte) const override {
    throw std::invalid_argument("Cannot write to Immediate target");
  }
  void Modify(CPU &, const std::function<byte(byte)> &) const override {
    throw std::invalid_argument("Cannot modify Immediate target");
  }
};

// Accumulator
struct Accum : public AddressingMode {
  byte Read(CPU &cpu) const override {
    return cpu.ac;
  }
  void Write(CPU &cpu, byte value) const override {
    cpu.ac = value;
  }
  void Modify(CPU &cpu, const std::function<byte(byte)> &func) const override {
    cpu.ac = func(cpu.ac);
  }
};

#undef DECLARE_MEMORY_MODE

}
#endif //CSIM6502_ADDRESSINGMODES_HH
