//
// Created by Michael Peng on 4/25/18.
//

#include "Decoder.hh"
#include <functional>
#include <memory>

using namespace opcode;
using namespace address;

#define M(code, mode) std::make_shared<MonadicExecutor>(code, mode())
#define N(code) std::make_shared<NiladicExecutor>(code)
#define ILLEGAL N(Illegal)

static const std::shared_ptr<Executor> kInstructionTable[] {
    // 0          1            2            3        4            5           6            7        8       9             A             B        C           D            E            F
    N(BRK),       M(ORA,XInd), ILLEGAL,     ILLEGAL, ILLEGAL,     M(ORA,Zpg), M(ASL,Zpg),  ILLEGAL, N(PHP), M(ORA,Immed), M(ASL,Accum), ILLEGAL, ILLEGAL,    M(ORA,Abs),  M(ASL,Abs),  ILLEGAL,
    N(BPL),       M(ORA,IndY), ILLEGAL,     ILLEGAL, ILLEGAL,     M(ORA,ZpgX),M(ASL,ZpgX), ILLEGAL, N(CLC), M(ORA,AbsY),  ILLEGAL,      ILLEGAL, ILLEGAL,    M(ORA,AbsX), M(ASL,AbsX), ILLEGAL,
    N(JSR),       M(AND,XInd), ILLEGAL,     ILLEGAL, M(BIT,Zpg),  M(AND,Zpg), M(ROL,Zpg),  ILLEGAL, N(PLP), M(AND,Immed), M(ROL,Accum), ILLEGAL, M(BIT,Abs), M(AND,Abs),  M(ROL,Abs),  ILLEGAL,
    N(BMI),       M(AND,IndY), ILLEGAL,     ILLEGAL, ILLEGAL,     M(AND,ZpgX),M(ROL,ZpgX), ILLEGAL, N(SEC), M(AND,AbsY),  ILLEGAL,      ILLEGAL, ILLEGAL,    M(AND,AbsX), M(ROL,AbsX), ILLEGAL,
    N(RTI),       M(EOR,XInd), ILLEGAL,     ILLEGAL, ILLEGAL,     M(EOR,Zpg), M(LSR,Zpg),  ILLEGAL, N(PHA), M(EOR,Immed), M(LSR,Accum), ILLEGAL, N(JMP_Abs), M(EOR,Abs),  M(LSR,Abs),  ILLEGAL,
    N(BVC),       M(EOR,IndY), ILLEGAL,     ILLEGAL, ILLEGAL,     M(EOR,ZpgX),M(LSR,ZpgX), ILLEGAL, N(CLI), M(EOR,AbsY),  ILLEGAL,      ILLEGAL, ILLEGAL,    M(EOR,AbsX), M(LSR,AbsX), ILLEGAL,
    N(RTS),       M(ADC,XInd), ILLEGAL,     ILLEGAL, ILLEGAL,     M(ADC,Zpg), M(ROR,Zpg),  ILLEGAL, N(PLA), M(ADC,Immed), M(ROR,Accum), ILLEGAL, N(JMP_Ind), M(ADC,Abs),  M(ROR,Abs),  ILLEGAL,
    N(BVS),       M(ADC,IndY), ILLEGAL,     ILLEGAL, ILLEGAL,     M(ADC,ZpgX),M(ROR,ZpgX), ILLEGAL, N(SEI), M(ADC,AbsY),  ILLEGAL,      ILLEGAL, ILLEGAL,    M(ADC,AbsX), M(ROR,AbsX), ILLEGAL,
    ILLEGAL,      M(STA,XInd), ILLEGAL,     ILLEGAL, M(STY,Zpg),  M(STA,Zpg), M(STX,Zpg),  ILLEGAL, N(DEY), ILLEGAL,      N(TXA),       ILLEGAL, M(STY,Abs), M(STA,Abs),  M(STX,Abs),  ILLEGAL,
    N(BCC),       M(STA,IndY), ILLEGAL,     ILLEGAL, M(STY,ZpgX), M(STA,ZpgX),M(STX,ZpgY), ILLEGAL, N(TYA), M(STA,AbsY),  N(TXS),       ILLEGAL, ILLEGAL,    M(STA,AbsX), ILLEGAL,     ILLEGAL,
    M(LDY,Immed), M(LDA,XInd), M(LDX,Immed),ILLEGAL, M(LDY,Zpg),  M(LDA,Zpg), M(LDX,Zpg),  ILLEGAL, N(TAY), M(LDA,Immed), N(TAX),       ILLEGAL, M(LDY,Abs), M(LDA,Abs),  M(LDX,Abs),  ILLEGAL,
    N(BCS),       M(LDA,IndY), ILLEGAL,     ILLEGAL, M(LDY,ZpgX), M(LDA,ZpgX),M(LDX,ZpgY), ILLEGAL, N(CLV), M(LDA,AbsY),  N(TSX),       ILLEGAL, M(LDY,AbsX),M(LDA,AbsX), M(LDX,AbsY), ILLEGAL,
    M(CPY,Immed), M(CMP,XInd), ILLEGAL,     ILLEGAL, M(CPY,Zpg),  M(CMP,Zpg), M(DEC,Zpg),  ILLEGAL, N(INY), M(CMP,Immed), N(DEX),       ILLEGAL, M(CPY,Abs), M(CMP,Abs),  M(DEC,Abs),  ILLEGAL,
    N(BNE),       M(CMP,IndY), ILLEGAL,     ILLEGAL, ILLEGAL,     M(CMP,ZpgX),M(DEC,ZpgX), ILLEGAL, N(CLD), M(CMP,AbsY),  ILLEGAL,      ILLEGAL, ILLEGAL,    M(CMP,AbsX), M(DEC,AbsX), ILLEGAL,
    M(CPX,Immed), M(SBC,XInd), ILLEGAL,     ILLEGAL, M(CPX,Zpg),  M(SBC,Zpg), M(INC,Zpg),  ILLEGAL, N(INX), M(SBC,Immed), N(NOP),       ILLEGAL, M(CPX,Abs), M(SBC,Abs),  M(INC,Abs),  ILLEGAL,
    N(BEQ),       M(SBC,IndY), ILLEGAL,     ILLEGAL, ILLEGAL,     M(SBC,ZpgX),M(INC,ZpgX), ILLEGAL, N(SED), M(SBC,AbsY),  ILLEGAL,      ILLEGAL, ILLEGAL,    M(SBC,AbsX), M(INC,AbsX), ILLEGAL
};

const std::shared_ptr<Executor> Decode(byte opcode) {
  return kInstructionTable[opcode];
}