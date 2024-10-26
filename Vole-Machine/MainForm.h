#pragma once

namespace VoleMachine {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			this->initializeRegistersList();
			this->initializeMemoryList();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ main_panel;
	private: System::Windows::Forms::Panel^ controls_panel;
	private: System::Windows::Forms::Label^ controls_label;
	private: System::Windows::Forms::Button^ export_to_file;
	private: System::Windows::Forms::Button^ step;


	private: System::Windows::Forms::Button^ reset_memory;
	private: System::Windows::Forms::Button^ reset_registers;
	private: System::Windows::Forms::Button^ run_instructions;




	private: System::Windows::Forms::Button^ load_from_file;
	private: System::Windows::Forms::NumericUpDown^ steps_spinbox;


	private: System::Windows::Forms::Label^ steps_label;

	private: System::Windows::Forms::Button^ run_until_halt;
	private: System::Windows::Forms::Panel^ registers_panel;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ListView^ registers_list;
	private: System::Windows::Forms::Label^ memory_label;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::DataGridView^ memory_list;





	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->main_panel = (gcnew System::Windows::Forms::Panel());
			this->memory_label = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->memory_list = (gcnew System::Windows::Forms::DataGridView());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->registers_panel = (gcnew System::Windows::Forms::Panel());
			this->registers_list = (gcnew System::Windows::Forms::ListView());
			this->controls_label = (gcnew System::Windows::Forms::Label());
			this->controls_panel = (gcnew System::Windows::Forms::Panel());
			this->run_until_halt = (gcnew System::Windows::Forms::Button());
			this->steps_label = (gcnew System::Windows::Forms::Label());
			this->steps_spinbox = (gcnew System::Windows::Forms::NumericUpDown());
			this->export_to_file = (gcnew System::Windows::Forms::Button());
			this->step = (gcnew System::Windows::Forms::Button());
			this->reset_memory = (gcnew System::Windows::Forms::Button());
			this->reset_registers = (gcnew System::Windows::Forms::Button());
			this->run_instructions = (gcnew System::Windows::Forms::Button());
			this->load_from_file = (gcnew System::Windows::Forms::Button());
			this->main_panel->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->memory_list))->BeginInit();
			this->registers_panel->SuspendLayout();
			this->controls_panel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->steps_spinbox))->BeginInit();
			this->SuspendLayout();
			// 
			// main_panel
			// 
			this->main_panel->Controls->Add(this->memory_label);
			this->main_panel->Controls->Add(this->panel1);
			this->main_panel->Controls->Add(this->label1);
			this->main_panel->Controls->Add(this->registers_panel);
			this->main_panel->Controls->Add(this->controls_label);
			this->main_panel->Controls->Add(this->controls_panel);
			this->main_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->main_panel->Location = System::Drawing::Point(0, 0);
			this->main_panel->Name = L"main_panel";
			this->main_panel->Padding = System::Windows::Forms::Padding(10);
			this->main_panel->Size = System::Drawing::Size(984, 561);
			this->main_panel->TabIndex = 0;
			this->main_panel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::panel1_Paint);
			// 
			// memory_label
			// 
			this->memory_label->AutoSize = true;
			this->memory_label->Location = System::Drawing::Point(232, 77);
			this->memory_label->Name = L"memory_label";
			this->memory_label->Size = System::Drawing::Size(44, 13);
			this->memory_label->TabIndex = 4;
			this->memory_label->Text = L"Memory";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->memory_list);
			this->panel1->Location = System::Drawing::Point(217, 84);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(240, 464);
			this->panel1->TabIndex = 3;
			// 
			// memory_list
			// 
			this->memory_list->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->memory_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->memory_list->Location = System::Drawing::Point(0, 0);
			this->memory_list->Name = L"memory_list";
			this->memory_list->Size = System::Drawing::Size(240, 464);
			this->memory_list->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(23, 77);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Registers";
			// 
			// registers_panel
			// 
			this->registers_panel->Controls->Add(this->registers_list);
			this->registers_panel->Location = System::Drawing::Point(10, 84);
			this->registers_panel->Name = L"registers_panel";
			this->registers_panel->Size = System::Drawing::Size(200, 465);
			this->registers_panel->TabIndex = 1;
			// 
			// registers_list
			// 
			this->registers_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->registers_list->HideSelection = false;
			this->registers_list->Location = System::Drawing::Point(0, 0);
			this->registers_list->Name = L"registers_list";
			this->registers_list->Size = System::Drawing::Size(200, 465);
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
			this->controls_panel->Controls->Add(this->steps_spinbox);
			this->controls_panel->Controls->Add(this->export_to_file);
			this->controls_panel->Controls->Add(this->step);
			this->controls_panel->Controls->Add(this->reset_memory);
			this->controls_panel->Controls->Add(this->reset_registers);
			this->controls_panel->Controls->Add(this->run_instructions);
			this->controls_panel->Controls->Add(this->load_from_file);
			this->controls_panel->Dock = System::Windows::Forms::DockStyle::Top;
			this->controls_panel->Location = System::Drawing::Point(10, 10);
			this->controls_panel->Name = L"controls_panel";
			this->controls_panel->Size = System::Drawing::Size(964, 59);
			this->controls_panel->TabIndex = 0;
			// 
			// run_until_halt
			// 
			this->run_until_halt->Location = System::Drawing::Point(444, 21);
			this->run_until_halt->Name = L"run_until_halt";
			this->run_until_halt->Size = System::Drawing::Size(99, 23);
			this->run_until_halt->TabIndex = 8;
			this->run_until_halt->Text = L"Run Until Halt";
			this->run_until_halt->UseVisualStyleBackColor = true;
			// 
			// steps_label
			// 
			this->steps_label->AutoSize = true;
			this->steps_label->Location = System::Drawing::Point(653, 25);
			this->steps_label->Name = L"steps_label";
			this->steps_label->Size = System::Drawing::Size(85, 13);
			this->steps_label->TabIndex = 7;
			this->steps_label->Text = L"instructions/step";
			// 
			// steps_spinbox
			// 
			this->steps_spinbox->Location = System::Drawing::Point(549, 22);
			this->steps_spinbox->Name = L"steps_spinbox";
			this->steps_spinbox->Size = System::Drawing::Size(98, 20);
			this->steps_spinbox->TabIndex = 6;
			// 
			// export_to_file
			// 
			this->export_to_file->Location = System::Drawing::Point(124, 21);
			this->export_to_file->Name = L"export_to_file";
			this->export_to_file->Size = System::Drawing::Size(101, 23);
			this->export_to_file->TabIndex = 5;
			this->export_to_file->Text = L"Export To File";
			this->export_to_file->UseVisualStyleBackColor = true;
			// 
			// step
			// 
			this->step->Location = System::Drawing::Point(846, 19);
			this->step->Name = L"step";
			this->step->Size = System::Drawing::Size(75, 23);
			this->step->TabIndex = 4;
			this->step->Text = L"Step";
			this->step->UseVisualStyleBackColor = true;
			// 
			// reset_memory
			// 
			this->reset_memory->Location = System::Drawing::Point(231, 21);
			this->reset_memory->Name = L"reset_memory";
			this->reset_memory->Size = System::Drawing::Size(101, 23);
			this->reset_memory->TabIndex = 3;
			this->reset_memory->Text = L"Reset Memory";
			this->reset_memory->UseVisualStyleBackColor = true;
			// 
			// reset_registers
			// 
			this->reset_registers->Location = System::Drawing::Point(338, 20);
			this->reset_registers->Name = L"reset_registers";
			this->reset_registers->Size = System::Drawing::Size(100, 23);
			this->reset_registers->TabIndex = 2;
			this->reset_registers->Text = L"Reset Registers";
			this->reset_registers->UseVisualStyleBackColor = true;
			// 
			// run_instructions
			// 
			this->run_instructions->Location = System::Drawing::Point(744, 19);
			this->run_instructions->Name = L"run_instructions";
			this->run_instructions->Size = System::Drawing::Size(96, 23);
			this->run_instructions->TabIndex = 1;
			this->run_instructions->Text = L"Run Instructions";
			this->run_instructions->UseVisualStyleBackColor = true;
			// 
			// load_from_file
			// 
			this->load_from_file->Location = System::Drawing::Point(15, 21);
			this->load_from_file->Name = L"load_from_file";
			this->load_from_file->Size = System::Drawing::Size(103, 23);
			this->load_from_file->TabIndex = 0;
			this->load_from_file->Text = L"Load From File";
			this->load_from_file->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(984, 561);
			this->Controls->Add(this->main_panel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->main_panel->ResumeLayout(false);
			this->main_panel->PerformLayout();
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->memory_list))->EndInit();
			this->registers_panel->ResumeLayout(false);
			this->controls_panel->ResumeLayout(false);
			this->controls_panel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->steps_spinbox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void initializeRegistersList();
		private: System::Void initializeMemoryList();

	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {}
	};
}
