#pragma once
#include "StorageUnit.h"
#include "ALU.h"          
#include <array>
#include <vector> 

class CU {
public:
    void executeInstruction(const std::vector<int>& instruction, std::array<StorageUnit, 16>& registers, std::array<StorageUnit, 256>& memory, ALU& alu);
    void loadFromMemory(int reg, int mem_addr, std::array<StorageUnit, 16>& registers, std::array<StorageUnit, 256>& memory);
    void loadValue(int reg, std::string value, std::array<StorageUnit, 16>& registers);
    void storeInMemory(int reg, int mem_addr, std::array<StorageUnit, 16>& registers, std::array<StorageUnit, 256>& memory);
    void jumpTo(int reg, int mem_addr, std::array<StorageUnit, 16>& registers);
    bool isScreen(int reg, int mem_addr);
    void move(int Reg1, int Reg2, std::array<StorageUnit, 16>& registers);
};

