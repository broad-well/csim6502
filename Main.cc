//
// Created by Michael Peng on 5/6/18.
//

#include <chrono>
#include <csignal>
#include <fstream>
#include <iostream>
#include "CPU.hh"
#include "HeapRAM.hh"
#include "opcode/Decoder.hh"

using namespace std;

constexpr int kMemorySize = 65536;

static HeapRAM memory(kMemorySize);
static CPU cpu(&memory);

// Speed measuring
static auto start_time = chrono::high_resolution_clock::now();
static unsigned long long cycle_count(0);

struct ConsoleHook : public Hook {
  ConsoleHook() = default;

  bool ShouldAddressAccessRedirect(word address) const override {
    return address == 0xFACE || address == 0xDEAD;
  }

  byte OnRead(RAM &, word) const override { return 0x00; }
  void OnWrite(RAM &, word address, byte value) const override {
    if (address == 0xDEAD)
      cout << static_cast<int>(value);
    else
      cout << value;
  }
};

void AddConsoleRAMHook() { memory.AddHook(new ConsoleHook()); }

double NsPerCycle() {
  auto now = chrono::high_resolution_clock::now();
  return chrono::duration<double, nano>(now - start_time).count() / cycle_count;
}

[[noreturn]]
void BreakAndAbort(int) {
  cout << "USER BREAK" << endl;
  cpu.DumpRegisterInfo(cout);

  auto ns(NsPerCycle());
  cout << endl
       << "Ns per cycle = " << ns << " -> " << 1 / ns * 1e3
       << " MHz. CPU halted. Exiting." << endl;
  exit(0);
}

void LoadMemoryFromFile(char *const *argv) {
  ifstream input(argv[1], ios::binary);

  byte input_buffer[kMemorySize];
  byte ptr = 0;
  while (!input.eof()) {
    input_buffer[ptr++] = static_cast<byte>(input.get());
  }

  memory.Load(input_buffer);
}

int main(int argc, char *argv[]) {
  using namespace std;

  signal(SIGINT, BreakAndAbort);
  AddConsoleRAMHook();

  if (argc == 1) {
    cout << "Usage: " << argv[0] << " <file>" << endl;
    exit(1);
  }

  LoadMemoryFromFile(argv);
  memory.WriteWord(0xfffe, 0x0000);

  cpu.Reset();

  while (true) {
    auto opcode = cpu.NextCodeByte();

    auto executor = Decode(opcode);

    executor->Call(cpu);

    cycle_count++;
  }
}
