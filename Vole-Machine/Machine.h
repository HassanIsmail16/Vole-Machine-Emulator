#pragma once
#include "CPU.h"
#include <array>

class Machine {
private:
    CPU processor;
    MainMemory memory;

public:
    void loadProgram();
    void outputState();
};