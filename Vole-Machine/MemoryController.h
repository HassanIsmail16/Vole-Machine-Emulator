#pragma once
#include "Controller.h"
#include <string>

ref class MemoryController : public Controller {
public:
	MemoryController(Machine* machine): Controller(machine) {}
	
	delegate void MemoryUpdatedEventHandler();
	event MemoryUpdatedEventHandler^ memory_updated;

	System::String^ getMemoryValueAt(int& index);
	void updateMemoryValueAt(int index, System::String^ new_value);

	void loadFromFile(std::string filename);

	bool is_updating_memory_list = false;
};

