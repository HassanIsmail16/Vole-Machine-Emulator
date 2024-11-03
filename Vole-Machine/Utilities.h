#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>
#include <wincrypt.h>

namespace Utilities {
	class Validation {
	public:
		static bool isValidInstruction(std::string& instruction_string);
		static bool isValidMemoryAddress(std::string& address);
		static bool isValidRegisterIndex(char& index);
		static bool isValidHexChar(char& ch);
		static bool isValidMemoryCellValue(std::string& cell_value);
	};

	class Conversion {
	public:
		static System::String^ convertStdStringToSystemString(std::string& string);
		static std::string convertSystemStringToStdString(System::String^ string);
		
		static std::string convertHexToDec(const std::string& hex);
		static std::string convertDecToHex(const int integer);
		static std::string convertIntToBin(int integer);

		static std::string convertFracToBin(double fraction, int precision = 8);

		static std::string convertDecToBin(double decimal);

		static double convvertBinToFloat(std::string& binary);

		static std::string convertFloatToBin(double decimal);

		static void clampFloatingValue(double& floating_point_value);
		static int convertHexToTwosComplementInt(const std::string& hex);
	};
}
