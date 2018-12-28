#ifndef __INSTRUCTION_MAKER_INTERFACE_H_
#define __INSTRUCTION_MAKER_INTERFACE_H_

#include "instructions/instruction.hpp"

class InstructionMakerInterface {
    public:
        virtual std::unique_ptr<Instruction> create(addressing_mode mode, std::shared_ptr<cpu_state> state) const = 0;
        virtual ~InstructionMakerInterface() {}
    };


#endif // __INSTRUCTION_MAKER_INTERFACE_H_
