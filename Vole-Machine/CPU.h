#pragma once
#include "StorageUnit.h"
#include "ALU.h"
#include "CU.h"
#include "Memory.h"
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
    void runInstructions(Memory& memory);
    void fetch(Memory& memory);
    std::vector<int> decode();
    void execute(Memory& memory, std::vector<int> instruction);
    void clearRegisters();
    bool isHalt();
    void halt();

    bool isInstructionPending();

    void resetProgram();

    size_t& getProgramCounter();
    std::string getCurrentInstruction();
};