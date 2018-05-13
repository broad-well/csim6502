//
// Created by Michael Peng on 4/25/18.
//

#include "Stack.hh"

namespace opcode {

NILADIC_OPCODE(PHA) { cpu.PushByteToStack(cpu.ac); }
NILADIC_OPCODE(PLA) { cpu.ac = cpu.PullByteFromStack(); }

NILADIC_OPCODE(PHP) { cpu.PushByteToStack(cpu.status.ToByte()); }
NILADIC_OPCODE(PLP) { cpu.status.LoadFromByte(cpu.PullByteFromStack()); }

}  // namespace opcode
