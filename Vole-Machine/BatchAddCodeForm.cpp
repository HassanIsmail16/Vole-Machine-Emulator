#include "BatchAddCodeForm.h"
#include "Utilities.h"

System::Void VoleMachine::BatchAddCodeForm::starting_address_textbox_KeyPress(Object^ sender, KeyPressEventArgs^ e) {
	if (e->KeyChar == '\b') {
		return;
	}

	e->KeyChar = Char::ToUpper(e->KeyChar);

	bool is_hex = (e->KeyChar >= '0' && e->KeyChar <= '9') ||
		(e->KeyChar >= 'A' && e->KeyChar <= 'F');

	bool within_length = starting_address_textbox->Text->Length < 2;

	if (!is_hex || !within_length) {
		e->Handled = true;
	} // supress key press if not valid
}

System::Void VoleMachine::BatchAddCodeForm::starting_address_textbox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (this->starting_address_textbox->SelectionLength == this->starting_address_textbox->Text->Length &&
		e->KeyCode != System::Windows::Forms::Keys::Back &&
		e->KeyCode != System::Windows::Forms::Keys::Delete &&
		e->KeyCode != System::Windows::Forms::Keys::Left &&
		e->KeyCode != System::Windows::Forms::Keys::Right &&
		e->KeyCode != System::Windows::Forms::Keys::Enter &&
		e->KeyCode != System::Windows::Forms::Keys::Escape) {
		this->starting_address_textbox->Text = "";  // clear text to allow overwriting
	}

	if (e->KeyCode == Keys::Enter || e->KeyCode == Keys::Escape) {
		this->updateStartingAddress();
		e->Handled = true;
		this->ActiveControl = nullptr;
	}
}

System::Void VoleMachine::BatchAddCodeForm::starting_address_textbox_Leave(System::Object^ sender, System::EventArgs^ e) {
	this->updateStartingAddress();
}

System::Void VoleMachine::BatchAddCodeForm::starting_address_textbox_Enter(System::Object^ sender, System::EventArgs^ e) {
	this->BeginInvoke(
		gcnew System::Action(
			this, &VoleMachine::BatchAddCodeForm::starting_address_textbox_SelectStartingAddressText
		)
	);
}

System::Void VoleMachine::BatchAddCodeForm::updateStartingAddress() {
	if (this->starting_address_textbox->Text == "FF") {
		this->starting_address_textbox->Text = Utilities::Conversion::convertDecToHexSystemString(this->exec_ctrl->getStartingAddress());
		return;
	}

	String^ text = this->starting_address_textbox->Text;

	if (text->Length == 2) {
		this->exec_ctrl->setStartingAddress(text);
		return;
	}

	while (text->Length < 2) {
		text = "0" + text;
	} // add leading zero

	this->starting_address_textbox->Text = text;
	this->updateStartingAddress();
}

System::Void VoleMachine::BatchAddCodeForm::starting_address_textbox_SelectStartingAddressText() {
	this->starting_address_textbox->SelectAll();
}

System::Void VoleMachine::BatchAddCodeForm::add_code_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->setStartingAddress(this->starting_address_textbox->Text);
	this->mem_ctrl->loadFromText(this->textbox->Text);
	this->exec_ctrl->setStartingAddress(this->starting_address);
	this->Close();
}
