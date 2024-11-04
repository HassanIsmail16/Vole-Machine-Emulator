#include "CU.h"
#include "Utilities.h"
#include <vector> 
#include <iostream>

void CU::executeInstruction(const std::vector<int>& instruction, Registers& registers, Memory& memory, ALU& alu, size_t& program_counter) {
    if (instruction.empty()) {
        return;
    } // skip if instruction is invalid (empty vector)

    OP_CODE operation_code = OP_CODE(instruction[0]);

    switch (operation_code) {
    case OP_CODE::LOAD_M: {
        int memory_address = instruction[2];
        loadFromMemory(instruction[1], memory_address, registers, memory);
        break;
    }
    case OP_CODE::LOAD_V: {
        int value = instruction[2];
        loadValue(instruction[1], value, registers);
        break;
    }
    case OP_CODE::STORE: {
        int memory_address = instruction[2];
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
        alu.rotateRight(instruction[1], instruction[3], registers);
        break;
    }
    case OP_CODE::JUMP_EQ: {
        int memory_address = instruction[2];
        jumpIfEqual(instruction[1], memory_address, registers, program_counter);
        break;
    }
    case OP_CODE::JUMP_GT: {
        int memory_address = instruction[2];
        jumpIfGreater(instruction[1], memory_address, registers, program_counter);
        break;
    }
    default:
        break;
    }
}

void CU::loadFromMemory(int reg, int memory_address, Registers& registers, Memory& memory) {
    registers[reg].setValue(memory.getValueAt(memory_address));
}

void CU::loadValue(int reg, int value, Registers& registers) {
    registers[reg].setValue(Utilities::Conversion::convertDecToHex(value));
}

void CU::storeInMemory(int reg, int memory_address, Registers& registers, Memory& memory) {
    memory.setValueAt(memory_address, registers[reg].getValue());
}

void CU::jumpIfEqual(int reg, int memory_address, Registers& registers, size_t& program_counter) {
    if (registers[reg].getValue() == registers[0].getValue()) {
        program_counter = memory_address;
    }
}

void CU::jumpIfGreater(int reg, int memory_address, Registers& registers, size_t& program_counter) {
    int reg_value = std::stoi(registers[reg].getValue(), nullptr, 16);
    int zero_reg_value = std::stoi(registers[0].getValue(), nullptr, 16);
    if (reg_value > zero_reg_value) {
        program_counter = memory_address;
    }
}

bool CU::isScreen(int reg, int memory_address) {
    return memory_address == 0x00;
}

void CU::move(int reg1, int reg2, Registers& registers) {
    registers[reg1].setValue(registers[reg2].getValue());
}
