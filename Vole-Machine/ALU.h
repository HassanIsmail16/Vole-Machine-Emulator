#pragma once
#include "StorageUnit.h"
#include <array>

typedef std::array<StorageUnit, 16> Registers;
typedef std::array<StorageUnit, 256> MainMemory;

class ALU {
public:
    void addTwoComp(int regR, int regS, int regT, Registers& registers);
    void addFloatingPoint(int regR, int regS, int regT, Registers& registers);
    std::string hexToDec(const std::string& hex);
    std::string ALU::decToHex(int integer);
    std::string integerToBinary(int num);
    std::string fractionToBinary(double fraction, int precision = 8);
    std::string decimalToBinary(double decimal);
    double binaryToFloat(std::string& binary);
    std::string floatToBinary(double decimal);
    void clampFloatingValue(double& floating_point_value);
    int hexToInt(std::string hex);
};

