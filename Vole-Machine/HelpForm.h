#pragma once

namespace VoleMachine {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class HelpForm : public System::Windows::Forms::Form {
	public:
		HelpForm(void) {
			InitializeComponent();
		}

	protected:

		~HelpForm() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ loi_panel;
	protected:


	private: System::Windows::Forms::Label^ loi_label;
	private: System::Windows::Forms::Label^ load_m_label;
	private: System::Windows::Forms::Label^ load_v_label;
	private: System::Windows::Forms::Label^ xor_label;
	private: System::Windows::Forms::Label^ and_label;
	private: System::Windows::Forms::Label^ or_label;
	private: System::Windows::Forms::Label^ add_f_label;
	private: System::Windows::Forms::Label^ add_label;
	private: System::Windows::Forms::Label^ move_label;
	private: System::Windows::Forms::Label^ store_label;
	private: System::Windows::Forms::Label^ jump_eq_label;
	private: System::Windows::Forms::Label^ rotate_label;
	private: System::Windows::Forms::Label^ jump_gt_label;
	private: System::Windows::Forms::Label^ halt_label;
	private: System::Windows::Forms::TextBox^ load_m_textbox;
	private: System::Windows::Forms::TextBox^ and_textbox;
	private: System::Windows::Forms::TextBox^ or_textbox;
	private: System::Windows::Forms::TextBox^ add_f_textbox;
	private: System::Windows::Forms::TextBox^ add_textbox;
	private: System::Windows::Forms::TextBox^ move_textbox;
	private: System::Windows::Forms::TextBox^ store_textbox;
	private: System::Windows::Forms::TextBox^ load_v_textbox;
	private: System::Windows::Forms::TextBox^ halt_textbox;
	private: System::Windows::Forms::TextBox^ jump_eq_textbox;
	private: System::Windows::Forms::TextBox^ rotate_textbox;
	private: System::Windows::Forms::TextBox^ xor_textbox;
	private: System::Windows::Forms::TextBox^ jump_gt_textbox;
	private: System::Windows::Forms::Panel^ fff_panel;

	private: System::Windows::Forms::Label^ fff_label;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::LinkLabel^ github_link;
	private:System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(HelpForm::typeid));
			this->loi_panel = (gcnew System::Windows::Forms::Panel());
			this->jump_gt_textbox = (gcnew System::Windows::Forms::TextBox());
			this->halt_textbox = (gcnew System::Windows::Forms::TextBox());
			this->jump_eq_textbox = (gcnew System::Windows::Forms::TextBox());
			this->rotate_textbox = (gcnew System::Windows::Forms::TextBox());
			this->xor_textbox = (gcnew System::Windows::Forms::TextBox());
			this->and_textbox = (gcnew System::Windows::Forms::TextBox());
			this->or_textbox = (gcnew System::Windows::Forms::TextBox());
			this->add_f_textbox = (gcnew System::Windows::Forms::TextBox());
			this->add_textbox = (gcnew System::Windows::Forms::TextBox());
			this->move_textbox = (gcnew System::Windows::Forms::TextBox());
			this->store_textbox = (gcnew System::Windows::Forms::TextBox());
			this->load_v_textbox = (gcnew System::Windows::Forms::TextBox());
			this->load_m_textbox = (gcnew System::Windows::Forms::TextBox());
			this->jump_gt_label = (gcnew System::Windows::Forms::Label());
			this->halt_label = (gcnew System::Windows::Forms::Label());
			this->jump_eq_label = (gcnew System::Windows::Forms::Label());
			this->rotate_label = (gcnew System::Windows::Forms::Label());
			this->xor_label = (gcnew System::Windows::Forms::Label());
			this->and_label = (gcnew System::Windows::Forms::Label());
			this->or_label = (gcnew System::Windows::Forms::Label());
			this->add_f_label = (gcnew System::Windows::Forms::Label());
			this->add_label = (gcnew System::Windows::Forms::Label());
			this->move_label = (gcnew System::Windows::Forms::Label());
			this->store_label = (gcnew System::Windows::Forms::Label());
			this->load_v_label = (gcnew System::Windows::Forms::Label());
			this->load_m_label = (gcnew System::Windows::Forms::Label());
			this->loi_label = (gcnew System::Windows::Forms::Label());
			this->fff_panel = (gcnew System::Windows::Forms::Panel());
			this->github_link = (gcnew System::Windows::Forms::LinkLabel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->fff_label = (gcnew System::Windows::Forms::Label());
			this->loi_panel->SuspendLayout();
			this->fff_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// loi_panel
			// 
			this->loi_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->loi_panel->Controls->Add(this->jump_gt_textbox);
			this->loi_panel->Controls->Add(this->halt_textbox);
			this->loi_panel->Controls->Add(this->jump_eq_textbox);
			this->loi_panel->Controls->Add(this->rotate_textbox);
			this->loi_panel->Controls->Add(this->xor_textbox);
			this->loi_panel->Controls->Add(this->and_textbox);
			this->loi_panel->Controls->Add(this->or_textbox);
			this->loi_panel->Controls->Add(this->add_f_textbox);
			this->loi_panel->Controls->Add(this->add_textbox);
			this->loi_panel->Controls->Add(this->move_textbox);
			this->loi_panel->Controls->Add(this->store_textbox);
			this->loi_panel->Controls->Add(this->load_v_textbox);
			this->loi_panel->Controls->Add(this->load_m_textbox);
			this->loi_panel->Controls->Add(this->jump_gt_label);
			this->loi_panel->Controls->Add(this->halt_label);
			this->loi_panel->Controls->Add(this->jump_eq_label);
			this->loi_panel->Controls->Add(this->rotate_label);
			this->loi_panel->Controls->Add(this->xor_label);
			this->loi_panel->Controls->Add(this->and_label);
			this->loi_panel->Controls->Add(this->or_label);
			this->loi_panel->Controls->Add(this->add_f_label);
			this->loi_panel->Controls->Add(this->add_label);
			this->loi_panel->Controls->Add(this->move_label);
			this->loi_panel->Controls->Add(this->store_label);
			this->loi_panel->Controls->Add(this->load_v_label);
			this->loi_panel->Controls->Add(this->load_m_label);
			this->loi_panel->Location = System::Drawing::Point(13, 13);
			this->loi_panel->Name = L"loi_panel";
			this->loi_panel->Size = System::Drawing::Size(595, 462);
			this->loi_panel->TabIndex = 0;
			// 
			// jump_gt_textbox
			// 
			this->jump_gt_textbox->Location = System::Drawing::Point(71, 415);
			this->jump_gt_textbox->Name = L"jump_gt_textbox";
			this->jump_gt_textbox->ReadOnly = true;
			this->jump_gt_textbox->Size = System::Drawing::Size(506, 20);
			this->jump_gt_textbox->TabIndex = 26;
			this->jump_gt_textbox->Text = L"Jump to instruction in memory cell \"XY\" if the content of register \"R\" is greater"
				L" than (>) that of register \"0\"";
			// 
			// halt_textbox
			// 
			this->halt_textbox->Location = System::Drawing::Point(71, 382);
			this->halt_textbox->Name = L"halt_textbox";
			this->halt_textbox->ReadOnly = true;
			this->halt_textbox->Size = System::Drawing::Size(506, 20);
			this->halt_textbox->TabIndex = 25;
			this->halt_textbox->Text = L"Halt execution";
			// 
			// jump_eq_textbox
			// 
			this->jump_eq_textbox->Location = System::Drawing::Point(71, 349);
			this->jump_eq_textbox->Name = L"jump_eq_textbox";
			this->jump_eq_textbox->ReadOnly = true;
			this->jump_eq_textbox->Size = System::Drawing::Size(506, 20);
			this->jump_eq_textbox->TabIndex = 24;
			this->jump_eq_textbox->Text = L"Jump to instruction in memory cell \"XY\" if the contents of registers \"R\" and \"0\" "
				L"are equal";
			// 
			// rotate_textbox
			// 
			this->rotate_textbox->Location = System::Drawing::Point(71, 316);
			this->rotate_textbox->Name = L"rotate_textbox";
			this->rotate_textbox->ReadOnly = true;
			this->rotate_textbox->Size = System::Drawing::Size(506, 20);
			this->rotate_textbox->TabIndex = 23;
			this->rotate_textbox->Text = L"Rotate the content of register \"R\" cyclically right \"X\" steps";
			// 
			// xor_textbox
			// 
			this->xor_textbox->Location = System::Drawing::Point(71, 283);
			this->xor_textbox->Name = L"xor_textbox";
			this->xor_textbox->ReadOnly = true;
			this->xor_textbox->Size = System::Drawing::Size(506, 20);
			this->xor_textbox->TabIndex = 22;
			this->xor_textbox->Text = L"Bitwise XOR  the contents of registers \"S\" and \"T\" and store them in register \"R\""
				L"";
			// 
			// and_textbox
			// 
			this->and_textbox->Location = System::Drawing::Point(71, 250);
			this->and_textbox->Name = L"and_textbox";
			this->and_textbox->ReadOnly = true;
			this->and_textbox->Size = System::Drawing::Size(506, 20);
			this->and_textbox->TabIndex = 21;
			this->and_textbox->Text = L"Bitwise AND the contents of registers \"S\" and \"T\" and store them in register \"R\"";
			// 
			// or_textbox
			// 
			this->or_textbox->Location = System::Drawing::Point(71, 217);
			this->or_textbox->Name = L"or_textbox";
			this->or_textbox->ReadOnly = true;
			this->or_textbox->Size = System::Drawing::Size(506, 20);
			this->or_textbox->TabIndex = 20;
			this->or_textbox->Text = L"Bitwise OR the contents of registers \"S\" and \"T\" and store them in register \"R\"";
			// 
			// add_f_textbox
			// 
			this->add_f_textbox->Location = System::Drawing::Point(71, 184);
			this->add_f_textbox->Name = L"add_f_textbox";
			this->add_f_textbox->ReadOnly = true;
			this->add_f_textbox->Size = System::Drawing::Size(506, 20);
			this->add_f_textbox->TabIndex = 19;
			this->add_f_textbox->Text = L"Add contents of registers \"S\" and \"T\" and store them in floating point notation i"
				L"nto register \"R\"";
			// 
			// add_textbox
			// 
			this->add_textbox->Location = System::Drawing::Point(71, 151);
			this->add_textbox->Name = L"add_textbox";
			this->add_textbox->ReadOnly = true;
			this->add_textbox->Size = System::Drawing::Size(506, 20);
			this->add_textbox->TabIndex = 18;
			this->add_textbox->Text = L"Add contents of registers \"S\" and \"T\" and store them in two\'s complement notation"
				L" into register \"R\"";
			// 
			// move_textbox
			// 
			this->move_textbox->Location = System::Drawing::Point(71, 118);
			this->move_textbox->Name = L"move_textbox";
			this->move_textbox->ReadOnly = true;
			this->move_textbox->Size = System::Drawing::Size(506, 20);
			this->move_textbox->TabIndex = 17;
			this->move_textbox->Text = L"Copy content of register \"R\" into register \"S\"";
			// 
			// store_textbox
			// 
			this->store_textbox->Location = System::Drawing::Point(71, 85);
			this->store_textbox->Name = L"store_textbox";
			this->store_textbox->ReadOnly = true;
			this->store_textbox->Size = System::Drawing::Size(506, 20);
			this->store_textbox->TabIndex = 16;
			this->store_textbox->Text = L"Copy content of register \"R\" into memory cell \"XY\", or 3R00 for writing to screen"
				L"";
			// 
			// load_v_textbox
			// 
			this->load_v_textbox->Location = System::Drawing::Point(71, 52);
			this->load_v_textbox->Name = L"load_v_textbox";
			this->load_v_textbox->ReadOnly = true;
			this->load_v_textbox->Size = System::Drawing::Size(506, 20);
			this->load_v_textbox->TabIndex = 15;
			this->load_v_textbox->Text = L"Load \"XY\" into register \"R\"";
			// 
			// load_m_textbox
			// 
			this->load_m_textbox->Location = System::Drawing::Point(71, 19);
			this->load_m_textbox->Name = L"load_m_textbox";
			this->load_m_textbox->ReadOnly = true;
			this->load_m_textbox->Size = System::Drawing::Size(506, 20);
			this->load_m_textbox->TabIndex = 14;
			this->load_m_textbox->Text = L"Load content of memory cell \"XY\" into register \"R\"";
			// 
			// jump_gt_label
			// 
			this->jump_gt_label->AutoSize = true;
			this->jump_gt_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->jump_gt_label->Location = System::Drawing::Point(13, 419);
			this->jump_gt_label->Name = L"jump_gt_label";
			this->jump_gt_label->Size = System::Drawing::Size(41, 13);
			this->jump_gt_label->TabIndex = 12;
			this->jump_gt_label->Text = L"DRXY";
			// 
			// halt_label
			// 
			this->halt_label->AutoSize = true;
			this->halt_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->halt_label->Location = System::Drawing::Point(13, 386);
			this->halt_label->Name = L"halt_label";
			this->halt_label->Size = System::Drawing::Size(33, 13);
			this->halt_label->TabIndex = 11;
			this->halt_label->Text = L"Cxxx";
			// 
			// jump_eq_label
			// 
			this->jump_eq_label->AutoSize = true;
			this->jump_eq_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->jump_eq_label->Location = System::Drawing::Point(13, 353);
			this->jump_eq_label->Name = L"jump_eq_label";
			this->jump_eq_label->Size = System::Drawing::Size(40, 13);
			this->jump_eq_label->TabIndex = 10;
			this->jump_eq_label->Text = L"BRXY";
			// 
			// rotate_label
			// 
			this->rotate_label->AutoSize = true;
			this->rotate_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rotate_label->Location = System::Drawing::Point(13, 320);
			this->rotate_label->Name = L"rotate_label";
			this->rotate_label->Size = System::Drawing::Size(38, 13);
			this->rotate_label->TabIndex = 9;
			this->rotate_label->Text = L"ARxX";
			// 
			// xor_label
			// 
			this->xor_label->AutoSize = true;
			this->xor_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->xor_label->Location = System::Drawing::Point(13, 287);
			this->xor_label->Name = L"xor_label";
			this->xor_label->Size = System::Drawing::Size(39, 13);
			this->xor_label->TabIndex = 8;
			this->xor_label->Text = L"9RST";
			// 
			// and_label
			// 
			this->and_label->AutoSize = true;
			this->and_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->and_label->Location = System::Drawing::Point(13, 254);
			this->and_label->Name = L"and_label";
			this->and_label->Size = System::Drawing::Size(39, 13);
			this->and_label->TabIndex = 7;
			this->and_label->Text = L"8RST";
			// 
			// or_label
			// 
			this->or_label->AutoSize = true;
			this->or_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->or_label->Location = System::Drawing::Point(13, 221);
			this->or_label->Name = L"or_label";
			this->or_label->Size = System::Drawing::Size(39, 13);
			this->or_label->TabIndex = 6;
			this->or_label->Text = L"7RST";
			// 
			// add_f_label
			// 
			this->add_f_label->AutoSize = true;
			this->add_f_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->add_f_label->Location = System::Drawing::Point(13, 188);
			this->add_f_label->Name = L"add_f_label";
			this->add_f_label->Size = System::Drawing::Size(39, 13);
			this->add_f_label->TabIndex = 5;
			this->add_f_label->Text = L"6RST";
			// 
			// add_label
			// 
			this->add_label->AutoSize = true;
			this->add_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->add_label->Location = System::Drawing::Point(13, 155);
			this->add_label->Name = L"add_label";
			this->add_label->Size = System::Drawing::Size(39, 13);
			this->add_label->TabIndex = 4;
			this->add_label->Text = L"5RST";
			// 
			// move_label
			// 
			this->move_label->AutoSize = true;
			this->move_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->move_label->Location = System::Drawing::Point(13, 122);
			this->move_label->Name = L"move_label";
			this->move_label->Size = System::Drawing::Size(37, 13);
			this->move_label->TabIndex = 3;
			this->move_label->Text = L"4xRS";
			// 
			// store_label
			// 
			this->store_label->AutoSize = true;
			this->store_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->store_label->Location = System::Drawing::Point(13, 89);
			this->store_label->Name = L"store_label";
			this->store_label->Size = System::Drawing::Size(39, 13);
			this->store_label->TabIndex = 2;
			this->store_label->Text = L"3RXY";
			// 
			// load_v_label
			// 
			this->load_v_label->AutoSize = true;
			this->load_v_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->load_v_label->Location = System::Drawing::Point(13, 56);
			this->load_v_label->Name = L"load_v_label";
			this->load_v_label->Size = System::Drawing::Size(39, 13);
			this->load_v_label->TabIndex = 1;
			this->load_v_label->Text = L"2RXY";
			// 
			// load_m_label
			// 
			this->load_m_label->AutoSize = true;
			this->load_m_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->load_m_label->Location = System::Drawing::Point(13, 23);
			this->load_m_label->Name = L"load_m_label";
			this->load_m_label->Size = System::Drawing::Size(39, 13);
			this->load_m_label->TabIndex = 0;
			this->load_m_label->Text = L"1RXY";
			// 
			// loi_label
			// 
			this->loi_label->AutoSize = true;
			this->loi_label->Location = System::Drawing::Point(23, 6);
			this->loi_label->Name = L"loi_label";
			this->loi_label->Size = System::Drawing::Size(92, 13);
			this->loi_label->TabIndex = 2;
			this->loi_label->Text = L"List of Instructions";
			// 
			// fff_panel
			// 
			this->fff_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->fff_panel->Controls->Add(this->github_link);
			this->fff_panel->Controls->Add(this->label2);
			this->fff_panel->Controls->Add(this->label1);
			this->fff_panel->Location = System::Drawing::Point(13, 491);
			this->fff_panel->Name = L"fff_panel";
			this->fff_panel->Size = System::Drawing::Size(595, 75);
			this->fff_panel->TabIndex = 3;
			// 
			// github_link
			// 
			this->github_link->AutoSize = true;
			this->github_link->Location = System::Drawing::Point(81, 43);
			this->github_link->Name = L"github_link";
			this->github_link->Size = System::Drawing::Size(111, 13);
			this->github_link->TabIndex = 2;
			this->github_link->TabStop = true;
			this->github_link->Text = L"the GitHub Repository";
			this->github_link->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &HelpForm::github_link_LinkClicked);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 43);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(68, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"You can visit";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(475, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"You can hover your cursor on some UI components to learn about their functionalit"
				L"y through tooltips";
			// 
			// fff_label
			// 
			this->fff_label->AutoSize = true;
			this->fff_label->Location = System::Drawing::Point(23, 483);
			this->fff_label->Name = L"fff_label";
			this->fff_label->Size = System::Drawing::Size(113, 13);
			this->fff_label->TabIndex = 4;
			this->fff_label->Text = L"For Further Information";
			// 
			// HelpForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(620, 578);
			this->Controls->Add(this->fff_label);
			this->Controls->Add(this->fff_panel);
			this->Controls->Add(this->loi_label);
			this->Controls->Add(this->loi_panel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"HelpForm";
			this->Text = L"Help";
			this->Activated += gcnew System::EventHandler(this, &HelpForm::HelpForm_Activated);
			this->loi_panel->ResumeLayout(false);
			this->loi_panel->PerformLayout();
			this->fff_panel->ResumeLayout(false);
			this->fff_panel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:
			System::Void github_link_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
			System::Void HelpForm_Activated(System::Object^ sender, System::EventArgs^ e);

};
}
