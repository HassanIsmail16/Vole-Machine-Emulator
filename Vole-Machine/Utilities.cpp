#include "Utilities.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <array>
#include <string>
using namespace Utilities;

bool InstructionValidation::isValidInstruction(std::string& instruction_string) {
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

bool InstructionValidation::isValidMemoryAddress(std::string& address) {
	if (address.size() != 2) {
		return false;
	}

	return isValidHexChar(address[0]) && isValidHexChar(address[1]);
}

bool InstructionValidation::isValidRegisterIndex(char& index) {
	return (index >= '0' && index <= '9') || (toupper(index) >= 'A' && toupper(index) <= 'F');
}

bool InstructionValidation::isValidHexChar(char& ch) {
	return (ch >= '0' && ch <= '9') || (toupper(ch) >= 'A' && toupper(ch) <= 'F');
}

System::String^ Conversion::convertStdStringToSystemString(std::string& string) {
	System::String^ result = gcnew System::String(string.c_str());
	return result;
}

std::string Utilities::Conversion::convertSystemStringToStdString(System::String^ string) {
	return msclr::interop::marshal_as<std::string>(string);
}


std::string Utilities::Conversion::convertHexToDec(const std::string& hex) {
	int decimalValue = std::stoi(hex, nullptr, 16);
	return std::to_string(decimalValue);
}

std::string Utilities::Conversion::convertDecToHex(const int integer) {
	std::stringstream stream;
	stream << std::hex << (integer & 0xFF);
	std::string result = stream.str();
	std::transform(result.begin(), result.end(), result.begin(), ::toupper);
	return result;
}
