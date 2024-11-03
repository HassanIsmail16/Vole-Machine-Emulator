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

	this->memory_list->CurrentCell = this->memory_list->Rows[0]->Cells[1];
}

System::Void VoleMachine::MainForm::resetRegistersColor() {
	for (int i = 0; i < 16; i++) {
		this->registers_list->Items[i]->BackColor = System::Drawing::Color::White;
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
	if (this->memory_list->InvokeRequired) {
		this->Invoke(gcnew MemoryController::MemoryUpdatedEventHandler(this,
			&MainForm::OnMemoryUpdated));
		return;
	}

	this->initializeMemoryList();
	for (int i = 0; i < 128; i++) {
		String^ first_value = Utilities::Conversion::convertStdStringToSystemString(
			this->machine->getMemory().getValueAt(i * 2));
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

	this->memory_list->Rows[row]->Cells[col]->Value =
		Utilities::Conversion::convertStdStringToSystemString(
			this->machine->getMemory().getValueAt(index));
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

	this->machine->displayMemory();
}

System::Void VoleMachine::MainForm::OnFetchInstruction() {
	this->current_address_textbox->Clear();
	String^ current_address = this->exec_ctrl->getCurrentAddress();
	this->current_address_textbox->Text = current_address;

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

	// TODO: update registers and screen
	this->machine->displayMemory(); // TODO: Remove
}

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
		this->registers_list->Refresh();
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
		this->registers_list->Refresh();
	}
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
	MessageBox::Show("Program halted.", "Program Halted", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void VoleMachine::MainForm::OnReachedEndOfMemory() {
	this->play->Text = "Play";
	this->exec_ctrl->pauseInstructions();
	this->exec_ctrl->resetProgram();
	this->resetRegistersColor();
	MessageBox::Show("Program reached end of memory.", "Reached End of Memory", MessageBoxButtons::OK, MessageBoxIcon::Warning);
}

System::Void VoleMachine::MainForm::OnExecutedAllInstructions() {
	this->mem_ctrl->memoryUpdated();
	this->reg_ctrl->updateAllRegisters();
	this->resetRegistersColor();
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
			} else {
				this->memory_list->Rows[reset_info->Item2]->Cells[reset_info->Item3]->Style->BackColor = Color::White;
			}
		} else {
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

System::Void VoleMachine::MainForm::load_from_file_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!this->machine->getMemory().isEmpty()) {
		Windows::Forms::DialogResult result = MessageBox::Show("Loading a file will overwrite the current memory and reset registers. Are you sure you want to continue?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
    
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
		this->reg_ctrl->resetRegisters();
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
	this->machine->displayMemory();
}

System::Void VoleMachine::MainForm::reset_registers_Click(System::Object^ sender, System::EventArgs^ e) {

	Windows::Forms::DialogResult result = MessageBox::Show("Are you sure you want to reset registers?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

	if (result == System::Windows::Forms::DialogResult::No) {
		return;
	}

	this->reg_ctrl->resetRegisters();
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

System::Void VoleMachine::MainForm::fetch_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->fetchInstruction();
}

System::Void VoleMachine::MainForm::reset_pc_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->resetProgram();
}

System::Void VoleMachine::MainForm::clear_screen_Click(System::Object^ sender, System::EventArgs^ e) {
	this->screen_textbox->Clear();
}

System::Void VoleMachine::MainForm::execute_Click(System::Object^ sender, System::EventArgs^ e) {
	this->exec_ctrl->executeCurrentInstruction();
}

System::Void VoleMachine::MainForm::steps_spinbox_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	int new_speed = static_cast<int>(this->steps_spinbox->Value);

	if (this->exec_ctrl->InstructionsPerSecond != new_speed) {
		this->exec_ctrl->updateSpeed(new_speed);
	}
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
	auto  decodedInstruction = exec_ctrl->decodeInstruction();
	if (decodedInstruction->Count == 0) return;
	
	this->opcode_textbox->Text = Utilities::Conversion::convertStdStringToSystemString(
		Utilities::Conversion::convertDecToHex(decodedInstruction[0]));

	OP_CODE opcode = static_cast<OP_CODE>(decodedInstruction[0]);
	UpdateOperandLabels(opcode);
	UpdateOperandsAndDescription(decodedInstruction, opcode);
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
		this->first_operand_label->Text = "";
		this->second_operand_label->Text = "";
		this->third_operand_label->Text = "";
		break;

	default:
		MessageBox::Show("Unknown opcode.", "Decode Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
}

void VoleMachine::MainForm::UpdateOperandsAndDescription(System::Collections::Generic::List<int>^ decodedInstruction, OP_CODE opcode) {
	System::String^ firstOperand = "";
	System::String^ secondOperand = "";
	System::String^ thirdOperand = "";
	System::String^ instructionDescription;

	if (decodedInstruction->Count > 1) {
		firstOperand = Utilities::Conversion::convertStdStringToSystemString(
			Utilities::Conversion::convertDecToHex(decodedInstruction[1]));

		std::cout << Utilities::Conversion::convertSystemStringToStdString(firstOperand) << std::endl;
	}
	if (decodedInstruction->Count > 2) {
		secondOperand = Utilities::Conversion::convertStdStringToSystemString(
			Utilities::Conversion::convertDecToHex(decodedInstruction[2])); // X
		thirdOperand = Utilities::Conversion::convertStdStringToSystemString(
			Utilities::Conversion::convertDecToHex(decodedInstruction[2]));         // Y
	}

	if (opcode == OP_CODE::MOVE && decodedInstruction->Count > 2) {
		secondOperand = Utilities::Conversion::convertStdStringToSystemString(
			Utilities::Conversion::convertDecToHex(decodedInstruction[2]));
	}
	if (decodedInstruction->Count > 3) {
		thirdOperand = Utilities::Conversion::convertStdStringToSystemString(
			Utilities::Conversion::convertDecToHex(decodedInstruction[3]));
	}

	instructionDescription = GetInstructionDescription(opcode, firstOperand, secondOperand, thirdOperand);

	
	this->first_operand_textbox->Text = firstOperand;
	this->second_operand_textbox->Text = secondOperand;
	this->third_operand_textbox->Text = thirdOperand;

	
	this->instruction_decode_textbox->Text = instructionDescription;
}

System::String^ VoleMachine::MainForm::GetInstructionDescription(OP_CODE opcode, System::String^ firstOperand, System::String^ secondOperand, System::String^ thirdOperand) {
	switch (opcode) {
	case OP_CODE::LOAD_M:
		return "Copy from memory " + secondOperand + thirdOperand + " to register " + firstOperand;
	case OP_CODE::LOAD_V:
		return "Copy bit-string " + secondOperand + thirdOperand + " to register " + firstOperand;
	case OP_CODE::STORE:
		return "Store register " + firstOperand + " in memory " + secondOperand + thirdOperand;
	case OP_CODE::JUMP_EQ:
		return "Jump to " + secondOperand + thirdOperand + " if register " + firstOperand + " == 0";
	case OP_CODE::JUMP_GT:
		return "Jump to " + secondOperand + thirdOperand + " if register " + firstOperand + " > 0";
	case OP_CODE::MOVE:
		return "Move register " + secondOperand + " to register " + thirdOperand;
	case OP_CODE::ADD:
		return "Add registers " + secondOperand + " and " + thirdOperand + " to register " + firstOperand;
	case OP_CODE::ADD_F:
		return "Add (float) registers " + secondOperand + " and " + thirdOperand + " to register " + firstOperand;
	case OP_CODE::BIT_OR:
		return "OR registers " + secondOperand + " and " + thirdOperand + " to register " + firstOperand;
	case OP_CODE::BIT_AND:
		return "AND registers " + secondOperand + " and " + thirdOperand + " to register " + firstOperand;
	case OP_CODE::BIT_XOR:
		return "XOR registers " + secondOperand + " and " + thirdOperand + " to register " + firstOperand;
	case OP_CODE::ROTATE:
		return "Rotate register " + firstOperand + " by " + secondOperand + " steps";
	case OP_CODE::HALT:
		return "Halt execution";
	default:
		return "Unknown opcode.";
	}
}

