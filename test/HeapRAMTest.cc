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

  ram.Write(0xa, 'c');
  ram.Write(0xb, 'a');
  ram.Write(0xc, 'r');

  ASSERT_EQ(ram.Read(0xa), 'c');
  ASSERT_EQ(ram.Read(0xb), 'a');
  ASSERT_EQ(ram.Read(0xc), 'r');
}

TEST(HeapRAM, AccessOutOfRange) {
  HeapRAM ram(0x10);

  ASSERT_THROW(ram.PtrTo(0x10), std::out_of_range);
  ASSERT_THROW(ram.Read(0x11), std::out_of_range);
  ASSERT_THROW(ram.Write(0x12, 2), std::out_of_range);
}

TEST(HeapRAM, ReadWord) {
  byte data[] {
    0x03, 0x15, 0xaf, 0x4d, 0xb3, 0x9e
  };
  HeapRAM ram(data, 6);

  ASSERT_EQ(ram.ReadWord(0x00), 0x1503);
  ASSERT_EQ(ram.ReadWord(0x04), 0x9eb3);
  ASSERT_THROW(ram.ReadWord(0x05), std::out_of_range);
}

TEST(HeapRAM, PtrToIndirectTarget) {
  byte data[] {
      0x4a, 0xa3, 0x81, 0x02, 0x00, 0x00, 0x04
  };
  HeapRAM ram(data, 7);

  ASSERT_EQ(ram.PtrToIndirectTarget(0x03), ram.PtrTo(0x02));
  ASSERT_EQ(ram.PtrToIndirectTarget(0x04), ram.PtrTo(0x00));
  ASSERT_THROW(ram.PtrToIndirectTarget(0x05), std::out_of_range);
  ASSERT_THROW(ram.PtrToIndirectTarget(0x06), std::out_of_range);
}
