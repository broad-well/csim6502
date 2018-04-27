//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_FORMATUTIL_HH
#define CSIM6502_FORMATUTIL_HH

#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include "types.hh"

namespace format {

  inline std::string AsPaddedHex(const unsigned &value, const std::uint8_t pad = 2) {
    using namespace std;

    stringstream sstream;
    sstream << setfill('0') << setw(pad) << hex << value;
    return sstream.str();
  }

}

namespace bit {
  inline uint16_t AsWord(const byte low, const byte high = 0) {
    return (high << 8U) + low;
  }

  inline uint8_t LowByte(const word input) {
    return static_cast<uint8_t>(input & 0x00ffU);
  }
  inline uint8_t HighByte(const word input) {
    return static_cast<uint8_t>(input >> 8U);
  }
}
#endif //CSIM6502_FORMATUTIL_HH
