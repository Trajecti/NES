#include "../include/cpu.hpp"
#include "../include/instruction_factory.hpp"

CPU::CPU() noexcept{
    state = std::make_shared<cpu_state>();
}

CPU::~CPU() noexcept{
    return;
}

int CPU::execute(){
    InstructionFactory factory;
    Instruction* instruction = factory.create(state);
    instruction->execute_instruction();
    return 0;
}
