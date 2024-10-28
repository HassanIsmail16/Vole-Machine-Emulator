#include "ALU.h"
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

    // interpret binary as floating-point representation and convert value to decimal flaot number.
    double floating_pointS = binaryToFloat(binaryS);
    double floating_pointT = binaryToFloat(binaryT);;

    // Floating point addition
    double floating_pointR = floating_pointS + floating_pointT;

    // convert back to floting-point binary representation


    // binary to hex


    // store the result in regeister R

}

std::string ALU::hexToDec(const std::string& hex_value) {
    int decimalValue = std::stoi(hex_value, nullptr, 16);
    return std::to_string(decimalValue);
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

double ALU::binaryToFloat(const std::string& binary) {
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
    std::string exponent_bits = integerToBinary(pow(2, exponent + bias));
    exponent_bits.insert(0, 3 - exponent_bits.size(), '0'); // make sure the exponent is 3-bits

    // extract mantissa
    std::string mantissa_bits = normal_binary.substr(significant_bit_position);
    mantissa_bits.erase(mantissa_bits.find('.'));
    mantissa_bits.insert(mantissa_bits.end(), 4 - mantissa_bits.size(), '0'); // make sure the mantissa is 4-bits

    // represent the floating point number
    std::string floating_point_representation = sign_bit + exponent_bits + mantissa_bits;
    return floating_point_representation;
}