#include "ALU.h"
#include <sstream>
#include <iomanip>
#include <array>
#include <string>

void ALU::addTwoComp(int regR, int regS, int regT, Registers& registers) {

    int valueS = std::stoi(registers[regS].getValue(), nullptr, 16); // convert hex to int
    int valueT = std::stoi(registers[regT].getValue(), nullptr, 16);
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
    registers[regR].setValue(stream.str());
}

void ALU::addFloatingPoint(int regR, int regS, int regT, Registers& registers) {
    
}

std::string ALU::hexToDec(const std::string& hex_value) {
    int decimalValue = std::stoi(hex_value, nullptr, 16);
    return std::to_string(decimalValue);
}
