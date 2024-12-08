#include "Machine.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>


void Machine::loadInstructions(std::istream& input) {
    std::string temp; // temporary string to hold 4 characters

    char ch;
    while (input >> ch) {
        // only process hexadecimal characters (0-9, A-F, a-f)
        if (std::isxdigit(ch)) {
            temp += std::toupper(ch); // add character in uppercase to the temporary string

            // when we have 4 characters, validate and potentially add to memory
            if (temp.length() == 4) {
                if (Utilities::Validation::isValidInstruction(temp)) {
                    this->memory.addInstruction(temp); // Add valid instruction to memory
                }
                // clear to start collecting the next 4 characters
                temp.clear();
            }
        } // ignore non-hexadecimal characters (spaces, commas, etc.)
    }

    // handle any remaining characters
    if (!temp.empty() && Utilities::Validation::isValidCode(temp)) {
        // add the final code if it's valid
        this->memory.addCode(temp);
    }
}


void Machine::loadProgramFromFile(std::string& filename) {
    this->memory.clearMemory();
    this->memory.setLastAddedInstructionIndex(this->processor.getStartingAddress());

    std::ifstream file(filename);
    
    loadInstructions(file);
}


void Machine::loadProgramFromTextBox(std::string input_text) {
    this->memory.setLastAddedInstructionIndex(this->processor.getStartingAddress());

    std::istringstream input_stream(input_text);
    loadInstructions(input_stream);
}

CPU& Machine::getCPU() {
	return this->processor;
}

Memory& Machine::getMemory() {
	return this->memory;
}