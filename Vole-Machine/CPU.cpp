#include "CPU.h"

CPU::CPU(MemoryPtr memory) {
	this->memory_interface = memory;
	this->initializeInstructionSet();
	this->clearRegisters();
	this->clearMemory();
	this->program_counter = 0;
	this->instruction_register = Instruction();
}

void CPU::runAllInstructions() {
	while (!this->isHalt()) {
		this->fetch();
		this->executeFetchedInstruction();
	}

	this->halt();
}

void CPU::fetch() {
	std::string first_cell_value = (*this->memory_interface)[this->program_counter].getValue();
	std::string second_cell_value = (*this->memory_interface)[this->program_counter + 1].getValue();

	this->instruction_register = Instruction(first_cell_value + second_cell_value);
	this->program_counter += 2;
}

void CPU::executeFetchedInstruction() {
	this->instruction_set[this->instruction_register.op_code](this->instruction_register.operands);
}

void CPU::loadFromMemory(std::string operands) {
	size_t R = hexToDec(std::to_string(operands[0]));
	size_t XY = hexToDec(operands.substr(1));

	this->registers[R].setValue((*this->memory_interface)[XY].getValue());
}

void CPU::loadValue(std::string operands) {
	size_t R = hexToDec(std::to_string(operands[0]));
	std::string XY = operands.substr(1);

	this->registers[R].setValue(XY);
}

void CPU::storeInMemory(std::string operands) {
	if (this->isWritingToScreen(operands)) {
		this->writeToScreen(operands);
		return;
	}

	size_t R = hexToDec(std::to_string(operands[0]));
	size_t XY = hexToDec(operands.substr(1));

	(*this->memory_interface)[XY].setValue(this->registers[R].getValue());
}

