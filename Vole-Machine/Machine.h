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
    void loadProgramFromFile(std::string& filename);
    void loadProgramFromTextBox(std::string input_text);
    CPU& getCPU();
    Memory& getMemory();
};