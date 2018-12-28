#ifndef __SINGLE_BYTE_INSTRUCTION_H_
#define __SINGLE_BYTE_INSTRUCTION_H_

#include "instruction.hpp"

class SingleByteInstruction: public Instruction {
  protected:
    void count_cycles();
  public:
    using Instruction::Instruction;
};

class BRKInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class CLCInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class CLDInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class CLIInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class CLVInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class DEXInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class DEYInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class INXInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class INYInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class NOPInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class PHAInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class PHPInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class PLAInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class PLPInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class RTIInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class RTSInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class SECInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class SEDInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class SEIInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class TAXInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class TAYInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class TSXInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class TXAInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class TXSInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

class TYAInstruction: public SingleByteInstruction {
  private:
  public:
    using SingleByteInstruction::SingleByteInstruction;
    int execute();
};

#endif // __SINGLE_BYTE_INSTRUCTION_H_
