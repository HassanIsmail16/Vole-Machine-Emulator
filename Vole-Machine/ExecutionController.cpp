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

void ExecutionController::screenUpdated(std::string value) {
	if (this->is_updating_screen) {
		return;
	}

	this->is_updating_screen = true;
	screen_updated(value);
	this->is_updating_screen = false;
}

void ExecutionController::speedChanged() {
	speed_changed();
}

void ExecutionController::fetchInstruction() {
	this->machine->getCPU().fetch(this->machine->getMemory());
	fetchedInstruction();
}

void ExecutionController::executeCurrentInstruction() { // TODO: Handle Halt
	if (!this->machine->getCPU().isInstructionPending()) {
		return;
	}

	std::vector<int> instruction = this->machine->getCPU().decode();
	this->machine->getCPU().execute(this->machine->getMemory(), instruction);

	if (instruction[0] == 3 && instruction[2] == 0) {
		screenUpdated(this->machine->getCPU().getRegisterValueAt(instruction[1]));
	}

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

int ExecutionController::getInstructionsPerSecond() {
	return this->instructions_per_sec;
}

void ExecutionController::setInstructionsPerSecond(int value) {
	this->instructions_per_sec = value;
}
