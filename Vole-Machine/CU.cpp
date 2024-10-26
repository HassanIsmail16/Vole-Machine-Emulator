#include "CU.h"
#include <vector> 

void CU::executeInstruction(const std::vector<int>& instruction, Registers& registers, MainMemory& memory, ALU& alu) {
    int op_code = instruction[0];  
}


void CU::loadFromMemory(int reg, int memory_address, Registers& registers, MainMemory& memory) {
    registers[reg].setValue(memory[memory_address].getValue());
}

void CU::loadValue(int reg, std::string value, Registers& registers) {
    registers[reg].setValue(value);
}

void CU::storeInMemory(int reg, int memory_address, Registers& registers, MainMemory& memory) {
    if (isScreen(reg, memory_address)) {
        // ??
    }
    else {
        memory[memory_address].setValue(registers[reg].getValue());
    }
}

void CU::jumpTo(int reg, int memory_address, Registers& registers, size_t& program_counter) {
    if (registers[reg].getValue() == registers[0].getValue()) {
        program_counter = memory_address;
    }
}


bool CU::isScreen(int reg, int memory_address) {
    return memory_address == 0x00;
}

void CU::move(int reg1, int reg2, Registers& registers) {
    registers[reg1].setValue(registers[reg2].getValue());
}

