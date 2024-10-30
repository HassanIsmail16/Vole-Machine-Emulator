#include "InstructionValidator.h"

bool InstructionValidator::isValidInstruction(std::string& instruction_string) {
	if (instruction_string.size() != 4) {
		return false;
	}

	if ((instruction_string[0] >= '1' && instruction_string[0] <= '3')
		|| (toupper(instruction_string[0]) == 'B')) {
		return isValidRegisterIndex(instruction_string[1]) && isValidMemoryAddress(instruction_string.substr(2));
	} // validate LOAD, STORE, and JUMP

	if (instruction_string.substr(0, 2) == "40") {
		return isValidRegisterIndex(instruction_string[2]) && isValidRegisterIndex(instruction_string[4]);
	} // validate MOVE 

	if (instruction_string[0] == '5' || instruction_string[0] == '6') {
		return isValidRegisterIndex(instruction_string[1]) &&
			isValidRegisterIndex(instruction_string[2]) && isValidRegisterIndex(instruction_string[3]);
	} // validate ADD

	if (instruction_string == "C000") {
		return true;
	} // validate HALT

	return false;
}

bool InstructionValidator::isValidMemoryAddress(std::string& address) {
	if (address.size() != 2) {
		return false;
	}

	return isValidHexChar(address[0]) && isValidHexChar(address[1]);
}

bool InstructionValidator::isValidRegisterIndex(char& index) {
	return (index >= '0' && index <= '9') || (toupper(index) >= 'A' && toupper(index) <= 'F');
}

bool InstructionValidator::isValidHexChar(char& ch) {
	return (ch >= '0' && ch <= '9') || (toupper(ch) >= 'A' && toupper(ch) <= 'F');
}
