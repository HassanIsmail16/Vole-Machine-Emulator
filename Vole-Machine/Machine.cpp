#include "Machine.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

void Machine::loadProgram(std::string& filename) {
	this->memory.clearMemory();

	for (int i = 0; i < this->processor.getStartingAddress() / 2; i++) {
		this->memory.addInstruction("0000");
	} // populate memory with empty instructions till starting address

	std::fstream file(filename);

	std::string current_instruction;
	while (file >> current_instruction) {
		if (!Utilities::Validation::isValidInstruction(current_instruction)) {
			continue;
		} // skip instruction if not valid

		this->memory.addInstruction(Utilities::Conversion::capitalize(current_instruction));
	}
}

CPU& Machine::getCPU() {
	return this->processor;
}

Memory& Machine::getMemory() {
	return this->memory;
}