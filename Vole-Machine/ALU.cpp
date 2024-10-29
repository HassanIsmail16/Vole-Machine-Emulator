#include "ALU.h"
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
    std::string binaryS = integerToBinary(valueS);
    std::string binaryT = integerToBinary(valueT);

    // interpret binary as floating-point representation and convert value to decimal float number.
    double floating_pointS = binaryToFloat(binaryS);
    double floating_pointT = binaryToFloat(binaryT);;

    // Floating point addition
    double floating_pointR = floating_pointS + floating_pointT;
    clampFloatingValue(floating_pointR);

    // convert back to floating-point binary representation
    std::string floating_point_representationR = floatToBinary(floating_pointR);

    // binary to int
    int valueR = std::stoi(floating_point_representationR, nullptr, 2);

    // int to hex
    std::string final_result = decToHex(valueR);

    // store the result in regeister R
    registers[regR].setValue(final_result);
}

std::string ALU::hexToDec(const std::string& hex) {
    int decimalValue = std::stoi(hex, nullptr, 16);
    return std::to_string(decimalValue);
}

std::string ALU::decToHex(int integer) {
    std::stringstream stream;
    stream << std::hex << (integer & 0xFF);
    std::string result = stream.str();
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string ALU::integerToBinary(int integer) {
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

std::string ALU::fractionToBinary(double fraction, int precision) {
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

std::string ALU::decimalToBinary(double decimal) {
    int integer = int(decimal);
    double fraction = decimal - integer;

    std::string binary = integerToBinary(integer) + fractionToBinary(fraction);
    return binary;
}

double ALU::binaryToFloat(std::string& binary) {
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


    // Get float value using explicit normalization
    const int bias = 4;
    double result = sign * mantissa * pow(2, exponent - bias);
    clampFloatingValue(result);
    return result;
}

std::string ALU::floatToBinary(double decimal) {
    // extract the sign
    char sign_bit = (decimal >= 0 ? '0' : '1');

    // extract the exponent bits
    std::string normal_binary = decimalToBinary(abs(decimal));
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
    const int bias = 4;
    std::string exponent_bits = integerToBinary(exponent + bias);
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

void ALU::clampFloatingValue(double& floating_point_value) {
    if (floating_point_value > 7.5) {
        floating_point_value = 7.5;
    }

    if (floating_point_value < -7.5) {
        floating_point_value = -7.5;
    }
}

int ALU::hexToInt(std::string hex) {
    std::string dec = hexToDec(hex);

    std::string binary = integerToBinary(std::stoi(dec));

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
