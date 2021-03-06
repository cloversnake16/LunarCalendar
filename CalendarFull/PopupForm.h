#pragma once

#include "global.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;


namespace CalendarFull {

	/// <summary>
	/// Summary for PopupForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class PopupForm : public System::Windows::Forms::Form
	{
	public:
		PopupForm(void)
		{			
			//
			//TODO: Add the constructor code here
			//
		}

		PopupForm(int newX, int newY){
			InitializeComponent();	
			this->Location=System::Drawing::Point(newX, newY);
			this->cmbArray=gcnew ArrayList;
			this->configureEventDate();			
			this->evtDates=gcnew array<String^>(10);
			this->moveFlag=0;
		}

		bool isInteger(String^ numStr){
			array<Char>^ charArray=numStr->ToCharArray();
			for(int i=0;i<numStr->Length;++i){
				char ch=(char)charArray[i];
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
		~PopupForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  closeLbl;
	private: System::Windows::Forms::TextBox^  qTxt;
	private: System::Windows::Forms::Button^  okBtn;
	private: System::Windows::Forms::PictureBox^  closePic;
	private: System::Windows::Forms::PictureBox^  normalPic;
	private: System::Windows::Forms::Timer^  timer1;	

	private: System::ComponentModel::IContainer^  components;
	
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		int moveFlag, countTime,cx,cy,px,py,upX,upY,formX,formY;
		ArrayList^ cmbArray;
		array<String^>^ evtDates;

		void configureEventDate(){
			for(int i=0;i<10;++i){
				// year combo
				ComboBox^ tmpCmb=gcnew ComboBox();
				tmpCmb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				tmpCmb->FormattingEnabled = true;
				tmpCmb->Location = System::Drawing::Point(12, 44+27*i);
				tmpCmb->Size = System::Drawing::Size(77, 21);
				this->configureYearComboBox(tmpCmb);
				tmpCmb->SelectedIndexChanged+=gcnew System::EventHandler(this,&PopupForm::combobox_SelectedIndexChanged);

				this->cmbArray->Add(tmpCmb);
				this->Controls->Add(tmpCmb);
				// month combo
				tmpCmb=gcnew ComboBox();
				tmpCmb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				tmpCmb->FormattingEnabled = true;
				tmpCmb->Location = System::Drawing::Point(113, 44+27*i);
				tmpCmb->Size = System::Drawing::Size(42, 21);
				this->configureMonthComboBox(tmpCmb);
				tmpCmb->SelectedIndexChanged+=gcnew System::EventHandler(this,&PopupForm::combobox_SelectedIndexChanged);

				this->cmbArray->Add(tmpCmb);
				this->Controls->Add(tmpCmb);
				// day combo
				tmpCmb=gcnew ComboBox();
				tmpCmb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				tmpCmb->FormattingEnabled = true;
				tmpCmb->Location = System::Drawing::Point(179, 44+27*i);
				tmpCmb->Size = System::Drawing::Size(36, 21);
				this->configureDayComboBox(tmpCmb,31);
				//tmpCmb->SelectedIndexChanged+=gcnew System::EventHandler(this,&PopupForm::combobox_SelectedIndexChanged);

				this->cmbArray->Add(tmpCmb);
				this->Controls->Add(tmpCmb);
				// year label
				Label^ tmpLabel=gcnew Label();
				tmpLabel->AutoSize = true;
				tmpLabel->Location = System::Drawing::Point(91, 48+27*i);
				tmpLabel->Size = System::Drawing::Size(19, 13);
				tmpLabel->Text = L"年";
				this->Controls->Add(tmpLabel);
				// month label
				tmpLabel=gcnew Label();
				tmpLabel->AutoSize = true;
				tmpLabel->Location = System::Drawing::Point(157, 48+27*i);
				tmpLabel->Size = System::Drawing::Size(19, 13);
				tmpLabel->Text = L"月";
				this->Controls->Add(tmpLabel);
				// day label
				tmpLabel=gcnew Label();
				tmpLabel->AutoSize = true;
				tmpLabel->Location = System::Drawing::Point(217, 48+27*i);
				tmpLabel->Size = System::Drawing::Size(19, 13);
				tmpLabel->Text = L"日";	
				this->Controls->Add(tmpLabel);
			}
		}

		void configureYearComboBox(ComboBox^ yearCmb){			
			for(int i=global::curYear-10;i<=global::curYear+10;++i)yearCmb->Items->Add(i);
		}

		void configureMonthComboBox(ComboBox^ monthCmb){
			for(int i=1;i<=12;++i)monthCmb->Items->Add(i);
		}

		void configureDayComboBox(ComboBox^ dayCmb,int ds){
			for(int i=1;i<=ds;++i)dayCmb->Items->Add(i);
		}

	
		bool isExistSelectedDate(){
			int cmbNo;
			IEnumerator^ cmbEnums=this->cmbArray->GetEnumerator();
			String^ dStr="";
			while(cmbEnums->MoveNext()){
				++cmbNo;
				ComboBox^ tmpCombo=safe_cast<ComboBox^> (cmbEnums->Current);
				String^ ys, ^ms, ^ds;
				if((cmbNo-1)%3==0) ys=tmpCombo->Text;
				if((cmbNo-1)%3==1) ms=tmpCombo->Text;					 
				if((cmbNo-1)%3==2){ //day combobox
					ds=tmpCombo->Text;
					int edno=(int) (cmbNo-1)/3;
					if(ys->Length<=0 || ms->Length<=0 || ds->Length<=0){
						this->evtDates[edno]="";
						ys="";ms="";ds="";
						continue;
					}
					int yn=Convert::ToInt32(ys);
					int mn=Convert::ToInt32(ms);
					int dn=Convert::ToInt32(ds);					
					this->evtDates[edno]=ys+"-"+ms+"-"+ds;
					dStr+=this->evtDates[edno];
					ys="";ms="";ds="";
				}				
			}
			if(dStr->Length<=0){// there don't exist selected event day.
				return true;
			}			
			return false;		
		}

		bool isExistSameDate(){
			for(int i=0;i<9;++i){//check same event day
				if(this->evtDates[i]->Length<=0) continue;
				for(int j=i+1;j<10;++j){
					if(this->evtDates[j]->Length<=0) continue;
					if(String::Equals(this->evtDates[i],this->evtDates[j])) return true;
				}
			}
		}

		void dateChanged(String^ ys, String^ ms, String^ ds, ComboBox^tmpCombo){
			if(ys->Length>0 && ms->Length>0 && ds->Length>0){
				int yn=Convert::ToInt32(ys);
				int mn=Convert::ToInt32(ms);
				int dn=Convert::ToInt32(ds);
				if((DateTime::IsLeapYear(yn) && dn>29) || (!DateTime::IsLeapYear(yn) && dn>28)){
					MessageBox::Show("");
					int dayNum=((DateTime^)(DateTime::Now))->DaysInMonth(yn,mn);
					tmpCombo->Items->Clear();
					this->configureDayComboBox(tmpCombo,dayNum);
				}						 
			}			
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PopupForm::typeid));
			this->closeLbl = (gcnew System::Windows::Forms::Label());
			this->qTxt = (gcnew System::Windows::Forms::TextBox());
			this->okBtn = (gcnew System::Windows::Forms::Button());
			this->closePic = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->normalPic = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->normalPic))->BeginInit();
			this->SuspendLayout();
			// 
			// closeLbl
			// 
			this->closeLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->closeLbl->Location = System::Drawing::Point(212, 14);
			this->closeLbl->Name = L"closeLbl";
			this->closeLbl->Size = System::Drawing::Size(20, 20);
			this->closeLbl->TabIndex = 0;
			this->closeLbl->Text = L"×";
			this->closeLbl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->closeLbl->MouseLeave += gcnew System::EventHandler(this, &PopupForm::qLbl_MouseLeave);
			this->closeLbl->Click += gcnew System::EventHandler(this, &PopupForm::closeLbl_Click);
			this->closeLbl->MouseEnter += gcnew System::EventHandler(this, &PopupForm::qLbl_MouseEnter);
			// 
			// qTxt
			// 
			this->qTxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->qTxt->Location = System::Drawing::Point(12, 11);
			this->qTxt->Name = L"qTxt";
			this->qTxt->Size = System::Drawing::Size(193, 26);
			this->qTxt->TabIndex = 1;
			this->qTxt->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &PopupForm::qTxt_KeyPress);
			// 
			// okBtn
			// 
			this->okBtn->Location = System::Drawing::Point(85, 320);
			this->okBtn->Name = L"okBtn";
			this->okBtn->Size = System::Drawing::Size(75, 21);
			this->okBtn->TabIndex = 8;
			this->okBtn->Text = L"确  认";
			this->okBtn->UseVisualStyleBackColor = true;
			this->okBtn->Click += gcnew System::EventHandler(this, &PopupForm::okBtn_Click);
			// 
			// closePic
			// 
			this->closePic->BackColor = System::Drawing::Color::Transparent;
			this->closePic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"closePic.Image")));
			this->closePic->Location = System::Drawing::Point(195, 301);
			this->closePic->Name = L"closePic";
			this->closePic->Size = System::Drawing::Size(20, 18);
			this->closePic->TabIndex = 9;
			this->closePic->TabStop = false;
			this->closePic->Visible = false;
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &PopupForm::timer1_Tick);
			// 
			// normalPic
			// 
			this->normalPic->BackColor = System::Drawing::Color::White;
			this->normalPic->Location = System::Drawing::Point(169, 301);
			this->normalPic->Name = L"normalPic";
			this->normalPic->Size = System::Drawing::Size(20, 18);
			this->normalPic->TabIndex = 9;
			this->normalPic->TabStop = false;
			this->normalPic->Visible = false;
			// 
			// PopupForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(245, 352);
			this->Controls->Add(this->normalPic);
			this->Controls->Add(this->closePic);
			this->Controls->Add(this->okBtn);
			this->Controls->Add(this->qTxt);
			this->Controls->Add(this->closeLbl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(200, 200);
			this->Name = L"PopupForm";
			this->Text = L" 选择日子";
			this->Deactivate += gcnew System::EventHandler(this, &PopupForm::PopupForm_Deactivate);
			this->Load += gcnew System::EventHandler(this, &PopupForm::PopupForm_Load);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &PopupForm::PopupForm_MouseUp);
			this->Activated += gcnew System::EventHandler(this, &PopupForm::PopupForm_Activated);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PopupForm::PopupForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &PopupForm::PopupForm_MouseMove);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->normalPic))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void qTxt_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 if(e->KeyChar==(char)13){	
					 if(this->qTxt->Text->Length<=0){
						MessageBox::Show(L"请输入整数。");
						return;
					 }
					 if(!this->isInteger(this->qTxt->Text)){
						 MessageBox::Show(L"请输入整数。");
						 this->qTxt->Text="";
						 return;
					 }
					 global::timeOut=Convert::ToInt32(this->qTxt->Text);
					 this->qTxt->Text="";
					 this->timer1->Enabled=true;
				 }
			 }

private: System::Void okBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->isExistSelectedDate() ==true){				 
				MessageBox::Show(L"请选择正确的事件一天。");
				return;
			 }
			 if(this->isExistSameDate() ==true){				 
				MessageBox::Show(L"存在同样的事件一天。");
				return;
			 }

			 IO::StreamWriter^ fsw=gcnew StreamWriter(gcnew FileStream("event.xml",IO::FileMode::Append,IO::FileAccess::Write));
			 for(int i=0;i<10;++i){
				 if(this->evtDates[i]->Length>0) fsw->WriteLine(this->evtDates[i]+":2");
			 }
			 fsw->Close();

			 this->DialogResult=System::Windows::Forms::DialogResult::OK;
			 this->Close();
		 }

private: System::Void qLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->closeLbl->BackgroundImage=this->closePic->Image;
			 this->closeLbl->ForeColor=System::Drawing::Color::White;
		 }
private: System::Void qLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->closeLbl->BackgroundImage=this->normalPic->Image ;
			 this->closeLbl->ForeColor=System::Drawing::Color::Black;
		 }
private: System::Void closeLbl_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void combobox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 IEnumerator^ cmbEnums=this->cmbArray->GetEnumerator();
			 int cmbNo;
			 String^ ys, ^ms, ^ds;
			 while(cmbEnums->MoveNext()){				 
				 ComboBox^ tmpCombo=safe_cast<ComboBox^> (cmbEnums->Current);
				 if(cmbNo%3==0)ys=tmpCombo->Text;
				 if(cmbNo%3==1)ms=tmpCombo->Text;
				 if(cmbNo%3==2){
					 ds=tmpCombo->Text;	
					 if(ys->Length>0 && ms->Length>0 && ds->Length>0){
						int yn=Convert::ToInt32(ys);
						int mn=Convert::ToInt32(ms);
						int dn=Convert::ToInt32(ds);
						int dayNum=((DateTime^)(DateTime::Now))->DaysInMonth(yn,mn);
						if(mn==2){
							if((DateTime::IsLeapYear(yn) && dn>29) || (!DateTime::IsLeapYear(yn) && dn>28)){
								MessageBox::Show(L"二月有28或29天。");		
								tmpCombo->Items->Clear();
								this->configureDayComboBox(tmpCombo,dayNum);
								tmpCombo->SelectedIndex=0;								
							}	
						}else{
							tmpCombo->Items->Clear();
							this->configureDayComboBox(tmpCombo,dayNum);
							tmpCombo->SelectedIndex=dn-1;
						}											 
					 }
				 }
				 ++cmbNo;
			 }			 
		 }

private: System::Void PopupForm_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void PopupForm_Activated(System::Object^  sender, System::EventArgs^  e) {
			 this->timer1->Enabled=true;
		 }
private: System::Void PopupForm_Deactivate(System::Object^  sender, System::EventArgs^  e) {
			 this->timer1->Enabled=false;

		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 ++this->countTime;
			 this->cx=System::Windows::Forms::Cursor::Position.X;
			 this->cy=System::Windows::Forms::Cursor::Position.Y;
			 if(this->cx!=this->px || this->cy!=this->py )this->countTime=0;
			 if(global::timeOut==this->countTime && global::timeOut>0){
				 this->timer1->Enabled=false;
				 this->Close();
			 }
			 this->px=this->cx;this->py=this->cy;
		 }
private: System::Void PopupForm_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->moveFlag=1-this->moveFlag;
			 this->upX=0;
			 this->upY=0;			 
		 }
private: System::Void PopupForm_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->moveFlag=1-this->moveFlag;
			 this->upX=e->X;
			 this->upY=e->Y;
			 
		 }
private: System::Void PopupForm_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(this->moveFlag<=0) return;
			 this->Left=this->Left+e->X-this->upX;
			 this->Top=this->Top+e->Y-this->upY;

		 }
};
}
