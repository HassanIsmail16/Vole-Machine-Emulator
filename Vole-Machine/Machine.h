#pragma once
#include "CPU.h"
#include <array>

class Machine {
private:
    CPU processor;
    std::array<StorageUnit, 256> memory;

public:
    void loadProgram();
    void outputState();
};