
#include "../include/instruction_maker.hpp"
#include "../include/instructions/branch_instruction.hpp"
#include "../include/instructions/full_addressing_mode_instruction.hpp"
#include "../include/instructions/single_byte_instruction.hpp"
#include "../include/instructions/jump_instruction.hpp"
#include "../include/instructions/bit_shift_instruction.hpp"
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <exception>

REGISTER_INSTRUCTION(BRKInstruction);
REGISTER_INSTRUCTION(RTIInstruction);
REGISTER_INSTRUCTION(RTSInstruction);
REGISTER_INSTRUCTION(PHPInstruction);
REGISTER_INSTRUCTION(CLCInstruction);
REGISTER_INSTRUCTION(PLPInstruction);
REGISTER_INSTRUCTION(SECInstruction);
REGISTER_INSTRUCTION(PHAInstruction);
REGISTER_INSTRUCTION(CLIInstruction);
REGISTER_INSTRUCTION(PLAInstruction);
REGISTER_INSTRUCTION(SEIInstruction);
REGISTER_INSTRUCTION(DEYInstruction);
REGISTER_INSTRUCTION(TYAInstruction);
REGISTER_INSTRUCTION(TAYInstruction);
REGISTER_INSTRUCTION(CLVInstruction);
REGISTER_INSTRUCTION(INYInstruction);
REGISTER_INSTRUCTION(CLDInstruction);
REGISTER_INSTRUCTION(INXInstruction);
REGISTER_INSTRUCTION(TXAInstruction);
REGISTER_INSTRUCTION(TXSInstruction);
REGISTER_INSTRUCTION(TAXInstruction);
REGISTER_INSTRUCTION(TSXInstruction);
REGISTER_INSTRUCTION(DEXInstruction);
REGISTER_INSTRUCTION(NOPInstruction);
REGISTER_INSTRUCTION(BPLInstruction);
REGISTER_INSTRUCTION(BMIInstruction);
REGISTER_INSTRUCTION(BVCInstruction);
REGISTER_INSTRUCTION(BVSInstruction);
REGISTER_INSTRUCTION(BCCInstruction);
REGISTER_INSTRUCTION(BCSInstruction);
REGISTER_INSTRUCTION(BNEInstruction);
REGISTER_INSTRUCTION(BEQInstruction);
REGISTER_INSTRUCTION(ORAInstruction);
REGISTER_INSTRUCTION(ANDInstruction);
REGISTER_INSTRUCTION(EORInstruction);
REGISTER_INSTRUCTION(ADCInstruction);
REGISTER_INSTRUCTION(STAInstruction);
REGISTER_INSTRUCTION(LDAInstruction);
REGISTER_INSTRUCTION(CMPInstruction);
REGISTER_INSTRUCTION(SBCInstruction);
REGISTER_INSTRUCTION(BITInstruction);
REGISTER_INSTRUCTION(JMPInstruction);
REGISTER_INSTRUCTION(STYInstruction);
REGISTER_INSTRUCTION(LDYInstruction);
REGISTER_INSTRUCTION(CPYInstruction);
REGISTER_INSTRUCTION(CPXInstruction);
REGISTER_INSTRUCTION(ASLInstruction);
REGISTER_INSTRUCTION(ROLInstruction);
REGISTER_INSTRUCTION(LSRInstruction);
REGISTER_INSTRUCTION(RORInstruction);
REGISTER_INSTRUCTION(STXInstruction);
REGISTER_INSTRUCTION(LDXInstruction);
REGISTER_INSTRUCTION(DECInstruction);
REGISTER_INSTRUCTION(INCInstruction);

std::map<int, std::string> branch_instruction_map = {{0x10, "BPLInstruction"},
                                                                   {0x30, "BMIInstruction"},
                                                                   {0x50, "BVCInstruction"},
                                                                   {0x70, "BVSInstruction"},
                                                                   {0x90, "BCCInstruction"},
                                                                   {0xB0, "BCSInstruction"},
                                                                   {0xD0, "BNEInstruction"},
                                                                   {0xF0, "BEQInstruction"}};

std::map<int, std::string> single_byte_instruction_map = {{0x00, "BRKInstruction"},
                                                                        {0x40, "RTIInstruction"},
                                                                        {0x60, "RTSInstruction"},
                                                                        {0x08, "PHPInstruction"},
                                                                        {0x18, "CLCInstruction"},
                                                                        {0x28, "PLPInstruction"},
                                                                        {0x38, "SECInstruction"},
                                                                        {0x48, "PHAInstruction"},
                                                                        {0x58, "CLIInstruction"},
                                                                        {0x68, "PLAInstruction"},
                                                                        {0x78, "SEIInstruction"},
                                                                        {0x88, "DEYInstruction"},
                                                                        {0x98, "TYAInstruction"},
                                                                        {0xA8, "TAYInstruction"},
                                                                        {0xB8, "CLVInstruction"},
                                                                        {0xC8, "INYInstruction"},
                                                                        {0xD8, "CLDInstruction"},
                                                                        {0xE8, "INXInstruction"},
                                                                        {0xF8, "CLVInstruction"},
                                                                        {0x8A, "TXAInstruction"},
                                                                        {0x9A, "TXSInstruction"},
                                                                        {0xAA, "TAXInstruction"},
                                                                        {0xBA, "TSXInstruction"},
                                                                        {0xCA, "DEXInstruction"},
                                                                        {0xEA, "NOPInstruction"}};

std::map<std::pair<int, int>, std::string> multi_byte_instruction_map ={{std::make_pair(0x0, 0x1), "ORAInstruction"},
                                                                           {std::make_pair(0x1, 0x1), "ANDInstruction"},
                                                                           {std::make_pair(0x2, 0x1), "EORInstruction"},
                                                                           {std::make_pair(0x3, 0x1), "ADCInstruction"},
                                                                           {std::make_pair(0x4, 0x1), "STAInstruction"},
                                                                           {std::make_pair(0x5, 0x1), "LDAInstruction"},
                                                                           {std::make_pair(0x6, 0x1), "CMPInstruction"},
                                                                           {std::make_pair(0x7, 0x1), "SBCInstruction"},
                                                                           {std::make_pair(0x1, 0x0), "BITInstruction"},
                                                                           {std::make_pair(0x2, 0x0), "JMPInstruction"},
                                                                           {std::make_pair(0x3, 0x0), "JMPInstruction"},
                                                                           {std::make_pair(0x4, 0x0), "STYInstruction"},
                                                                           {std::make_pair(0x5, 0x0), "LDYInstruction"},
                                                                           {std::make_pair(0x6, 0x0), "CPYInstruction"},
                                                                           {std::make_pair(0x7, 0x0), "CPXInstruction"},
                                                                           {std::make_pair(0x0, 0x2), "ASLInstruction"},
                                                                           {std::make_pair(0x1, 0x2), "ROLInstruction"},
                                                                           {std::make_pair(0x2, 0x2), "LSRInstruction"},
                                                                           {std::make_pair(0x3, 0x2), "RORInstruction"},
                                                                           {std::make_pair(0x4, 0x2), "STXInstruction"},
                                                                           {std::make_pair(0x5, 0x2), "LDXInstruction"},
                                                                           {std::make_pair(0x6, 0x2), "DECInstruction"},
                                                                           {std::make_pair(0x7, 0x2), "INCInstruction"},
                                                                           {std::make_pair(0x1, 0x1), "ANDInstruction"}};

std::map<std::pair<int, int>, addressing_mode> address_mode_map ={{std::make_pair(0x000, 0x01), addressing_mode::indirect_x_indexed},
                                                                            {std::make_pair(0x001, 0x01), addressing_mode::zero_page},
                                                                            {std::make_pair(0x010, 0x01), addressing_mode::immediate},
                                                                            {std::make_pair(0x011, 0x01), addressing_mode::absolute},
                                                                            {std::make_pair(0x100, 0x01), addressing_mode::indirect_y_indexed},
                                                                            {std::make_pair(0x101, 0x01), addressing_mode::zero_page_x},
                                                                            {std::make_pair(0x110, 0x01), addressing_mode::absolute_x},
                                                                            {std::make_pair(0x111, 0x01), addressing_mode::absolute_y},
                                                                            {std::make_pair(0x000, 0x10), addressing_mode::immediate},
                                                                            {std::make_pair(0x001, 0x10), addressing_mode::zero_page},
                                                                            {std::make_pair(0x010, 0x10), addressing_mode::accumulator},
                                                                            {std::make_pair(0x011, 0x10), addressing_mode::absolute},
                                                                            {std::make_pair(0x101, 0x10), addressing_mode::zero_page_x},
                                                                            {std::make_pair(0x111, 0x10), addressing_mode::absolute_x},
                                                                            {std::make_pair(0x000, 0x00), addressing_mode::immediate},
                                                                            {std::make_pair(0x001, 0x00), addressing_mode::zero_page},
                                                                            {std::make_pair(0x011, 0x00), addressing_mode::absolute},
                                                                            {std::make_pair(0x101, 0x00), addressing_mode::zero_page_x},
                                                                            {std::make_pair(0x111, 0x00), addressing_mode::absolute_x}};


std::unique_ptr<Instruction> InstructionFactory::create(std::shared_ptr<cpu_state> state){
    const int JSR_OPCODE = 0x20;
    const int STX_ZPY_OPCODE = 0x98;

    int opcode = *state->memory[state->pc];
    bool is_single_byte_instruction = single_byte_instruction_map.count(opcode);
    bool is_branch_instruction = branch_instruction_map.count(opcode);
    addressing_mode address_mode;
    std::string instruction_type = "instruction";

    if (is_single_byte_instruction) {
        address_mode = addressing_mode::implied;
        instruction_type = single_byte_instruction_map[opcode];
    }
    else if (is_branch_instruction) {
        address_mode = addressing_mode::relative;
        instruction_type = branch_instruction_map[opcode];
    }
    else {
        if (opcode == JSR_OPCODE) {
            address_mode = addressing_mode::absolute;
            instruction_type = "JSRInstruction";
        } else if (opcode == STX_ZPY_OPCODE) {
            address_mode = addressing_mode::zero_page_y;
            instruction_type = "STXInstruction";
        } else {
            int cc = opcode & 0x3;
            int bbb = (opcode >> 2) & 0x7;
            int aaa = (opcode >> 5) & 0x7;
            address_mode = address_mode_map[std::make_pair(bbb,cc)];
            instruction_type = multi_byte_instruction_map[std::make_pair(aaa,cc)];
        }
    }
    auto i = _makers.find(instruction_type);
    InstructionMakerInterface* maker = i->second;
    return maker->create(address_mode, state);
 }

void InstructionFactory::RegisterMaker(const std::string& key, InstructionMakerInterface* maker)
{
    if (_makers.find(key) != _makers.end())
    {
        throw -1;
    }
    _makers[key] = maker;
}

InstructionFactory& InstructionFactory::Instance()
{
    static InstructionFactory factory;
    return factory;
}
