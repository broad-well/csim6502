//
// Created by Michael Peng on 4/26/18.
//

#include <gtest/gtest.h>
#include "../Util.hh"

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