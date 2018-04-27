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

TEST(Util, PositiveToSigned) {
  ASSERT_EQ(ToSigned(127), 127);
  ASSERT_EQ(ToSigned(31), 31);
}

TEST(Util, ZeroToSigned) {
  ASSERT_EQ(ToSigned(0), 0);
}

TEST(Util, NegativeToSigned) {
  ASSERT_EQ(ToSigned(0b11110111), -9);
}