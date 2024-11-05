#pragma once
#include "CPU.h"
#include "Memory.h"
#include <array>
#include <sstream>

class Machine {
private:
    CPU processor;
    Memory memory;

    void loadInstructions(std::istream& input);

public:
    void loadProgram(std::string& filename);
    void loadProgramFromTextBox(std::string inputText);
    CPU& getCPU();
    Memory& getMemory();
};