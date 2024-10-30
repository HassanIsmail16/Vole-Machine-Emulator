#pragma once
#include "StorageUnit.h"
#include "ALU.h"          
#include <array>
#include <vector> 
#include <map>

enum class OP_CODE : int {
	LOAD_M = 1,
	LOAD_V = 2,
	STORE = 3,
	MOVE = 4,
	ADD = 5,
	ADD_F = 6,
	JUMP = 11,
	HALT = 12,
};

class CU {
public:
    void executeInstruction(const std::vector<int>& instruction, Registers& registers, MainMemory& memory, ALU& alu, size_t& program_counter);
    void loadFromMemory(int reg, int memory_address, Registers& registers, MainMemory& memory);
    void loadValue(int reg, const std::string& value, Registers& registers);
    void storeInMemory(int reg, int memory_address, Registers& registers, MainMemory& memory);
    void jumpTo(int reg, int memory_address, Registers& registers, size_t& program_counter);
    bool isScreen(int reg, int memory_address);
    void move(int reg1, int reg2, Registers& registers);
};

