#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "cpu.hpp"

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
    Instruction(addressing_mode mode, std::shared_ptr<cpu_state> state);
    int execute_instruction();
};

class FullAddressingModeInstruction: public Instruction {
  protected:
    void count_cycles();
};

class ADCInstruction: FullAddressingModeInstruction {
  private:
  public:
    int execute();
};

class ANDInstruction: FullAddressingModeInstruction {
  private:
  public:
    int execute();
};

class CMPInstruction: FullAddressingModeInstruction {
  private:
  public:
    int execute();
};

class EORInstruction: FullAddressingModeInstruction {
  private:
  public:
    int execute();
};

class LDAInstruction: FullAddressingModeInstruction {
  private:
  public:
    int execute();
};

class ORAInstruction: FullAddressingModeInstruction {
  private:
  public:
    int execute();
};

class SBCInstruction: FullAddressingModeInstruction {
  private:
  public:
    int execute();
};

class STAInstruction: FullAddressingModeInstruction {
  private:
  public:
    int execute();
};

class ShiftModeInstruction: public Instruction {
  protected:
    void count_cycles();
};

class ASLInstruction: ShiftModeInstruction{
  private:
  public:
    int execute();
};

class LSRInstruction: ShiftModeInstruction{
  private:
  public:
    int execute();
};

class ROLInstruction: ShiftModeInstruction{
  private:
  public:
    int execute();
};

class RORInstruction: ShiftModeInstruction{
  private:
  public:
    int execute();
};

class BranchInstruction: public Instruction {
  protected:
    void count_cycles();
    int get_branch_target();
};

class BCCInstruction: public BranchInstruction {
  private:
  public:
    int execute();
};

class BCSInstruction: public BranchInstruction {
  private:
  public:
    int execute();
};

class BEQInstruction: public BranchInstruction {
  private:
  public:
    int execute();
};

class BMIInstruction: public BranchInstruction {
  private:
  public:
    int execute();
};

class BNEInstruction: public BranchInstruction {
  private:
  public:
    int execute();
};

class BPLInstruction: public BranchInstruction {
  private:
  public:
    int execute();
};

class BVCInstruction: public BranchInstruction {
  private:
  public:
    int execute();
};

class BVSInstruction: public BranchInstruction {
  private:
  public:
    int execute();
};

class ImpliedAddressingInstruction: public Instruction {
  protected:
    void count_cycles();
};

class BRKInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class CLCInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class CLDInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class CLIInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class CLVInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class DEXInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class DEYInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class INXInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class INYInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class NOPInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class PHAInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class PHPInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class PLAInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class PLPInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class RTIInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class RTSInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class SECInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class SEDInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class SEIInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class TAXInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class TAYInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class TSXInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class TXAInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class TXSInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class TYAInstruction: public ImpliedAddressingInstruction {
  private:
  public:
    int execute();
};

class JumpInstruction: public Instruction {
  protected:
    void count_cycles();
  public:
    int get_memory_value();
};

class JMPInstruction: public JumpInstruction {
  private:
  public:
    int execute();
};

class JSRInstruction: public JumpInstruction {
  private:
  public:
    int execute();
};

class MiscInstruction: public Instruction {
  protected:
    void count_cycles();
};

class BITInstruction: public MiscInstruction {
  private:
  public:
    int execute();
};

class CPXInstruction: public MiscInstruction {
  private:
  public:
    int execute();
};

class CPYInstruction: public MiscInstruction {
  private:
  public:
    int execute();
};

class DECInstruction: public MiscInstruction {
  private:
  public:
    int execute();
};

class INCInstruction: public MiscInstruction {
  private:
  public:
    int execute();
};

class LDXInstruction: public MiscInstruction {
  private:
  public:
    int execute();
};

class LDYInstruction: public MiscInstruction {
  private:
  public:
    int execute();
};

class STXInstruction: public MiscInstruction {
  private:
  public:
    int execute();
};

class STYInstruction: public MiscInstruction {
  private:
  public:
    int execute();
};

#endif // __INSTRUCTION_H_
