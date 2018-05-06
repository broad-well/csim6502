//
// Created by Michael Peng on 4/26/18.
//

#include <gtest/gtest.h>
#include "Util.hh"

using namespace format;
using namespace bit;

TEST(Util, PaddedHex) {
  ASSERT_EQ(AsPaddedHex(128), "80");
  ASSERT_EQ(AsPaddedHex(4), "04");
  ASSERT_EQ(AsPaddedHex(76), "4c");
}

TEST(Util, CustomWidthPaddedHex) {
  ASSERT_EQ(AsPaddedHex(53, 5), "00035");
  ASSERT_EQ(AsPaddedHex(94, 8), "0000005e");
}

TEST(Bit, BytesToWord) {
  ASSERT_EQ(AsWord(0x4d), 0x4d);
  ASSERT_EQ(AsWord(0x91), 0x91);
  ASSERT_EQ(AsWord(0x16, 0xfb), 0xfb16);
  ASSERT_EQ(AsWord(0x00, 0xeb), 0xeb00);
}

TEST(Bit, WordToBytes) {
  ASSERT_EQ(LowByte(0x4adc), 0xdc);
  ASSERT_EQ(LowByte(0xface), 0xce);
  ASSERT_EQ(LowByte(0x0a10), 0x10);
  ASSERT_EQ(HighByte(0xf2a6), 0xf2);
  ASSERT_EQ(HighByte(0x01c3), 0x01);
  ASSERT_EQ(HighByte(0x8081), 0x80);
}

TEST(Bit, NthBit) {
  ASSERT_TRUE(IsNthBitSet(0b10101110, 3));
  ASSERT_TRUE(IsNthBitSet(0b11001000, 6));
  ASSERT_FALSE(IsNthBitSet(0b01100010, 0));
}