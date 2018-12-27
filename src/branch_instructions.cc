
#include "../include/instruction.hpp"

using SR = cpu_state::SR;

void BranchInstruction::count_cycles() {
    Instruction::cycles += 1;
}

int BranchInstruction::get_branch_target() {
   ++state->pc;
   int pcl = state->pc >> 4;
   int pch = state->pc & 0x0F;

   int operand = state->memory[pch][pcl];
   int operand_sign = operand >> 7;
   int seven_bit_operand = operand & 0x7f;
   int signed_operand_value = (operand_sign * MIN_SIGNED_INT) + seven_bit_operand;
   int target = pcl + signed_operand_value;
   if (target > 0xFF) {
       pch = (pch + 1) % MAX_INT;
       target = (target) % MAX_INT;
       Instruction::cycles+=1;
   }
   target = (target << 4) + pch;
   return target;
}

int BCCInstruction::execute(){
    int target = BranchInstruction::get_branch_target();
    if (!(state->status[SR::CARRY_BIT])){
        state->pc = target;
        Instruction::cycles+=1;
    }
    return 0;
}

int BCSInstruction::execute(){
    int target = BranchInstruction::get_branch_target();
    if (state->status[SR::CARRY_BIT]){
        state->pc = target;
        Instruction::cycles+=1;
    }
    return 0;
}

int BEQInstruction::execute(){
    int target = BranchInstruction::get_branch_target();
    if (state->status[SR::ZERO_BIT]){
        state->pc = target;
        Instruction::cycles+=1;
    }
    return 0;
}

int BMIInstruction::execute(){
    int target = BranchInstruction::get_branch_target();
    if (state->status[SR::NEGATIVE_BIT]){
        state->pc = target;
        Instruction::cycles+=1;
    }
    return 0;
}

int BNEInstruction::execute(){
    int target = BranchInstruction::get_branch_target();
    if (!(state->status[SR::ZERO_BIT])){
        state->pc = target;
        Instruction::cycles+=1;
    }
    return 0;
}

int BPLInstruction::execute(){
    int target = BranchInstruction::get_branch_target();
    if (!(state->status[SR::NEGATIVE_BIT])){
        state->pc = target;
        Instruction::cycles+=1;
    }
    return 0;
}

int BVCInstruction::execute(){
    int target = BranchInstruction::get_branch_target();
    if (!(state->status[SR::OVERFLOW_BIT])){
        state->pc = target;
        Instruction::cycles+=1;
    }
    return 0;
}

int BVSInstruction::execute(){
    int target = BranchInstruction::get_branch_target();
    if (state->status[SR::OVERFLOW_BIT]){
        state->pc = target;
        Instruction::cycles+=1;
    }
    return 0;
}
