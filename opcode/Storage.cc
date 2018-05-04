//
// Created by Michael Peng on 4/25/18.
//

#include "Storage.hh"

#define OPCODE_ASSIGNS(code, flag, condition) NILADIC_OPCODE(code) { \
  cpu.status.flag = (condition); \
}
#define OPCODE_SETS(code, flag) OPCODE_ASSIGNS(code, flag, true)
#define OPCODE_CLEARS(code, flag) OPCODE_ASSIGNS(code, flag, false)

namespace opcode {

OPCODE_CLEARS(CLC, carry);
OPCODE_SETS(SEC, carry);
OPCODE_CLEARS(CLI, irq_disable);
OPCODE_SETS(SEI, irq_disable);
OPCODE_CLEARS(CLV, overflow);
OPCODE_CLEARS(CLD, decimal_mode);
OPCODE_SETS(SED, decimal_mode);

}
