#include "ExecutionController.h"
#include "Utilities.h"
#include <iostream>

void ExecutionController::fetchedInstruction() {
	if (this->is_fetching_instruction) {
		return;
	}

	this->is_fetching_instruction = true;
	fetched_instruction();
	this->is_fetching_instruction = false;
}

void ExecutionController::decodedInstruction() {
	if (this->is_decoding_instruction) {
		return;
	}

	this->is_decoding_instruction = true;
	decoded_instruction();
	this->is_decoding_instruction = false;
}

void ExecutionController::executedInstruction() {
	if (this->is_executing_instruction) {
		return;
	}

	this->is_executing_instruction = true;
	executed_instruction();
	this->is_executing_instruction = false;
}

void ExecutionController::fetchInstruction() {
	this->machine->getCPU().fetch(this->machine->getMemory());
	fetchedInstruction();
}

void ExecutionController::executeCurrentInstruction() { // TODO: Handle Halt
	if (!this->machine->getCPU().isInstructionPending()) {
		return;
	}

	std::cout << "t1" << std::endl;


	this->machine->getCPU().execute(this->machine->getMemory(), this->machine->getCPU().decode());
	std::cout << "t2" << std::endl;

	executedInstruction();
}

void ExecutionController::resetProgram() {
	this->machine->getCPU().resetProgram();
	fetchedInstruction();
}

System::String^ ExecutionController::getCurrentAddress() {
	return this->machine->getCPU().getProgramCounter().ToString("X2");
}

System::String^ ExecutionController::getCurrentInstruction() {
	return Utilities::Conversion::convertStdStringToSystemString(this->machine->getCPU().getCurrentInstruction());
}
