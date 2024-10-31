#pragma once
#include "Machine.h"
#include <memory>
#include <msclr/marshal.h>

ref class Controller {
protected:
	Machine* machine;

public:
	Controller(Machine* machine): machine(machine) {}
};

