#pragma once
#include "StorageUnit.h"
#include <array>

typedef std::array<StorageUnit, 16> Registers;
typedef std::array<StorageUnit, 256> MainMemory;

class ALU {
public:
    void addTwoComp(int regR, int regS, int regT, Registers& registers);
    void addFloatingPoint(int regR, int regS, int regT, Registers& registers);
    std::string hexToDec(const std::string& hex_value);
};

