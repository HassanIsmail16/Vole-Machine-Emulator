#include "Machine.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

void Machine::loadProgram(std::string& filename) {
	this->memory.clearMemory();

	std::fstream file(filename);

	std::string current_instruction;
	while (file >> current_instruction) {
		if (!Utilities::Validation::isValidInstruction(current_instruction)) {
			continue;
		} // skip instruction if not valid

		this->memory.addInstruction(current_instruction);
	}
}

CPU& Machine::getCPU() {
	return this->processor;
}

Memory& Machine::getMemory() {
	return this->memory;
}

// TODO: remove this
void Machine::displayMemory() { 
	std::cout << std::string(20, '-') << std::endl;
	for (int i = 0; i < 128; i += 2) {
		std::cout << this->memory.memory[i].getValue() << " " << this->memory.memory[i + 1].getValue() << std::endl;
	}
	std::cout << std::string(20, '-') << std::endl;
}
