#pragma once
#include "StorageUnit.h"
#include "ALU.h"  
#include "memory.h"
#include <array>
#include <vector> 
#include <map>

enum class OP_CODE : int {
    LOAD_M = 1,      // RXY: Copy content of RAM cell XY to register R
    LOAD_V = 2,      // RXY: Copy bit-string XY to register R
    STORE = 3,       // RXY: Copy content of register R to RAM cell XY
    MOVE = 4,        // xRS: Copy content of register R to register S
    ADD = 5,         // RST: Add content of registers S and T, result in R (two's complement)
    ADD_F = 6,       // RST: Add content of registers S and T, result in R (floating-point)
    BIT_OR = 7,      // RST: Bitwise OR of registers S and T, result in R
    BIT_AND = 8,     // RST: Bitwise AND of registers S and T, result in R
    BIT_XOR = 9,     // RST: Bitwise XOR of registers S and T, result in R
    ROTATE = 10,     // RxX: Rotate register R right by X steps
    JUMP_EQ = 11,    // RXY: Jump to RAM cell XY if register R equals register 0
    HALT = 12,       // xxx: Halt execution
    JUMP_GT = 13,     // RXY: Jump to RAM cell XY if register R > register 0 (two's complement)
    UNKNOWN = 0       // 0xxx: undefined instruction
};

class CU {
public:
    void executeInstruction(const std::vector<int>& instruction, Registers& registers, Memory& memory, ALU& alu, size_t& program_counter);
    void loadFromMemory(int reg, int memory_address, Registers& registers, Memory& memory);
    void loadValue(int reg, int value, Registers& registers);
    void storeInMemory(int reg, int memory_address, Registers& registers, Memory& memory);
    void jumpIfEqual(int reg, int memory_address, Registers& registers, size_t& program_counter);
    void jumpIfGreater(int reg, int memory_address, Registers& registers, size_t& program_counter);
    void move(int reg1, int reg2, Registers& registers);
};
