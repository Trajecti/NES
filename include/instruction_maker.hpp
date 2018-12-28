#ifndef __INSTRUCTION_MAKER_H_
#define __INSTRUCTION_MAKER_H_

#include "instruction_factory.hpp"
#include "instruction_maker_interface.hpp"

#define REGISTER_INSTRUCTION(T) static InstructionMaker<T> maker_##T(#T);

template<typename T>
class InstructionMaker : public InstructionMakerInterface
{
public:
    InstructionMaker(const std::string& key) {
        InstructionFactory::Instance().RegisterMaker(key, this);
    }
    std::unique_ptr<Instruction> create(addressing_mode mode, std::shared_ptr<cpu_state> state) const
    {
        return std::make_unique<T>(mode, state);
    }
    ~InstructionMaker() {};
};

#endif // __INSTRUCTION_MAKER_H_
