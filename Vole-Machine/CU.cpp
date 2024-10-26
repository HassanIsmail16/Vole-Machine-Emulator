#include "CU.h"
#include <vector> 

void CU::executeInstruction(const std::vector<int>& instruction, std::array<StorageUnit, 16>& registers, std::array<StorageUnit, 256>& memory, ALU& alu) {
    int op_code = instruction[0];  
}


void CU::loadFromMemory(int reg, int mem_addr, std::array<StorageUnit, 16>& registers, std::array<StorageUnit, 256>& memory) {
    registers[reg].setValue(memory[mem_addr].getValue());
}

void CU::loadValue(int reg, std::string value, std::array<StorageUnit, 16>& registers) {
    registers[reg].setValue(value);
}

void CU::storeInMemory(int reg, int mem_addr, std::array<StorageUnit, 16>& registers, std::array<StorageUnit, 256>& memory) {
    if (isScreen(reg, mem_addr)) {
        // ??
    }
    else {
        memory[mem_addr].setValue(registers[reg].getValue());
    }
}

void CU::jumpTo(int reg, int mem_addr, std::array<StorageUnit, 16>& registers, size_t& program_counter) {
    if (registers[reg].getValue() == registers[0].getValue()) {
        program_counter = mem_addr;
    }
}


bool CU::isScreen(int reg, int mem_addr) {
    return mem_addr == 0x00;
}

void CU::move(int Reg1, int Reg2, std::array<StorageUnit, 16>& registers) {
    registers[Reg1].setValue(registers[Reg2].getValue());
}

