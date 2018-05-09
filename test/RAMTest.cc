//
// Created by Michael Peng on 4/30/18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MockRAM.hh"
#include "RAM.hh"
#include "types.hh"

using namespace ::testing;

static MockRAM ram {
  0x4f, 0x1d, 0xe3, 0xb5, 0x4e, 0xfa, 0xa1, 0xfe
};

constexpr word kAddressRangeMin = 0x05;
constexpr word kAddressRangeMax = 0x07;

class MockHook : public Hook {
  public:

  bool ShouldAddressAccessRedirect(word address) const override {
    return address >= kAddressRangeMin && address <= kAddressRangeMax;
  }

  MOCK_CONST_METHOD2(OnRead, byte(RAM& caller, word address));
  MOCK_CONST_METHOD3(OnWrite, void(RAM& caller, word address, byte value));
};

class TransparentHook : public Hook {
  public:

  bool ShouldAddressAccessRedirect(word address) const override {
    return address >= kAddressRangeMin && address <= kAddressRangeMax;
  }
  byte OnRead(RAM& caller, word address) const override {
    return loadFrom(caller, address);
  }
  void OnWrite(RAM& caller, word address, byte value) const override {
    storeTo(caller, address, value);
  }
};

TEST(RAM, HookRedirection) {
  auto hook = new StrictMock<MockHook>;
  ram.AddHook(hook);

  EXPECT_CALL(*hook, OnRead(Ref(ram), 0x05)).WillRepeatedly(Return(0x99));
  EXPECT_CALL(*hook, OnWrite(Ref(ram), 0x06, 0x14));

  ram.Read(0x05);
  ram.Write(0x06, 0x14);

  ram.ClearHooks();
}

TEST(RAM, HookOverride) {
  auto hook = new StrictMock<MockHook>;
  ram.AddHook(hook);

  EXPECT_CALL(*hook, OnRead(Ref(ram), _)).WillRepeatedly(Return(0x01));
  EXPECT_CALL(*hook, OnWrite(Ref(ram), _, _));

  ASSERT_EQ(ram.Read(0x07), 0x01);
  ram.Write(0x05, 0x41);

  ram.ClearHooks();
  ASSERT_EQ(ram.Read(0x05), 0xfa);
  ASSERT_EQ(ram.Read(0x07), 0xfe);
}

TEST(RAM, DirectStoreLoad) {
  auto hook = new TransparentHook;
  ram.AddHook(hook);

  ram.Write(0x02, 0x04);
  ASSERT_EQ(ram.Read(0x02), 0x04);
  ASSERT_EQ(ram.Read(0x04), 0x4e);
}
