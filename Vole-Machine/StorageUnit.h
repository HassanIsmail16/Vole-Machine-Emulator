#pragma once
#include <string>

ref class StorageUnit {
public:
	StorageUnit();
	void setValue(System::String^ new_value);
	System::String^ getValue();
	void clear();

private:
	System::String^ value;
};

