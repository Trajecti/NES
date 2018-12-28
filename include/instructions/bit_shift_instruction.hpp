#ifndef __BIT_SHIFT_INSTRUCTION_H_
#define __BIT_SHIFT_INSTRUCTION_H_

#include "instruction.hpp"

class BitShiftInstruction: public Instruction {
  public:
    using Instruction::Instruction;
  protected:
    void count_cycles();
};

class ASLInstruction: public BitShiftInstruction{
  private:
  public:
    using BitShiftInstruction::BitShiftInstruction;
    int execute();
};

class LSRInstruction: public BitShiftInstruction{
  private:
  public:
    using BitShiftInstruction::BitShiftInstruction;
    int execute();
};

class ROLInstruction: public BitShiftInstruction{
  private:
  public:
    using BitShiftInstruction::BitShiftInstruction;
    int execute();
};

class RORInstruction: public BitShiftInstruction{
  private:
  public:
    using BitShiftInstruction::BitShiftInstruction;
    int execute();
};


#endif // __BIT_SHIFT_INSTRUCTION_H_
