//
// Created by Michael Peng on 5/2/18.
//

#ifndef CSIM6502_ADDRESSINGMODES_HH
#define CSIM6502_ADDRESSINGMODES_HH

#include <functional>
#include "../types.hh"
#include "../CPU.hh"
#include "../Util.hh"

struct AddressingMode {
  std::function<word(CPU &)> Read;
  std::function<void(CPU &, byte)> Write;
};

// Shorthand for a trivial Addressing Mode that uses the given function to deduce the address, which is returned
inline AddressingMode ModeWithAddressAs(const std::function<word(CPU &)> &address_supplier) {
  return {
      [address_supplier](CPU &cpu) {
        return cpu.memory->Read(address_supplier(cpu));
      },
      [address_supplier](CPU &cpu, byte value) {
        cpu.memory->Write(address_supplier(cpu), value);
      }
  };
}

namespace address {

#define MODE_ADDRESSED_AS(operation) ModeWithAddressAs([](CPU &cpu) { return (operation); })

static const AddressingMode Immediate = {
    [](CPU &cpu) {
      return cpu.NextCodeByte();
    },
    // Should throw bad_function_call
    nullptr
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
