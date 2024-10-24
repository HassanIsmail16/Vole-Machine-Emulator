#pragma once
#include <string>

class StorageUnit {
public:
	StorageUnit();
	void setValue(std::string new_value);
	std::string getValue();
	void clear();

private:
	std::string value;
};

