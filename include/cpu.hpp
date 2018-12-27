#ifndef __CPU_H_
#define __CPU_H_

#include <memory>
#include <bitset>

struct cpu_state
/*
 * MOS 6502 emulator CPU state
 * PC: Program Counter
 * AC: Accumulator
 * X: X register
 * Y: Y register
 * status: Status Register
 * sp: Stack Pointer
  */
{
    int pc: 16 = 0;
    unsigned int ac = 0;
    unsigned int x = 0;
    unsigned int y = 0;
    std::bitset<8> status;
    enum SR: unsigned int {NEGATIVE_BIT, OVERFLOW_BIT, IGNORE_BIT, BREAK_BIT, DECIMAL_BIT, INTERRUPT_BIT, ZERO_BIT, CARRY_BIT};
    unsigned int sp: 8 = 0xFF;
    char memory[256][256];
    char stack[256];
};

class CPU {
  private:
    std::shared_ptr<cpu_state> state;
  public:
    int execute();
    CPU() noexcept;
    ~CPU() noexcept;
};

#endif // __CPU_H_
