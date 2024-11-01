#include "MemoryController.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

void MemoryController::memoryUpdated() {
	if (this->is_updating_memory_list) {
		return;
	}

	this->is_updating_memory_list = true;
	this->memory_updated();
	this->is_updating_memory_list = false;
}

System::String^ MemoryController::getMemoryValueAt(int& index) {
	return Utilities::Conversion::convertStdStringToSystemString(this->machine->getMemory().getValueAt(index));
}

void MemoryController::updateMemoryValueAt(int index, System::String^ new_value) {
	this->machine->getMemory().setValueAt(index, Utilities::Conversion::convertSystemStringToStdString(new_value));
}

void MemoryController::loadFromFile(std::string filename) {
	this->machine->loadProgram(filename);
	this->memoryUpdated();
}

void MemoryController::resetMemory() {
	this->machine->getMemory().clearMemory();
	this->memoryUpdated();
}

void MemoryController::exportToFile(std::string filename) {
	std::ofstream outfile(filename);

	if (!outfile.is_open()) 
		throw std::runtime_error("Could not open file for writing");

		for (int i = 0; i < 128; i+=2)
		{
			std::string opcode = this->machine->getMemory().getValueAt(i);
			std::string operand = this->machine->getMemory().getValueAt(i + 1);
			outfile << opcode << operand << " ";
		}

	outfile.close();
}

