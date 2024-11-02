#pragma once
#include "Controller.h"
#include "Utilities.h"
#include <algorithm>

ref class RegistersController : public Controller {
public:
	RegistersController(Machine* machine): Controller(machine) {}
	delegate void RegisterUpdatedEventHandler();
	event RegisterUpdatedEventHandler^ register_updated;

	void registerUpdated();

	System::String^ getHexRegisterValueAt(int index);

	System::String^ getIntRegisterValueAt(int index);

	System::String^ getBinRegisterValueAt(int index);

	System::String^ getFloatRegisterValueAt(int index);
	std::string RegistersController::getCurrentInstruction();
	System::Nullable<int> getUpdatedRegister();
private:

};

