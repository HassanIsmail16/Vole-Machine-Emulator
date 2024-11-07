#include "HelpForm.h"

System::Void VoleMachine::HelpForm::github_link_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
	System::Diagnostics::Process::Start("https://github.com/HassanIsmail16/Vole-Machine-Emulator/tree/main");
}

System::Void VoleMachine::HelpForm::HelpForm_Activated(System::Object^ sender, System::EventArgs^ e) {
	this->BringToFront();
}
