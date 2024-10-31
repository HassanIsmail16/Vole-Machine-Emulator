#include "MemoryController.h"
#include "Utilities.h"
#include <iostream>

System::String^ MemoryController::getMemoryValueAt(int& index) {
	return Utilities::Conversion::convertStdStringToSystemString(this->machine->getMemory().getValueAt(index));
}

void MemoryController::updateMemoryValueAt(int index, System::String^ new_value) {
	this->machine->getMemory().setValueAt(index, Utilities::Conversion::convertSystemStringToStdString(new_value));
}

void MemoryController::loadFromFile(std::string filename) {
	this->machine->loadProgram(filename);
	this->memory_updated();
}

