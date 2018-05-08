//
// Created by Michael Peng on 5/2/18.
//

#ifndef CSIM6502_EXECUTOR_HH
#define CSIM6502_EXECUTOR_HH

#include "../types.hh"
#include "AddressingModes.hh"
#include <functional>

struct Executor {
  virtual ~Executor() = default;

  virtual void Call(CPU &) = 0;
};

struct NiladicExecutor : public Executor {
  void (*function)(CPU &cpu);

  explicit NiladicExecutor(void (*function)(CPU &)) : function(function) {}

  void Call(CPU &cpu) override {
    function(cpu);
  }
};

struct MonadicExecutor : public Executor {
  void (*function)(CPU &, const AddressingMode &);
  const AddressingMode *mode;

  MonadicExecutor(void (*function)(CPU &, const AddressingMode &), const AddressingMode *mode)
      : function(function), mode(mode) {}

  void Call(CPU &cpu) override {
    function(cpu, *mode);
  }
};

#define OPCODE_SET namespace opcode
#define NILADIC_OPCODE(name) void name(CPU& cpu)
#define STATIC_OPCODE(name) void name(CPU&)
#define MONADIC_OPCODE(name) void name(CPU& cpu, const AddressingMode& mode)

#endif //CSIM6502_EXECUTOR_HH
