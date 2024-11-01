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
	return instruction_register == "Cxxx";
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

std::string CPU::getRegisterValueAt(int index) {
	return this->registers[index].getValue();
}

void CPU::setRegisterValueAt(int index, std::string& value) {
	this->registers[index].setValue(value);
}

size_t& CPU::getProgramCounter() {
	return program_counter;
}

std::string CPU::getCurrentInstruction() {
	return this->instruction_register;
}
