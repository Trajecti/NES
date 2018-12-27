#include <map>
#include "instruction.hpp"
#include "instruction_maker_interface.hpp"

class InstructionFactory {
   public:
        Instruction* create(std::shared_ptr<cpu_state> state);
        static InstructionFactory& Instance();
        void RegisterMaker(const std::string& key, InstructionMakerInterface * maker);
    private:
        std::map<std::string, InstructionMakerInterface*> _makers;
};
