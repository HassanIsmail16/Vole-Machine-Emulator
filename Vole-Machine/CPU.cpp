#include "CPU.h"
#include "Memory.h"
#include "Utilities.h"
#include <iostream>
#include <algorithm>

CPU::CPU() {
	this->setProgramCounter(0);
	this->instruction_register = "";
	this->clearRegisters();
}

void CPU::runInstructions(Memory& memory) {
	while (!this->isHalt() && this->program_counter + 2 < 256) {
		this->fetch(memory);
		std::vector<int> instruction = this->decode();
		this->execute(memory, instruction);
	}
	this->halt();
}

void CPU::fetch(Memory& memory) {
	if (this->hasReachedEndOfMemory()) {
		this->setProgramCounter(this->starting_address);
	}

	std::string instruction1 = memory.getValueAt(this->program_counter);
	std::string instruction2 = memory.getValueAt(this->program_counter + 1);
	this->instruction_register = instruction1 + instruction2;
	this->program_counter += ((!this->isProgramCounterOdd() && this->program_counter == 254) ||
							 (this->isProgramCounterOdd() && this->program_counter == 253)) ? 1 : 2;
}

std::vector<int> CPU::decode() {
	if (!Utilities::Validation::isValidInstruction(this->instruction_register)) {
		return {};
	} // return special value if instruction is not valid

	std::vector<int> instruction;
	instruction.push_back(std::stoi(this->instruction_register.substr(0, 1), nullptr, 16));

	if ((instruction[0] >= 1 && instruction[0] <= 3) || instruction[0] == 11 || instruction[0] == 13) {
		instruction.push_back(std::stoi(this->instruction_register.substr(1, 1), nullptr, 16));
		instruction.push_back(std::stoi(this->instruction_register.substr(2, 2), nullptr, 16));
	} // handle RXY

	if (instruction[0] >= 4 && instruction[0] <= 10) {
		instruction.push_back(std::stoi(this->instruction_register.substr(1, 1), nullptr, 16));
		instruction.push_back(std::stoi(this->instruction_register.substr(2, 1), nullptr, 16));
		instruction.push_back(std::stoi(this->instruction_register.substr(3, 1), nullptr, 16));
	} // handle RST

	return instruction;
}

void CPU::execute(Memory& memory, std::vector<int> instruction) {
	this->cu.executeInstruction(instruction, registers, memory, alu, program_counter);
}

void CPU::clearRegisters() {
	for (auto& reg : registers) {
		reg.clear();
	}
}

bool CPU::isHalt() {
	return toupper(instruction_register[0]) == 'C';
}

void CPU::halt() {
	return;
}

bool CPU::isInstructionPending() {
	return !this->instruction_register.empty();
}

void CPU::resetProgram(int starting_address) {
	this->setProgramCounter(starting_address); // set PC to starting address
	this->starting_address = starting_address;
	this->instruction_register.clear();
}

int CPU::getStartingAddress() {
	return this->starting_address;
}

void CPU::setStartingAddress(int starting_address) {
	this->starting_address = starting_address;
	this->setProgramCounter(max(this->program_counter, starting_address));
}

std::string CPU::getRegisterValueAt(int index) {
	return this->registers[index].getValue();
}

void CPU::setRegisterValueAt(int index, std::string& value) {
	this->registers[index].setValue(value);
}

void CPU::setProgramCounter(int address) {
	this->program_counter = address;
	this->is_program_counter_odd == address % 2 == 1;
}

size_t& CPU::getProgramCounter() {
	return program_counter;
}

bool CPU::isProgramCounterOdd() {
	return this->is_program_counter_odd;
}

bool CPU::hasReachedEndOfMemory() {
	return (this->isProgramCounterOdd() && this->program_counter == 254) ||
		(!this->isProgramCounterOdd() && this->program_counter == 255);
}

std::string CPU::getCurrentInstruction() {
	return this->instruction_register;
}

void CPU::resetInstructionRegister() {
	this->instruction_register.clear();
}

