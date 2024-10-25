#pragma once
#include "StorageUnit.h"
#include "ALU.h"
#include "CU.h"
#include <array>
#include <vector>
#include <string>

class CPU {
private:
    std::array<StorageUnit, 16> registers;
    size_t program_counter;
    std::string instruction_register;
    ALU alu;
    CU cu;

public:
    void runInstructions(std::array<StorageUnit, 256>& memory);
    void fetch(std::array<StorageUnit, 256>& memory);
    std::vector<int> decode();
    void execute(std::array<StorageUnit, 16>& Register, std::array<StorageUnit, 256>& memory, std::vector<int> instruction);
    void clearRegisters();
    bool isHalt();
    void halt();
};