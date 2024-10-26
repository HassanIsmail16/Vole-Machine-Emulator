#pragma once
#include "StorageUnit.h"
#include <array>

class ALU {
public:
    void addTwoComp(int RegR, int RegS, int RegT, std::array<StorageUnit, 16>& registers);
    void addFloatingPoint(int RegR, int RegS, int RegT, std::array<StorageUnit, 16>& registers);
    std::string hexToDec();
};
