#pragma once
#include "CPU.h"
#include "Memory.h"
#include <array>

class Machine {
private:
    CPU processor;
    Memory memory;

public:
    void loadProgram(std::string& filename);
    void outputState();
    CPU& getCPU();
    Memory& getMemory();
};