#include "Machine.h"
#include "InstructionValidator.h"
#include <fstream>

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
