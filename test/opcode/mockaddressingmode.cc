#include "MockAddressingMode.hh"
#include "types.hh"

static byte data;

byte GetData(CPU&) {
  return data;
}

void SetData(CPU&, byte new_value) {
  data = new_value;
}

void ModifyData(CPU&, const std::function<byte(byte)>& mutator) {
  data = mutator(data);
}

AddressingMode kMockAddressMode {
  GetData, SetData, ModifyData
};

void SetMockAddressValue(const byte value) {
  data = value;
}
byte MockAddressValue() {
  return data;
}
