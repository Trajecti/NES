#ifndef __BRANCH_INSTRUCTION_H_
#define __BRANCH_INSTRUCTION_H_

#include "instruction.hpp"

class BranchInstruction: public Instruction {
  public:
    using Instruction::Instruction;
  protected:
    void count_cycles();
    int get_branch_target();
};

class BCCInstruction: public BranchInstruction {
  private:
  public:
    using BranchInstruction::BranchInstruction;
    int execute();
};

class BCSInstruction: public BranchInstruction {
  private:
  public:
    using BranchInstruction::BranchInstruction;
    int execute();
};

class BEQInstruction: public BranchInstruction {
  private:
  public:
    using BranchInstruction::BranchInstruction;
    int execute();
};

class BMIInstruction: public BranchInstruction {
  private:
  public:
    using BranchInstruction::BranchInstruction;
    int execute();
};

class BNEInstruction: public BranchInstruction {
  private:
  public:
    using BranchInstruction::BranchInstruction;
    int execute();
};

class BPLInstruction: public BranchInstruction {
  private:
  public:
    using BranchInstruction::BranchInstruction;
    int execute();
};

class BVCInstruction: public BranchInstruction {
  private:
  public:
    using BranchInstruction::BranchInstruction;
    int execute();
};

class BVSInstruction: public BranchInstruction {
  private:
  public:
    using BranchInstruction::BranchInstruction;
    int execute();
};

#endif // __BRANCH_INSTRUCTION_H_
