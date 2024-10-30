#include "Machine.h"
#include "InstructionValidator.h"
#include <fstream>
#include <iostream>

void Machine::loadProgram(std::string& filename) {
	std::fstream file(filename);

	std::string current_instruction;
	while (file >> current_instruction) {
		if (!InstructionValidator::isValidInstruction(current_instruction)) {
			continue;
		} // skip instruction if not valid

		this->memory.addInstruction(current_instruction);
	}
}

// TODO: remove this
void Machine::displayMemory() { 
	for (int i = 0; i < 128; i += 2) {
		std::cout << this->memory.memory[i].getValue() << " " << this->memory.memory[i + 1].getValue() << std::endl;
	}
}
