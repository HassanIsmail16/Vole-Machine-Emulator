#pragma once
#include "Controller.h"
#include "ExecutionController.h"
#include <iostream>
#include <vector>

ref class ExecutionController : public Controller {
public:
	ExecutionController(Machine* machine): Controller(machine) {}

	// fetched instruction 
	delegate void InstructionFetchedEventHandler();
	event InstructionFetchedEventHandler^ fetched_instruction;
	void fetchedInstruction();
	bool is_fetching_instruction = false;
	void fetchInstruction();

	// decoded instruction 
	delegate void InstructionDecodedEventHandler();
	event InstructionDecodedEventHandler^ decoded_instruction;
	void decodedInstruction();
	bool is_decoding_instruction = false;
	System::Collections::Generic::List<int>^ decodeInstruction();

	// executed instruction 
	delegate void InstructionExecutedEventHandler();
	event InstructionExecutedEventHandler^ executed_instruction;
	void executedInstruction();
	bool is_executing_instruction = false;
	void executeCurrentInstruction();
	void step();
	void playInstructions();
	void pauseInstructions();
	System::Nullable<int> getUpdatedAddress();

	// all instructions executed 
	delegate void AllInstructionsExecutedEventHandler();
	event AllInstructionsExecutedEventHandler^ all_instructions_executed;
	void runAllInstructions();

	// screen updated 
	delegate void ScreenUpdatedEventHandler(std::string value);
	event ScreenUpdatedEventHandler^ screen_updated;
	void screenUpdated(std::string value);
	bool is_updating_screen = false;

	// speed changed 
	delegate void SpeedChangedEventHandler();
	SpeedChangedEventHandler^ speed_changed;
	void updateSpeed(int new_speed);

	// program halted 
	delegate void ProgramHaltedEventHandler();
	ProgramHaltedEventHandler^ program_halted;

	// reached end of memory 
	delegate void ReachedEndOfMemoryEventHandler();
	ReachedEndOfMemoryEventHandler^ reached_end_of_memory;

	// reset instruction register 
	delegate void ResetInstructionRegisterEventHandler();
	event ResetInstructionRegisterEventHandler^ reset_instruction_register;
	void resetInstructionRegister();

	// reset program
	void resetProgram();

	// accessors
	System::String^ getCurrentAddress();
	System::String^ getCurrentInstruction();
	int getStartingAddress();

	void setCurrentAddress(System::String^ address);
	void setCurrentAddress(int address);

	void setStartingAddress(System::String^ address);
	void setStartingAddress(int address);

	property int InstructionsPerSecond {
		int get() { return this->instructions_per_sec; }
		void set(int value) {
			if (value <= 0) return;

			instructions_per_sec = value;

			if (instruction_timer != nullptr) {
				instruction_timer->Stop();
				instruction_timer->Interval = 1000 / instructions_per_sec;

				if (is_running) {
					instruction_timer->Start();
				}
			}

			if (speed_changed != nullptr) {
				speed_changed();
			}
		}
	}
private:
	System::Windows::Forms::Timer^ instruction_timer;
	void OnTimerTick(Object^ sender, System::EventArgs^ e);

	int instructions_per_sec = 5;
	bool is_running = false;
	bool all_instructions = false;
	int starting_address = 0;
};