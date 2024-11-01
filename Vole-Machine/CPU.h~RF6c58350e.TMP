#pragma once
#include "StorageUnit.h"
#include "ALU.h"
#include "CU.h"
#include <array>
#include <vector>
#include <string>

class CPU {
private:
    Registers registers;
    size_t program_counter;
    std::string instruction_register;
    ALU alu;
    CU cu;
public:
    CPU();
    void runInstructions(MainMemory& memory);
    void fetch(MainMemory& memory);
    std::vector<int> decode();
    void execute(Registers& registers, MainMemory& memory, std::vector<int> instruction);
    void clearRegisters();
    bool isHalt();
    void halt();

    size_t& getProgramCounter();
};