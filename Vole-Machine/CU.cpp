#include "CU.h"
#include <vector> 
#include <iostream>

void CU::executeInstruction(const std::vector<int>& instruction, Registers& registers, Memory& memory, ALU& alu, size_t& program_counter) {
    OP_CODE operation_code = OP_CODE(instruction[0]);
    
    switch (operation_code) {
        case OP_CODE::LOAD_M: {
            std::cout << "loadM" << std::endl;
            int memory_address = std::stoi(std::to_string(instruction[2]) + std::to_string(instruction[3]), nullptr, 16);
            loadFromMemory(instruction[1], memory_address, registers, memory);
        }
        case OP_CODE::LOAD_V: {
            std::cout << "loadV" << std::endl;
            std::string value = std::to_string(instruction[2]) + std::to_string(instruction[3]);
            loadValue(instruction[1], value, registers);
        }
        case OP_CODE::STORE: {
            std::cout << "STORE" << std::endl;
            int memory_address = std::stoi(std::to_string(instruction[2]) + std::to_string(instruction[3]), nullptr, 16);
            storeInMemory(instruction[1], memory_address, registers, memory);
        }
        case OP_CODE::MOVE: {
            std::cout << "MOVE" << std::endl;
            move(instruction[2], instruction[3], registers);
        }
        case OP_CODE::ADD: {
            std::cout << "ADD" << std::endl;
            alu.addTwoComp(instruction[1], instruction[2], instruction[3], registers);
        }
        case OP_CODE::ADD_F: {
            std::cout << "ADD_F" << std::endl;
            alu.addFloatingPoint(instruction[1], instruction[2], instruction[3], registers);
        }
        case OP_CODE::JUMP: {
            std::cout << "JUMP" << std::endl;
            int memory_address = std::stoi(std::to_string(instruction[2]) + std::to_string(instruction[3]), nullptr, 16);
            jumpTo(instruction[1], memory_address, registers, program_counter);
        }
        default: {
            std::cout << "def" << std::endl;
            break;
        }
    }
}


void CU::loadFromMemory(int reg, int memory_address, Registers& registers, Memory& memory) {
    registers[reg].setValue(memory.getValueAt(memory_address));
}

void CU::loadValue(int reg, const std::string& value, Registers& registers) {
    registers[reg].setValue(value);
}

void CU::storeInMemory(int reg, int memory_address, Registers& registers, Memory& memory) {
    if (isScreen(reg, memory_address)) {
        // ??
    }
    else {
        memory.setValueAt(memory_address, registers[reg].getValue());
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

