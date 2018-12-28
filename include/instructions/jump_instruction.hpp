#ifndef __JUMP_INSTRUCTION_H_
#define __JUMP_INSTRUCTION_H_

#include "instruction.hpp"

class JumpInstruction: public Instruction {
  protected:
    void count_cycles();
  public:
    using Instruction::Instruction;
    int get_memory_value();
};

class JMPInstruction: public JumpInstruction {
  private:
  public:
    using JumpInstruction::JumpInstruction;
    int execute();
};

class JSRInstruction: public JumpInstruction {
  private:
  public:
    using JumpInstruction::JumpInstruction;
    int execute();
};

#endif // __JUMP_INSTRUCTION_H_
