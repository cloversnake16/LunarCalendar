#pragma once

#include "DetailMonth.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CalendarFull {

	/// <summary>
	/// Summary for YearControl
	/// </summary>
	public ref class YearControl : public System::Windows::Forms::UserControl
	{
	public:
		YearControl(void)
		{
			//
			//TODO: Add the constructor code here
			//
		}

		YearControl(Form^ newAddr,int newYear, int newSize){
			InitializeComponent();
			this->curYear=newYear;
			this->parentAddr=newAddr;
			this->monthArray=gcnew ArrayList;
			this->dayArray=gcnew ArrayList;
			this->gapX=20;
			this->gapY=5;
			this->realSize=newSize;
			this->fontRatio=(float)this->realSize/10;
			this->redrawDayElement();
		}

	private: System::Windows::Forms::PictureBox^  leavePic;
	private: System::Windows::Forms::PictureBox^  enterPic;
	private: System::Windows::Forms::PictureBox^  markTodayPic;
	private: System::Windows::Forms::PictureBox^  markEnterPic;
	private: System::Windows::Forms::PictureBox^  markLeavePic;
	private: System::Windows::Forms::PictureBox^  todayPic;
	public: 
		Hashtable^ evtTable;
		
		void setGapXandY(int newX, int newY){
			this->gapX=newX;
			this->gapY=newY;
		}

		void loadEventInfoFromXMLFile(){
			this->evtTable=gcnew Hashtable();
			IO::StreamReader^ fsr=gcnew StreamReader(gcnew IO::FileStream("event.xml",IO::FileMode::OpenOrCreate,IO::FileAccess::Read));
			String^ lineStr;			
			while(lineStr=fsr->ReadLine()){
				int pos=lineStr->IndexOf(":");
				String^ evtDate=lineStr->Substring(0,pos);
				pos=lineStr->IndexOf(":");
				String^ evtCt=lineStr->Substring(pos+1,lineStr->Length-pos-1);
				if(this->evtTable->ContainsKey(evtDate))this->evtTable->Remove(evtDate);
				this->evtTable->Add(evtDate,evtCt);					
			}
			fsr->Close();

		}

		void configureYear(){
			loadEventInfoFromXMLFile();
			this->monthArray=gcnew ArrayList;
			int mx=0,my=0;
			for(int i=0;i<12;++i){				
				if(i%4==0 && i>0){
					mx=0;
					++my;
				}				
				this->configureMonth(this->curYear,i+1,(this->gapX+this->realSize)*7*mx+this->gapX*2*mx,(this->gapY+this->realSize)*8*my+5*this->fontRatio*(my+0.5));
				this->monthArray->Add(this->dayArray);
				++mx;				
			}
			this->redrawDayElement();
		}

	private:
		int curYear, gapX, gapY, realSize;
		float fontRatio;
		Form^ parentAddr;
		void configureMonth(int yearNo, int monthNo, int mx, int my){
			String^ yearStr;
			String^ monthStr;
			yearStr=L"年"; monthStr=L"月";
			array<String^>^ dayArray=gcnew array<String^>(7);
			dayArray[0]=L"日";
			dayArray[1]=L"一";
			dayArray[2]=L"二";
			dayArray[3]=L"三";
			dayArray[4]=L"四";
			dayArray[5]=L"五";
			dayArray[6]=L"六";
			
			//configure month label
			Label^ tmp=gcnew Label();
			tmp->Size=System::Drawing::Size(this->realSize,this->realSize);
			tmp->Location=System::Drawing::Point(mx+this->gapX*4,my+this->gapY*3);
			if(this->fontRatio<=0) this->fontRatio=1;
			tmp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6*this->fontRatio, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			tmp->AutoSize=true;
			tmp->ForeColor = System::Drawing::Color::Red;			
			tmp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			tmp->Text=Convert::ToString(monthNo)+monthStr;
			tmp->MouseLeave += gcnew System::EventHandler(this, &YearControl::monthLabel_MouseLeave);
			tmp->Click += gcnew System::EventHandler(this, &YearControl::monthLabel_Click);
			tmp->MouseEnter += gcnew System::EventHandler(this, &YearControl::monthLabel_MouseEnter);
			this->Controls->Add(tmp);

			//configure day label
			for(int i=0;i<7;++i){
				tmp=gcnew Label();
				tmp->Size=System::Drawing::Size(this->realSize,this->realSize);
				tmp->Location=System::Drawing::Point(mx+this->gapX*4+i*(this->realSize+this->gapX),my+this->gapY*3+this->realSize);
				tmp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6*this->fontRatio, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				tmp->AutoSize=false;
				tmp->ForeColor = System::Drawing::Color::Blue;	
				tmp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				tmp->Text=dayArray[i];
				this->Controls->Add(tmp);
			}
			
			int daysInMonth=DateTime::DaysInMonth(yearNo,monthNo);
			int dayNum=this->numberOfDay(yearNo,monthNo,1);
			
			Label^ dayLabel;
			for(int dd=0;dd<daysInMonth;++dd){
				String^ hashKey=Convert::ToString(yearNo)+"-"+Convert::ToString(monthNo)+"-"+Convert::ToString(dd+1);
				int dx,dy;
				dx=((dd+dayNum)%7)*(this->realSize+this->gapX)+mx+this->gapX*4;
				dy=((int)(dd+dayNum)/7)*this->realSize+2*this->realSize+my+this->gapY*3;				

				dayLabel=gcnew Label();
				dayLabel->Size=System::Drawing::Size(this->realSize,this->realSize);
				dayLabel->Location=System::Drawing::Point(dx, dy);
				dayLabel->BackColor=System::Drawing::Color::White;
				dayLabel->AutoSize=false;
				dayLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				dayLabel->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 3.5*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				
				DateTime^ chk=(DateTime^)DateTime::Now;
				if(chk->Year==yearNo && chk->Month==monthNo && chk->Day==(dd+1)){//check today;					
					if(this->evtTable->Contains(hashKey)){
						this->redrawMarkImage(Convert::ToString(dd+1));
						dayLabel->Image=this->markTodayPic->Image;
					}else{
						dayLabel->Image=this->todayPic->Image;
					}
				}else{
					if(this->evtTable->Contains(hashKey)){
						this->redrawMarkImage(Convert::ToString(dd+1));
						dayLabel->Image=this->markLeavePic->Image;
					}
				}
				dayLabel->Text=Convert::ToString(dd+1);

				dayLabel->MouseLeave += gcnew System::EventHandler(this, &YearControl::dayLabel_MouseLeave);
				dayLabel->Click += gcnew System::EventHandler(this, &YearControl::dayLabel_Click);
				dayLabel->MouseEnter += gcnew System::EventHandler(this, &YearControl::dayLabel_MouseEnter);

				this->Controls->Add(dayLabel);
				this->dayArray->Add(dayLabel);
			}
		}		

		int numberOfDay(int yearNo, int monthNo, int dayNo){
			DateTime^ dt=gcnew DateTime(yearNo,monthNo,dayNo);
			String^ dayStr=Convert::ToString(dt->DayOfWeek);
			if(String::Equals(dayStr,"Sunday")){
				return 0;
			}else if(String::Equals(dayStr,"Monday")){
				return 1;
			}else if(String::Equals(dayStr,"Tuesday")){
				return 2;
			}else if(String::Equals(dayStr,"Wednesday")){
				return 3;
			}else if(String::Equals(dayStr,"Thursday")){
				return 4;
			}else if(String::Equals(dayStr,"Friday")){
				return 5;
			}else if(String::Equals(dayStr,"Saturday")){
				return 6;
			}
		}

		int getDateInfo(int xx, int yy){
			int bx,by;
			float areaWid, areaHei;
			areaWid=(float)(this->Width-this->gapX*4)/4;
			areaHei=(float)(this->Height)/3;
			bx=(int)(xx/areaWid);by=(int)(yy/areaHei);
			return 4*by+bx+1;
		}

		void redrawDayElement(){
			if(this->realSize<=0) return;
			this->todayPic->Width=this->realSize;
			this->todayPic->Height=this->realSize;
			Bitmap^ bmp=gcnew Bitmap(this->realSize,this->realSize);
			Graphics^ gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::Red,0,0,this->realSize,this->realSize);
			this->todayPic->Image=bmp;
			
			this->enterPic->Width=this->realSize;
			this->enterPic->Height=this->realSize;
			bmp=gcnew Bitmap(this->realSize,this->realSize);
			gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::DodgerBlue,0,0,this->realSize,this->realSize);
			this->enterPic->Image=bmp;

			this->leavePic->Width=this->realSize;
			this->leavePic->Height=this->realSize;
			bmp=gcnew Bitmap(this->realSize,this->realSize);
			gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			this->leavePic->Image=bmp;
			delete gPic;
		}

		void redrawMarkImage(String^ num){
			if(this->realSize<=0) return;
			//mark leave image
			Bitmap^ bmp=gcnew Bitmap(this->realSize,this->realSize);
			Graphics^ gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::Gray,0,0,this->realSize,this->realSize);
			int rr=(int)this->realSize/8;
			gPic->FillEllipse(Brushes::Pink,this->realSize/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString("!", gcnew Drawing::Font(L"Microsoft Sans Serif", 3*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black,  (Single)this->realSize/6-rr/2, (Single)rr/2);
			gPic->FillEllipse(Brushes::OrangeRed,this->realSize/2-rr,0,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 3*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/2-rr*2/3, 0.0);
			gPic->FillEllipse(Brushes::RoyalBlue,this->realSize*5/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 3*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize*5/6-rr*2/3, (Single)rr/2);
			this->markLeavePic->Image=bmp;
			//mark enter image;
			bmp=gcnew Bitmap(this->realSize,this->realSize);
			gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::DodgerBlue,0,0,this->realSize,this->realSize);
			rr=(int)this->realSize/8;
			gPic->FillEllipse(Brushes::Pink,this->realSize/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString("!", gcnew Drawing::Font(L"Microsoft Sans Serif", 3*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/6-rr/2, (Single)rr/2);
			gPic->FillEllipse(Brushes::OrangeRed,this->realSize/2-rr,0,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 3*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/2-rr*2/3, 0.0);
			gPic->FillEllipse(Brushes::RoyalBlue,this->realSize*5/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 3*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize*5/6-rr*2/3, (Single)rr/2);
			this->markEnterPic->Image=bmp;
			//mark today image;
			bmp=gcnew Bitmap(this->realSize,this->realSize);
			gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::LightCoral,0,0,this->realSize,this->realSize);
			rr=(int)this->realSize/8;
			gPic->FillEllipse(Brushes::Pink,this->realSize/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString("!", gcnew Drawing::Font(L"Microsoft Sans Serif", 3*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/6-rr/2, (Single)rr/2);
			gPic->FillEllipse(Brushes::OrangeRed,this->realSize/2-rr,0,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 3*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/2-rr*2/3, 0.0);
			gPic->FillEllipse(Brushes::RoyalBlue,this->realSize*5/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 3*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize*5/6-rr*2/3, (Single)rr/2);
			this->markTodayPic->Image=bmp;

			delete gPic;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~YearControl()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		ArrayList ^monthArray, ^dayArray;		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->leavePic = (gcnew System::Windows::Forms::PictureBox());
			this->enterPic = (gcnew System::Windows::Forms::PictureBox());
			this->todayPic = (gcnew System::Windows::Forms::PictureBox());
			this->markTodayPic = (gcnew System::Windows::Forms::PictureBox());
			this->markEnterPic = (gcnew System::Windows::Forms::PictureBox());
			this->markLeavePic = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->leavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->enterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->todayPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markTodayPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markEnterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markLeavePic))->BeginInit();
			this->SuspendLayout();
			// 
			// leavePic
			// 
			this->leavePic->Location = System::Drawing::Point(244, 206);
			this->leavePic->Name = L"leavePic";
			this->leavePic->Size = System::Drawing::Size(20, 20);
			this->leavePic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->leavePic->TabIndex = 3;
			this->leavePic->TabStop = false;
			this->leavePic->Visible = false;
			// 
			// enterPic
			// 
			this->enterPic->Location = System::Drawing::Point(192, 206);
			this->enterPic->Name = L"enterPic";
			this->enterPic->Size = System::Drawing::Size(20, 20);
			this->enterPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->enterPic->TabIndex = 4;
			this->enterPic->TabStop = false;
			this->enterPic->Visible = false;
			// 
			// todayPic
			// 
			this->todayPic->Location = System::Drawing::Point(142, 206);
			this->todayPic->Name = L"todayPic";
			this->todayPic->Size = System::Drawing::Size(20, 20);
			this->todayPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->todayPic->TabIndex = 2;
			this->todayPic->TabStop = false;
			this->todayPic->Visible = false;
			// 
			// markTodayPic
			// 
			this->markTodayPic->Location = System::Drawing::Point(142, 264);
			this->markTodayPic->Name = L"markTodayPic";
			this->markTodayPic->Size = System::Drawing::Size(20, 20);
			this->markTodayPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->markTodayPic->TabIndex = 2;
			this->markTodayPic->TabStop = false;
			this->markTodayPic->Visible = false;
			// 
			// markEnterPic
			// 
			this->markEnterPic->Location = System::Drawing::Point(192, 264);
			this->markEnterPic->Name = L"markEnterPic";
			this->markEnterPic->Size = System::Drawing::Size(20, 20);
			this->markEnterPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->markEnterPic->TabIndex = 4;
			this->markEnterPic->TabStop = false;
			this->markEnterPic->Visible = false;
			// 
			// markLeavePic
			// 
			this->markLeavePic->Location = System::Drawing::Point(244, 264);
			this->markLeavePic->Name = L"markLeavePic";
			this->markLeavePic->Size = System::Drawing::Size(20, 20);
			this->markLeavePic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->markLeavePic->TabIndex = 3;
			this->markLeavePic->TabStop = false;
			this->markLeavePic->Visible = false;
			// 
			// YearControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->Controls->Add(this->markLeavePic);
			this->Controls->Add(this->leavePic);
			this->Controls->Add(this->markEnterPic);
			this->Controls->Add(this->enterPic);
			this->Controls->Add(this->markTodayPic);
			this->Controls->Add(this->todayPic);
			this->Name = L"YearControl";
			this->Size = System::Drawing::Size(379, 381);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &YearControl::YearControl_MouseMove);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->leavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->enterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->todayPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markTodayPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markEnterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markLeavePic))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void YearControl_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void dayLabel_Click(System::Object^  sender, System::EventArgs^  e) {
			 Label^ curLabel=safe_cast<Label^>(sender);		
			 //MessageBox::Show(Convert::ToString(this->getDateInfo(curLabel->Left,curLabel->Top)));
			 DetailMonth^ detail=gcnew DetailMonth(this->parentAddr,this->getDateInfo(curLabel->Left,curLabel->Top));	
			 detail->configureDetailMonth();
			 detail->StartPosition=FormStartPosition::CenterScreen;
			 detail->Show();
			 this->parentAddr->Hide();
		 }
private: System::Void dayLabel_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 Label^ curLabel=safe_cast<Label^>(sender);	
			 int mm=this->getDateInfo(curLabel->Left,curLabel->Top);
			 String^ evtStr=Convert::ToString(this->curYear)+"-"+Convert::ToString(mm)+"-"+curLabel->Text;
			 if(this->evtTable->ContainsKey(evtStr)){
				 curLabel->Image=this->markEnterPic->Image;
			 }else{
				 curLabel->Image=this->enterPic->Image;
			 }			 
		 }

private: System::Void dayLabel_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 //if(this->isToday==0){
			 Label^ curLabel=safe_cast<Label^>(sender);			 
			 int monthNo=this->getDateInfo(curLabel->Left,curLabel->Top);
			 DateTime^ today=(DateTime^)DateTime::Now;
			 int mm=this->getDateInfo(curLabel->Left,curLabel->Top);			 
			 String^ evtStr=Convert::ToString(this->curYear)+"-"+Convert::ToString(mm)+"-"+curLabel->Text;
			 //MessageBox::Show(evtStr);
			 if(today->Year==this->curYear && today->Month==monthNo && today->Day==Convert::ToInt32(curLabel->Text)){
				 if(this->evtTable->ContainsKey(evtStr)){
					 curLabel->Image=this->markTodayPic->Image;
				 }else{
					 curLabel->Image=this->todayPic->Image;
					 
				 }
			 }else{
				 if(this->evtTable->ContainsKey(evtStr)){
					 curLabel->Image=this->markLeavePic->Image;
				 }else{
					 curLabel->Image=this->leavePic->Image;
				 }
			 }	 
		 }

private: System::Void monthLabel_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 Label^ tmp=safe_cast<Label^>(sender);
			 tmp->ForeColor=System::Drawing::Color::Red;
		 }
private: System::Void monthLabel_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 Label^ tmp=safe_cast<Label^>(sender);
			 tmp->ForeColor=System::Drawing::Color::LightSalmon;
		 }
private: System::Void monthLabel_Click(System::Object^  sender, System::EventArgs^  e) {
			 Label^ tmp=safe_cast<Label^>(sender);
			 String^ mStr=tmp->Text->Substring(0,tmp->Text->Length-1);
			 DetailMonth^ detail=gcnew DetailMonth(this->parentAddr,Convert::ToInt32(mStr));	
			 detail->configureDetailMonth();
			 detail->StartPosition=FormStartPosition::CenterScreen;
			 detail->Show();
			 this->parentAddr->Hide();
		 }

private: System::Void YearControl_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->Cursor=System::Windows::Forms::Cursors::Default;
		 }
};
}
