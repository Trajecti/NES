
#include "../include/instruction.hpp"

using SR = cpu_state::SR;

void FullAddressingModeInstruction::count_cycles(){
    switch (Instruction::mode){
        case addressing_mode::immediate:
            Instruction::cycles += 2;
        case addressing_mode::zero_page:
            Instruction::cycles += 3;
        case addressing_mode::zero_page_x:
            Instruction::cycles += 4;
        case addressing_mode::absolute:
            Instruction::cycles += 4;
        case addressing_mode::absolute_x:
            Instruction::cycles += 4;
        case addressing_mode::absolute_y:
            Instruction::cycles += 4;
        case addressing_mode::indirect_x_indexed:
            Instruction::cycles += 6;
        case addressing_mode::indirect_y_indexed:
            Instruction::cycles += 5;
        default:
            Instruction::cycles += 0;
        }
    return;
}

int ADCInstruction::execute() {
    int sum = memory_byte + state->ac + state->status[SR::CARRY_BIT];
    state->status[SR::CARRY_BIT] = sum > 0xFF;
    state->status[SR::OVERFLOW_BIT] = ~(memory_byte ^ state->ac) & (memory_byte ^ sum) & 0x80;
    state->status[SR::ZERO_BIT] = (sum == 0);
    state->status[SR::NEGATIVE_BIT] = sum >> 7;
    state->ac = sum;
    return 0;
}

int ANDInstruction::execute() {
    int result = memory_byte & state->ac;
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    state->ac = result;
    return 0;
}

int CMPInstruction::execute() {
    int sum = state->ac - memory_byte;
    state->status[SR::CARRY_BIT] = (state->ac >= memory_byte);
    state->status[SR::ZERO_BIT] = (sum == 0);
    state->status[SR::NEGATIVE_BIT] = sum >> 7;
    return 0;
}

int EORInstruction::execute() {
    int result = state->ac ^ memory_byte;
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    state->ac = result;
    return 0;
}

int LDAInstruction::execute() {
    state->status[SR::ZERO_BIT] = (memory_byte == 0);
    state->status[SR::NEGATIVE_BIT] = memory_byte >> 7;
    state->ac = memory_byte;
    return 0;
}

int ORAInstruction::execute() {
    int result = state->ac | memory_byte;
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    state->ac = result;
    return 0;
}

int SBCInstruction::execute() {
    int sum = state->ac - memory_byte - state->status[SR::CARRY_BIT];
    state->status[SR::CARRY_BIT] = sum > 0xFF;
    state->status[SR::OVERFLOW_BIT] = ~(memory_byte ^ state->ac) & (memory_byte ^ sum) & 0x80;
    state->status[SR::ZERO_BIT] = (sum == 0);
    state->status[SR::NEGATIVE_BIT] = sum >> 7;
    state->ac = sum;
    return 0;
}

int STAInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::absolute_x:
        case addressing_mode::absolute_y:
        case addressing_mode::indirect_y_indexed:
            Instruction::cycles += 1;
        default:
            Instruction::cycles += 0;
        }
    state->status[SR::ZERO_BIT] = (memory_byte == 0);
    state->status[SR::NEGATIVE_BIT] = memory_byte >> 7;
    state->ac = memory_byte;
    return 0;
}
