#pragma once
#include "StorageUnit.h"
#include <array>
#include <string>

class Memory {
private:
	std::array<StorageUnit, 256> memory;
	int last_added_instruction_index;

public:
	Memory(): memory(), last_added_instruction_index(0) {}
	void addInstruction(std::string instruction);
	std::string getValueAt(const size_t index);
	void setValueAt(const size_t index, StorageUnit& value);
	void setValueAt(const size_t index, std::string& value);
	void clearValueAt(const size_t index);
	void clearMemory();
	bool isEmpty();
};