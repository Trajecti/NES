
#include "../include/instruction.hpp"

using SR = cpu_state::SR;

void JumpInstruction::count_cycles(){
    switch (Instruction::mode){
        case addressing_mode::absolute:
            Instruction::cycles += 3;
        case addressing_mode::indirect:
            Instruction::cycles += 5;
        default:
            Instruction::cycles += 0;
        }
    return;
}


int JMPInstruction::execute() {
    int pch =  memory_byte & 0xFF;
    int pcl =  (memory_byte >> 8) & 0xFF;
    state->pc = (pcl << 4) + pch;
    return 0;
}

int JSRInstruction::execute() {
    Instruction::cycles = 6;
    int cur_pch =  state->pc & 0xFF;
    int cur_pcl =  (state->pc >> 8) & 0xFF;
    state->stack[state->sp] = cur_pch;
    state->stack[state->sp - 1] = cur_pcl;
    state->sp -= 2;

    int next_pch =  memory_byte & 0xFF;
    int next_pcl =  (memory_byte >> 8) & 0xFF;
    state->pc = (next_pcl << 4) + next_pch;
    return 0;
}
