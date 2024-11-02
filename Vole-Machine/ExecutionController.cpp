#include "ExecutionController.h"
#include "Utilities.h"
#include <iostream>
#include <vector>

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

void ExecutionController::runAllInstructions() {
	this->is_running = true;
	while (true) {
		this->machine->getCPU().fetch(this->machine->getMemory());
		this->machine->getCPU().execute(this->machine->getMemory(), this->machine->getCPU().decode());

		if (this->machine->getCPU().isHalt()) {
			program_halted();
			break;
		}

		if (this->getCurrentAddress() == "FF") {
			reached_end_of_memory();
			break;
		}
	}
	this->all_instructions_executed();
	this->is_running = false;
}

void ExecutionController::fetchInstruction() {
	if (this->getCurrentAddress() == "FF") {
		reached_end_of_memory();
	}

	this->machine->getCPU().fetch(this->machine->getMemory());
	fetchedInstruction();
}

void ExecutionController::executeCurrentInstruction() { // TODO: Handle Halt
	if (!this->machine->getCPU().isInstructionPending()) {
		return;
	}

	std::vector<int> instruction = this->machine->getCPU().decode();
	
	if (this->machine->getCPU().isHalt()) {
		program_halted();
	}

	this->machine->getCPU().execute(this->machine->getMemory(), instruction);

	if (instruction[0] == 3 && instruction[2] == 0) {
		screenUpdated(this->machine->getCPU().getRegisterValueAt(instruction[1]));
	}

	executedInstruction();
}

void ExecutionController::step() {
	this->fetchInstruction();
	this->executeCurrentInstruction();
}

void ExecutionController::playInstructions() {
	if (instruction_timer == nullptr) {
		instruction_timer = gcnew System::Windows::Forms::Timer();
		instruction_timer->Interval = 1000 / instructions_per_sec;
		instruction_timer->Tick += gcnew System::EventHandler(this, &ExecutionController::OnTimerTick);
	}
	is_running = true;
	instruction_timer->Start();
}

void ExecutionController::pauseInstructions() {
	is_running = false;
	if (instruction_timer != nullptr) {
		instruction_timer->Stop();
	}
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

void ExecutionController::OnTimerTick(Object^ sender, System::EventArgs^ e) {
	if (is_running) {
		fetchInstruction();
		executeCurrentInstruction();
	}
}

void ExecutionController::updateSpeed(int new_speed) {
	this->InstructionsPerSecond = new_speed;
}

System::Nullable<int> ExecutionController::getUpdatedAddress() {
	auto current_instruction = this->getCurrentInstruction();

	if (current_instruction->Length == 0) {
		return System::Nullable<int>();
	}
	
	if (current_instruction[0] == '3') {
		return System::Convert::ToInt32(current_instruction->Substring(2, 2), 16);
	}

	return System::Nullable<int>();
}


std::vector<int> ExecutionController::decodeInstruction() {
	return this->machine->getCPU().decode();
}