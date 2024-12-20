#include "Utilities.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <array>
#include <string>
using namespace Utilities;

bool Validation::isValidInstruction(std::string& instruction_string) {
	if (instruction_string.size() != 4) {
		return false;
	}

	if ((instruction_string[0] >= '1' && instruction_string[0] <= '3')
		|| (toupper(instruction_string[0]) == 'B') || (toupper(instruction_string[0]) == 'D')) {
		return isValidRegisterIndex(instruction_string[1]) && isValidMemoryAddress(instruction_string.substr(2));
	} // validate LOAD, STORE, and JUMP

	if (instruction_string[0] == '4') {
		return isValidRegisterIndex(instruction_string[2]) && isValidRegisterIndex(instruction_string[3]);
	} // validate MOVE 

	if (instruction_string[0] >= '5' && instruction_string[0] <= '9') {
		return isValidRegisterIndex(instruction_string[1]) &&
			isValidRegisterIndex(instruction_string[2]) && isValidRegisterIndex(instruction_string[3]);
	} // validate ADD

	if (toupper(instruction_string[0]) == 'A') {
		return isValidRegisterIndex(instruction_string[1]) && isValidHexChar(instruction_string[3]);
	} // validate MOVE 

	if (toupper(instruction_string[0]) == 'C') {
		return true;
	} // validate HALT

	return false;
}

bool Utilities::Validation::isValidCode(std::string& code) {
	if (code.size() != 2) {
		return false;
	}

	if ((code[0] >= '1' && code[0] <= '3') || (toupper(code[0]) == 'B') || (toupper(code[0]) == 'D')) {
		return isValidRegisterIndex(code[1]);
	}

	if (code[0] == '4') {
		return true;
	}

	if (code[0] >= '5' && code[0] <= '9') {
		return isValidRegisterIndex(code[1]);
	}

	if (toupper(code[0] == 'A')) {
		return isValidRegisterIndex(code[1]);
	}

	if (toupper(code[0] == 'C')) {
		return true;
	}

	return false;
}

bool Validation::isValidMemoryAddress(std::string& address) {
	if (address.size() != 2) {
		return false;
	}

	return isValidHexChar(address[0]) && isValidHexChar(address[1]);
}

bool Validation::isValidRegisterIndex(char& index) {
	return (index >= '0' && index <= '9') || (toupper(index) >= 'A' && toupper(index) <= 'F');
}

bool Validation::isValidHexChar(char& ch) {
	return (ch >= '0' && ch <= '9') || (toupper(ch) >= 'A' && toupper(ch) <= 'F');
}

bool Utilities::Validation::isValidMemoryCellValue(std::string& cell_value) {
	if (cell_value.size() == 2) {
		return isValidHexChar(cell_value[0]) && isValidHexChar(cell_value[1]);
	}

	if (cell_value.size() == 1) {
		return isValidHexChar(cell_value[0]);
	}

	if (cell_value.size() == 0) {
		return true;
	}
	
	return false;
}

System::String^ Conversion::convertStdStringToSystemString(std::string& string) {
	System::String^ result = gcnew System::String(string.c_str());
	return result;
}

std::string Conversion::convertSystemStringToStdString(System::String^ string) {
	return msclr::interop::marshal_as<std::string>(string);
}

std::string Utilities::Conversion::convertStdStringToASCIIChar(std::string& string) {
	int ascii_code = std::stoi(string, nullptr, 16);
	char char_result = char(ascii_code);
	std::string result = "";
	result.push_back(char_result); 
	return result;
}

std::string Utilities::Conversion::convertASCIICharToStdString(char& ch) {
	int ascii_code = int(ch);
	std::string result = Conversion::convertDecToHex(ascii_code);
	return result;
}


std::string Conversion::convertHexToDec(const std::string& hex) {
	int decimalValue = std::stoi(hex, nullptr, 16);
	return std::to_string(decimalValue);
}

int Utilities::Conversion::convertHexSystemStringToDecInt(System::String^ hex) {
	return stoi(
		Conversion::convertHexToDec(
			Conversion::convertSystemStringToStdString(hex)
		)
	);
}

std::string Conversion::convertDecToHex(const int integer) {
	std::stringstream stream;
	stream << std::hex << (integer & 0xFF);
	std::string result = stream.str();
	std::transform(result.begin(), result.end(), result.begin(), ::toupper);

	return result;
}

std::string Conversion::convertIntToBin(int integer) {
	if (integer == 0) {
		return "0";
	}

	std::string binary = "";
	while (integer > 0) {
		binary = std::to_string(integer % 2) + binary;
		integer /= 2;
	}

	return binary;
}

std::string Conversion::convertFracToBin(double fraction, int precision) {
	std::string binary_fraction = ".";
	while (fraction > 0 && precision-- > 0) {
		fraction *= 2;
		if (fraction >= 1) {
			binary_fraction += "1";
			fraction -= 1;
		}
		else {
			binary_fraction += "0";
		}
	}
	return binary_fraction;
}


std::string Conversion::convertDecToBin(double decimal) {
	int integer = int(decimal);
	double fraction = decimal - integer;

	std::string binary = Conversion::convertIntToBin(integer) + Conversion::convertFracToBin(fraction);
	return binary;
}

System::String^ Conversion::convertDecToHexSystemString(int dec) {
	return convertStdStringToSystemString(Conversion::convertDecToHex(dec));
}

double Conversion::convvertBinToFloat(std::string& binary) {
	// make sure it's 8-bits
	binary.insert(0, 8 - binary.size(), '0');

	int sign = (binary[0] == '0' ? 1 : -1); // 1-bit sign

	// 3-bit exponent
	int exponent = 4 * std::stoi(std::to_string(binary[1] - '0'))
		+ 2 * std::stoi(std::to_string(binary[2] - '0'))
		+ 1 * std::stoi(std::to_string(binary[3] - '0'));


	// 4-bit mantissa
	double mantissa = 0.5 * std::stoi(std::to_string(binary[4] - '0'))
		+ 0.25 * std::stoi(std::to_string(binary[5] - '0'))
		+ 0.125 * std::stoi(std::to_string(binary[6] - '0'))
		+ 0.0625 * std::stoi(std::to_string(binary[7] - '0'));


	// get float value using explicit normalization
	const int BIAS = 4;
	double result = sign * mantissa * pow(2, exponent - BIAS);
	Conversion::clampFloatingValue(result);
	return result;
}

std::string Utilities::Conversion::capitalize(std::string str) {
	for (char& ch : str) {
		ch = toupper(ch);
	}

	return str;
}

std::string Conversion::convertFloatToBin(double decimal) {
	// extract the sign
	char sign_bit = (decimal >= 0 ? '0' : '1');

	// extract the exponent bits
	std::string normal_binary = Conversion::convertDecToBin(abs(decimal));
	int radix_point_position = normal_binary.find('.');
	int significant_bit_position = normal_binary.find('1');

	// calculate the shift exponent
	int exponent;
	// shift left
	if (radix_point_position > significant_bit_position) {
		exponent = radix_point_position - significant_bit_position;
	}
	// shift right (or no shift)
	else {
		exponent = radix_point_position - significant_bit_position + 1;
	}

	// normalize
	const int BIAS = 4;
	std::string exponent_bits = Conversion::convertIntToBin(exponent + BIAS);
	exponent_bits.insert(0, 3 - exponent_bits.size(), '0'); // make sure the exponent is 3-bits

	// extract mantissa
	std::string mantissa_bits;
	for (int i = significant_bit_position; i < normal_binary.size(); i++) {
		// skip the radix point
		if (normal_binary[i] != '.') {
			mantissa_bits.push_back(normal_binary[i]);
		}

		// don't take more than 4 bits
		if (mantissa_bits.size() == 4) {
			break;
		}
	}

	// make sure the mantissa is 4-bits
	mantissa_bits.insert(mantissa_bits.end(), 4 - mantissa_bits.size(), '0');

	// represent the floating point number
	std::string floating_point_representation = sign_bit + exponent_bits + mantissa_bits;
	return floating_point_representation;
}

void Conversion::clampFloatingValue(double& floating_point_value) {
	if (floating_point_value > 7.5) {
		floating_point_value = 7.5;
	}

	if (floating_point_value < -7.5) {
		floating_point_value = -7.5;
	}
}

int Conversion::convertHexToTwosComplementInt(const std::string& hex) {
	std::string dec = Conversion::convertHexToDec(hex);

	std::string binary = Conversion::convertIntToBin(std::stoi(dec));

	// fill the 8-bits for two's comp
	binary.insert(0, 8 - binary.size(), '0');



	if (binary[0] == '1') {  // negative in two's complement
		// Invert the bits
		for (char& bit : binary) {
			bit = (bit == '0') ? '1' : '0';
		}

		// Convert to decimal and add 1
		int intValue = std::stoi(binary, nullptr, 2);
		return -(intValue + 1);
	}
	else {
		return std::stoi(binary, nullptr, 2);
	}
}
