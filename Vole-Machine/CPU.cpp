#include "CPU.h"

CPU::CPU() {
	this->program_counter = 0;
	this->instruction_register = "";
	this->clearRegisters();
}

void CPU::runInstructions(MainMemory& memory) {
	while (!this->isHalt()) {
		this->fetch(memory);
		std::vector<int> instruction = this->decode();
		this->execute(this->registers, memory, instruction);
	}
	this->halt();
}

void CPU::fetch(MainMemory& memory) {
	std::string instruction1 = memory[this->program_counter].getValue();
	std::string instruction2 = memory[this->program_counter + 1].getValue();
	this->instruction_register = instruction1 + instruction2;
	this->program_counter += 2;
}

std::vector<int> CPU::decode() {
	std::vector<int> instruction;
	instruction.push_back(std::stoi(instruction_register.substr(0, 2), nullptr, 16)); // op-code
	instruction.push_back(std::stoi(instruction_register.substr(2, 2), nullptr, 16)); // operands
	return instruction;
}

void CPU::execute(Registers& registers, MainMemory& memory, std::vector<int> instruction) {
	this->cu.executeInstruction(instruction, registers, memory, alu);
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
