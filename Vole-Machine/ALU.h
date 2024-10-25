#pragma once
#include "StorageUnit.h"

class ALU {
public:
    void addTwoComp(int Reg1, int Reg2, std::array<StorageUnit, 16>& Register);
    void addFloatingPoint(int Reg1, int Reg2, std::array<StorageUnit, 16>& Register);
    std::string hexToDec();
};