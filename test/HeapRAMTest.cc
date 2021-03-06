//
// Created by Michael Peng on 4/26/18.
//

#include <gtest/gtest.h>
#include "HeapRAM.hh"

TEST(HeapRAM, ReadInRange) {
  constexpr auto data = "Read my RAM";
  HeapRAM ram(reinterpret_cast<const byte*>(data), strlen(data));

  ASSERT_EQ(ram.Read(0x00), 'R');
  ASSERT_EQ(ram.Read(0x01), 'e');
  ASSERT_EQ(ram.Read(0x05), 'm');
  ASSERT_EQ(ram.Read(0x0a), 'M');
}

TEST(HeapRAM, WriteInRange) {
  auto data = "Change my RAM";
  HeapRAM ram(strlen(data));
  ram.Load(reinterpret_cast<const byte*>(data));

  ram.Write(0xa, 'c');
  ram.Write(0xb, 'a');
  ram.Write(0xc, 'r');

  ASSERT_EQ(ram.Read(0xa), 'c');
  ASSERT_EQ(ram.Read(0xb), 'a');
  ASSERT_EQ(ram.Read(0xc), 'r');
}

TEST(HeapRAM, AccessOutOfRange) {
  HeapRAM ram(0x10);

  ASSERT_THROW(ram.Read(0x11), std::out_of_range);
  ASSERT_THROW(ram.Write(0x10, 2), std::out_of_range);
}

TEST(HeapRAM, ReadWord) {
  byte data[]{0x03, 0x15, 0xaf, 0x4d, 0xb3, 0x9e};
  HeapRAM ram(data, 6);

  ASSERT_EQ(ram.ReadWord(0x00), 0x1503);
  ASSERT_EQ(ram.ReadWord(0x04), 0x9eb3);
  ASSERT_THROW(ram.ReadWord(0x05), std::out_of_range);
}

TEST(HeapRAM, WriteWord) {
  byte data[]{0x41, 0x13, 0xfc, 0xb4};
  HeapRAM ram(4);
  ram.Load(data);

  ram.WriteWord(0x00, 0x4dac);
  ASSERT_EQ(ram.ReadWord(0x00), 0x4dac);
  ASSERT_EQ(ram.Read(0x01), 0x4d);
  ASSERT_EQ(ram.Read(0x00), 0xac);
}
