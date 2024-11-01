#pragma once
#include "Machine.h"
#include "Utilities.h"
#include "MemoryController.h"
#include "RegistersController.h"
#include "ExecutionController.h"

namespace VoleMachine {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form {

	public:
		MemoryController^ memoryController;
		MainForm(void) {

			this->machine = new Machine();
			this->mem_ctrl = gcnew MemoryController(this->machine);
			this->reg_ctrl = gcnew RegistersController(this->machine);
			this->exec_ctrl = gcnew ExecutionController(this->machine);
			this->InitializeComponent();
			this->memory_list->CellValueChanged += gcnew DataGridViewCellEventHandler(this, &MainForm::memory_list_OnMemoryCellValueChanged);
			this->initializeRegistersList();
			this->initializeMemoryList();
			this->mem_ctrl->memory_updated += gcnew MemoryController::MemoryUpdatedEventHandler(this, &VoleMachine::MainForm::OnMemoryUpdated);
			this->exec_ctrl->fetched_instruction += gcnew ExecutionController::InstructionFetchedEventHandler(this, &VoleMachine::MainForm::OnFetchInstruction);
		}

	protected:
		~MainForm() {
			this->!MainForm();
			if (components)
			{
				delete components;
			}
		}

		!MainForm() {
			if (this->machine) {
				delete this->machine;
				this->machine = nullptr;
			}
		}

	private: System::Windows::Forms::Panel^ main_panel;
	private: System::Windows::Forms::Panel^ controls_panel;
	private: System::Windows::Forms::Label^ controls_label;
	private: System::Windows::Forms::Button^ export_to_file;
	private: System::Windows::Forms::Button^ step;

	private: System::Windows::Forms::Button^ reset_memory;
	private: System::Windows::Forms::Button^ reset_registers;
	private: System::Windows::Forms::Button^ play;

	private: System::Windows::Forms::Button^ load_from_file;
	private: System::Windows::Forms::NumericUpDown^ steps_spinbox;

	private: System::Windows::Forms::Label^ steps_label;

	private: System::Windows::Forms::Button^ run_until_halt;
	private: System::Windows::Forms::Panel^ registers_panel;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ListView^ registers_list;
	private: System::Windows::Forms::Label^ memory_label;
	private: System::Windows::Forms::Panel^ memory_panel;

	private: System::Windows::Forms::DataGridView^ memory_list;
	private: System::Windows::Forms::Panel^ program_counter_panel;
	private: System::Windows::Forms::Label^ program_counter_label;
	private: System::Windows::Forms::Label^ program_counter_address_label;
	private: System::Windows::Forms::Panel^ instruction_register_panel;
	private: System::Windows::Forms::Label^ instruction_register_label;

	private: System::Windows::Forms::Label^ screen_label;
	private: System::Windows::Forms::Panel^ screen_panel;
	private: System::Windows::Forms::Button^ clear_screen;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::TextBox^ screen_textbox;
	private: System::Windows::Forms::TextBox^ current_address_textbox;

	private: System::Windows::Forms::TextBox^ current_instruction_textbox;

	private: System::Windows::Forms::Label^ instruction_register_instruction_label;
	private: System::Windows::Forms::Button^ decode;
	private: System::Windows::Forms::Button^ fetch;

	private: System::Windows::Forms::Label^ opcode_label;
	private: System::Windows::Forms::TextBox^ opcode_textbox;

	private: System::Windows::Forms::Label^ first_operand_label;
	private: System::Windows::Forms::TextBox^ first_operand_textbox;
	private: System::Windows::Forms::TextBox^ third_operand_textbox;

	private: System::Windows::Forms::TextBox^ second_operand_textbox;
	private: System::Windows::Forms::Label^ third_operand_label;
	private: System::Windows::Forms::Label^ second_operand_label;

	private: System::Windows::Forms::Button^ execute;
	private: System::Windows::Forms::TextBox^ instruction_decode_textbox;
	private: System::Windows::Forms::Button^ dark_mode;
	private: System::Windows::Forms::Label^ credits_label;
	private: System::Windows::Forms::Button^ reset_pc;





	private: System::ComponentModel::IContainer^ components;

	private:

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			this->main_panel = (gcnew System::Windows::Forms::Panel());
			this->credits_label = (gcnew System::Windows::Forms::Label());
			this->dark_mode = (gcnew System::Windows::Forms::Button());
			this->clear_screen = (gcnew System::Windows::Forms::Button());
			this->screen_label = (gcnew System::Windows::Forms::Label());
			this->screen_panel = (gcnew System::Windows::Forms::Panel());
			this->screen_textbox = (gcnew System::Windows::Forms::TextBox());
			this->instruction_register_label = (gcnew System::Windows::Forms::Label());
			this->instruction_register_panel = (gcnew System::Windows::Forms::Panel());
			this->instruction_decode_textbox = (gcnew System::Windows::Forms::TextBox());
			this->third_operand_textbox = (gcnew System::Windows::Forms::TextBox());
			this->second_operand_textbox = (gcnew System::Windows::Forms::TextBox());
			this->first_operand_textbox = (gcnew System::Windows::Forms::TextBox());
			this->opcode_textbox = (gcnew System::Windows::Forms::TextBox());
			this->third_operand_label = (gcnew System::Windows::Forms::Label());
			this->second_operand_label = (gcnew System::Windows::Forms::Label());
			this->first_operand_label = (gcnew System::Windows::Forms::Label());
			this->opcode_label = (gcnew System::Windows::Forms::Label());
			this->execute = (gcnew System::Windows::Forms::Button());
			this->decode = (gcnew System::Windows::Forms::Button());
			this->current_instruction_textbox = (gcnew System::Windows::Forms::TextBox());
			this->instruction_register_instruction_label = (gcnew System::Windows::Forms::Label());
			this->program_counter_label = (gcnew System::Windows::Forms::Label());
			this->program_counter_panel = (gcnew System::Windows::Forms::Panel());
			this->current_address_textbox = (gcnew System::Windows::Forms::TextBox());
			this->program_counter_address_label = (gcnew System::Windows::Forms::Label());
			this->reset_pc = (gcnew System::Windows::Forms::Button());
			this->fetch = (gcnew System::Windows::Forms::Button());
			this->memory_label = (gcnew System::Windows::Forms::Label());
			this->memory_panel = (gcnew System::Windows::Forms::Panel());
			this->memory_list = (gcnew System::Windows::Forms::DataGridView());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->registers_panel = (gcnew System::Windows::Forms::Panel());
			this->registers_list = (gcnew System::Windows::Forms::ListView());
			this->controls_label = (gcnew System::Windows::Forms::Label());
			this->controls_panel = (gcnew System::Windows::Forms::Panel());
			this->run_until_halt = (gcnew System::Windows::Forms::Button());
			this->steps_label = (gcnew System::Windows::Forms::Label());
			this->step = (gcnew System::Windows::Forms::Button());
			this->steps_spinbox = (gcnew System::Windows::Forms::NumericUpDown());
			this->export_to_file = (gcnew System::Windows::Forms::Button());
			this->reset_memory = (gcnew System::Windows::Forms::Button());
			this->reset_registers = (gcnew System::Windows::Forms::Button());
			this->play = (gcnew System::Windows::Forms::Button());
			this->load_from_file = (gcnew System::Windows::Forms::Button());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->main_panel->SuspendLayout();
			this->screen_panel->SuspendLayout();
			this->instruction_register_panel->SuspendLayout();
			this->program_counter_panel->SuspendLayout();
			this->memory_panel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->memory_list))->BeginInit();
			this->registers_panel->SuspendLayout();
			this->controls_panel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->steps_spinbox))->BeginInit();
			this->SuspendLayout();
			// 
			// main_panel
			// 
			this->main_panel->Controls->Add(this->credits_label);
			this->main_panel->Controls->Add(this->dark_mode);
			this->main_panel->Controls->Add(this->clear_screen);
			this->main_panel->Controls->Add(this->screen_label);
			this->main_panel->Controls->Add(this->screen_panel);
			this->main_panel->Controls->Add(this->instruction_register_label);
			this->main_panel->Controls->Add(this->instruction_register_panel);
			this->main_panel->Controls->Add(this->program_counter_label);
			this->main_panel->Controls->Add(this->program_counter_panel);
			this->main_panel->Controls->Add(this->memory_label);
			this->main_panel->Controls->Add(this->memory_panel);
			this->main_panel->Controls->Add(this->label1);
			this->main_panel->Controls->Add(this->registers_panel);
			this->main_panel->Controls->Add(this->controls_label);
			this->main_panel->Controls->Add(this->controls_panel);
			this->main_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->main_panel->Location = System::Drawing::Point(0, 0);
			this->main_panel->Name = L"main_panel";
			this->main_panel->Padding = System::Windows::Forms::Padding(10, 10, 10, 10);
			this->main_panel->Size = System::Drawing::Size(957, 584);
			this->main_panel->TabIndex = 0;
			// 
			// credits_label
			// 
			this->credits_label->AutoSize = true;
			this->credits_label->Location = System::Drawing::Point(7, 560);
			this->credits_label->Name = L"credits_label";
			this->credits_label->Size = System::Drawing::Size(382, 13);
			this->credits_label->TabIndex = 13;
			this->credits_label->Text = L"Made with (not that much) love by: Hassan Ali, Abdullah Ali, Momen Abdelkader";
			// 
			// dark_mode
			// 
			this->dark_mode->Location = System::Drawing::Point(836, 555);
			this->dark_mode->Name = L"dark_mode";
			this->dark_mode->Size = System::Drawing::Size(110, 23);
			this->dark_mode->TabIndex = 12;
			this->dark_mode->Text = L"Dark Mode";
			this->dark_mode->UseVisualStyleBackColor = true;
			// 
			// clear_screen
			// 
			this->clear_screen->Location = System::Drawing::Point(849, 316);
			this->clear_screen->Name = L"clear_screen";
			this->clear_screen->Size = System::Drawing::Size(83, 23);
			this->clear_screen->TabIndex = 11;
			this->clear_screen->Text = L"Clear Screen";
			this->clear_screen->UseVisualStyleBackColor = true;
			// 
			// screen_label
			// 
			this->screen_label->AutoSize = true;
			this->screen_label->Location = System::Drawing::Point(675, 321);
			this->screen_label->Name = L"screen_label";
			this->screen_label->Size = System::Drawing::Size(41, 13);
			this->screen_label->TabIndex = 10;
			this->screen_label->Text = L"Screen";
			// 
			// screen_panel
			// 
			this->screen_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->screen_panel->Controls->Add(this->screen_textbox);
			this->screen_panel->Location = System::Drawing::Point(667, 329);
			this->screen_panel->Name = L"screen_panel";
			this->screen_panel->Size = System::Drawing::Size(279, 220);
			this->screen_panel->TabIndex = 9;
			// 
			// screen_textbox
			// 
			this->screen_textbox->BackColor = System::Drawing::SystemColors::Control;
			this->screen_textbox->Location = System::Drawing::Point(5, 15);
			this->screen_textbox->Multiline = true;
			this->screen_textbox->Name = L"screen_textbox";
			this->screen_textbox->ReadOnly = true;
			this->screen_textbox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->screen_textbox->Size = System::Drawing::Size(268, 198);
			this->screen_textbox->TabIndex = 0;
			// 
			// instruction_register_label
			// 
			this->instruction_register_label->AutoSize = true;
			this->instruction_register_label->Location = System::Drawing::Point(675, 77);
			this->instruction_register_label->Name = L"instruction_register_label";
			this->instruction_register_label->Size = System::Drawing::Size(98, 13);
			this->instruction_register_label->TabIndex = 8;
			this->instruction_register_label->Text = L"Instruction Register";
			// 
			// instruction_register_panel
			// 
			this->instruction_register_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->instruction_register_panel->Controls->Add(this->instruction_decode_textbox);
			this->instruction_register_panel->Controls->Add(this->third_operand_textbox);
			this->instruction_register_panel->Controls->Add(this->second_operand_textbox);
			this->instruction_register_panel->Controls->Add(this->first_operand_textbox);
			this->instruction_register_panel->Controls->Add(this->opcode_textbox);
			this->instruction_register_panel->Controls->Add(this->third_operand_label);
			this->instruction_register_panel->Controls->Add(this->second_operand_label);
			this->instruction_register_panel->Controls->Add(this->first_operand_label);
			this->instruction_register_panel->Controls->Add(this->opcode_label);
			this->instruction_register_panel->Controls->Add(this->execute);
			this->instruction_register_panel->Controls->Add(this->decode);
			this->instruction_register_panel->Controls->Add(this->current_instruction_textbox);
			this->instruction_register_panel->Controls->Add(this->instruction_register_instruction_label);
			this->instruction_register_panel->Location = System::Drawing::Point(667, 84);
			this->instruction_register_panel->Name = L"instruction_register_panel";
			this->instruction_register_panel->Size = System::Drawing::Size(279, 226);
			this->instruction_register_panel->TabIndex = 7;
			// 
			// instruction_decode_textbox
			// 
			this->instruction_decode_textbox->AcceptsReturn = true;
			this->instruction_decode_textbox->BackColor = System::Drawing::SystemColors::Control;
			this->instruction_decode_textbox->Location = System::Drawing::Point(17, 111);
			this->instruction_decode_textbox->Multiline = true;
			this->instruction_decode_textbox->Name = L"instruction_decode_textbox";
			this->instruction_decode_textbox->Size = System::Drawing::Size(242, 71);
			this->instruction_decode_textbox->TabIndex = 5;
			// 
			// third_operand_textbox
			// 
			this->third_operand_textbox->Location = System::Drawing::Point(233, 81);
			this->third_operand_textbox->Name = L"third_operand_textbox";
			this->third_operand_textbox->ReadOnly = true;
			this->third_operand_textbox->Size = System::Drawing::Size(21, 20);
			this->third_operand_textbox->TabIndex = 4;
			// 
			// second_operand_textbox
			// 
			this->second_operand_textbox->Location = System::Drawing::Point(180, 81);
			this->second_operand_textbox->Name = L"second_operand_textbox";
			this->second_operand_textbox->ReadOnly = true;
			this->second_operand_textbox->Size = System::Drawing::Size(21, 20);
			this->second_operand_textbox->TabIndex = 4;
			// 
			// first_operand_textbox
			// 
			this->first_operand_textbox->Location = System::Drawing::Point(127, 81);
			this->first_operand_textbox->Name = L"first_operand_textbox";
			this->first_operand_textbox->ReadOnly = true;
			this->first_operand_textbox->Size = System::Drawing::Size(21, 20);
			this->first_operand_textbox->TabIndex = 4;
			// 
			// opcode_textbox
			// 
			this->opcode_textbox->Location = System::Drawing::Point(65, 81);
			this->opcode_textbox->Name = L"opcode_textbox";
			this->opcode_textbox->ReadOnly = true;
			this->opcode_textbox->Size = System::Drawing::Size(21, 20);
			this->opcode_textbox->TabIndex = 4;
			// 
			// third_operand_label
			// 
			this->third_operand_label->AutoSize = true;
			this->third_operand_label->Location = System::Drawing::Point(213, 85);
			this->third_operand_label->Name = L"third_operand_label";
			this->third_operand_label->Size = System::Drawing::Size(16, 13);
			this->third_operand_label->TabIndex = 3;
			this->third_operand_label->Text = L"\?:";
			// 
			// second_operand_label
			// 
			this->second_operand_label->AutoSize = true;
			this->second_operand_label->Location = System::Drawing::Point(160, 85);
			this->second_operand_label->Name = L"second_operand_label";
			this->second_operand_label->Size = System::Drawing::Size(16, 13);
			this->second_operand_label->TabIndex = 3;
			this->second_operand_label->Text = L"\?:";
			// 
			// first_operand_label
			// 
			this->first_operand_label->AutoSize = true;
			this->first_operand_label->Location = System::Drawing::Point(107, 85);
			this->first_operand_label->Name = L"first_operand_label";
			this->first_operand_label->Size = System::Drawing::Size(16, 13);
			this->first_operand_label->TabIndex = 3;
			this->first_operand_label->Text = L"\?:";
			// 
			// opcode_label
			// 
			this->opcode_label->AutoSize = true;
			this->opcode_label->Location = System::Drawing::Point(14, 85);
			this->opcode_label->Name = L"opcode_label";
			this->opcode_label->Size = System::Drawing::Size(48, 13);
			this->opcode_label->TabIndex = 3;
			this->opcode_label->Text = L"Opcode:";
			// 
			// execute
			// 
			this->execute->Location = System::Drawing::Point(17, 188);
			this->execute->Name = L"execute";
			this->execute->Size = System::Drawing::Size(243, 23);
			this->execute->TabIndex = 2;
			this->execute->Text = L"Execute";
			this->execute->UseVisualStyleBackColor = true;
			// 
			// decode
			// 
			this->decode->Location = System::Drawing::Point(17, 50);
			this->decode->Name = L"decode";
			this->decode->Size = System::Drawing::Size(243, 23);
			this->decode->TabIndex = 2;
			this->decode->Text = L"Decode";
			this->decode->UseVisualStyleBackColor = true;
			// 
			// current_instruction_textbox
			// 
			this->current_instruction_textbox->Location = System::Drawing::Point(138, 18);
			this->current_instruction_textbox->Name = L"current_instruction_textbox";
			this->current_instruction_textbox->ReadOnly = true;
			this->current_instruction_textbox->Size = System::Drawing::Size(92, 20);
			this->current_instruction_textbox->TabIndex = 1;
			// 
			// instruction_register_instruction_label
			// 
			this->instruction_register_instruction_label->AutoSize = true;
			this->instruction_register_instruction_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->instruction_register_instruction_label->Location = System::Drawing::Point(17, 22);
			this->instruction_register_instruction_label->Name = L"instruction_register_instruction_label";
			this->instruction_register_instruction_label->Size = System::Drawing::Size(112, 13);
			this->instruction_register_instruction_label->TabIndex = 0;
			this->instruction_register_instruction_label->Text = L"Current Instruction";
			// 
			// program_counter_label
			// 
			this->program_counter_label->AutoSize = true;
			this->program_counter_label->Location = System::Drawing::Point(23, 79);
			this->program_counter_label->Name = L"program_counter_label";
			this->program_counter_label->Size = System::Drawing::Size(86, 13);
			this->program_counter_label->TabIndex = 6;
			this->program_counter_label->Text = L"Program Counter";
			// 
			// program_counter_panel
			// 
			this->program_counter_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->program_counter_panel->Controls->Add(this->current_address_textbox);
			this->program_counter_panel->Controls->Add(this->program_counter_address_label);
			this->program_counter_panel->Controls->Add(this->reset_pc);
			this->program_counter_panel->Controls->Add(this->fetch);
			this->program_counter_panel->Location = System::Drawing::Point(10, 84);
			this->program_counter_panel->Name = L"program_counter_panel";
			this->program_counter_panel->Size = System::Drawing::Size(393, 63);
			this->program_counter_panel->TabIndex = 5;
			// 
			// current_address_textbox
			// 
			this->current_address_textbox->Location = System::Drawing::Point(122, 23);
			this->current_address_textbox->Name = L"current_address_textbox";
			this->current_address_textbox->ReadOnly = true;
			this->current_address_textbox->Size = System::Drawing::Size(78, 20);
			this->current_address_textbox->TabIndex = 1;
			// 
			// program_counter_address_label
			// 
			this->program_counter_address_label->AutoSize = true;
			this->program_counter_address_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->program_counter_address_label->Location = System::Drawing::Point(13, 26);
			this->program_counter_address_label->Name = L"program_counter_address_label";
			this->program_counter_address_label->Size = System::Drawing::Size(101, 13);
			this->program_counter_address_label->TabIndex = 0;
			this->program_counter_address_label->Text = L"Current Address:";
			// 
			// reset_pc
			// 
			this->reset_pc->Location = System::Drawing::Point(300, 21);
			this->reset_pc->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->reset_pc->Name = L"reset_pc";
			this->reset_pc->Size = System::Drawing::Size(78, 23);
			this->reset_pc->TabIndex = 4;
			this->reset_pc->Text = L"Reset";
			this->reset_pc->UseVisualStyleBackColor = true;
			this->reset_pc->Click += gcnew System::EventHandler(this, &MainForm::reset_pc_Click);
			// 
			// fetch
			// 
			this->fetch->Location = System::Drawing::Point(205, 22);
			this->fetch->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->fetch->Name = L"fetch";
			this->fetch->Size = System::Drawing::Size(91, 23);
			this->fetch->TabIndex = 4;
			this->fetch->Text = L"Fetch";
			this->fetch->UseVisualStyleBackColor = true;
			this->fetch->Click += gcnew System::EventHandler(this, &MainForm::fetch_Click);
			// 
			// memory_label
			// 
			this->memory_label->AutoSize = true;
			this->memory_label->Location = System::Drawing::Point(426, 77);
			this->memory_label->Name = L"memory_label";
			this->memory_label->Size = System::Drawing::Size(44, 13);
			this->memory_label->TabIndex = 4;
			this->memory_label->Text = L"Memory";
			// 
			// memory_panel
			// 
			this->memory_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->memory_panel->Controls->Add(this->memory_list);
			this->memory_panel->Location = System::Drawing::Point(411, 84);
			this->memory_panel->Name = L"memory_panel";
			this->memory_panel->Size = System::Drawing::Size(249, 464);
			this->memory_panel->TabIndex = 3;
			// 
			// memory_list
			// 
			this->memory_list->BackgroundColor = System::Drawing::SystemColors::Control;
			this->memory_list->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->memory_list->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->memory_list->Location = System::Drawing::Point(7, 8);
			this->memory_list->Name = L"memory_list";
			this->memory_list->RowHeadersWidth = 51;
			this->memory_list->Size = System::Drawing::Size(238, 449);
			this->memory_list->TabIndex = 0;
			this->memory_list->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::memory_list_CellEndEdit);
			this->memory_list->CellPainting += gcnew System::Windows::Forms::DataGridViewCellPaintingEventHandler(this, &MainForm::memory_list_CellPainting);
			this->memory_list->CellStateChanged += gcnew System::Windows::Forms::DataGridViewCellStateChangedEventHandler(this, &MainForm::memory_list_AddressCellStateChanged);
			this->memory_list->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::memory_list_KeyDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(23, 154);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Registers";
			// 
			// registers_panel
			// 
			this->registers_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->registers_panel->Controls->Add(this->registers_list);
			this->registers_panel->Location = System::Drawing::Point(10, 162);
			this->registers_panel->Name = L"registers_panel";
			this->registers_panel->Size = System::Drawing::Size(393, 387);
			this->registers_panel->TabIndex = 1;
			// 
			// registers_list
			// 
			this->registers_list->HideSelection = false;
			this->registers_list->Location = System::Drawing::Point(7, 8);
			this->registers_list->Name = L"registers_list";
			this->registers_list->Size = System::Drawing::Size(378, 372);
			this->registers_list->TabIndex = 0;
			this->registers_list->UseCompatibleStateImageBehavior = false;
			// 
			// controls_label
			// 
			this->controls_label->AutoSize = true;
			this->controls_label->Location = System::Drawing::Point(23, 4);
			this->controls_label->Name = L"controls_label";
			this->controls_label->Size = System::Drawing::Size(45, 13);
			this->controls_label->TabIndex = 0;
			this->controls_label->Text = L"Controls";
			// 
			// controls_panel
			// 
			this->controls_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->controls_panel->Controls->Add(this->run_until_halt);
			this->controls_panel->Controls->Add(this->steps_label);
			this->controls_panel->Controls->Add(this->step);
			this->controls_panel->Controls->Add(this->steps_spinbox);
			this->controls_panel->Controls->Add(this->export_to_file);
			this->controls_panel->Controls->Add(this->reset_memory);
			this->controls_panel->Controls->Add(this->reset_registers);
			this->controls_panel->Controls->Add(this->play);
			this->controls_panel->Controls->Add(this->load_from_file);
			this->controls_panel->Location = System::Drawing::Point(10, 10);
			this->controls_panel->Name = L"controls_panel";
			this->controls_panel->Size = System::Drawing::Size(936, 59);
			this->controls_panel->TabIndex = 0;
			// 
			// run_until_halt
			// 
			this->run_until_halt->Location = System::Drawing::Point(444, 19);
			this->run_until_halt->Name = L"run_until_halt";
			this->run_until_halt->Size = System::Drawing::Size(99, 23);
			this->run_until_halt->TabIndex = 8;
			this->run_until_halt->Text = L"Run Until Halt";
			this->run_until_halt->UseVisualStyleBackColor = true;
			// 
			// steps_label
			// 
			this->steps_label->AutoSize = true;
			this->steps_label->Location = System::Drawing::Point(653, 23);
			this->steps_label->Name = L"steps_label";
			this->steps_label->Size = System::Drawing::Size(85, 13);
			this->steps_label->TabIndex = 7;
			this->steps_label->Text = L"instructions/step";
			// 
			// step
			// 
			this->step->Location = System::Drawing::Point(836, 17);
			this->step->Name = L"step";
			this->step->Size = System::Drawing::Size(75, 23);
			this->step->TabIndex = 4;
			this->step->Text = L"Step";
			this->step->UseVisualStyleBackColor = true;
			// 
			// steps_spinbox
			// 
			this->steps_spinbox->Location = System::Drawing::Point(549, 20);
			this->steps_spinbox->Name = L"steps_spinbox";
			this->steps_spinbox->Size = System::Drawing::Size(98, 20);
			this->steps_spinbox->TabIndex = 6;
			// 
			// export_to_file
			// 
			this->export_to_file->Location = System::Drawing::Point(124, 19);
			this->export_to_file->Name = L"export_to_file";
			this->export_to_file->Size = System::Drawing::Size(101, 23);
			this->export_to_file->TabIndex = 5;
			this->export_to_file->Text = L"Export To File";
			this->export_to_file->UseVisualStyleBackColor = true;
			this->export_to_file->Click += gcnew System::EventHandler(this, &MainForm::export_to_file_Click);
			// 
			// reset_memory
			// 
			this->reset_memory->Location = System::Drawing::Point(231, 19);
			this->reset_memory->Name = L"reset_memory";
			this->reset_memory->Size = System::Drawing::Size(101, 23);
			this->reset_memory->TabIndex = 3;
			this->reset_memory->Text = L"Reset Memory";
			this->reset_memory->UseVisualStyleBackColor = true;
			this->reset_memory->Click += gcnew System::EventHandler(this, &MainForm::reset_memory_Click);
			// 
			// reset_registers
			// 
			this->reset_registers->Location = System::Drawing::Point(338, 18);
			this->reset_registers->Name = L"reset_registers";
			this->reset_registers->Size = System::Drawing::Size(100, 23);
			this->reset_registers->TabIndex = 2;
			this->reset_registers->Text = L"Reset Registers";
			this->reset_registers->UseVisualStyleBackColor = true;
			this->reset_registers->Click += gcnew System::EventHandler(this, &MainForm::reset_registers_Click);
			// 
			// play
			// 
			this->play->Location = System::Drawing::Point(744, 17);
			this->play->Name = L"play";
			this->play->Size = System::Drawing::Size(78, 23);
			this->play->TabIndex = 1;
			this->play->Text = L"Play";
			this->play->UseVisualStyleBackColor = true;
			// 
			// load_from_file
			// 
			this->load_from_file->Location = System::Drawing::Point(15, 19);
			this->load_from_file->Name = L"load_from_file";
			this->load_from_file->Size = System::Drawing::Size(103, 23);
			this->load_from_file->TabIndex = 0;
			this->load_from_file->Text = L"Load From File";
			this->load_from_file->UseVisualStyleBackColor = true;
			this->load_from_file->Click += gcnew System::EventHandler(this, &MainForm::load_from_file_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(957, 584);
			this->Controls->Add(this->main_panel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->main_panel->ResumeLayout(false);
			this->main_panel->PerformLayout();
			this->screen_panel->ResumeLayout(false);
			this->screen_panel->PerformLayout();
			this->instruction_register_panel->ResumeLayout(false);
			this->instruction_register_panel->PerformLayout();
			this->program_counter_panel->ResumeLayout(false);
			this->program_counter_panel->PerformLayout();
			this->memory_panel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->memory_list))->EndInit();
			this->registers_panel->ResumeLayout(false);
			this->controls_panel->ResumeLayout(false);
			this->controls_panel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->steps_spinbox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		System::Void initializeRegistersList();
		System::Void initializeMemoryList();

		System::Void memory_list_CellEndEdit(Object^ sender, DataGridViewCellEventArgs^ e);
		System::Void memory_list_AddressCellStateChanged(Object^ sender, DataGridViewCellStateChangedEventArgs^ e);
		System::Void memory_list_CellPainting(Object^ sender, DataGridViewCellPaintingEventArgs^ e);
		System::Void memory_list_HandleCellSelection(int edited_cell_col, int edited_cell_row);
		System::Void memory_list_KeyDown(Object^ sender, KeyEventArgs^ e);
		
		System::Void OnMemoryUpdated();
		System::Void memory_list_OnMemoryCellValueChanged(Object^ sender, DataGridViewCellEventArgs^ e);

		System::Void OnFetchInstruction();

		int memory_list_selected_cell_row = 0;
		int memory_list_selected_cell_col = 1;
		Machine* machine;
		MemoryController^ mem_ctrl;
		RegistersController^ reg_ctrl;
		ExecutionController^ exec_ctrl;
		private: System::Void load_from_file_Click(System::Object^ sender, System::EventArgs^ e);


private: System::Void export_to_file_Click(System::Object^ sender, System::EventArgs^ e) {
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
	saveFileDialog->Filter = "Text Files|*.txt|All Files|*.*";
	saveFileDialog->Title = "Export Memory to File";

	if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		std::string filename = Utilities::Conversion::convertSystemStringToStdString(saveFileDialog->FileName);
		memoryController->exportToFile(filename);
	}
	MessageBox::Show("File saved successfully.", "Export Complete", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
		private: System::Void reset_memory_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void reset_registers_Click(System::Object^ sender, System::EventArgs^ e) {}
		private: System::Void fetch_Click(System::Object^ sender, System::EventArgs^ e);
		private: System::Void reset_pc_Click(System::Object^ sender, System::EventArgs^ e);
};
}