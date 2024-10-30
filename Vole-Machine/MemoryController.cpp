#include "MemoryController.h"

void MemoryController::onMemoryUpdated() {
	return;
}

void MemoryController::loadFromFile(std::string filename) {
	this->machine->loadProgram(filename);

	this->onMemoryUpdated();
}