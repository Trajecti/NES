
#include "../include/instruction.hpp"

using SR = cpu_state::SR;

void ImpliedAddressingInstruction::count_cycles() {
    Instruction::cycles = 2;
}

int BRKInstruction::execute(){
    Instruction::cycles = 7;
    state->pc = state->pc + 2;
    state->stack[state->sp] = state->pc & 0x0F;
    state->stack[state->sp - 1] = state->pc >> 8;
    state->stack[(state->sp)-2] = state->status.to_ulong();
    state->sp -= 3;
    state->status[SR::BREAK_BIT] = 0x01;
    state->pc = state->memory[0xFF][0xFE];
    return 0;
}

int CLCInstruction::execute(){
    state->status[SR::CARRY_BIT] = 0;
    return 0;
}

int CLDInstruction::execute(){
    state->status[SR::DECIMAL_BIT] = 0;
    return 0;
}

int CLIInstruction::execute(){
    state->status[SR::INTERRUPT_BIT] = 0;
    return 0;
}

int CLVInstruction::execute(){
    state->status[SR::OVERFLOW_BIT] = 0;
    return 0;
}

int DEXInstruction::execute(){
    state->x = (state->x - 1) % MAX_INT;
    return 0;
}

int DEYInstruction::execute(){
    state->x = (state->y - 1) % MAX_INT;
    return 0;
}

int INXInstruction::execute(){
    state->x = (state->x + 1) % MAX_INT;
    return 0;
}

int INYInstruction::execute(){
    state->x = (state->y + 1) % MAX_INT;
    return 0;
}

int NOPInstruction::execute(){
    return 0;
}

int PHAInstruction::execute(){
    Instruction::cycles = 3;
    state->stack[state->sp] = state->ac;
    state->sp -= 2;
    return 0;
}

int PHPInstruction::execute(){
    Instruction::cycles = 3;
    state->stack[state->sp] = state->status.to_ulong();
    state->sp -= 2;
    return 0;
}

int PLAInstruction::execute(){
    Instruction::cycles = 4;
    state->ac = state->stack[(state->sp) + 1];
    state->status[SR::ZERO_BIT] = (state->ac == 0);
    state->status[SR::NEGATIVE_BIT] = state->ac >> 7;
    state->sp += 1;
    return 0;
}

int PLPInstruction::execute(){
    Instruction::cycles = 4;
    state->status = std::bitset<8>(state->stack[(state->sp) + 1]);
    state->sp += 1;
    return 0;
}

int RTIInstruction::execute(){
    Instruction::cycles = 6;
    int pch = state->stack[(state->sp) + 3];
    int pcl = state->stack[(state->sp) + 2];
    state->pc = (pcl << 4) + pch;
    state->status = std::bitset<8>(state->stack[(state->sp) + 1]);
    state->sp += 3;
    return 0;
}

int RTSInstruction::execute(){
    Instruction::cycles = 6;
    int pcl = state->stack[(state->sp) + 2];
    int pch = state->stack[(state->sp) + 1];
    state->pc = (pcl << 4) + pch;
    state->sp += 2;
    return 0;
}

int SECInstruction::execute(){
    state->status[SR::CARRY_BIT] = 0x01;
    return 0;
}

int SEDInstruction::execute(){
    state->status[SR::DECIMAL_BIT] = 0x01;
    return 0;
}

int SEIInstruction::execute(){
    state->status[SR::INTERRUPT_BIT] = 0x01;
    return 0;
}

int TAXInstruction::execute(){
    state->x = state->ac;
    return 0;
}

int TAYInstruction::execute(){
    state->y = state->ac;
    return 0;
}

int TSXInstruction::execute(){
    state->sp = state->x;
    return 0;
}

int TXAInstruction::execute(){
    state->ac = state->x;
    return 0;
}

int TXSInstruction::execute(){
    state->sp = state->x;
    return 0;
}

int TYAInstruction::execute(){
    state->ac = state->y;
    return 0;
}
