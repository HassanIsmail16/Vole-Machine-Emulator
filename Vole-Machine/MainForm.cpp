#include "MainForm.h"
#include <msclr/marshal_cppstd.h>
#include <iostream>
#include "Utilities.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<System::String^>^ args) {
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
	this->registers_list->Columns->Add("Binary", 100, HorizontalAlignment::Left);
	this->registers_list->Columns->Add("Integer", 80, HorizontalAlignment::Left);
	this->registers_list->Columns->Add("Floating Point", 80, HorizontalAlignment::Left);

	for (int i = 0; i < 16; i++) {
		ListViewItem^ item = gcnew ListViewItem("R" + i.ToString());
		item->SubItems->Add("0x00");
		item->SubItems->Add("00000000");
		item->SubItems->Add("0");
		item->SubItems->Add("0");
		this->registers_list->Items->Add(item);
	}
}

System::Void VoleMachine::MainForm::initializeMemoryList() {
	this->memory_list->Columns->Clear();
	this->memory_list->Rows->Clear();

	this->memory_list->ColumnCount = 4;
	this->memory_list->RowHeadersVisible = false;
	this->memory_list->AllowUserToAddRows = false;
	this->memory_list->AllowUserToResizeColumns = false;
	this->memory_list->AllowUserToResizeRows = false;
	this->memory_list->SelectionMode = DataGridViewSelectionMode::CellSelect;
	this->memory_list->DefaultCellStyle->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10);
	this->memory_list->ColumnHeadersVisible = false;

	this->memory_list->Columns[0]->Name = "Address";
	this->memory_list->Columns[0]->ReadOnly = true;
	this->memory_list->Columns[0]->Width = 60;
	this->memory_list->Columns[0]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
	this->memory_list->Columns[0]->DefaultCellStyle->BackColor = SystemColors::Control;

	this->memory_list->Columns[1]->Name = "Value";
	this->memory_list->Columns[1]->Width = 50;
	this->memory_list->Columns[1]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;

	this->memory_list->Columns[2]->Name = "Value";
	this->memory_list->Columns[2]->Width = 50;
	this->memory_list->Columns[2]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;

	this->memory_list->Columns[3]->Name = "Address";
	this->memory_list->Columns[3]->ReadOnly = true;
	this->memory_list->Columns[3]->Width = 60;
	this->memory_list->Columns[3]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
	this->memory_list->Columns[3]->DefaultCellStyle->BackColor = SystemColors::Control;

	for (int i = 0; i < 128; i++) {
		int address1 = i * 2;
		int address2 = address1 + 1;
		
		String^ address1_hex = address1.ToString("X2");
		String^ address2_hex = address2.ToString("X2");

		String^ value = "00";

		this->memory_list->Rows->Add(address1_hex, value, value, address2_hex);
	}
}

System::Void VoleMachine::MainForm::memory_list_CellEndEdit(Object^ sender, DataGridViewCellEventArgs^ e) {
	int edited_cell_col = e->ColumnIndex;
	int edited_cell_row = e->RowIndex;

	if (edited_cell_col == 1) {
		String^ entered_value = this->memory_list->Rows[edited_cell_row]->Cells[edited_cell_col]->Value->ToString();

		if (entered_value == "C0") {
			this->memory_list->ClearSelection(); 
			return; 
		}
	} 

	this->memory_list->BeginInvoke(gcnew Action<int, int>(
		this,
		&MainForm::memory_list_HandleCellSelection),
		edited_cell_col, edited_cell_row);
}

System::Void VoleMachine::MainForm::memory_list_AddressCellStateChanged(Object^ sender, DataGridViewCellStateChangedEventArgs^ e) {
	if (this->memory_list->RowCount != 128 || this->memory_list->ColumnCount != 4) {
		return;
	}

	if (!e->Cell || e->StateChanged != DataGridViewElementStates::Selected) {
		return;
	}

	if (e->Cell->RowIndex == this->memory_list_selected_cell_row && e->Cell->ColumnIndex == this->memory_list_selected_cell_col) {
		return;
	}

	if (!e->Cell->Selected) {
		return;
	}

	if (e->Cell->ColumnIndex == 0 || e->Cell->ColumnIndex == 3) {
		e->Cell->Selected = false;
		this->memory_list->Rows[this->memory_list_selected_cell_row]->Cells[this->memory_list_selected_cell_col]->Selected = true;
	} else {
		this->memory_list_selected_cell_row = e->Cell->RowIndex;
		this->memory_list_selected_cell_col = e->Cell->ColumnIndex;
	}
}

System::Void VoleMachine::MainForm::memory_list_HandleCellSelection(int edited_cell_col, int edited_cell_row) {
	if (edited_cell_col == 1) {
		int target_col = edited_cell_col + 1;
		if (target_col < this->memory_list->Columns->Count) {
			this->memory_list->CurrentCell = this->memory_list->Rows[edited_cell_row]->Cells[target_col];
			this->memory_list->BeginEdit(true);
		}
	} else if (edited_cell_col == 2) {
		this->memory_list->CurrentCell = this->memory_list->Rows[edited_cell_row]->Cells[edited_cell_col];
		this->memory_list->EndEdit();
	}
}

System::Void VoleMachine::MainForm::memory_list_KeyDown(Object^ sender, KeyEventArgs^ e) {
	if (e->KeyCode == Keys::Enter) {
		if (this->memory_list->IsCurrentCellInEditMode && this->memory_list->CurrentCell->ColumnIndex == 2) {
			e->SuppressKeyPress = true;
			this->memory_list->EndEdit();
			e->Handled = true;
		} else if (!this->memory_list->IsCurrentCellInEditMode) {
			e->SuppressKeyPress = true;

			int current_col = this->memory_list->CurrentCell->ColumnIndex;
			int current_row = this->memory_list->CurrentCell->RowIndex;

			if (current_col == 1) {
				this->memory_list->CurrentCell = this->memory_list->Rows[current_row]->Cells[current_col + 1];
			} else if (current_col == 2) {
				if (current_row < 128) {
					this->memory_list->CurrentCell = this->memory_list->Rows[current_row + 1]->Cells[1];
				}
			}
		}
	}
}

System::Void VoleMachine::MainForm::OnMemoryUpdated() {
	this->initializeMemoryList();

	for (int i = 0; i < 128; i++) {
		String^ first_value = Utilities::Conversion::convertStdStringToSystemString(this->machine->getMemory().getValueAt(i * 2));
		String^ second_value = Utilities::Conversion::convertStdStringToSystemString(this->machine->getMemory().getValueAt(i * 2 + 1));
		
		this->memory_list->Rows[i]->Cells[1]->Value = first_value;
		this->memory_list->Rows[i]->Cells[2]->Value = second_value;
	}
}

System::Void VoleMachine::MainForm::memory_list_OnMemoryCellValueChanged(Object^ sender, DataGridViewCellEventArgs^ e) {
	if (this->mem_ctrl->is_updating_memory_list) {
		return;
	}
	
	int address = e->RowIndex * 2 + e->ColumnIndex - 1;
	String^ value = this->memory_list->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();

	this->mem_ctrl->updateMemoryValueAt(address, value);

	this->machine->displayMemory();
}

System::Void VoleMachine::MainForm::OnFetchInstruction() {
	this->current_address_textbox->Clear();
	String^ current_address = this->exec_ctrl->getCurrentAddress();
	this->current_address_textbox->Text = current_address;

	this->current_instruction_textbox->Clear();
	String^ current_instruction = this->exec_ctrl->getCurrentInstruction();
	this->current_instruction_textbox->Text = current_instruction;
}

System::Void VoleMachine::MainForm::memory_list_CellPainting(Object^ sender, DataGridViewCellPaintingEventArgs^ e) {
	if (e->ColumnIndex == 0 || e->ColumnIndex == 3) {
		e->AdvancedBorderStyle->Left = DataGridViewAdvancedCellBorderStyle::None;
		e->AdvancedBorderStyle->Top = DataGridViewAdvancedCellBorderStyle::None;
		e->AdvancedBorderStyle->Bottom = DataGridViewAdvancedCellBorderStyle::None;
	}
	e->Handled = false;
}

System::Void VoleMachine::MainForm::load_from_file_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!this->machine->getMemory().isEmpty()) {
		Windows::Forms::DialogResult result = MessageBox::Show("Loading a file will overwrite the current memory. Are you sure you want to continue?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
    
		if (result == System::Windows::Forms::DialogResult::No) {
			return;
		}
	}
	
	OpenFileDialog^ file_dialog = gcnew OpenFileDialog();

	file_dialog->Filter = "Text Files (*.txt)|*.txt|All Files(*.*)|*.*";
	file_dialog->FilterIndex = 1;
	file_dialog->RestoreDirectory = true;

	if (file_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		String^ filename = file_dialog->FileName;
		std::string std_filename = Utilities::Conversion::convertSystemStringToStdString(filename); 
		this->mem_ctrl->loadFromFile(std_filename);
		MessageBox::Show("File loaded successfully!");
		this->machine->displayMemory(); // TODO: remove 
;	}
}

System::Void VoleMachine::MainForm::export_to_file_Click(System::Object^ sender, System::EventArgs^ e) {
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
	saveFileDialog->Filter = "Text Files|*.txt|All Files|*.*";
	saveFileDialog->Title = "Export Memory to File";

	if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		std::string filename = Utilities::Conversion::convertSystemStringToStdString(saveFileDialog->FileName);
		memoryController->exportToFile(filename);
	}
	MessageBox::Show("File saved successfully.", "Export Complete", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void VoleMachine::MainForm::reset_memory_Click(System::Object^ sender, System::EventArgs^ e) {
	Windows::Forms::DialogResult result = MessageBox::Show("Are you sure you want to reset the memory?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

	if (result == System::Windows::Forms::DialogResult::No) {
		return;
	}

	this->mem_ctrl->resetMemory();
	this->machine->displayMemory();
}

System::Void VoleMachine::MainForm::fetch_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->fetchInstruction();
}

System::Void VoleMachine::MainForm::reset_pc_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->resetProgram();
}
