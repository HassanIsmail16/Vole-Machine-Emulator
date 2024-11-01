#include "CPU.h"
#include "Memory.h"

CPU::CPU() {
	this->program_counter = 0;
	this->instruction_register = "";
	this->clearRegisters();
}

void CPU::runInstructions(Memory& memory) {
	while (!this->isHalt()) {
		this->fetch(memory);
		std::vector<int> instruction = this->decode();
		this->execute(memory, instruction);
	}
	this->halt();
}

void CPU::fetch(Memory& memory) {
	if (this->program_counter == 255) {
		this->program_counter = 0;
	}

	std::string instruction1 = memory.getValueAt(this->program_counter);
	std::string instruction2 = memory.getValueAt(this->program_counter + 1);
	this->instruction_register = instruction1 + instruction2;
	this->program_counter += (this->program_counter == 254) ? 1 : 2;
}

std::vector<int> CPU::decode() {
	std::vector<int> instruction;
	instruction.push_back(std::stoi(instruction_register.substr(0, 2), nullptr, 16)); // op-code
	instruction.push_back(std::stoi(instruction_register.substr(2, 2), nullptr, 16)); // operands
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
	return instruction_register == "C000";
}

void CPU::halt() {
	program_counter = 0;
	clearRegisters();
	instruction_register.clear();
}

bool CPU::isInstructionPending() {
	return !this->instruction_register.empty();
}

void CPU::resetProgram() {
	this->program_counter = 0;
	this->instruction_register.clear();
}

size_t& CPU::getProgramCounter() {
	return program_counter;
}

std::string CPU::getCurrentInstruction() {
	return this->instruction_register;
}
