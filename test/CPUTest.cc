//
// Created by michael on 4/26/18.
//

#include <gtest/gtest.h>
#include "../CPU.hh"

HeapRAM ram(0x10000);
CPU cpu(&ram);

TEST(CPU, MemoryPtr) {
  ASSERT_EQ(cpu.MemoryPtrTo(0x02), ram.PtrTo(0x02));
  ASSERT_EQ(cpu.MemoryPtrTo(0x05, 0x02), ram.PtrTo(0x05, 0x02));
}

TEST(CPU, UpdateFlagsForNegative) {
  cpu.UpdateFlagsFor(0b10001000);

  ASSERT_TRUE(cpu.status.IsCleared(ZERO_RESULT));
  ASSERT_TRUE(cpu.status.IsSet(NEGATIVE_RESULT));
}

TEST(CPU, UpdateFlagsForZero) {
  cpu.UpdateFlagsFor(0);

  ASSERT_TRUE(cpu.status.IsSet(ZERO_RESULT));
  ASSERT_TRUE(cpu.status.IsCleared(NEGATIVE_RESULT));
}

TEST(CPU, UpdateFlagsForPositive) {
  cpu.UpdateFlagsFor(0b00111010);

  ASSERT_TRUE(cpu.status.IsCleared(ZERO_RESULT));
  ASSERT_TRUE(cpu.status.IsCleared(NEGATIVE_RESULT));
}