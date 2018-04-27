//
// Created by Michael Peng on 4/26/18.
//

#include <gtest/gtest.h>
#include "../FormatUtil.hh"

using namespace format;

TEST(FormatUtil, PaddedHex) {
  ASSERT_EQ(AsPaddedHex(128), "80");
  ASSERT_EQ(AsPaddedHex(4), "04");
  ASSERT_EQ(AsPaddedHex(76), "4c");
}

TEST(FormatUtil, CustomWidthPaddedHex) {
  ASSERT_EQ(AsPaddedHex(53, 5), "00035");
  ASSERT_EQ(AsPaddedHex(94, 8), "0000005e");
}