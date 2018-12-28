
#include "../include/instructions/instruction.hpp"

using SR = cpu_state::SR;

Instruction::Instruction(addressing_mode mode, std::shared_ptr<cpu_state> state) {
    this->state = state;
    this->mode = mode;
}

int Instruction::execute_instruction() {
    if (Instruction::mode != addressing_mode::relative) {
        get_memory_value_and_address();
    }
    count_cycles();
    return execute();
}

void Instruction::get_memory_value_and_address(){
    ++state->pc;
    int pch = state->pc & 0xFF;
    int pcl = state->pc << 8;

    const int ZERO_PAGE = 0;
    int indirect_page_number = -1;
    int indirect_page_offset = -1;
    int operand = state->memory[pch][pcl];
    int operand_second_byte;
    Instruction::cycles = 0;
    switch (Instruction::mode){
        case addressing_mode::accumulator:
            memory_byte = state->ac;
        case addressing_mode::immediate:
            memory_byte = state->memory[pch][pcl];
        case addressing_mode::zero_page:
            page_number = ZERO_PAGE;
            memory_byte = state->memory[page_number][operand];
        case addressing_mode::zero_page_x:
            page_number = ZERO_PAGE;
            page_offset =  (operand & 0xFF + state->x) % MAX_INT;
            memory_byte = state->memory[page_number][page_offset];
        case addressing_mode::zero_page_y:
            page_number = ZERO_PAGE;
            page_offset =  (operand & 0xFF + state->y) % MAX_INT;
            memory_byte = state->memory[page_number][page_offset];
        case addressing_mode::absolute:
            ++state->pc;
            pch = state->pc & 0xFF;
            pcl = state->pc << 8;
            operand_second_byte = state->memory[pch][pcl];
            page_number = operand_second_byte;
            page_offset = operand;
            memory_byte = state->memory[page_number][page_offset];
        case addressing_mode::absolute_x:
            ++state->pc;
            pch = state->pc & 0xFF;
            pcl = state->pc << 8;
            operand_second_byte = state->memory[pch][pcl];

            page_number = operand_second_byte;
            page_offset = operand + state->x;
            if (page_offset > 0xFF) {
                page_number = (page_number + 1) % MAX_INT;
                Instruction::cycles +=1;
            }
            page_offset = page_offset % MAX_INT;
            memory_byte = state->memory[page_number][page_offset];
        case addressing_mode::absolute_y:
            ++state->pc;
            pch = state->pc & 0xFF;
            pcl = state->pc << 8;
            operand_second_byte = state->memory[pch][pcl];

            page_number = operand_second_byte;
            page_offset = operand + state->y;
            if (page_offset > 0xFF) {
                page_number = (page_number + 1) % MAX_INT;
                Instruction::cycles +=1;
            }
            page_offset = page_offset % MAX_INT;
            memory_byte = state->memory[page_number][page_offset];
        case addressing_mode::indirect:
            ++state->pc;
            pch = state->pc & 0xFF;
            pcl = state->pc << 8;
            operand_second_byte = state->memory[pch][pcl];

            indirect_page_number = operand_second_byte;
            indirect_page_offset = operand;
            page_offset = state->memory[indirect_page_number][indirect_page_offset];
            page_number = state->memory[indirect_page_number][(indirect_page_offset + 1) % MAX_INT];
            memory_byte = state->memory[page_number][page_offset];
        case addressing_mode::indirect_x_indexed:
            indirect_page_offset = operand + state->x % MAX_INT;
            indirect_page_number = ZERO_PAGE;
            page_offset = state->memory[indirect_page_number][indirect_page_offset];
            page_number = state->memory[indirect_page_number][(indirect_page_offset + 1) % MAX_INT];
            memory_byte = state->memory[page_number][page_offset];
        case addressing_mode::indirect_y_indexed:
            indirect_page_offset = operand;
            indirect_page_number = ZERO_PAGE;
            page_offset = state->memory[indirect_page_number][indirect_page_offset];
            page_number = state->memory[indirect_page_number][(indirect_page_offset + 1) % MAX_INT];
            page_offset = page_offset + state->y;
            if (page_offset > 0xFF) {
                page_offset = (page_offset + 1) % MAX_INT;
                page_number = (page_number + 1) % MAX_INT;
                Instruction::cycles +=1;
            }
            memory_byte = state->memory[page_number][page_offset];
        case addressing_mode::implied:
            return;
        default:
            memory_byte = 0;
        }
    ++state->pc;
    return;
}

void MiscInstruction::count_cycles() {
    Instruction::cycles = 0;
    return;
}

int BITInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::zero_page: Instruction::cycles = 3;
        case addressing_mode::absolute: Instruction::cycles = 3;
    }
    state->status[SR::ZERO_BIT] = memory_byte & state->ac;
    state->status[SR::NEGATIVE_BIT] = memory_byte >> 7;
    state->status[SR::OVERFLOW_BIT] = memory_byte >> 6;
    return 0;
}

int CPXInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::immediate: Instruction::cycles = 2;
        case addressing_mode::zero_page: Instruction::cycles = 3;
        case addressing_mode::absolute: Instruction::cycles = 4;
    }

    int result = (state-> x - memory_byte) % MAX_INT;
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    state->status[SR::CARRY_BIT] = (state->x >= memory_byte);
    return 0;
}

int CPYInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::immediate: Instruction::cycles = 2;
        case addressing_mode::zero_page: Instruction::cycles = 3;
        case addressing_mode::absolute: Instruction::cycles = 4;
    }

    int result = (state-> y - memory_byte) % MAX_INT;
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    state->status[SR::CARRY_BIT] = (state->x >= memory_byte);
    return 0;
}

int DECInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::zero_page: Instruction::cycles = 5;
        case addressing_mode::zero_page_x: Instruction::cycles = 6;
        case addressing_mode::absolute: Instruction::cycles = 3;
        case addressing_mode::absolute_x: Instruction::cycles = 7;
    }

    int result = memory_byte - 1;
    state->memory[page_number][page_offset] = result; 
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    return 0;
}

int INCInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::zero_page: Instruction::cycles = 5;
        case addressing_mode::zero_page_x: Instruction::cycles = 6;
        case addressing_mode::absolute: Instruction::cycles = 6;
        case addressing_mode::absolute_x: Instruction::cycles = 7;
    }

    int result = memory_byte + 1;
    state->memory[page_number][page_offset] = result; 
    state->status[SR::ZERO_BIT] = (result == 0);
    state->status[SR::NEGATIVE_BIT] = result >> 7;
    return 0;
}

int LDXInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::immediate: Instruction::cycles = 2;
        case addressing_mode::zero_page: Instruction::cycles = 3;
        case addressing_mode::zero_page_y: Instruction::cycles = 4;
        case addressing_mode::absolute: Instruction::cycles = 4;
        case addressing_mode::absolute_y: Instruction::cycles = 4;
    }

    state->x = memory_byte; 
    state->status[SR::ZERO_BIT] = (memory_byte == 0);
    state->status[SR::NEGATIVE_BIT] = memory_byte >> 7;
    return 0;
}

int LDYInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::immediate: Instruction::cycles += 2;
        case addressing_mode::zero_page: Instruction::cycles += 3;
        case addressing_mode::zero_page_x: Instruction::cycles += 4;
        case addressing_mode::absolute: Instruction::cycles  += 4;
        case addressing_mode::absolute_x: Instruction::cycles += 4;
    }

    state->y = memory_byte; 
    state->status[SR::ZERO_BIT] = (memory_byte == 0);
    state->status[SR::NEGATIVE_BIT] = memory_byte >> 7;
    return 0;
}

int STXInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::zero_page: Instruction::cycles += 3;
        case addressing_mode::zero_page_y: Instruction::cycles += 4;
        case addressing_mode::absolute: Instruction::cycles += 4;
    }

    state->memory[page_number][page_offset] = state->x; 
    return 0;
}

int STYInstruction::execute() {
    switch (Instruction::mode){
        case addressing_mode::zero_page: Instruction::cycles += 3;
        case addressing_mode::zero_page_x: Instruction::cycles += 4;
        case addressing_mode::absolute: Instruction::cycles += 4;
    }

    state->memory[page_number][page_offset] = state->y; 
    return 0;
}

