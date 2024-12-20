#include "RegistersController.h"

void RegistersController::registerUpdated() {
	this->register_updated();
}

void RegistersController::updateAllRegisters() {
	this->all_registers_updated();
}

void RegistersController::resetRegisters() {
	this->machine->getCPU().clearRegisters();
	this->register_reset();
}

System::String^ RegistersController::getHexRegisterValueAt(int index) {
	std::string hex_value = this->machine->getCPU().getRegisterValueAt(index);

	if (hex_value.length() == 1) {
		hex_value = "0" + hex_value;
	}

	std::transform(hex_value.begin(), hex_value.end(), hex_value.begin(), ::toupper);
	return Utilities::Conversion::convertStdStringToSystemString(hex_value);
}

System::String^ RegistersController::getIntRegisterValueAt(int index) {
	std::string hex_value = this->machine->getCPU().getRegisterValueAt(index);
	int int_value = Utilities::Conversion::convertHexToTwosComplementInt(hex_value);
	return System::Convert::ToString(int_value);
}

System::String^ RegistersController::getBinRegisterValueAt(int index) {
	std::string hex_value = this->machine->getCPU().getRegisterValueAt(index);
	int dec_value = std::stoi(hex_value, nullptr, 16);
	std::string binary_value = Utilities::Conversion::convertIntToBin(dec_value);
	binary_value.insert(binary_value.begin(), 8 - binary_value.size(), '0');
	return Utilities::Conversion::convertStdStringToSystemString(binary_value);
}

System::String^ RegistersController::getFloatRegisterValueAt(int index) {
	std::string binary_value = Utilities::Conversion::convertSystemStringToStdString(this->getBinRegisterValueAt(index));
	double float_value = Utilities::Conversion::convvertBinToFloat(binary_value);
	return System::Convert::ToString(float_value);
}

std::string RegistersController::getCurrentInstruction() {
	return this->machine->getCPU().getCurrentInstruction();
}

System::Nullable<int> RegistersController::getUpdatedRegister() {
	std::string current_instruction = this->getCurrentInstruction();

	if (current_instruction.length() == 0 || current_instruction[0] == 'B' || current_instruction[0] == 'D') {
		return System::Nullable<int>();
	} // handle instructions that do not update registers


	if (current_instruction[0] == '4') {
		return System::Convert::ToInt32(Utilities::Conversion::convertStdStringToSystemString(current_instruction)->Substring(3, 1), 16);
	} // handle jump instructions

	return System::Convert::ToInt32(Utilities::Conversion::convertStdStringToSystemString(current_instruction)->Substring(1, 1), 16);
}

