#include "ALU.h"
#include "Utilities.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
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
    // hex to int
    int valueS = std::stoi(registers[regS].getValue(), nullptr, 16);
    int valueT = std::stoi(registers[regT].getValue(), nullptr, 16);

    // int to binary
    std::string binaryS = Utilities::Conversion::convertIntToBin(valueS);
    std::string binaryT = Utilities::Conversion::convertIntToBin(valueT);

    // interpret binary as floating-point representation and convert value to decimal float number.
    double floating_pointS = Utilities::Conversion::convvertBinToFloat(binaryS);
    double floating_pointT = Utilities::Conversion::convvertBinToFloat(binaryT);

    // Floating point addition
    double floating_pointR = floating_pointS + floating_pointT;
    Utilities::Conversion::clampFloatingValue(floating_pointR);

    // convert back to floating-point binary representation
    std::string floating_point_representationR = Utilities::Conversion::convertFloatToBin(floating_pointR);

    // binary to int
    int valueR = std::stoi(floating_point_representationR, nullptr, 2);

    // int to hex
    std::string final_result = Utilities::Conversion::convertDecToHex(valueR);

    // store the result in regeister R
    registers[regR].setValue(final_result);
}

void ALU::bitwiseOr(int regR, int regS, int regT, Registers& registers) {
    int valueS = std::stoi(registers[regS].getValue(), nullptr, 16);
    int valueT = std::stoi(registers[regT].getValue(), nullptr, 16);
    int result = valueS | valueT;
    registers[regR].setValue(Utilities::Conversion::convertDecToHex(result));
}

void ALU::bitwiseAnd(int regR, int regS, int regT, Registers& registers) {
    int valueS = std::stoi(registers[regS].getValue(), nullptr, 16);
    int valueT = std::stoi(registers[regT].getValue(), nullptr, 16);
    int result = valueS & valueT;
    registers[regR].setValue(Utilities::Conversion::convertDecToHex(result));
}

void ALU::bitwiseXor(int regR, int regS, int regT, Registers& registers) {
    int valueS = std::stoi(registers[regS].getValue(), nullptr, 16);
    int valueT = std::stoi(registers[regT].getValue(), nullptr, 16);
    int result = valueS ^ valueT;
    registers[regR].setValue(Utilities::Conversion::convertDecToHex(result));
}

void ALU::rotateRight(int regR, int steps, Registers& registers) {
    int value = std::stoi(registers[regR].getValue(), nullptr, 16);
    value = (value >> steps) | (value << (8 - steps)) & 0xFF;
    registers[regR].setValue(Utilities::Conversion::convertDecToHex(value));
}

