#include "MemoryController.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

void MemoryController::memoryUpdated() {
	this->memory_updated();
}

void MemoryController::memoryUpdatedAtAddress(int index) {
    this->memory_updated_at_address(index);
}

System::String^ MemoryController::getMemoryValueAt(int index) {
	return Utilities::Conversion::convertStdStringToSystemString(this->machine->getMemory().getValueAt(index));
}

void MemoryController::setMemoryValueAt(int index, System::String^ new_value) {
	this->machine->getMemory().setValueAt(index, Utilities::Conversion::convertSystemStringToStdString(new_value));
}

void MemoryController::loadFromFile(std::string filename) {
	this->machine->loadProgramFromFile(filename);
	this->memoryUpdated();
}

void MemoryController::loadFromText(System::String^ text) {
    std::string text_string = Utilities::Conversion::convertSystemStringToStdString(text);
    this->machine->loadProgramFromTextBox(text_string);
    this->memoryUpdated();
}

void MemoryController::resetMemory() {
	this->machine->getMemory().clearMemory();
	this->memoryUpdated();
}

bool MemoryController::isMemoryEmpty() {
    return this->machine->getMemory().isEmpty();
}

bool MemoryController::isUpdatingMemoryList() {
    return this->is_updating_memory_list;
}

void MemoryController::exportToFile(std::string filename) {
    if (!machine) {
        throw std::runtime_error("Machine object is not initialized.");
    }

    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (int i = 0; i < 128; i += 2) {
        std::string opcode = machine->getMemory().getValueAt(i);
        std::string operand = machine->getMemory().getValueAt(i + 1);
        outfile << opcode << operand << " ";
    }

    outfile.close();
}



