#include <iostream>
#include "../include/cpu.hpp"
#include <memory>

using namespace std;

int main(int argc, char *argv[]){
    std::unique_ptr<CPU> cpu = std::make_unique<CPU>();
    cpu->execute();
    cpu.reset();
    return 0;
}
