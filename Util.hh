//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_FORMATUTIL_HH
#define CSIM6502_FORMATUTIL_HH

#include <string>
#include <cstdint>
#include <sstream>
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
  signed_byte ToSigned(const byte& unsigned_byte) {

    bool is_positive = unsigned_byte < 0b10000000;
    const byte without_sign = static_cast<const byte>(unsigned_byte & 0b01111111);

    return (signed_byte) (is_positive ?
                          without_sign : without_sign - 128);

  }
}

#endif //CSIM6502_FORMATUTIL_HH
