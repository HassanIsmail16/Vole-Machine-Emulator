#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	VoleMachine::MainForm form;
	Application::Run(% form);
	return 0;
}

System::Void VoleMachine::MainForm::initializeRegistersList() {
	this->registers_list->View = View::Details;
	this->registers_list->FullRowSelect = true;
	this->registers_list->GridLines = false;
	this->registers_list->HeaderStyle = ColumnHeaderStyle::Nonclickable;

	this->registers_list->Columns->Add("Register", 60, HorizontalAlignment::Left);
	this->registers_list->Columns->Add("Hex", 50, HorizontalAlignment::Left);
	this->registers_list->Columns->Add("Bin", 100, HorizontalAlignment::Left);

	for (int i = 0; i < 16; i++) {
		ListViewItem^ item = gcnew ListViewItem("R" + i.ToString());
		item->SubItems->Add("0x00");
		item->SubItems->Add("00000000");
		this->registers_list->Items->Add(item);
	}
}

System::Void VoleMachine::MainForm::initializeMemoryList() {
	this->memory_list->ColumnCount = 4;
	this->memory_list->RowHeadersVisible = false;
	this->memory_list->AllowUserToAddRows = false;
	this->memory_list->AllowUserToResizeColumns = false;
	this->memory_list->AllowUserToResizeRows = false;
	this->memory_list->SelectionMode = DataGridViewSelectionMode::CellSelect;
	this->memory_list->DefaultCellStyle->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10);
		
	this->memory_list->Columns[0]->Name = "Address";
	this->memory_list->Columns[0]->ReadOnly = true;
	this->memory_list->Columns[0]->Width = 60;
	this->memory_list->Columns[0]->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
	this->memory_list->Columns[0]->DefaultCellStyle->Font = gcnew System::Drawing::Font("Consolas", 10, System::Drawing::FontStyle::Regular);

	this->memory_list->Columns[1]->Name = "Value";
	this->memory_list->Columns[1]->Width = 50;

	this->memory_list->Columns[2]->Name = "Value";
	this->memory_list->Columns[2]->Width = 50;

	this->memory_list->Columns[3]->Name = "Address";
	this->memory_list->Columns[3]->ReadOnly = true;
	this->memory_list->Columns[3]->Width = 60;

	for (int i = 0; i < 128; i++) {
		int address1 = i * 2;
		int address2 = address1 + 1;
		
		String^ address1_hex = address1.ToString("X2");
		String^ address2_hex = address2.ToString("X2");

		String^ value = "00";

		this->memory_list->Rows->Add(address1_hex, value, value, address2_hex);
	}
}

//System::Void VoleMachine::MainForm::memory_list_KeyDown(Object^ sender, KeyEventArgs^ e) {
//	// Only handle Enter key when not editing a cell
//	if (this->move_after_edit) {
//		MessageBox::Show("Enter was pressed to end editing.");
//		this->move_after_edit = false;
//	}
//}

// Separate method to handle the navigation logic
//System::Void VoleMachine::MainForm::MoveToNextEditableCell() {
//	int currentColumn = this->memory_list->CurrentCell->ColumnIndex;
//	int currentRow = this->memory_list->CurrentCell->RowIndex;
//
//	// Loop to find the next editable cell
//	do {
//		if (currentColumn < this->memory_list->ColumnCount - 1) {
//			currentColumn++;
//		} else if (currentRow < this->memory_list->RowCount - 1) {
//			currentColumn = 0;
//			currentRow++;
//		} else {
//			currentColumn = 0;
//			currentRow = 0; // Loop back to the start of the grid
//		}
//	} while (this->memory_list->Rows[currentRow]->Cells[currentColumn]->ReadOnly);
//
//	this->memory_list->CurrentCell = this->memory_list->Rows[currentRow]->Cells[currentColumn];
//}

System::Void VoleMachine::MainForm::memory_list_CellEndEdit(Object^ sender, DataGridViewCellEventArgs^ e) {
	if (this->move_after_edit) {
		MessageBox::Show("Enter was pressed to end editing.");
		this->move_after_edit = false;
	}
}

System::Void VoleMachine::MainForm::memory_list_PreviewKeyDown(Object^ sender, PreviewKeyDownEventArgs^ e) {
	if (e->KeyCode == Keys::Enter && this->memory_list->IsCurrentCellInEditMode) {
		this->move_after_edit = true;
	}
}
