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
    int starting_address = 0;
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
    void resetProgram(int starting_address = 0);
    int getStartingAddress();
    void setStartingAddress(int starting_address);

    std::string getRegisterValueAt(int index);
    void setRegisterValueAt(int index, std::string& value);

    void setProgramCounter(int address);
    size_t& getProgramCounter();
    std::string getCurrentInstruction();
};