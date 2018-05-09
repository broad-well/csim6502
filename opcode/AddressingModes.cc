//
// Created by michael on 5/7/18.
//

#include "AddressingModes.hh"

namespace address {

#define DEFINE_MEMORY_MODE(name, operation) \
namespace _##name##_ { \
byte Read(CPU &cpu) { \
  return cpu.memory->Read((operation)); \
}\
void Write(CPU &cpu, byte value) { \
  cpu.memory->Write((operation), value); \
}\
void Modify(CPU &cpu, const std::function<byte(byte)> &func) { \
  const auto addr = (operation); \
  cpu.memory->Write(addr, func(cpu.memory->Read(addr))); \
}\
} \
AddressingMode name { _##name##_::Read, _##name##_::Write, _##name##_::Modify };

DEFINE_MEMORY_MODE(Abs, cpu.NextOperandWord())
DEFINE_MEMORY_MODE(AbsX, cpu.NextOperandWord() + cpu.x)
DEFINE_MEMORY_MODE(AbsY, cpu.NextOperandWord() + cpu.y)

DEFINE_MEMORY_MODE(Zpg, cpu.NextCodeByte())
DEFINE_MEMORY_MODE(ZpgX, bit::LowByte(cpu.NextCodeByte() + cpu.x))
DEFINE_MEMORY_MODE(ZpgY, bit::LowByte(cpu.NextCodeByte() + cpu.y))

DEFINE_MEMORY_MODE(Ind, cpu.memory->ReadWord(cpu.NextOperandWord()))
DEFINE_MEMORY_MODE(XInd, cpu.memory->ReadWord(bit::LowByte(cpu.NextCodeByte() + cpu.x)))
DEFINE_MEMORY_MODE(IndY, cpu.memory->ReadWord(cpu.NextCodeByte()) + cpu.y)

// Immediate
byte ImRead(CPU &cpu) {
  return cpu.NextCodeByte();
}
[[noreturn]]
void ImWrite(CPU &, byte) {
  throw std::invalid_argument("Cannot write to Immediate target");
}
[[noreturn]]
void ImModify(CPU &, const std::function<byte(byte)> &) {
  throw std::invalid_argument("Cannot modify Immediate target");
}
AddressingMode Immed{
    ImRead, ImWrite, ImModify
};

// Accumulator
byte AcRead(CPU &cpu) {
  return cpu.ac;
}
void AcWrite(CPU &cpu, byte value) {
  cpu.ac = value;
}
void AcModify(CPU &cpu, const std::function<byte(byte)> &func) {
  cpu.ac = func(cpu.ac);
}
AddressingMode Accum{
    AcRead, AcWrite, AcModify
};

#undef DEFINE_MEMORY_MODE
}
