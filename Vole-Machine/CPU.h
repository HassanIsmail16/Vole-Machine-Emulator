#pragma once
#include "Instruction.h"
#include "StorageUnit.h"
#include <functional>
#include <string>
#include <array>
#include <memory>
#include <unordered_map>

enum class OP_CODE : char {
	LOAD_M   = '1',
	LOAD_V   = '2',
	STORE    = '3',
	MOVE     = '4',
	ADD      = '5',
	ADD_F    = '6',
	JUMP     = 'B',
	HALT     = 'C'
};

typedef std::shared_ptr<std::array<StorageUnit, 256>> MemoryPtr;

class CPU {
public:
	CPU(MemoryPtr memory);
	void runAllInstructions();

private:
	void fetch(); // program counter fetches the next instruction from memory and places it into instruction register
	void executeFetchedInstruction(); // executes the instruction in instruction register

	void loadFromMemory(std::string operands); // 1RXY
	void loadValue(std::string operands); // 2RXY
	
	void storeInMemory(std::string operands); // 3RXY
	void writeToScreen(std::string operands); // 3R00
	bool isWritingToScreen(Instruction instruction);

	void move(std::string operands); // 40RS

	void addTwoComplement(std::string operands); // 5RST
	void addFloatingPoint(std::string operands); // 6RST

	void jumpTo(std::string operands); // BRXY
	bool canJump(std::string operands);

	void halt(); // C000
	bool isHalt(); /// is the instruction inside the IR a halt instruction 

	void clearRegisters(); // reset all registers to "00"
	void clearMemory(); // reset all memory cells to "00"

	void initializeInstructionSet();


	std::array<StorageUnit, 16> registers;
	MemoryPtr memory_interface;
	size_t program_counter;
	Instruction instruction_register;
	std::unordered_map<char, std::function<void(std::string)>> instruction_set;

};

