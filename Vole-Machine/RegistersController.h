#pragma once
#include "Controller.h"
#include "Utilities.h"
#include <algorithm>

ref class RegistersController : public Controller {
public:
	RegistersController(Machine* machine): Controller(machine) {}


	// register updated event
	delegate void RegisterUpdatedEventHandler();
	event RegisterUpdatedEventHandler^ register_updated;
	void registerUpdated();

	// all registers updated reset
	delegate void AllRegistersUpdatedEventHandler();
	event AllRegistersUpdatedEventHandler^ all_registers_updated;
	void updateAllRegisters();


	// registers reset event
	delegate void RegisterResetEvenHandler();
	event RegisterResetEvenHandler^ register_reset;
	void resetRegisters();

	// accessors
	System::String^ getHexRegisterValueAt(int index);
	System::String^ getIntRegisterValueAt(int index);
	System::String^ getBinRegisterValueAt(int index);
	System::String^ getFloatRegisterValueAt(int index);
	std::string RegistersController::getCurrentInstruction();
	System::Nullable<int> getUpdatedRegister();
};

