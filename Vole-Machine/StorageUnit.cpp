#include "StorageUnit.h"

StorageUnit::StorageUnit() : value("") {}

void StorageUnit::setValue(std::string new_value) {
	this->value = new_value;
}

std::string StorageUnit::getValue() {
	return this->value;
}

void StorageUnit::clear() {
	this->value = "00";
}
