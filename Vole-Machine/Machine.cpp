#include "Machine.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

void Machine::loadProgram(std::string& filename) {
	this->memory.clearMemory();

	// begin adding instructions from the starting address
	this->memory.setLastAddedInstructionIndex(this->processor.getStartingAddress());

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