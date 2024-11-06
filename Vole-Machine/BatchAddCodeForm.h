#pragma once
#include "ExecutionController.h"
#include "MemoryController.h"

namespace VoleMachine {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class BatchAddCodeForm : public System::Windows::Forms::Form {
	public:
		BatchAddCodeForm(MemoryController^ mem_ctrl, ExecutionController^ exec_ctrl, String^ starting_address) {
			InitializeComponent();
			this->mem_ctrl = mem_ctrl;
			this->exec_ctrl = exec_ctrl;
			this->starting_address = starting_address;
		}

	protected:
		~BatchAddCodeForm() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textbox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ starting_address_textbox;

	private: System::Windows::Forms::Button^ add_code;

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->textbox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->starting_address_textbox = (gcnew System::Windows::Forms::TextBox());
			this->add_code = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textbox
			// 
			this->textbox->Location = System::Drawing::Point(13, 13);
			this->textbox->Multiline = true;
			this->textbox->Name = L"textbox";
			this->textbox->Size = System::Drawing::Size(364, 430);
			this->textbox->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 453);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(154, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Add starting at memory address";
			// 
			// starting_address_textbox
			// 
			this->starting_address_textbox->Location = System::Drawing::Point(173, 449);
			this->starting_address_textbox->Name = L"starting_address_textbox";
			this->starting_address_textbox->Size = System::Drawing::Size(63, 20);
			this->starting_address_textbox->TabIndex = 2;
			this->starting_address_textbox->Text = "00";
			this->starting_address_textbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &BatchAddCodeForm::starting_address_textbox_KeyPress);
			this->starting_address_textbox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &BatchAddCodeForm::starting_address_textbox_KeyDown);
			this->starting_address_textbox->Leave += gcnew System::EventHandler(this, &BatchAddCodeForm::starting_address_textbox_Leave);
			this->starting_address_textbox->Enter += gcnew System::EventHandler(this, &BatchAddCodeForm::starting_address_textbox_Enter);
			// 
			// add_code
			// 
			this->add_code->Location = System::Drawing::Point(244, 448);
			this->add_code->Name = L"add_code";
			this->add_code->Size = System::Drawing::Size(133, 23);
			this->add_code->TabIndex = 3;
			this->add_code->Text = L"Add Code";
			this->add_code->UseVisualStyleBackColor = true;
			this->add_code->Click += gcnew System::EventHandler(this, &BatchAddCodeForm::add_code_Click);
			// 
			// BatchAddCodeForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(389, 478);
			this->Controls->Add(this->add_code);
			this->Controls->Add(this->starting_address_textbox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textbox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"BatchAddCodeForm";
			this->Text = L"Batch Add Code";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void starting_address_textbox_KeyPress(Object^ sender, KeyPressEventArgs^ e);
		System::Void starting_address_textbox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		System::Void starting_address_textbox_Leave(System::Object^ sender, System::EventArgs^ e);
		System::Void starting_address_textbox_Enter(System::Object^ sender, System::EventArgs^ e);
		System::Void updateStartingAddress();
		System::Void starting_address_textbox_SelectStartingAddressText();
		System::Void add_code_Click(System::Object^ sender, System::EventArgs^ e);

		ExecutionController^ exec_ctrl;
		MemoryController^ mem_ctrl;
		String^ starting_address;
	};
}
