#include "MainForm.h"
#include <msclr/marshal_cppstd.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "Utilities.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading::Tasks;

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
	this->registers_list->Columns->Add("Floating Point", 100, HorizontalAlignment::Left);

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
	this->memory_list->MultiSelect = false;

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

	this->memory_list->CurrentCell = this->memory_list->Rows[0]->Cells[1];
	this->highlightAddress(this->starting_address_textbox->Text);
}

System::Void VoleMachine::MainForm::initializeControllers() {
	this->initializeMemoryController();
	this->initializeRegistersController();
	this->initializeExecutionController();
}

System::Void VoleMachine::MainForm::initializeMemoryController() {
	this->mem_ctrl = gcnew MemoryController(this->machine);

	// events
	this->mem_ctrl->memory_updated += gcnew MemoryController::MemoryUpdatedEventHandler(this, &VoleMachine::MainForm::OnMemoryUpdated);
	this->mem_ctrl->memory_updated_at_address += gcnew MemoryController::MemoryUpdatedAtAddressEventHandler(this, &VoleMachine::MainForm::OnMemoryUpdatedAtAddress);
}

System::Void VoleMachine::MainForm::initializeRegistersController() {
	this->reg_ctrl = gcnew RegistersController(this->machine);

	// events
	this->reg_ctrl->register_updated += gcnew RegistersController::RegisterUpdatedEventHandler(this, &VoleMachine::MainForm::OnRegisterUpdated);
	this->reg_ctrl->register_reset += gcnew RegistersController::RegisterResetEvenHandler(this, &VoleMachine::MainForm::OnResetRegisters);
	this->reg_ctrl->all_registers_updated += gcnew RegistersController::AllRegistersUpdatedEventHandler(this, &VoleMachine::MainForm::OnAllRegistersUpdated);
}

System::Void VoleMachine::MainForm::initializeExecutionController() {
	this->exec_ctrl = gcnew ExecutionController(this->machine);

	// events
	this->exec_ctrl->fetched_instruction += gcnew ExecutionController::InstructionFetchedEventHandler(this, &VoleMachine::MainForm::OnFetchInstruction);
	this->exec_ctrl->executed_instruction += gcnew ExecutionController::InstructionExecutedEventHandler(this, &VoleMachine::MainForm::OnExecuteInstruction);
	this->exec_ctrl->screen_updated += gcnew ExecutionController::ScreenUpdatedEventHandler(this, &VoleMachine::MainForm::OnUpdateScreen);
	this->exec_ctrl->speed_changed += gcnew ExecutionController::SpeedChangedEventHandler(this, &VoleMachine::MainForm::OnChangeSpeed);
	this->exec_ctrl->program_halted += gcnew ExecutionController::ProgramHaltedEventHandler(this, &VoleMachine::MainForm::OnHaltProgram);
	this->exec_ctrl->reached_end_of_memory += gcnew ExecutionController::ReachedEndOfMemoryEventHandler(this, &VoleMachine::MainForm::OnReachedEndOfMemory);
	this->exec_ctrl->all_instructions_executed += gcnew ExecutionController::AllInstructionsExecutedEventHandler(this, &VoleMachine::MainForm::OnExecutedAllInstructions);
	this->exec_ctrl->resetInstructionReg += gcnew ExecutionController::ResetInstructionRegEventHandler(this, &MainForm::ResetInstructionReg);
}

#pragma region MemoryList Events
System::Void VoleMachine::MainForm::memory_list_CellEndEdit(Object^ sender, DataGridViewCellEventArgs^ e) {
	int edited_cell_col = e->ColumnIndex;
	int edited_cell_row = e->RowIndex;

	if (edited_cell_col == 1 || edited_cell_col == 2) {
		String^ entered_value = this->memory_list->Rows[edited_cell_row]->Cells[edited_cell_col]->Value->ToString();

		if (entered_value->Length == 1) {
			entered_value = "0" + entered_value; // Pad single-digit hex values
		}

		// Ensure the text is in uppercase
		entered_value = entered_value->ToUpper();

		this->memory_list->Rows[edited_cell_row]->Cells[edited_cell_col]->Value = entered_value;

		// Special case if "C0" is entered in column 1
		if (entered_value[0] == 'C' && edited_cell_col == 1) {
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

System::Void VoleMachine::MainForm::memory_list_EditingControlShowing(Object^ sender, DataGridViewEditingControlShowingEventArgs^ e) {
	// Ensure we only attach the event to columns 1 and 2
	if (this->memory_list->CurrentCell->ColumnIndex == 1 || this->memory_list->CurrentCell->ColumnIndex == 2) {
		// Cast the editing control to TextBox
		TextBox^ editingTextBox = dynamic_cast<TextBox^>(e->Control);

		if (editingTextBox != nullptr) {
			// Remove any existing handler first to avoid duplicate handlers
			editingTextBox->KeyPress -= gcnew KeyPressEventHandler(this, &VoleMachine::MainForm::memory_list_KeyPress);
			// Add KeyPress event handler for hex validation
			editingTextBox->KeyPress += gcnew KeyPressEventHandler(this, &VoleMachine::MainForm::memory_list_KeyPress);
		}
	}
}
System::Void VoleMachine::MainForm::memory_list_KeyPress(Object^ sender, KeyPressEventArgs^ e) {
	TextBox^ textBox = dynamic_cast<TextBox^>(sender);

	if (e->KeyChar == '\b') {
		return; // Allow backspace
	}

	// Convert to uppercase
	e->KeyChar = Char::ToUpper(e->KeyChar);

	// Check if the key is a valid hex digit
	bool isHex = (e->KeyChar >= '0' && e->KeyChar <= '9') || (e->KeyChar >= 'A' && e->KeyChar <= 'F');
	bool withinLength = textBox->Text->Length < 2 || textBox->SelectionLength == textBox->Text->Length;

	if (!isHex || !withinLength) {
		e->Handled = true; // Suppress the keypress if not valid
	} else if (textBox->SelectionLength == textBox->Text->Length) {
		// Clear text if the entire text is selected
		textBox->Text = "";
	}
}

System::Void VoleMachine::MainForm::memory_list_OnCellClick(Object^ sender, DataGridViewCellEventArgs^ e) {
	if (e->ColumnIndex == 0 || e->ColumnIndex == 3) {
		int row = e->RowIndex;
		this->exec_ctrl->setCurrentAddress(row * 2);

		String^ hex_address = this->memory_list->Rows[row]->Cells[0]->Value->ToString();
		this->highlightAddress(hex_address);
		this->current_address_textbox->Text = hex_address;
	}
}

System::Void VoleMachine::MainForm::memory_list_OnCellMouseEnter(Object^ sender, DataGridViewCellEventArgs^ e) {
	if (e->ColumnIndex == 0 || e->ColumnIndex == 3) {
		this->memory_list->Cursor = Cursors::Hand;
		this->memory_list->Rows[e->RowIndex]->Cells[0]->Style->BackColor = Color::Azure;
		this->memory_list->Rows[e->RowIndex]->Cells[3]->Style->BackColor = Color::Azure;
	} else {
		this->memory_list->Cursor = Cursors::IBeam;
		this->memory_list->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->BackColor = Color::AntiqueWhite;
	}
}

System::Void VoleMachine::MainForm::memory_list_OnCellMouseLeave(Object^ sender, DataGridViewCellEventArgs^ e) {
	this->memory_list->Cursor = Cursors::Default;
	if (e->ColumnIndex == 0 || e->ColumnIndex == 3) {
		if (last_highlighted_address == this->memory_list->Rows[e->RowIndex]->Cells[0]->Value->ToString()) {
			this->memory_list->Rows[e->RowIndex]->Cells[0]->Style->BackColor = Color::LightBlue;
			this->memory_list->Rows[e->RowIndex]->Cells[3]->Style->BackColor = Color::LightBlue;
		} else {
			this->memory_list->Rows[e->RowIndex]->Cells[0]->Style->BackColor = SystemColors::Control;
			this->memory_list->Rows[e->RowIndex]->Cells[3]->Style->BackColor = SystemColors::Control;
		}
	} else {
		this->memory_list->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->BackColor = Color::White;
	}
}

System::Void VoleMachine::MainForm::memory_list_ScrollUpdate() {
	int current_address = stoi(
		Utilities::Conversion::convertHexToDec(
			Utilities::Conversion::convertSystemStringToStdString(this->exec_ctrl->getCurrentAddress())
		)
	);

	if (current_address % 20 == 0) {
		this->memory_list->FirstDisplayedScrollingRowIndex += 10;
	}

	int starting_address = stoi(
		Utilities::Conversion::convertHexToDec(
			Utilities::Conversion::convertSystemStringToStdString(this->starting_address_textbox->Text)
		)
	);

	if (current_address == starting_address) {
		this->memory_list->FirstDisplayedScrollingRowIndex = max(starting_address / 2 - 10, 0);
	}
}

System::Void VoleMachine::MainForm::OnMemoryUpdated() {
	if (this->memory_list->InvokeRequired) {
		this->Invoke(gcnew MemoryController::MemoryUpdatedEventHandler(this,
			&MainForm::OnMemoryUpdated));
		return;
	}

	this->initializeMemoryList();
	for (int i = 0; i < 128; i++) {
		String^ first_value = Utilities::Conversion::convertStdStringToSystemString(
			this->machine->getMemory().getValueAt(i * 2)); // TODO: move to memory controller
		String^ second_value = Utilities::Conversion::convertStdStringToSystemString(
			this->machine->getMemory().getValueAt(i * 2 + 1));

		this->memory_list->Rows[i]->Cells[1]->Value = first_value;
		this->memory_list->Rows[i]->Cells[2]->Value = second_value;
		this->memory_list->Rows[i]->Cells[1]->Style->BackColor = Color::Coral;
		this->memory_list->Rows[i]->Cells[2]->Style->BackColor = Color::Coral;
	}

	this->color_reset_queue->Enqueue(
		gcnew System::Tuple<System::DateTime, int, int>(
			System::DateTime::Now,
			-1,  // special value for full reset
			-1
		)
	);

	if (!this->reset_color_timer->Enabled) {
		this->reset_color_timer->Start();
	}
}

System::Void VoleMachine::MainForm::OnMemoryUpdatedAtAddress(int index) {
	if (this->memory_list->InvokeRequired) {
		this->Invoke(gcnew MemoryController::MemoryUpdatedAtAddressEventHandler(this,
			&MainForm::OnMemoryUpdatedAtAddress), index);
		return;
	}

	int row = index / 2;
	int col = index % 2 + 1;

	this->memory_list->Rows[row]->Cells[col]->Value = Utilities::Conversion::convertStdStringToSystemString(this->machine->getMemory().getValueAt(index)); // TODO: move to memory controller

	this->memory_list->Rows[row]->Cells[col]->Style->BackColor = Color::Coral;

	this->color_reset_queue->Enqueue(
		gcnew System::Tuple<System::DateTime, int, int>(
			System::DateTime::Now,
			row,
			col
		)
	);

	if (!this->reset_color_timer->Enabled) {
		this->reset_color_timer->Start();
	}
}

System::Void VoleMachine::MainForm::memory_list_OnMemoryCellValueChanged(Object^ sender, DataGridViewCellEventArgs^ e) {
	if (this->mem_ctrl->is_updating_memory_list) {
		return;
	}
	
	int address = e->RowIndex * 2 + e->ColumnIndex - 1;
	String^ value = this->memory_list->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();

	this->mem_ctrl->updateMemoryValueAt(address, value);

	this->machine->displayMemory(); // TODO: remove
}

System::Void VoleMachine::MainForm::memory_list_ResetCellColor(Object^ sender, EventArgs^ e) {
	System::DateTime now = System::DateTime::Now;

	while (this->color_reset_queue->Count > 0) {
		auto reset_info = this->color_reset_queue->Peek();
		TimeSpan duration = now - reset_info->Item1;

		if (duration.TotalMilliseconds >= 200) {
			this->color_reset_queue->Dequeue();

			if (reset_info->Item2 == -1 && reset_info->Item3 == -1) {
				for (int i = 0; i < 128; i++) {
					this->memory_list->Rows[i]->Cells[1]->Style->BackColor = Color::White;
					this->memory_list->Rows[i]->Cells[2]->Style->BackColor = Color::White;
				}
			}
			else {
				this->memory_list->Rows[reset_info->Item2]->Cells[reset_info->Item3]->Style->BackColor = Color::White;
			}
		}
		else {
			break;
		}
	}

	if (this->color_reset_queue->Count == 0) {
		this->reset_color_timer->Stop();
	}
}

System::Void VoleMachine::MainForm::highlightAddress(String^ address) {
	this->unHiglightLastAdderss();
	int numeric_address = stoi(
		Utilities::Conversion::convertHexToDec(
			Utilities::Conversion::convertSystemStringToStdString(address)
		)
	);

	int row = numeric_address / 2;

	this->memory_list->Rows[row]->Cells[0]->Style->BackColor = Color::LightBlue;
	this->memory_list->Rows[row]->Cells[3]->Style->BackColor = Color::LightBlue;

	this->last_highlighted_address = address;
}

System::Void VoleMachine::MainForm::unHiglightLastAdderss() {
	if (this->last_highlighted_address->Length == 0) {
		return;
	}

	int numeric_address = stoi(
		Utilities::Conversion::convertHexToDec(
			Utilities::Conversion::convertSystemStringToStdString(this->last_highlighted_address)
		)
	);

	int row = numeric_address / 2;

	this->memory_list->Rows[row]->Cells[0]->Style->BackColor = SystemColors::Control;
	this->memory_list->Rows[row]->Cells[3]->Style->BackColor = SystemColors::Control;
}

System::Void VoleMachine::MainForm::memory_list_CellPainting(Object^ sender, DataGridViewCellPaintingEventArgs^ e) {
	if (e->ColumnIndex == 0 || e->ColumnIndex == 3) {
		e->AdvancedBorderStyle->Left = DataGridViewAdvancedCellBorderStyle::None;
		e->AdvancedBorderStyle->Top = DataGridViewAdvancedCellBorderStyle::None;
		e->AdvancedBorderStyle->Bottom = DataGridViewAdvancedCellBorderStyle::None;
	}
	e->Handled = false;
}

#pragma endregion

#pragma region RegisterList Events
System::Void VoleMachine::MainForm::OnRegisterUpdated() {
	// Get Updated Register Number
	auto updated_register = this->reg_ctrl->getUpdatedRegister();

	if (updated_register.HasValue) {
		// Reset Highlight From Previous Update
		this->resetRegistersColor();

		// Highlight Updated Register
		this->registers_list->Items[updated_register.Value]->BackColor = System::Drawing::Color::LightGreen;

		// Get Values
		System::String^ hex_value = "0x" + this->reg_ctrl->getHexRegisterValueAt(updated_register.Value);
		System::String^ binary_value = this->reg_ctrl->getBinRegisterValueAt(updated_register.Value);
		System::String^ int_value = this->reg_ctrl->getIntRegisterValueAt(updated_register.Value);
		System::String^ float_value = this->reg_ctrl->getFloatRegisterValueAt(updated_register.Value);

		// Update Values
		this->registers_list->Items[updated_register.Value]->SubItems[1]->Text = hex_value;
		this->registers_list->Items[updated_register.Value]->SubItems[2]->Text = binary_value;
		this->registers_list->Items[updated_register.Value]->SubItems[3]->Text = int_value;
		this->registers_list->Items[updated_register.Value]->SubItems[4]->Text = float_value;
	}
}

System::Void VoleMachine::MainForm::OnAllRegistersUpdated() {
	for (int i = 0; i < 16; i++) {
		this->resetRegistersColor();

		// Get Values
		System::String^ hex_value = "0x" + this->reg_ctrl->getHexRegisterValueAt(i);
		System::String^ binary_value = this->reg_ctrl->getBinRegisterValueAt(i);
		System::String^ int_value = this->reg_ctrl->getIntRegisterValueAt(i);
		System::String^ float_value = this->reg_ctrl->getFloatRegisterValueAt(i);

		// Update Values
		this->registers_list->Items[i]->SubItems[1]->Text = hex_value;
		this->registers_list->Items[i]->SubItems[2]->Text = binary_value;
		this->registers_list->Items[i]->SubItems[3]->Text = int_value;
		this->registers_list->Items[i]->SubItems[4]->Text = float_value;
	}
	this->registers_list->Refresh();
}

System::Void VoleMachine::MainForm::OnResetRegisters() {
	// Reset Displayed Registers
	this->resetRegistersColor();

	for (int i = 0; i < 16; i++) {
		this->registers_list->Items[i]->SubItems[1]->Text = "0x00";
		this->registers_list->Items[i]->SubItems[2]->Text = "00000000";
		this->registers_list->Items[i]->SubItems[3]->Text = "0";
		this->registers_list->Items[i]->SubItems[4]->Text = "0";
	}
}

System::Void VoleMachine::MainForm::resetRegistersColor() {
	for (int i = 0; i < 16; i++) {
		this->registers_list->Items[i]->BackColor = System::Drawing::Color::White;
	}
}

#pragma endregion

#pragma region Execution Events

System::Void VoleMachine::MainForm::OnFetchInstruction() {
	this->current_address_textbox->Clear();
	String^ current_address = this->exec_ctrl->getCurrentAddress();
	this->current_address_textbox->Text = current_address;

	this->memory_list_ScrollUpdate();
	this->highlightAddress(current_address);

	this->current_instruction_textbox->Clear();
	String^ current_instruction = this->exec_ctrl->getCurrentInstruction();
	this->current_instruction_textbox->Text = current_instruction;
}

System::Void VoleMachine::MainForm::OnExecuteInstruction() {
	auto updated_address = this->exec_ctrl->getUpdatedAddress();

	if (updated_address.HasValue) {
		this->mem_ctrl->memoryUpdatedAtAddress(updated_address.Value);
	}

	this->reg_ctrl->registerUpdated();
	// TODO: Update screen
	this->machine->displayMemory(); // TODO: Remove
}

System::Void VoleMachine::MainForm::OnUpdateScreen(std::string value) {
	this->screen_textbox->AppendText(Utilities::Conversion::convertStdStringToSystemString(value));
	this->screen_textbox->ScrollToCaret();
}

System::Void VoleMachine::MainForm::OnChangeSpeed() {
	if (this->InvokeRequired) {
		this->Invoke(gcnew ExecutionController::SpeedChangedEventHandler(this,
			&MainForm::OnChangeSpeed));
		return;
	}

	if (this->steps_spinbox->Value != this->exec_ctrl->InstructionsPerSecond) {
		this->steps_spinbox->Value = this->exec_ctrl->InstructionsPerSecond;
	}
}

System::Void VoleMachine::MainForm::OnHaltProgram() {
	this->play->Text = "Play";
	this->exec_ctrl->pauseInstructions();
	this->exec_ctrl->resetProgram();
	this->resetRegistersColor();
	this->memory_list_ScrollUpdate();
	MessageBox::Show("Program halted.", "Program Halted", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void VoleMachine::MainForm::OnReachedEndOfMemory() {
	this->play->Text = "Play";
	this->exec_ctrl->pauseInstructions();
	this->exec_ctrl->resetProgram();
	this->resetRegistersColor();
	this->memory_list_ScrollUpdate();
	MessageBox::Show("Program reached end of memory.", "Reached End of Memory", MessageBoxButtons::OK, MessageBoxIcon::Warning);
}

System::Void VoleMachine::MainForm::OnExecutedAllInstructions() {
	this->mem_ctrl->memoryUpdated();
	this->reg_ctrl->updateAllRegisters();
	this->resetRegistersColor();
}
#pragma endregion

#pragma region Button Click Events

System::Void VoleMachine::MainForm::load_from_file_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!this->machine->getMemory().isEmpty()) { // TODO: move to execution controller
		Windows::Forms::DialogResult result = MessageBox::Show("Loading a file will overwrite the current memory and reset everything. Are you sure you want to continue?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
    
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
		this->exec_ctrl->resetProgram();
		this->reg_ctrl->resetRegisters();
		this->screen_textbox->Clear();
		// TODO: Reset Decoded Instruction
		MessageBox::Show("File loaded successfully!", "File Loaded", MessageBoxButtons::OK, MessageBoxIcon::Information);
		this->machine->displayMemory(); // TODO: remove 
;	}
}

System::Void VoleMachine::MainForm::export_to_file_Click(System::Object^ sender, System::EventArgs^ e) {
	if (mem_ctrl == nullptr) {
		MessageBox::Show("MemoryController is not initialized!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
	saveFileDialog->Filter = "Text Files|*.txt|All Files|*.*";
	saveFileDialog->Title = "Export Memory to File";

	if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		std::string filename = Utilities::Conversion::convertSystemStringToStdString(saveFileDialog->FileName);
		mem_ctrl->exportToFile(filename);
		MessageBox::Show("File saved successfully.", "Export Complete", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}

System::Void VoleMachine::MainForm::reset_memory_Click(System::Object^ sender, System::EventArgs^ e) {
	Windows::Forms::DialogResult result = MessageBox::Show("Are you sure you want to reset the memory?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

	if (result == System::Windows::Forms::DialogResult::No) {
		return;
	}

	this->mem_ctrl->resetMemory();
	this->machine->displayMemory(); // TODO: remove
}

System::Void VoleMachine::MainForm::reset_registers_Click(System::Object^ sender, System::EventArgs^ e) {

	Windows::Forms::DialogResult result = MessageBox::Show("Are you sure you want to reset registers?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

	if (result == System::Windows::Forms::DialogResult::No) {
		return;
	}

	this->reg_ctrl->resetRegisters();
}

System::Void VoleMachine::MainForm::fetch_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->fetchInstruction();
}

System::Void VoleMachine::MainForm::reset_pc_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->resetProgram();
	this->memory_list_ScrollUpdate();
}

System::Void VoleMachine::MainForm::clear_screen_Click(System::Object^ sender, System::EventArgs^ e) {
	this->screen_textbox->Clear();
}

System::Void VoleMachine::MainForm::execute_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->executeCurrentInstruction();
}

System::Void VoleMachine::MainForm::play_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->play->Text == "Play") {
		this->exec_ctrl->playInstructions();
		this->play->Text = "Stop";
	} else if (this->play->Text == "Stop") {
		this->exec_ctrl->pauseInstructions();
		this->play->Text = "Play";
	}
}

System::Void VoleMachine::MainForm::run_until_halt_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->runAllInstructions();
}

System::Void VoleMachine::MainForm::step_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->step();
}

System::Void VoleMachine::MainForm::decode_Click(System::Object^ sender, System::EventArgs^ e) {
	auto decoded_instruction = exec_ctrl->decodeInstruction();

	if (decoded_instruction == nullptr) {
		return;
	}

	this->opcode_textbox->Text = Utilities::Conversion::convertStdStringToSystemString(
		Utilities::Conversion::convertDecToHex(decoded_instruction[0])
	);

	OP_CODE opcode = static_cast<OP_CODE>(decoded_instruction[0]);
	UpdateOperandLabels(opcode);
	UpdateOperandsAndDescription(decoded_instruction, opcode);
}

System::Void VoleMachine::MainForm::ResetInstructionReg() {
	this->opcode_textbox->Clear();
	this->first_operand_textbox->Clear();
	this->second_operand_textbox->Clear();
	this->third_operand_textbox->Clear();
	this->instruction_decode_textbox->Clear();
}

void VoleMachine::MainForm::UpdateOperandLabels(OP_CODE opcode) {
	switch (opcode) {
	case OP_CODE::LOAD_M:
	case OP_CODE::LOAD_V:
	case OP_CODE::STORE:
	case OP_CODE::JUMP_EQ:
	case OP_CODE::JUMP_GT:
		this->first_operand_label->Text = "R:";
		this->second_operand_label->Text = "X:";
		this->third_operand_label->Text = "Y:";
		break;

	case OP_CODE::MOVE:
		this->first_operand_label->Text = "x:";
		this->second_operand_label->Text = "R:";
		this->third_operand_label->Text = "S:";
		break;

	case OP_CODE::ADD:
	case OP_CODE::ADD_F:
	case OP_CODE::BIT_OR:
	case OP_CODE::BIT_AND:
	case OP_CODE::BIT_XOR:
		this->first_operand_label->Text = "R:";
		this->second_operand_label->Text = "S:";
		this->third_operand_label->Text = "T:";
		break;

	case OP_CODE::ROTATE:
		this->first_operand_label->Text = "R:";
		this->second_operand_label->Text = "x:";
		this->third_operand_label->Text = "X:";
		break;

	case OP_CODE::HALT:
		this->first_operand_label->Text = "x";
		this->second_operand_label->Text = "x";
		this->third_operand_label->Text = "x";
		break;

	case OP_CODE::UNKNOWN:
		this->first_operand_label->Text = "?";
		this->second_operand_label->Text = "?";
		this->third_operand_label->Text = "?";
		break;

	default:
		MessageBox::Show("Unknown opcode.", "Decode Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
}

void VoleMachine::MainForm::UpdateOperandsAndDescription(System::Collections::Generic::List<int>^ decoded_instruction, OP_CODE opcode) {
	System::String^ first_operand = "";
	System::String^ second_operand = "";
	System::String^ third_operand = "";
	System::String^ instruction_description;

	if (decoded_instruction->Count > 1) {
		first_operand = Utilities::Conversion::convertStdStringToSystemString(
			Utilities::Conversion::convertDecToHex(decoded_instruction[1])
		);
	}

	if (decoded_instruction->Count > 2) {
		System::String^ second_third_operand = Utilities::Conversion::convertStdStringToSystemString(
			Utilities::Conversion::convertDecToHex(decoded_instruction[2])
		);

		if (second_third_operand->Length > 1) {
			second_operand += second_third_operand[0]; // X
			third_operand += second_third_operand[1]; // Y
		} else {
			second_operand = "0"; // X
			third_operand = second_third_operand; // Y
		}
	}

	if (opcode == OP_CODE::MOVE && decoded_instruction->Count > 2) {
		second_operand = Utilities::Conversion::convertStdStringToSystemString(
			Utilities::Conversion::convertDecToHex(decoded_instruction[2]));
	}
	if (decoded_instruction->Count > 3) {
		third_operand = Utilities::Conversion::convertStdStringToSystemString(
			Utilities::Conversion::convertDecToHex(decoded_instruction[3]));
	}
	
	instruction_description = GetInstructionDescription(opcode, first_operand, second_operand, third_operand);

	this->first_operand_textbox->Text = first_operand;
	this->second_operand_textbox->Text = second_operand;
	this->third_operand_textbox->Text = third_operand;

	
	this->instruction_decode_textbox->Text = instruction_description;
}

System::String^ VoleMachine::MainForm::GetInstructionDescription(OP_CODE opcode, System::String^ first_operand, System::String^ second_operand, System::String^ third_operand) {
	switch (opcode) {
	case OP_CODE::LOAD_M:
		return "Copy the content from memory address " + second_operand + third_operand + " to register " + first_operand;
	case OP_CODE::LOAD_V:
		return "Copy the value " + second_operand + third_operand + " to register " + first_operand;
	case OP_CODE::STORE:
		return "Store the content of register " + first_operand + " in memory address " + second_operand + third_operand;
	case OP_CODE::MOVE:
		return "Move the content of register " + second_operand + " to register " + third_operand;
	case OP_CODE::ADD:
		return "Add (in two's complement representation) the contents of registers " + second_operand + " and " + third_operand + " into register " + first_operand;
	case OP_CODE::ADD_F:
		return "Add (in floating point representation) the contents of registers " + second_operand + " and " + third_operand + " into register " + first_operand;
	case OP_CODE::BIT_OR:
		return "Bitwise OR the contents of registers " + second_operand + " and " + third_operand + " into register " + first_operand;
	case OP_CODE::BIT_AND:
		return "Bitwise AND the contents of registers " + second_operand + " and " + third_operand + " into register " + first_operand;
	case OP_CODE::BIT_XOR:
		return "Bitwise XOR the conetnts of registers " + second_operand + " and " + third_operand + " into register " + first_operand;
	case OP_CODE::ROTATE:
		return "Rotate register " + first_operand + " by " + third_operand + " steps cyclically right";
	case OP_CODE::JUMP_EQ:
		return "Jump to the instruction at memory address " + second_operand + third_operand + " if register " + first_operand + " contains the value 00";
	case OP_CODE::HALT:
		return "Halt execution";
	case OP_CODE::JUMP_GT:
		return "Jump to the instruction at memory address" + second_operand + third_operand + " if register " + first_operand + " contains a value greater than 00";
	case OP_CODE::UNKNOWN:
	default:
		return "Unknown instruction. Do nothing and advance to the next instruction.";
	}
}

#pragma endregion

#pragma region Text Boxes Events
System::Void VoleMachine::MainForm::steps_spinbox_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	int new_speed = static_cast<int>(this->steps_spinbox->Value);

	if (this->exec_ctrl->InstructionsPerSecond != new_speed) {
		this->exec_ctrl->updateSpeed(new_speed);
	}
}

System::Void VoleMachine::MainForm::starting_address_textbox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	return;
	if (this->starting_address_textbox->Text->Length == 2) {
		this->exec_ctrl->setStartingAddress(this->starting_address_textbox->Text);
		return;
	}

	if (this->starting_address_textbox->Text->Length == 1) {
		this->starting_address_textbox->Text = "0" + this->starting_address_textbox->Text;
		return;
	}

	if (this->starting_address_textbox->Text->Length == 0) {
		this->starting_address_textbox->Text = "00";
		return;
	}
}

System::Void VoleMachine::MainForm::starting_address_textbox_KeyPress(Object^ sender, KeyPressEventArgs^ e) {
	if (e->KeyChar == '\b') {
		return;
	}

	e->KeyChar = Char::ToUpper(e->KeyChar);

	bool isHex = (e->KeyChar >= '0' && e->KeyChar <= '9') ||
		(e->KeyChar >= 'A' && e->KeyChar <= 'F');

	bool withinLength = starting_address_textbox->Text->Length < 2;

	if (!isHex || !withinLength) {
		e->Handled = true;  // Suppress the keypress
	}
}

System::Void VoleMachine::MainForm::starting_address_textbox_Click(System::Object^ sender, System::EventArgs^ e) {
	//this->starting_address_textbox->Clear();
	return;
}

System::Void VoleMachine::MainForm::starting_address_textbox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (this->starting_address_textbox->SelectionLength == this->starting_address_textbox->Text->Length &&
		e->KeyCode != System::Windows::Forms::Keys::Back &&
		e->KeyCode != System::Windows::Forms::Keys::Delete &&
		e->KeyCode != System::Windows::Forms::Keys::Left &&
		e->KeyCode != System::Windows::Forms::Keys::Right &&
		e->KeyCode != System::Windows::Forms::Keys::Enter &&
		e->KeyCode != System::Windows::Forms::Keys::Escape) {
		this->starting_address_textbox->Text = "";  // Clear text to allow overwriting
	}

	if (e->KeyCode == Keys::Enter || e->KeyCode == Keys::Escape) {
		this->updateStartingAddress();
		e->Handled = true;
		this->ActiveControl = nullptr;
	}
}

System::Void VoleMachine::MainForm::starting_address_textbox_Leave(System::Object^ sender, System::EventArgs^ e) {
	this->updateStartingAddress();
}

System::Void VoleMachine::MainForm::starting_address_textbox_Enter(System::Object^ sender, System::EventArgs^ e) {
	this->BeginInvoke(
		gcnew System::Action(
			this, &VoleMachine::MainForm::starting_address_textbox_SelectStartingAddressText
		)
	);
}

System::Void VoleMachine::MainForm::updateStartingAddress() {
	String^ text = this->starting_address_textbox->Text;

	if (text->Length == 2) {
		int decimal_value = stoi(
			Utilities::Conversion::convertHexToDec(
				Utilities::Conversion::convertSystemStringToStdString(text)
			)
		);

		if (decimal_value % 2 != 0) {
			decimal_value--;

			text = Utilities::Conversion::convertStdStringToSystemString(
				Utilities::Conversion::convertDecToHex(decimal_value)
			);


			if (text->Length == 1) {
				text = "0" + text;
			}

			this->starting_address_textbox->Text = text;
		} // handle odd addresses

		int current_execution_address = stoi(
			Utilities::Conversion::convertHexToDec(
				Utilities::Conversion::convertSystemStringToStdString(
					this->exec_ctrl->getCurrentAddress()
				)
			)
		);

		if (current_execution_address < decimal_value) {
			this->current_address_textbox->Text = text;
			this->highlightAddress(text);
		} // update program counter

		this->exec_ctrl->setStartingAddress(text);
		this->memory_list_ScrollUpdate();
		return;
	}

	while (text->Length < 2) {
		text = "0" + text;
	}

	this->starting_address_textbox->Text = text;
	this->updateStartingAddress();
}

System::Void VoleMachine::MainForm::starting_address_textbox_SelectStartingAddressText() {
	this->starting_address_textbox->SelectAll();
}
#pragma endregion