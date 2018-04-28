//
// Created by Michael Peng on 4/28/18.
//

#include <gtest/gtest.h>
#include "MockRAM.hh"

MockRAM ram {
  0x14, 0xd2, 0xa2, 0x5f, 0xe1, 0xbb, 0xae, 0x5d
};

TEST(MockRAM, Persistence) {
  ram.Write(0xf2, 0x13);
  ASSERT_EQ(ram.Read(0xf2), 0x13);
}