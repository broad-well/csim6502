//
// Created by Michael Peng on 4/25/18.
//

#ifndef CSIM6502_DECODER_HH
#define CSIM6502_DECODER_HH

#include <cstdint>
#include "../types.hh"

// Macros that resolve addressing modes
// ADDR2 => instructions that take 2 bytes (1 byte operand)
// ADDR3 => instructions that take 3 bytes (2 byte, little-endian operand)

#define ADDR2_IMMEDIATE(operand_ptr) (operand_ptr)
#define ADDR2_ACCUMULATOR(cpu) ((cpu)->ac)
#define ADDR2_ZEROPAGE(mem, operand_ptr) ((mem)->PtrTo(*(operand_ptr)))
#define ADDR2_ZEROPAGE_X(cpu, mem, operand_ptr) ((mem)->PtrTo(*(operand_ptr) + (cpu)->x))
#define ADDR2_ZEROPAGE_Y(cpu, mem, operand_ptr) ((mem)->PtrTo(*(operand_ptr) + (cpu)->y))
#define ADDR2_INDIRECT_X(cpu, mem, operand_ptr) ADDR2_ZEROPAGE(mem, ADDR2_ZEROPAGE_X(cpu, mem, operand_ptr))
//#define ADDR2_INDIRECT_Y(cpu, mem, operand_ptr) ((mem)->Read(*(operand_ptr)) + (cpu)->y)

class OpcodeHandler {

};

class Decoder {
};


#endif //CSIM6502_DECODER_HH
