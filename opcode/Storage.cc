//
// Created by Michael Peng on 4/25/18.
//

#include "Storage.hh"

#define OPCODE_ASSIGNS(code, flag, condition) \
  NILADIC_OPCODE(code) { cpu.status.flag = (condition); }

#define OPCODE_SETS(code, flag) OPCODE_ASSIGNS(code, flag, true)
#define OPCODE_CLEARS(code, flag) OPCODE_ASSIGNS(code, flag, false)

#define OPCODE_LOADS(code, register_name)  \
  MONADIC_OPCODE(code) {                   \
    cpu.register_name = mode.Read(cpu);    \
    cpu.UpdateFlagsFor(cpu.register_name); \
  }

#define OPCODE_STORES(code, register_name) \
  MONADIC_OPCODE(code) { mode.Write(cpu, cpu.register_name); }

#define OPCODE_TRANSFERS(code, src, dest) \
  NILADIC_OPCODE(code) {                  \
    cpu.dest = cpu.src;                   \
    cpu.UpdateFlagsFor(cpu.dest);         \
  }

OPCODE_SET {

  OPCODE_CLEARS(CLC, carry)
  OPCODE_SETS(SEC, carry)
  OPCODE_CLEARS(CLI, irq_disable)
  OPCODE_SETS(SEI, irq_disable)
  OPCODE_CLEARS(CLV, overflow)
  OPCODE_CLEARS(CLD, decimal_mode)
  OPCODE_SETS(SED, decimal_mode)

  OPCODE_LOADS(LDA, ac)
  OPCODE_LOADS(LDX, x)
  OPCODE_LOADS(LDY, y)

  OPCODE_STORES(STA, ac)
  OPCODE_STORES(STX, x)
  OPCODE_STORES(STY, y)

  OPCODE_TRANSFERS(TAX, ac, x)
  OPCODE_TRANSFERS(TAY, ac, y)
  OPCODE_TRANSFERS(TSX, sp, x)
  OPCODE_TRANSFERS(TXA, x, ac)
  OPCODE_TRANSFERS(TXS, x, sp)
  OPCODE_TRANSFERS(TYA, y, ac)

}  // namespace opcode
