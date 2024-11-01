#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>

namespace Utilities {
	class InstructionValidation {
	public:
		static bool isValidInstruction(std::string& instruction_string);
		static bool isValidMemoryAddress(std::string& address);
		static bool isValidRegisterIndex(char& index);
		static bool isValidHexChar(char& ch);
	};

	class Conversion {
	public:
		static System::String^ convertStdStringToSystemString(std::string& string);
		static std::string convertSystemStringToStdString(System::String^ string);
	};
}