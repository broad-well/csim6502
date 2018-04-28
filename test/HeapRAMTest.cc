//
// Created by Michael Peng on 4/26/18.
//

#include <gtest/gtest.h>
#include "../RAM.hh"

TEST(HeapRAM, PtrInRange)
{
  HeapRAM ram(0x100);
  ASSERT_EQ(ram.PtrTo(0x00), ram.PtrTo(0x01) - 1*sizeof(byte));
}

TEST(HeapRAM, ReadInRange)
{
  constexpr auto data = "Read my RAM";
  HeapRAM ram((byte*)data, strlen(data));

  ASSERT_EQ(ram.Read(0x00), 'R');
  ASSERT_EQ(ram.Read(0x01), 'e');
  ASSERT_EQ(ram.Read(0x05), 'm');
  ASSERT_EQ(ram.Read(0x0a), 'M');
}

TEST(HeapRAM, WriteInRange)
{
  auto data = "Change my RAM";
  HeapRAM ram((byte*) data, strlen(data));

  ram.Write('c', 0xa);
  ram.Write('a', 0xb);
  ram.Write('r', 0xc);

  ASSERT_EQ(ram.Read(0xa), 'c');
  ASSERT_EQ(ram.Read(0xb), 'a');
  ASSERT_EQ(ram.Read(0xc), 'r');
}

TEST(HeapRAM, AccessOutOfRange) {
  HeapRAM ram(0x10);

  ASSERT_THROW(ram.PtrTo(0x10), std::out_of_range);
  ASSERT_THROW(ram.Read(0x11), std::out_of_range);
  ASSERT_THROW(ram.Write(2, 0x12), std::out_of_range);
}
