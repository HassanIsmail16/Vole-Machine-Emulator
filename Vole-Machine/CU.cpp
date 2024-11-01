#include "CU.h"
#include <vector> 
#include <iostream>

void CU::executeInstruction(const std::vector<int>& instruction, Registers& registers, Memory& memory, ALU& alu, size_t& program_counter) {
    OP_CODE operation_code = OP_CODE(instruction[0]);

    switch (operation_code) {
    case OP_CODE::LOAD_M: {
        int memory_address = std::stoi(std::to_string(instruction[2]) + std::to_string(instruction[3]), nullptr, 16);
        loadFromMemory(instruction[1], memory_address, registers, memory);
        break;
    }
    case OP_CODE::LOAD_V: {
        std::string value = std::to_string(instruction[2]) + std::to_string(instruction[3]);
        loadValue(instruction[1], value, registers);
        break;
    }
    case OP_CODE::STORE: {
        int memory_address = std::stoi(std::to_string(instruction[2]) + std::to_string(instruction[3]), nullptr, 16);
        storeInMemory(instruction[1], memory_address, registers, memory);
        break;
    }
    case OP_CODE::MOVE: {
        move(instruction[2], instruction[3], registers);
        break;
    }
    case OP_CODE::ADD: {
        alu.addTwoComp(instruction[1], instruction[2], instruction[3], registers);
        break;
    }
    case OP_CODE::ADD_F: {
        alu.addFloatingPoint(instruction[1], instruction[2], instruction[3], registers);
        break;
    }
    case OP_CODE::BIT_OR: {
        alu.bitwiseOr(instruction[1], instruction[2], instruction[3], registers);
        break;
    }
    case OP_CODE::BIT_AND: {
        alu.bitwiseAnd(instruction[1], instruction[2], instruction[3], registers);
        break;
    }
    case OP_CODE::BIT_XOR: {
        alu.bitwiseXor(instruction[1], instruction[2], instruction[3], registers);
        break;
    }
    case OP_CODE::ROTATE: {
        alu.rotateRight(instruction[1], instruction[2], registers);
        break;
    }
    case OP_CODE::JUMP_EQ: {
        int memory_address = std::stoi(std::to_string(instruction[2]) + std::to_string(instruction[3]), nullptr, 16);
        jumpIfEqual(instruction[1], memory_address, registers, program_counter);
        break;
    }
    case OP_CODE::HALT: {
        program_counter = 0;
        break;
    }
    case OP_CODE::JUMP_GT: {
        int memory_address = std::stoi(std::to_string(instruction[2]) + std::to_string(instruction[3]), nullptr, 16);
        jumpIfGreater(instruction[1], memory_address, registers, program_counter);
        break;
    }
    default:
        break;
    }
}

void CU::loadFromMemory(int reg, int memory_address, Registers& registers, MainMemory& memory) {
    registers[reg].setValue(memory[memory_address].getValue());
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

void CU::jumpIfEqual(int reg, int memory_address, Registers& registers, size_t& program_counter) {
    if (registers[reg].getValue() == registers[0].getValue()) {
        program_counter = memory_address;
    }
}

void CU::jumpIfGreater(int reg, int memory_address, Registers& registers, size_t& program_counter) {
    int regValue = std::stoi(registers[reg].getValue(), nullptr, 16);
    int zeroRegValue = std::stoi(registers[0].getValue(), nullptr, 16);
    if (regValue > zeroRegValue) {
        program_counter = memory_address;
    }
}

bool CU::isScreen(int reg, int memory_address) {
    return memory_address == 0x00;
}

void CU::move(int reg1, int reg2, Registers& registers) {
    registers[reg1].setValue(registers[reg2].getValue());
}
