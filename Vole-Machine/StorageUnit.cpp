#include "StorageUnit.h"

StorageUnit::StorageUnit() {
	this->value = "00";
}

void StorageUnit::setValue(System::String^ new_value) {
	this->value = new_value;
}

System::String^ StorageUnit::getValue() {
	return this->value;
}

void StorageUnit::clear() {
	this->value = "00";
}
