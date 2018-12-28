#ifndef __FULL_ADDRESSING_MODE_INSTRUCTION_H_
#define __FULL_ADDRESSING_MODE_INSTRUCTION_H_

#include "instruction.hpp"

class FullAddressingModeInstruction: public Instruction {
  public:
    using Instruction::Instruction;
  protected:
    void count_cycles();
};

class ADCInstruction: public FullAddressingModeInstruction {
  private:
  public:
    using FullAddressingModeInstruction::FullAddressingModeInstruction;
    int execute();
};

class ANDInstruction: public FullAddressingModeInstruction {
  private:
  public:
    using FullAddressingModeInstruction::FullAddressingModeInstruction;
    int execute();
};

class CMPInstruction: public FullAddressingModeInstruction {
  private:
  public:
    using FullAddressingModeInstruction::FullAddressingModeInstruction;
    int execute();
};

class EORInstruction: public FullAddressingModeInstruction {
  private:
  public:
    using FullAddressingModeInstruction::FullAddressingModeInstruction;
    int execute();
};

class LDAInstruction: public FullAddressingModeInstruction {
  private:
  public:
    using FullAddressingModeInstruction::FullAddressingModeInstruction;
    int execute();
};

class ORAInstruction: public FullAddressingModeInstruction {
  private:
  public:
    using FullAddressingModeInstruction::FullAddressingModeInstruction;
    int execute();
};

class SBCInstruction: public FullAddressingModeInstruction {
  private:
  public:
    using FullAddressingModeInstruction::FullAddressingModeInstruction;
    int execute();
};

class STAInstruction: public FullAddressingModeInstruction {
  private:
  public:
    using FullAddressingModeInstruction::FullAddressingModeInstruction;
    int execute();
};

#endif // __FULL_ADDRESSING_MODE_INSTRUCTION_H_
