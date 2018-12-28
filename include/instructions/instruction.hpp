#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "../cpu.hpp"

const int MAX_INT = 256;
const int MIN_SIGNED_INT = -128;

enum addressing_mode {zero_page, immediate, absolute, accumulator, indirect, implied,
                      zero_page_y, zero_page_x, absolute_x, absolute_y, indirect_x_indexed, indirect_y_indexed, relative};
class Instruction {
  protected:
    std::shared_ptr<cpu_state> state;
    addressing_mode mode;
    int cycles;
    int memory_byte;
    int page_offset;
    int page_number;
    void get_memory_value_and_address();
    virtual void count_cycles() = 0;
    virtual int execute() = 0;
  public:
    explicit Instruction(addressing_mode mode, std::shared_ptr<cpu_state> state);
    int execute_instruction();
};

class MiscInstruction: public Instruction {
  protected:
    void count_cycles();
  public:
    using Instruction::Instruction;
};

class BITInstruction: public MiscInstruction {
  private:
  public:
    using MiscInstruction::MiscInstruction;
    int execute();
};

class CPXInstruction: public MiscInstruction {
  private:
  public:
    using MiscInstruction::MiscInstruction;
    int execute();
};

class CPYInstruction: public MiscInstruction {
  private:
  public:
    using MiscInstruction::MiscInstruction;
    int execute();
};

class DECInstruction: public MiscInstruction {
  private:
  public:
    using MiscInstruction::MiscInstruction;
    int execute();
};

class INCInstruction: public MiscInstruction {
  private:
  public:
    using MiscInstruction::MiscInstruction;
    int execute();
};

class LDXInstruction: public MiscInstruction {
  private:
  public:
    using MiscInstruction::MiscInstruction;
    int execute();
};

class LDYInstruction: public MiscInstruction {
  private:
  public:
    using MiscInstruction::MiscInstruction;
    int execute();
};

class STXInstruction: public MiscInstruction {
  private:
  public:
    using MiscInstruction::MiscInstruction;
    int execute();
};

class STYInstruction: public MiscInstruction {
  private:
  public:
    using MiscInstruction::MiscInstruction;
    int execute();
};

#endif // __INSTRUCTION_H_
