#pragma once
#include "Controller.h"
#include "ExecutionController.h"
#include <iostream>

ref class ExecutionController : public Controller {
public:
	ExecutionController(Machine* machine): Controller(machine) {}
	
	delegate void InstructionFetchedEventHandler();
	event InstructionFetchedEventHandler^ fetched_instruction;
	void fetchedInstruction();
	bool is_fetching_instruction = false;

	delegate void InstructionDecodedEventHandler();
	event InstructionDecodedEventHandler^ decoded_instruction;
	void decodedInstruction();
	bool is_decoding_instruction = false;

	delegate void InstructionExecutedEventHandler();
	event InstructionExecutedEventHandler^ executed_instruction;
	void executedInstruction();
	bool is_executing_instruction = false;

	delegate void AllInstructionsExecutedEventHandler();
	event AllInstructionsExecutedEventHandler^ all_instructions_executed;

	delegate void ScreenUpdatedEventHandler(std::string value);
	event ScreenUpdatedEventHandler^ screen_updated;
	void screenUpdated(std::string value);
	bool is_updating_screen = false;

	delegate void SpeedChangedEventHandler();
	SpeedChangedEventHandler^ speed_changed;

	delegate void ProgramHaltedEventHandler();
	ProgramHaltedEventHandler^ program_halted;

	delegate void ReachedEndOfMemoryEventHandler();
	ReachedEndOfMemoryEventHandler^ reached_end_of_memory;

	void runAllInstructions();
	void fetchInstruction();
	void decodeInstruction() {}
	void executeCurrentInstruction();
	void step();
	void playInstructions();
	void pauseInstructions();

	void resetProgram();

	System::String^ getCurrentAddress();
	System::String^ getCurrentInstruction();

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

	void updateSpeed(int new_speed);

	System::Nullable<int> getUpdatedAddress();
	

private:
	System::Windows::Forms::Timer^ instruction_timer;
	void OnTimerTick(Object^ sender, System::EventArgs^ e);

	int instructions_per_sec = 5;
	bool is_running = false;

};

