#pragma once
#include "Controller.h"

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

	void fetchInstruction();
	void decodeInstruction() {}
	void executeCurrentInstruction() {}

	void resetProgram();

	System::String^ getCurrentAddress();
	System::String^ getCurrentInstruction();

private:

};

