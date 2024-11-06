#include "ExecutionController.h"
#include "Utilities.h"
#include <iostream>
#include <vector>

void ExecutionController::fetchedInstruction() {
	if (this->is_fetching_instruction) {
		return;
	} // exit if an instruction is already being fetched

	this->is_fetching_instruction = true;
	fetched_instruction();
	this->is_fetching_instruction = false;
}

void ExecutionController::decodedInstruction() {
	if (this->is_decoding_instruction) {
		return;
	} // exit if an instruction is already being decoded

	this->is_decoding_instruction = true;
	decoded_instruction();
	this->is_decoding_instruction = false;
}

void ExecutionController::executedInstruction() {
	if (this->is_executing_instruction) {
		return;
	} // exit if an instruction is already being executed

	this->is_executing_instruction = true;
	executed_instruction();
	this->is_executing_instruction = false;
}

void ExecutionController::screenUpdated(std::string value) {
	if (this->is_updating_screen) {
		return;
	} // exit if screen is already being updated

	this->is_updating_screen = true;
	screen_updated(value);
	this->is_updating_screen = false;
}

void ExecutionController::runAllInstructions() {
	this->all_instructions = true; // flag to prevent early halting
	this->is_running = true;
	while (true) {
		this->machine->getCPU().fetch(this->machine->getMemory());
		this->executeCurrentInstruction();

		if (this->machine->getCPU().isHalt()) {
			program_halted();
			break;
		} // exit if program is halted

		if (this->getCurrentAddress() == "FF") {
			reached_end_of_memory();
			break;
		} // exit if reached end of memory
	}
	this->all_instructions_executed();
	this->is_running = false;
	this->all_instructions = false;
}

void ExecutionController::fetchInstruction() {
	if (this->hasReachedEndOfMemory() || this->getCurrentAddress() == "FF") {
		reached_end_of_memory();
		return;
	} // exit if reached end of memory

	this->machine->getCPU().fetch(this->machine->getMemory());
	fetchedInstruction();
}

void ExecutionController::executeCurrentInstruction() {
	if (!this->machine->getCPU().isInstructionPending()) {
		return;
	} // exit if no instruction is pending

	std::vector<int> instruction = this->machine->getCPU().decode();
	
	if (!Utilities::Validation::isValidInstruction(this->machine->getCPU().getCurrentInstruction())) {
		return;
	} // skip if instruction is invalid


	if (this->machine->getCPU().isHalt() && !this->all_instructions) {
		program_halted();
	}

	this->machine->getCPU().execute(this->machine->getMemory(), instruction);

	if (instruction[0] == 3 && instruction[2] == 0) {
		screenUpdated(this->machine->getCPU().getRegisterValueAt(instruction[1]));
	}

	// update program counter to accont for jumps
	this->setCurrentAddress(this->machine->getCPU().getProgramCounter().ToString("X2")); 

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
	this->machine->getCPU().resetProgram(this->starting_address);
	resetInstructionRegister();
	fetchedInstruction();
	this->reset_instruction_register();
}

void ExecutionController::resetInstructionRegister() {
	this->machine->getCPU().resetInstructionRegister();
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

void ExecutionController::setStartingAddress(int address) {
	this->machine->getCPU().setStartingAddress(address);
}

bool ExecutionController::hasReachedEndOfMemory() {
	return this->machine->getCPU().hasReachedEndOfMemory();
}

bool ExecutionController::isProgramCounterOdd() {
	return this->machine->getCPU().isProgramCounterOdd();
}

void ExecutionController::setStartingAddress(System::String^ address) {
	this->starting_address = stoi(
		Utilities::Conversion::convertHexToDec(
			Utilities::Conversion::convertSystemStringToStdString(address)
		)
	);

	this->machine->getCPU().setStartingAddress(this->starting_address);
}

void ExecutionController::setCurrentAddress(System::String^ address) {
	this->setCurrentAddress(Utilities::Conversion::convertHexSystemStringToDecInt(address));
}

void ExecutionController::setCurrentAddress(int address) {
	this->machine->getCPU().setProgramCounter(address);
}

int ExecutionController::getStartingAddress() {
	return this->starting_address;
}

System::Collections::Generic::List<int>^ ExecutionController::decodeInstruction() {
	if (!this->machine->getCPU().isInstructionPending()) {
		return nullptr;
	}

	System::Collections::Generic::List<int>^ result = gcnew System::Collections::Generic::List<int>();
	std::string current_instruction = this->machine->getCPU().getCurrentInstruction();

	if (!Utilities::Validation::isValidInstruction(current_instruction)) {

		for (int i = 0; i < 4; i++) {
			result->Add(stoi(current_instruction.substr(i, 1), nullptr, 16));
		}

		return result;
	} // handle invalid instructions


	std::vector<int> temp = machine->getCPU().decode();

	for (auto& it : temp) {
		result->Add(it);
	}

	return result;
}