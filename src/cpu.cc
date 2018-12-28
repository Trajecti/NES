#include "../include/cpu.hpp"
#include "../include/instruction_factory.hpp"
#include <iostream>

CPU::CPU() noexcept{
    state = std::make_shared<cpu_state>();
    state->pc = 0;
}

CPU::~CPU() noexcept{
    return;
}

int CPU::execute(){
    state->memory[0][0]= 0x0;
    state->memory[0][1]= 0x0;
    state->memory[0][2]= 0x0;
    auto instruction = InstructionFactory::Instance().create(state);
    instruction->execute_instruction();
    return 0;
}
