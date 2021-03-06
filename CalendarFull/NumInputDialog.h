#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CalendarFull {

	/// <summary>
	/// Summary for NumInputDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class NumInputDialog : public System::Windows::Forms::Form
	{
	public:
		NumInputDialog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		bool isInteger(String^ numStr){
			array<Char>^ charArray=numStr->ToCharArray();
			for(int i=0;i<numStr->Length;++i){
				char ch=(char) charArray[i];
				if(ch>=(char)48 && ch<=(char)57){
					continue;
				}else{
					return false;
				}
			}
			return true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NumInputDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  numLbl;
	public: System::Windows::Forms::TextBox^  numTxt;
	protected: 

	private: System::Windows::Forms::Button^  okBtn;

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
			this->numLbl = (gcnew System::Windows::Forms::Label());
			this->numTxt = (gcnew System::Windows::Forms::TextBox());
			this->okBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// numLbl
			// 
			this->numLbl->AutoSize = true;
			this->numLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->numLbl->Location = System::Drawing::Point(27, 21);
			this->numLbl->Name = L"numLbl";
			this->numLbl->Size = System::Drawing::Size(41, 20);
			this->numLbl->TabIndex = 0;
			this->numLbl->Text = L"数字";
			// 
			// numTxt
			// 
			this->numTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->numTxt->Location = System::Drawing::Point(93, 18);
			this->numTxt->Name = L"numTxt";
			this->numTxt->Size = System::Drawing::Size(156, 26);
			this->numTxt->TabIndex = 1;
			this->numTxt->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &NumInputDialog::numTxt_KeyPress);
			// 
			// okBtn
			// 
			this->okBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->okBtn->Location = System::Drawing::Point(102, 62);
			this->okBtn->Name = L"okBtn";
			this->okBtn->Size = System::Drawing::Size(75, 32);
			this->okBtn->TabIndex = 2;
			this->okBtn->Text = L"确认";
			this->okBtn->UseVisualStyleBackColor = true;
			this->okBtn->Click += gcnew System::EventHandler(this, &NumInputDialog::okBtn_Click);
			// 
			// NumInputDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(278, 106);
			this->Controls->Add(this->okBtn);
			this->Controls->Add(this->numTxt);
			this->Controls->Add(this->numLbl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"NumInputDialog";
			this->Text = L"输入数字";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void numTxt_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {				 
				 if(e->KeyChar==(char)13){
					 if(this->numTxt->Text->Length<=0){
						MessageBox::Show(L"请输入整数。");
						return;
					 }
					 if(!this->isInteger(this->numTxt->Text)){
						 MessageBox::Show(L"请输入整数。");
						 this->numTxt->Text="";
						 return;
					 }
					 this->DialogResult=System::Windows::Forms::DialogResult::OK;
					 this->Close();
				 }
			 }

private: System::Void okBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->numTxt->Text->Length<=0){
				MessageBox::Show(L"请输入整数。");
				this->numTxt->Text="";
				return;
			 }
			 if(!this->isInteger(this->numTxt->Text)){
			    MessageBox::Show(L"请输入整数。");
				this->numTxt->Text="";
				return;
			 }
			 this->DialogResult=System::Windows::Forms::DialogResult::OK;
			 this->Close();
		 }
};
}
