#pragma once
#include "Machine.h"
#include <memory>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Controller {
protected:
	Machine* machine;

public:
	Controller(Machine* machine): machine(machine) {}
};

