#pragma once
#include <string>

class InstructionValidator {
public:
	static bool isValidInstruction(std::string& instruction_string);
	static bool isValidMemoryAddress(std::string& address);
	static bool isValidRegisterIndex(char& index);
	static bool isValidHexChar(char& ch);
};