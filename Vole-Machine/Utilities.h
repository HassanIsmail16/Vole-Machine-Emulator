#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>
#include <wincrypt.h>

namespace Utilities {
	class Validation {
	public:
		static bool isValidInstruction(std::string& instruction_string);
		static bool isValidCode(std::string& code);
		static bool isValidMemoryAddress(std::string& address);
		static bool isValidRegisterIndex(char& index);
		static bool isValidHexChar(char& ch);
		static bool isValidMemoryCellValue(std::string& cell_value);
	};

	class Conversion {
	public:
		static System::String^ convertStdStringToSystemString(std::string& string);
		static std::string convertSystemStringToStdString(System::String^ string);

		static std::string convertStdStringToASCIIChar(std::string& string);
		
		static std::string convertASCIICharToStdString(char& ch);

		static std::string convertHexToDec(const std::string& hex);
		static int convertHexSystemStringToDecInt(System::String^ hex);
		static std::string convertDecToHex(const int integer);
		static std::string convertIntToBin(int integer);
		static std::string convertFracToBin(double fraction, int precision = 8);
		static std::string convertDecToBin(double decimal);
		static System::String^ convertDecToHexSystemString(int dec);
		static double convvertBinToFloat(std::string& binary);
		static std::string capitalize(std::string str);
		static std::string convertFloatToBin(double decimal);

		static void clampFloatingValue(double& floating_point_value);
		static int convertHexToTwosComplementInt(const std::string& hex);
	};
}
