#pragma once
#include "Machine.h"
#include <memory>

ref class Controller {
private:
	Machine* machine;

public:
	Controller(Machine* machine): machine(machine) {}
};

