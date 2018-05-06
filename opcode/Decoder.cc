//
// Created by Michael Peng on 4/25/18.
//

#include "Decoder.hh"
#include <functional>

using namespace opcode;
using namespace address;

#define M(code, mode) [](CPU& cpu) { code(cpu, mode); }
#define N(code) Executor(code)
#define ILLEGAL N(Illegal)

static const Executor kInstructionTable[] {
    // 0             1                        2                3        4                        5                         6                        7        8       9                        A                   B        C                        D                        E                        F
    N(BRK),          M(ORA,XIndexedIndirect), ILLEGAL,         ILLEGAL, ILLEGAL,                 M(ORA,ZeroPage),          M(ASL,ZeroPage),         ILLEGAL, N(PHP), M(ORA,Immediate),        M(ASL,Accumulator), ILLEGAL, ILLEGAL,                 M(ORA,Absolute),         M(ASL,Absolute),         ILLEGAL,
    N(BPL),          M(ORA,IndirectYIndexed), ILLEGAL,         ILLEGAL, ILLEGAL,                 M(ORA,ZeroPageIndexedX),  M(ASL,ZeroPageIndexedX), ILLEGAL, N(CLC), M(ORA,AbsoluteIndexedY), ILLEGAL,            ILLEGAL, ILLEGAL,                 M(ORA,AbsoluteIndexedX), M(ASL,AbsoluteIndexedX), ILLEGAL,
    N(JSR),          M(AND,XIndexedIndirect), ILLEGAL,         ILLEGAL, M(BIT,ZeroPage),         M(AND,ZeroPage),          M(ROL,ZeroPage),         ILLEGAL, N(PLP), M(AND,Immediate),        M(ROL,Accumulator), ILLEGAL, M(BIT,Absolute),         M(AND,Absolute),         M(ROL,Absolute),         ILLEGAL,
    N(BMI),          M(AND,IndirectYIndexed), ILLEGAL,         ILLEGAL, ILLEGAL,                 M(AND,ZeroPageIndexedX),  M(ROL,ZeroPageIndexedX), ILLEGAL, N(SEC), M(AND,AbsoluteIndexedY), ILLEGAL,            ILLEGAL, ILLEGAL,                 M(AND,AbsoluteIndexedX), M(ROL,AbsoluteIndexedX), ILLEGAL,
    N(RTI),          M(EOR,XIndexedIndirect), ILLEGAL,         ILLEGAL, ILLEGAL,                 M(EOR,ZeroPage),          M(LSR,ZeroPage),         ILLEGAL, N(PHA), M(EOR,Immediate),        M(LSR,Accumulator), ILLEGAL, N(JMP_Absolute),         M(EOR,Absolute),         M(LSR,Absolute),         ILLEGAL,
    N(BVC),          M(EOR,IndirectYIndexed), ILLEGAL,         ILLEGAL, ILLEGAL,                 M(EOR,ZeroPageIndexedX),  M(LSR,ZeroPageIndexedX), ILLEGAL, N(CLI), M(EOR,AbsoluteIndexedY), ILLEGAL,            ILLEGAL, ILLEGAL,                 M(EOR,AbsoluteIndexedX), M(LSR,AbsoluteIndexedX), ILLEGAL,
    N(RTS),          M(ADC,XIndexedIndirect), ILLEGAL,         ILLEGAL, ILLEGAL,                 M(ADC,ZeroPage),          M(ROR,ZeroPage),         ILLEGAL, N(PLA), M(ADC,Immediate),        M(ROR,Accumulator), ILLEGAL, N(JMP_Indirect),         M(ADC,Absolute),         M(ROR,Absolute),         ILLEGAL,
    N(BVS),          M(ADC,IndirectYIndexed), ILLEGAL,         ILLEGAL, ILLEGAL,                 M(ADC,ZeroPageIndexedX),  M(ROR,ZeroPageIndexedX), ILLEGAL, N(SEI), M(ADC,AbsoluteIndexedY), ILLEGAL,            ILLEGAL, ILLEGAL,                 M(ADC,AbsoluteIndexedX), M(ROR,AbsoluteIndexedX), ILLEGAL,
    ILLEGAL,         M(STA,XIndexedIndirect), ILLEGAL,         ILLEGAL, M(STY,ZeroPage),         M(STA,ZeroPage),          M(STX,ZeroPage),         ILLEGAL, N(DEY), ILLEGAL,                 N(TXA),             ILLEGAL, M(STY,Absolute),         M(STA,Absolute),         M(STX,Absolute),         ILLEGAL,
    N(BCC),          M(STA,IndirectYIndexed), ILLEGAL,         ILLEGAL, M(STY,ZeroPageIndexedX), M(STA,ZeroPageIndexedX),  M(STX,ZeroPageIndexedY), ILLEGAL, N(TYA), M(STA,AbsoluteIndexedY), N(TXS),             ILLEGAL, ILLEGAL,                 M(STA,AbsoluteIndexedX), ILLEGAL,                 ILLEGAL,
    M(LDY,Immediate),M(LDA,XIndexedIndirect), M(LDX,Immediate),ILLEGAL, M(LDY,ZeroPage),         M(LDA,ZeroPage),          M(LDX,ZeroPage),         ILLEGAL, N(TAY), M(LDA,Immediate),        N(TAX),             ILLEGAL, M(LDY,Absolute),         M(LDA,Absolute),         M(LDX,Absolute),         ILLEGAL,
    N(BCS),          M(LDA,IndirectYIndexed), ILLEGAL,         ILLEGAL, M(LDY,ZeroPageIndexedX), M(LDA,ZeroPageIndexedX),  M(LDX,ZeroPageIndexedY), ILLEGAL, N(CLV), M(LDA,AbsoluteIndexedY), N(TSX),             ILLEGAL, M(LDY,AbsoluteIndexedX), M(LDA,AbsoluteIndexedX), M(LDX,AbsoluteIndexedY), ILLEGAL,
    M(CPY,Immediate),M(CMP,XIndexedIndirect), ILLEGAL,         ILLEGAL, M(CPY,ZeroPage),         M(CMP,ZeroPage),          M(DEC,ZeroPage),         ILLEGAL, N(INY), M(CMP,Immediate),        N(DEX),             ILLEGAL, M(CPY,Absolute),         M(CMP,Absolute),         M(DEC,Absolute),         ILLEGAL,
    N(BNE),          M(CMP,IndirectYIndexed), ILLEGAL,         ILLEGAL, ILLEGAL,                 M(CMP,ZeroPageIndexedX),  M(DEC,ZeroPageIndexedX), ILLEGAL, N(CLD), M(CMP,AbsoluteIndexedY), ILLEGAL,            ILLEGAL, ILLEGAL,                 M(CMP,AbsoluteIndexedX), M(DEC,AbsoluteIndexedX), ILLEGAL,
    M(CPX,Immediate),M(SBC,XIndexedIndirect), ILLEGAL,         ILLEGAL, M(CPX,ZeroPage),         M(SBC,ZeroPage),          M(INC,ZeroPage),         ILLEGAL, N(INX), M(SBC,Immediate),        N(NOP),             ILLEGAL, M(CPX,Absolute),         M(SBC,Absolute),         M(INC,Absolute),         ILLEGAL,
    N(BEQ),          M(SBC,IndirectYIndexed), ILLEGAL,         ILLEGAL, ILLEGAL,                 M(SBC,ZeroPageIndexedX),  M(INC,ZeroPageIndexedX), ILLEGAL, N(SED), M(SBC,AbsoluteIndexedY), ILLEGAL,            ILLEGAL, ILLEGAL,                 M(SBC,AbsoluteIndexedX), M(INC,AbsoluteIndexedX), ILLEGAL
};

Executor Decode(byte opcode) {
  return kInstructionTable[opcode];
}