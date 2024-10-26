#pragma once
#include "StorageUnit.h"
#include "ALU.h"          
#include <array>
#include <vector> 

class CU {
public:
    void executeInstruction(const std::vector<int>& instruction, Registers& registers, MainMemory& memory, ALU& alu);
    void loadFromMemory(int reg, int memory_address, Registers& registers, MainMemory& memory);
    void loadValue(int reg, std::string value, Registers& registers);
    void storeInMemory(int reg, int memory_address, Registers& registers, MainMemory& memory);
    void jumpTo(int reg, int memory_address, Registers& registers, size_t& program_counter);
    bool isScreen(int reg, int memory_address);
    void move(int reg1, int reg2, Registers& registers);
};

