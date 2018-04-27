//
// Created by Michael Peng on 4/26/18.
//

#include "gtest/gtest.h"

#include "../Bitset.hh"

TEST(Bitset, ReadBit) {
  Bitset bitset(0b10001001);

  ASSERT_TRUE(bitset.IsSet(0));
  ASSERT_TRUE(bitset.IsSet(3));
  ASSERT_TRUE(bitset.IsSet(7));
  ASSERT_TRUE(bitset.IsCleared(1));
  ASSERT_TRUE(bitset.IsCleared(4));
}

TEST(Bitset, WriteBit) {
  Bitset bitset(0b00101011);

  bitset.Set(2);
  bitset.Clear(1);
  bitset.Change(5, false);

  ASSERT_EQ(bitset.Data(), 0b00001101);
}

TEST(Bitset, OutOfRangeAccess) {
  Bitset bitset;

  ASSERT_THROW(bitset.Set(8), std::out_of_range);
  ASSERT_THROW(bitset.Clear(10), std::out_of_range);
  ASSERT_THROW(bitset.IsSet(9), std::out_of_range);
  ASSERT_THROW(bitset.IsCleared(15), std::out_of_range);
}