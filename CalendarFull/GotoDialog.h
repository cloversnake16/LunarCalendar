#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CalendarFull {

	/// <summary>
	/// Summary for GotoDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class GotoDialog : public System::Windows::Forms::Form
	{
	public:
		GotoDialog(void)
		{
			InitializeComponent();
			this->configureComboBoxYearAndMonth();
			
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GotoDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::ComboBox^  yearCmb;
	public: System::Windows::Forms::ComboBox^  monthCmb;
	public: System::Windows::Forms::ComboBox^  dayCmb;
	
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  okBtn;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		void configureComboBoxYearAndMonth(){
			DateTime^ dt=(DateTime^)DateTime::Now;
			int yy, mm, dd;
			yy=dt->Year;
			mm=dt->Month;
			dd=dt->Day;
			for(int i=yy-5;i<=yy+5;++i)this->yearCmb->Items->Add(i);			
			this->yearCmb->SelectedIndex=5;
			for(int i=1;i<=12;++i)this->monthCmb->Items->Add(i);
			this->monthCmb->SelectedIndex=mm-1;			
			this->configureDayComboBox(DateTime::DaysInMonth(yy,mm),dd);			
		}

		void configureDayComboBox(int dds, int dd){
			for(int i=1;i<=dds;++i)this->dayCmb->Items->Add(i);
			this->dayCmb->SelectedIndex=dd;
		}

		void dateChanged(){
			if(this->yearCmb->Text->Length>0 && this->monthCmb->Text->Length>0){
				this->dayCmb->Items->Clear();
				this->dayCmb->Refresh();
				int dn=DateTime::DaysInMonth(Convert::ToInt32(this->yearCmb->Text), Convert::ToInt32(this->monthCmb->Text));
				this->configureDayComboBox(dn,0);
			}
			
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->yearCmb = (gcnew System::Windows::Forms::ComboBox());
			this->monthCmb = (gcnew System::Windows::Forms::ComboBox());
			this->dayCmb = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->okBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// yearCmb
			// 
			this->yearCmb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->yearCmb->FormattingEnabled = true;
			this->yearCmb->Location = System::Drawing::Point(12, 12);
			this->yearCmb->Name = L"yearCmb";
			this->yearCmb->Size = System::Drawing::Size(77, 21);
			this->yearCmb->TabIndex = 0;
			this->yearCmb->SelectedIndexChanged += gcnew System::EventHandler(this, &GotoDialog::yearCmb_SelectedIndexChanged);
			// 
			// monthCmb
			// 
			this->monthCmb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->monthCmb->FormattingEnabled = true;
			this->monthCmb->Location = System::Drawing::Point(113, 12);
			this->monthCmb->Name = L"monthCmb";
			this->monthCmb->Size = System::Drawing::Size(42, 21);
			this->monthCmb->TabIndex = 0;
			this->monthCmb->SelectedIndexChanged += gcnew System::EventHandler(this, &GotoDialog::monthCmb_SelectedIndexChanged);
			// 
			// dayCmb
			// 
			this->dayCmb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->dayCmb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->dayCmb->FormattingEnabled = true;
			this->dayCmb->Location = System::Drawing::Point(179, 12);
			this->dayCmb->Name = L"dayCmb";
			this->dayCmb->Size = System::Drawing::Size(36, 21);
			this->dayCmb->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(91, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(19, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"年";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(157, 16);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(19, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"月";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(217, 16);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(19, 13);
			this->label3->TabIndex = 1;
			this->label3->Text = L"日";
			// 
			// okBtn
			// 
			this->okBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->okBtn->Location = System::Drawing::Point(105, 46);
			this->okBtn->Name = L"okBtn";
			this->okBtn->Size = System::Drawing::Size(50, 23);
			this->okBtn->TabIndex = 2;
			this->okBtn->Text = L"确认";
			this->okBtn->UseVisualStyleBackColor = true;
			// 
			// GotoDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(254, 81);
			this->Controls->Add(this->okBtn);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dayCmb);
			this->Controls->Add(this->monthCmb);
			this->Controls->Add(this->yearCmb);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"GotoDialog";
			this->Text = L" 选择日子";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void yearCmb_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->dateChanged();
		 }
private: System::Void monthCmb_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->dateChanged();
		 }
};
}
