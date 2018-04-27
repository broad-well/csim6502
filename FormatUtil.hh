//
// Created by Michael Peng on 4/26/18.
//

#ifndef CSIM6502_FORMATUTIL_HH
#define CSIM6502_FORMATUTIL_HH

#include <string>
#include <cstdint>
#include <sstream>

namespace format {

  inline std::string AsPaddedHex(const unsigned &value, const std::uint8_t pad = 2) {
    using namespace std;

    stringstream sstream;
    sstream << setfill('0') << setw(pad) << hex << value;
    return sstream.str();
  }

}

#endif //CSIM6502_FORMATUTIL_HH
