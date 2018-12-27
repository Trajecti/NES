
#include "../include/instruction.hpp"

using SR = cpu_state::SR;

void ShiftModeInstruction::count_cycles(){
    switch (Instruction::mode){
        case addressing_mode::zero_page:
            Instruction::cycles += 5;
        case addressing_mode::zero_page_x:
            Instruction::cycles += 6;
        case addressing_mode::absolute:
            Instruction::cycles += 6;
        case addressing_mode::absolute_x:
            Instruction::cycles += 7;
        default:
            Instruction::cycles += 0;
        }
}

int ASLInstruction::execute() {
    int result = memory_byte << 1;
    state->status[SR::CARRY_BIT] = result > 0xFF;
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    if (Instruction::mode == addressing_mode::accumulator){
        state->ac = result;
        return 0;
    }
    state->memory[page_number][page_offset] = result;
    return 0;
}

int LSRInstruction::execute() {
    int result = memory_byte >> 1;
    state->status[SR::CARRY_BIT] = result & 0x01;
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    if (Instruction::mode == addressing_mode::accumulator){
        state->ac = result;
        return 0;
    }
    state->memory[page_number][page_offset] = result;
    return 0;
}

int ROLInstruction::execute() {
    int result = (memory_byte >> 1) + (state->status[SR::CARRY_BIT] << 7);
    state->status[SR::CARRY_BIT] = memory_byte >> 7;
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    if (Instruction::mode == addressing_mode::accumulator){
        state->ac = result;
        return 0;
    }
    state->memory[page_number][page_offset] = result;
    return 0;
}

int RORInstruction::execute() {
    int result = (memory_byte << 1) + state->status[SR::CARRY_BIT];
    state->status[SR::CARRY_BIT] = memory_byte & 0x01;
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    if (Instruction::mode == addressing_mode::accumulator){
        state->ac = result;
        return 0;
    }
    state->memory[page_number][page_offset] = result;
    return 0;
}
