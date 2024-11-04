#include "Memory.h"
#include <iostream>

void Memory::addInstruction(std::string instruction) {
	if (this->last_added_instruction_index == 256) {
		return;
	} // skip if memory is full

	this->setValueAt(this->last_added_instruction_index, instruction.substr(0, 2));
	this->setValueAt(this->last_added_instruction_index + 1, instruction.substr(2));

	this->last_added_instruction_index += 2; // shift last added instruction index
}

std::string Memory::getValueAt(const size_t index) {
	return this->memory[index].getValue();
}

void Memory::setValueAt(const size_t index, StorageUnit& value) {
	this->memory[index].setValue(value.getValue());
}

void Memory::setValueAt(const size_t index, std::string& value) {
	if (value.size() > 2) {
		throw "attempted to add a " + value.size() + "-char long value to memory";
	}

	this->memory[index].setValue(value);
}

void Memory::clearValueAt(const size_t index) {
	this->memory[index].clear();
}

void Memory::clearMemory() {
	for (auto &cell : this->memory) {
		cell.clear();
	}

	this->last_added_instruction_index = 0;		
}

bool Memory::isEmpty() {
	return this->last_added_instruction_index == 0;
}
