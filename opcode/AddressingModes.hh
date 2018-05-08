//
// Created by Michael Peng on 5/2/18.
//

#ifndef CSIM6502_ADDRESSINGMODES_HH
#define CSIM6502_ADDRESSINGMODES_HH

#include <functional>
#include <exception>
#include <stdexcept>
#include "../CPU.hh"
#include "../types.hh"
#include "../Util.hh"

struct AddressingMode {
  byte (*Read)(CPU &);
  void (*Write)(CPU &, byte);
  void (*Modify)(CPU &, const std::function<byte(byte)> &);
};

namespace address {

extern AddressingMode
    Abs, AbsX, AbsY,
    Zpg, ZpgX, ZpgY, Ind, XInd, IndY, Immed, Accum;

}
#endif //CSIM6502_ADDRESSINGMODES_HH
