#pragma once
#include <string>

struct Instruction {
	Instruction(): op_code('0'), operands("000") {}
	Instruction(std::string bit_pattern): op_code(bit_pattern[0]), operands(bit_pattern.substr(1)) {}
	char op_code;
	std::string operands;
};

