#include "ALU.h"
#include <sstream>
#include <iomanip>
#include <array>
#include <string>

void ALU::addTwoComp(int RegR, int RegS, int RegT, std::array<StorageUnit, 16>& registers) {

    int valueS = std::stoi(registers[RegS].getValue(), nullptr, 16); // convert hex to int
    int valueT = std::stoi(registers[RegT].getValue(), nullptr, 16);
    int result = valueS + valueT;

    // Handle two's complement overflow
    if (result > 127) {
        result -= 256;
    }
    else if (result < -128) {
        result += 256;
    }

    std::stringstream stream;
    stream << std::hex << (result & 0xFF);
    registers[RegR].setValue(stream.str());
}

void ALU::addFloatingPoint(int RegR, int RegS, int RegT, std::array<StorageUnit, 16>& registers) {
    
}

std::string hexToDec(const std::string& hexValue) {
    int decimalValue = std::stoi(hexValue, nullptr, 16);
    return std::to_string(decimalValue);
}
