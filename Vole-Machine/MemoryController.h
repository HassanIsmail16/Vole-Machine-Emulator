#pragma once
#include "Controller.h"
#include <string>

ref class MemoryController : public Controller {
public:
	MemoryController(Machine* machine): Controller(machine) {}
	
	delegate void MemoryUpdatedEventHandler(Object^ sender, EventArgs^ e);
	event MemoryUpdatedEventHandler^ memory_updated;

	void onMemoryUpdated();
	void loadFromFile(std::string filename);

private:

};

