#pragma once
#include "Controller.h"
#include <string>

ref class MemoryController : public Controller {
public:
	MemoryController(Machine* machine): Controller(machine) {}
	
	// memory updated 
	delegate void MemoryUpdatedEventHandler();
	event MemoryUpdatedEventHandler^ memory_updated;
	void memoryUpdated();

	// memory updated at address
	delegate void MemoryUpdatedAtAddressEventHandler(int index);
	event MemoryUpdatedAtAddressEventHandler^ memory_updated_at_address;
	void memoryUpdatedAtAddress(int index);


	// accessors
	System::String^ getMemoryValueAt(int index);
	void setMemoryValueAt(int index, System::String^ new_value);

	void loadFromFile(std::string filename);
	void loadFromText(System::String^ text);

	void exportToFile(std::string filename);

	void resetMemory();
	bool isMemoryEmpty();

	bool isUpdatingMemoryList();

private:
	bool is_updating_memory_list = false;
};

