//
// Created by Michael Peng on 5/2/18.
//

#ifndef CSIM6502_ADDRESSINGMODES_HH
#define CSIM6502_ADDRESSINGMODES_HH

#include <functional>
#include "../CPU.hh"
#include "../types.hh"
#include "../Util.hh"

struct AddressingMode {
  std::function<byte(CPU &)> Read;
  std::function<void(CPU &, byte)> Write;
};

namespace address {

#define MODE_ADDRESSED_AS(operation) { \
[](CPU &cpu) { \
  return cpu.memory->Read((operation)); \
}, \
[](CPU &cpu, byte value) { \
  cpu.memory->Write((operation), value); \
}}

static const AddressingMode Immediate = {
    [](CPU &cpu) {
      return cpu.NextCodeByte();
    },
    // Should throw bad_function_call
    nullptr
},

    Accumulator = {
    [](CPU &cpu) {
      return cpu.ac;
    },
    [](CPU &cpu, byte value) {
      cpu.ac = value;
    }
},
    Absolute = MODE_ADDRESSED_AS(cpu.NextOperandWord()),
    AbsoluteIndexedX = MODE_ADDRESSED_AS(cpu.NextOperandWord() + cpu.x),
    AbsoluteIndexedY = MODE_ADDRESSED_AS(cpu.NextOperandWord() + cpu.y),

    ZeroPage = MODE_ADDRESSED_AS(cpu.NextCodeByte()),
    ZeroPageIndexedX = MODE_ADDRESSED_AS(bit::LowByte(cpu.NextCodeByte() + cpu.x)),
    ZeroPageIndexedY = MODE_ADDRESSED_AS(bit::LowByte(cpu.NextCodeByte() + cpu.y)),

//  For Relative, use cpu.JumpRelative
    Indirect = MODE_ADDRESSED_AS(cpu.memory->ReadWord(cpu.NextOperandWord())),
    XIndexedIndirect = MODE_ADDRESSED_AS(cpu.memory->ReadWord(bit::LowByte(cpu.NextCodeByte() + cpu.x))),
    IndirectYIndexed = MODE_ADDRESSED_AS(cpu.memory->ReadWord(cpu.NextCodeByte()) + cpu.y);

#undef MODE_ADDRESSED_AS

}
#endif //CSIM6502_ADDRESSINGMODES_HH
