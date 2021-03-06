#pragma once

#include "EventSettingDialog.h"
#include "Solar.h"
#include "Lunar.h"


using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CalendarFull {

	/// <summary>
	/// Summary for DayControl
	/// </summary>
	public ref class DayControl : public System::Windows::Forms::UserControl
	{
	public:
		DayControl(void)
		{
			//
			//TODO: Add the constructor code here
			//
		}

		DayControl(int yy,int mm, int dd, int newSize){
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->clickFlag=0;
			this->evtNum=-1;//no event;	
			this->evtArray=gcnew ArrayList;
			this->realSize=newSize;
			this->Width=newSize;
			this->Height=newSize;
			this->fontRatio=(float) this->realSize/64;
			this->redrawDayElement();

			this->curYear=yy;
			this->curMonth=mm;
			this->curDay=dd;

			this->chineseLunarStr=gcnew array<String^>(3);
			this->chineseLunarStr[0]=L"初";
			this->chineseLunarStr[1]=L"十";
			this->chineseLunarStr[2]=L"廿";

			this->chineseMonthStr=gcnew array<String^>(12);
			this->chineseMonthStr[0]=L"一";
			this->chineseMonthStr[1]=L"二";
			this->chineseMonthStr[2]=L"三";
			this->chineseMonthStr[3]=L"四";
			this->chineseMonthStr[4]=L"五";
			this->chineseMonthStr[5]=L"六";
			this->chineseMonthStr[6]=L"七";
			this->chineseMonthStr[7]=L"八";
			this->chineseMonthStr[8]=L"九";
			this->chineseMonthStr[9]=L"十";
			this->chineseMonthStr[10]=L"十一";
			this->chineseMonthStr[11]=L"十二";
		}

		int curYear, curMonth, curDay, realSize;
		float fontRatio;
	private: System::Windows::Forms::PictureBox^  markEnterPic;
	private: System::Windows::Forms::PictureBox^  markTodayPic;
	public: 
		ArrayList^ evtArray;

		void configureDay(){		

			Solar^ sol=gcnew Solar();				
			sol->solarYear=this->curYear;
			sol->solarMonth=this->curMonth;
			sol->solarDay=this->curDay;
			Lunar^ lun=this->SolarToLunar(sol);
			String^ lunarStr;
			if(lun->lunarDay==1){
				lunarStr=this->chineseMonthStr[lun->lunarMonth-1]+L"月";
			}else{
				if(lun->lunarDay==20)
					lunarStr=L"二十";
				else
					lunarStr=this->chineseLunarStr[(int)((lun->lunarDay-1)/10)]+this->chineseMonthStr[(lun->lunarDay-1)%10];
			}

			this->dayLbl->Text=Convert::ToString(this->curDay)+Environment::NewLine+lunarStr;
			
			String^ dateStr=Convert::ToString(this->curYear)+"-"+Convert::ToString(this->curMonth)+"-"+Convert::ToString(this->curDay);
			IO::StreamReader^ fsr=gcnew StreamReader(gcnew IO::FileStream("event.xml",IO::FileMode::OpenOrCreate,IO::FileAccess::Read));
			String^ lineStr;			
			while(lineStr=fsr->ReadLine()){
				int pos=lineStr->IndexOf(":");
				String^ ctStr=lineStr->Substring(0,pos);
				if(String::Equals(ctStr,dateStr)){
					int pos=lineStr->IndexOf(":");
					ctStr=lineStr->Substring(pos+1,lineStr->Length-pos-1);		
					
					this->drawBackground(ctStr);
					//break;
				}					
			}
			fsr->Close();	

			DateTime^ dt=(DateTime^)DateTime::Now;
			if(dt->Year==this->curYear && dt->Month==this->curMonth && dt->Day==this->curDay){
				if(this->evtNum<=0){
					this->BackgroundImage=this->todayPic->Image;				
				}else{
					this->BackgroundImage=this->markTodayPic->Image;
				}
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DayControl()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  leavePic;
	private: System::Windows::Forms::PictureBox^  todayPic;
	private: System::Windows::Forms::PictureBox^  markLeavePic;

	private: System::Windows::Forms::Label^  dayLbl;
	private:array<String^>^chineseLunarStr, ^chineseMonthStr;
	private:System::Windows::Forms::PictureBox^  enterPic;
	public: int clickFlag,evtNum;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		void redrawDayElement(){
			if(this->realSize<=0) return;
			this->dayLbl->Width=this->realSize;
			this->dayLbl->Height=this->realSize;
			this->dayLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10*this->fontRatio, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			//today image
			this->todayPic->Width=this->realSize;
			this->todayPic->Height=this->realSize;
			Bitmap^ bmp=gcnew Bitmap(this->realSize,this->realSize);
			Graphics^ gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::LightCoral,0,0,this->realSize,this->realSize);
			this->todayPic->Image=bmp;
			//enter image
			this->enterPic->Width=this->realSize;
			this->enterPic->Height=this->realSize;
			bmp=gcnew Bitmap(this->realSize,this->realSize);
			gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::DodgerBlue,0,0,this->realSize,this->realSize);
			this->enterPic->Image=bmp;
			//leave image
			this->leavePic->Width=this->realSize;
			this->leavePic->Height=this->realSize;
			bmp=gcnew Bitmap(this->realSize,this->realSize);
			gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			this->leavePic->Image=bmp;

			delete gPic;
		}

		void drawBackground(String^ num){
			if(this->realSize<=0) return;
			this->clickFlag=1;
			this->evtNum=Convert::ToInt32(num);
			//mark leave image
			Bitmap^ bmp=gcnew Bitmap(this->realSize,this->realSize);
			Graphics^ gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::Gray,0,0,this->realSize,this->realSize);
			int rr=(int)this->realSize/8;
			gPic->FillEllipse(Brushes::Pink,this->realSize/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString("!", gcnew Drawing::Font(L"Microsoft Sans Serif", 5*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/6-rr/2, (Single)rr);
			gPic->FillEllipse(Brushes::OrangeRed,this->realSize/2-rr,0,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 5*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/2-rr*2/3, (Single)rr/2);
			gPic->FillEllipse(Brushes::RoyalBlue,this->realSize*5/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 5*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize*5/6-rr*2/3, (Single)rr);
			this->markLeavePic->Image=bmp;
			this->BackgroundImage=this->markLeavePic->Image;
			//mark enter image;
			bmp=gcnew Bitmap(this->realSize,this->realSize);
			gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::DodgerBlue,0,0,this->realSize,this->realSize);
			rr=(int)this->realSize/8;
			gPic->FillEllipse(Brushes::Pink,this->realSize/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString("!", gcnew Drawing::Font(L"Microsoft Sans Serif", 5*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/6-rr/2, (Single)rr);
			gPic->FillEllipse(Brushes::OrangeRed,this->realSize/2-rr,0,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 5*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/2-rr*2/3, (Single)rr/2);
			gPic->FillEllipse(Brushes::RoyalBlue,this->realSize*5/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 5*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize*5/6-rr*2/3, (Single)rr);
			this->markEnterPic->Image=bmp;
			this->dayLbl->ForeColor=System::Drawing::Color::Transparent;
			//mark today image;
			bmp=gcnew Bitmap(this->realSize,this->realSize);
			gPic=Graphics::FromImage(bmp);
			gPic->Clear(Color::Transparent);
			gPic->FillEllipse(Brushes::LightCoral,0,0,this->realSize,this->realSize);
			rr=(int)this->realSize/8;
			gPic->FillEllipse(Brushes::Pink,this->realSize/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString("!", gcnew Drawing::Font(L"Microsoft Sans Serif", 5*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/6-rr/2, (Single)rr);
			gPic->FillEllipse(Brushes::OrangeRed,this->realSize/2-rr,0,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 5*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize/2-rr*2/3, (Single)rr/2);
			gPic->FillEllipse(Brushes::RoyalBlue,this->realSize*5/6-rr,rr/2,2*rr,2*rr);
			gPic->DrawString(num, gcnew Drawing::Font(L"Microsoft Sans Serif", 5*this->fontRatio,System::Drawing::FontStyle::Bold),Brushes::Black, (Single)this->realSize*5/6-rr*2/3, (Single)rr);
			this->markTodayPic->Image=bmp;
			this->dayLbl->ForeColor=System::Drawing::Color::Transparent;

			delete gPic;
		}

		void clickedDay(){
			 EventSettingDialog^ settingDlg=gcnew EventSettingDialog();
			 settingDlg->StartPosition=FormStartPosition::CenterParent;
			 settingDlg->ShowDialog(this);
			 if(settingDlg->DialogResult==System::Windows::Forms::DialogResult::OK){	 
				 this->drawBackground(settingDlg->numTxt->Text);
				 insertEventInformation(settingDlg->numTxt->Text);				 
			 }
		}

		void mouseEnterInControl(){
			 if(this->evtNum<=0){
				 this->BackgroundImage=this->enterPic->Image;
			 }else{
				 this->BackgroundImage=this->markEnterPic->Image;
			 }
		}

		void mouseLeaveFromControl(){
			 DateTime^ dt=(DateTime^)DateTime::Now;
			 if(dt->Year==this->curYear && dt->Month==this->curMonth && dt->Day==this->curDay){
				 if(this->evtNum<=0){
					this->BackgroundImage=this->todayPic->Image;
				 }else{
					 this->BackgroundImage=this->markTodayPic->Image;
				 }
				 return;
			 }
			 if(this->evtNum<=0){
				 this->BackgroundImage=this->leavePic->Image;
			 }else{
				 this->BackgroundImage=this->markLeavePic->Image;
			 }
		}

		void insertEventInformation(String^ infoStr){
			String^ dateStr=Convert::ToString(this->curYear)+"-"+Convert::ToString(this->curMonth)+"-"+Convert::ToString(this->curDay);
			IO::StreamWriter^ fsw=gcnew StreamWriter(gcnew FileStream("event.xml",IO::FileMode::Append,IO::FileAccess::Write));				
			
			//IEnumerator^ evtRecord=this->evtArray->GetEnumerator();			
			//while(evtRecord->MoveNext()){
			//	String^ curRecord=safe_cast<String^> (evtRecord->Current);
			//	if(curRecord->Contains(dateStr)){
			//		this->evtArray->Remove(curRecord);
			//	}				
			//}

			this->evtArray->Add(dateStr+":"+infoStr);	

			IEnumerator^ evtRecord=this->evtArray->GetEnumerator();	
			String^ evtStr;
			while(evtRecord->MoveNext()){
				String^ curRecord=safe_cast<String^> (evtRecord->Current);
				evtStr+=curRecord+Environment::NewLine;
			}			
			fsw->Write(evtStr);
			fsw->Close();		
		}
	//------------------------Lunar to Solar----------------------------
		int GetBitInt(int data, int length, int shift) {
			return (data & (((1 << length) - 1) << shift)) >> shift;
		}

		//WARNING: Dates before Oct. 1582 are inaccurate
		long SolarToInt(int y, int m, int d) {
			m = (m + 9) % 12;
			y = y - m / 10;
			return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
		}

		Solar^ SolarFromInt(long g) {
			//C版本的SolarFromInt函数有溢出，导致计算结果错误
			long y = (10000LL * g + 14780) / 3652425;
			long ddd = g - (365 * y + y / 4 - y / 100 + y / 400);
			if (ddd < 0) {
				y--;
				ddd = g - (365 * y + y / 4 - y / 100 + y / 400);
			}
			long mi = (100 * ddd + 52) / 3060;
			long mm = (mi + 2) % 12 + 1;
			y = y + (mi + 2) / 12;
			long dd = ddd - (mi * 306 + 5) / 10 + 1;
			Solar^ solar =gcnew Solar();
			solar->solarYear=(int) y;
			solar->solarMonth=(int) mm;
			solar->solarDay=(int) dd;
			return solar;
		}

		Solar^ LunarToSolar(Lunar^ lunar) {

			int lunar_month_days[] =
				{
						1887, 0x1694, 0x16aa, 0x4ad5, 0xab6, 0xc4b7, 0x4ae, 0xa56, 0xb52a,
						0x1d2a, 0xd54, 0x75aa, 0x156a, 0x1096d, 0x95c, 0x14ae, 0xaa4d, 0x1a4c, 0x1b2a, 0x8d55, 0xad4, 0x135a, 0x495d,
						0x95c, 0xd49b, 0x149a, 0x1a4a, 0xbaa5, 0x16a8, 0x1ad4, 0x52da, 0x12b6, 0xe937, 0x92e, 0x1496, 0xb64b, 0xd4a,
						0xda8, 0x95b5, 0x56c, 0x12ae, 0x492f, 0x92e, 0xcc96, 0x1a94, 0x1d4a, 0xada9, 0xb5a, 0x56c, 0x726e, 0x125c,
						0xf92d, 0x192a, 0x1a94, 0xdb4a, 0x16aa, 0xad4, 0x955b, 0x4ba, 0x125a, 0x592b, 0x152a, 0xf695, 0xd94, 0x16aa,
						0xaab5, 0x9b4, 0x14b6, 0x6a57, 0xa56, 0x1152a, 0x1d2a, 0xd54, 0xd5aa, 0x156a, 0x96c, 0x94ae, 0x14ae, 0xa4c,
						0x7d26, 0x1b2a, 0xeb55, 0xad4, 0x12da, 0xa95d, 0x95a, 0x149a, 0x9a4d, 0x1a4a, 0x11aa5, 0x16a8, 0x16d4,
						0xd2da, 0x12b6, 0x936, 0x9497, 0x1496, 0x1564b, 0xd4a, 0xda8, 0xd5b4, 0x156c, 0x12ae, 0xa92f, 0x92e, 0xc96,
						0x6d4a, 0x1d4a, 0x10d65, 0xb58, 0x156c, 0xb26d, 0x125c, 0x192c, 0x9a95, 0x1a94, 0x1b4a, 0x4b55, 0xad4,
						0xf55b, 0x4ba, 0x125a, 0xb92b, 0x152a, 0x1694, 0x96aa, 0x15aa, 0x12ab5, 0x974, 0x14b6, 0xca57, 0xa56, 0x1526,
						0x8e95, 0xd54, 0x15aa, 0x49b5, 0x96c, 0xd4ae, 0x149c, 0x1a4c, 0xbd26, 0x1aa6, 0xb54, 0x6d6a, 0x12da, 0x1695d,
						0x95a, 0x149a, 0xda4b, 0x1a4a, 0x1aa4, 0xbb54, 0x16b4, 0xada, 0x495b, 0x936, 0xf497, 0x1496, 0x154a, 0xb6a5,
						0xda4, 0x15b4, 0x6ab6, 0x126e, 0x1092f, 0x92e, 0xc96, 0xcd4a, 0x1d4a, 0xd64, 0x956c, 0x155c, 0x125c, 0x792e,
						0x192c, 0xfa95, 0x1a94, 0x1b4a, 0xab55, 0xad4, 0x14da, 0x8a5d, 0xa5a, 0x1152b, 0x152a, 0x1694, 0xd6aa,
						0x15aa, 0xab4, 0x94ba, 0x14b6, 0xa56, 0x7527, 0xd26, 0xee53, 0xd54, 0x15aa, 0xa9b5, 0x96c, 0x14ae, 0x8a4e,
						0x1a4c, 0x11d26, 0x1aa4, 0x1b54, 0xcd6a, 0xada, 0x95c, 0x949d, 0x149a, 0x1a2a, 0x5b25, 0x1aa4, 0xfb52,
						0x16b4, 0xaba, 0xa95b, 0x936, 0x1496, 0x9a4b, 0x154a, 0x136a5, 0xda4, 0x15ac
				};

			int solar_1_1[] =
				{
						1887, 0xec04c, 0xec23f, 0xec435, 0xec649, 0xec83e, 0xeca51, 0xecc46, 0xece3a,
						0xed04d, 0xed242, 0xed436, 0xed64a, 0xed83f, 0xeda53, 0xedc48, 0xede3d, 0xee050, 0xee244, 0xee439, 0xee64d,
						0xee842, 0xeea36, 0xeec4a, 0xeee3e, 0xef052, 0xef246, 0xef43a, 0xef64e, 0xef843, 0xefa37, 0xefc4b, 0xefe41,
						0xf0054, 0xf0248, 0xf043c, 0xf0650, 0xf0845, 0xf0a38, 0xf0c4d, 0xf0e42, 0xf1037, 0xf124a, 0xf143e, 0xf1651,
						0xf1846, 0xf1a3a, 0xf1c4e, 0xf1e44, 0xf2038, 0xf224b, 0xf243f, 0xf2653, 0xf2848, 0xf2a3b, 0xf2c4f, 0xf2e45,
						0xf3039, 0xf324d, 0xf3442, 0xf3636, 0xf384a, 0xf3a3d, 0xf3c51, 0xf3e46, 0xf403b, 0xf424e, 0xf4443, 0xf4638,
						0xf484c, 0xf4a3f, 0xf4c52, 0xf4e48, 0xf503c, 0xf524f, 0xf5445, 0xf5639, 0xf584d, 0xf5a42, 0xf5c35, 0xf5e49,
						0xf603e, 0xf6251, 0xf6446, 0xf663b, 0xf684f, 0xf6a43, 0xf6c37, 0xf6e4b, 0xf703f, 0xf7252, 0xf7447, 0xf763c,
						0xf7850, 0xf7a45, 0xf7c39, 0xf7e4d, 0xf8042, 0xf8254, 0xf8449, 0xf863d, 0xf8851, 0xf8a46, 0xf8c3b, 0xf8e4f,
						0xf9044, 0xf9237, 0xf944a, 0xf963f, 0xf9853, 0xf9a47, 0xf9c3c, 0xf9e50, 0xfa045, 0xfa238, 0xfa44c, 0xfa641,
						0xfa836, 0xfaa49, 0xfac3d, 0xfae52, 0xfb047, 0xfb23a, 0xfb44e, 0xfb643, 0xfb837, 0xfba4a, 0xfbc3f, 0xfbe53,
						0xfc048, 0xfc23c, 0xfc450, 0xfc645, 0xfc839, 0xfca4c, 0xfcc41, 0xfce36, 0xfd04a, 0xfd23d, 0xfd451, 0xfd646,
						0xfd83a, 0xfda4d, 0xfdc43, 0xfde37, 0xfe04b, 0xfe23f, 0xfe453, 0xfe648, 0xfe83c, 0xfea4f, 0xfec44, 0xfee38,
						0xff04c, 0xff241, 0xff436, 0xff64a, 0xff83e, 0xffa51, 0xffc46, 0xffe3a, 0x10004e, 0x100242, 0x100437,
						0x10064b, 0x100841, 0x100a53, 0x100c48, 0x100e3c, 0x10104f, 0x101244, 0x101438, 0x10164c, 0x101842, 0x101a35,
						0x101c49, 0x101e3d, 0x102051, 0x102245, 0x10243a, 0x10264e, 0x102843, 0x102a37, 0x102c4b, 0x102e3f, 0x103053,
						0x103247, 0x10343b, 0x10364f, 0x103845, 0x103a38, 0x103c4c, 0x103e42, 0x104036, 0x104249, 0x10443d, 0x104651,
						0x104846, 0x104a3a, 0x104c4e, 0x104e43, 0x105038, 0x10524a, 0x10543e, 0x105652, 0x105847, 0x105a3b, 0x105c4f,
						0x105e45, 0x106039, 0x10624c, 0x106441, 0x106635, 0x106849, 0x106a3d, 0x106c51, 0x106e47, 0x10703c, 0x10724f,
						0x107444, 0x107638, 0x10784c, 0x107a3f, 0x107c53, 0x107e48
				};

			int days = lunar_month_days[lunar->lunarYear - lunar_month_days[0]];
			int leap = GetBitInt(days, 4, 13);
			int offset = 0;
			int loopend = leap;
			if (!lunar->isleap) {
				if (lunar->lunarMonth <= leap || leap == 0) {
					loopend = lunar->lunarMonth - 1;
				}
				else {
					loopend = lunar->lunarMonth;
				}
			}
			for (int i = 0; i < loopend; i++) {
				offset += GetBitInt(days, 1, 12 - i) == 1 ? 30 : 29;
			}
			offset += lunar->lunarDay;

			int solar11 = solar_1_1[lunar->lunarYear - solar_1_1[0]];

			int y = GetBitInt(solar11, 12, 9);
			int m = GetBitInt(solar11, 4, 5);
			int d = GetBitInt(solar11, 5, 0);

			return SolarFromInt(SolarToInt(y, m, d) + offset - 1);
		}

		Lunar^ SolarToLunar(Solar^ solar) {

			int lunar_month_days[] =
				{
						1887, 0x1694, 0x16aa, 0x4ad5, 0xab6, 0xc4b7, 0x4ae, 0xa56, 0xb52a,
						0x1d2a, 0xd54, 0x75aa, 0x156a, 0x1096d, 0x95c, 0x14ae, 0xaa4d, 0x1a4c, 0x1b2a, 0x8d55, 0xad4, 0x135a, 0x495d,
						0x95c, 0xd49b, 0x149a, 0x1a4a, 0xbaa5, 0x16a8, 0x1ad4, 0x52da, 0x12b6, 0xe937, 0x92e, 0x1496, 0xb64b, 0xd4a,
						0xda8, 0x95b5, 0x56c, 0x12ae, 0x492f, 0x92e, 0xcc96, 0x1a94, 0x1d4a, 0xada9, 0xb5a, 0x56c, 0x726e, 0x125c,
						0xf92d, 0x192a, 0x1a94, 0xdb4a, 0x16aa, 0xad4, 0x955b, 0x4ba, 0x125a, 0x592b, 0x152a, 0xf695, 0xd94, 0x16aa,
						0xaab5, 0x9b4, 0x14b6, 0x6a57, 0xa56, 0x1152a, 0x1d2a, 0xd54, 0xd5aa, 0x156a, 0x96c, 0x94ae, 0x14ae, 0xa4c,
						0x7d26, 0x1b2a, 0xeb55, 0xad4, 0x12da, 0xa95d, 0x95a, 0x149a, 0x9a4d, 0x1a4a, 0x11aa5, 0x16a8, 0x16d4,
						0xd2da, 0x12b6, 0x936, 0x9497, 0x1496, 0x1564b, 0xd4a, 0xda8, 0xd5b4, 0x156c, 0x12ae, 0xa92f, 0x92e, 0xc96,
						0x6d4a, 0x1d4a, 0x10d65, 0xb58, 0x156c, 0xb26d, 0x125c, 0x192c, 0x9a95, 0x1a94, 0x1b4a, 0x4b55, 0xad4,
						0xf55b, 0x4ba, 0x125a, 0xb92b, 0x152a, 0x1694, 0x96aa, 0x15aa, 0x12ab5, 0x974, 0x14b6, 0xca57, 0xa56, 0x1526,
						0x8e95, 0xd54, 0x15aa, 0x49b5, 0x96c, 0xd4ae, 0x149c, 0x1a4c, 0xbd26, 0x1aa6, 0xb54, 0x6d6a, 0x12da, 0x1695d,
						0x95a, 0x149a, 0xda4b, 0x1a4a, 0x1aa4, 0xbb54, 0x16b4, 0xada, 0x495b, 0x936, 0xf497, 0x1496, 0x154a, 0xb6a5,
						0xda4, 0x15b4, 0x6ab6, 0x126e, 0x1092f, 0x92e, 0xc96, 0xcd4a, 0x1d4a, 0xd64, 0x956c, 0x155c, 0x125c, 0x792e,
						0x192c, 0xfa95, 0x1a94, 0x1b4a, 0xab55, 0xad4, 0x14da, 0x8a5d, 0xa5a, 0x1152b, 0x152a, 0x1694, 0xd6aa,
						0x15aa, 0xab4, 0x94ba, 0x14b6, 0xa56, 0x7527, 0xd26, 0xee53, 0xd54, 0x15aa, 0xa9b5, 0x96c, 0x14ae, 0x8a4e,
						0x1a4c, 0x11d26, 0x1aa4, 0x1b54, 0xcd6a, 0xada, 0x95c, 0x949d, 0x149a, 0x1a2a, 0x5b25, 0x1aa4, 0xfb52,
						0x16b4, 0xaba, 0xa95b, 0x936, 0x1496, 0x9a4b, 0x154a, 0x136a5, 0xda4, 0x15ac
				};

			int solar_1_1[] =
				{
						1887, 0xec04c, 0xec23f, 0xec435, 0xec649, 0xec83e, 0xeca51, 0xecc46, 0xece3a,
						0xed04d, 0xed242, 0xed436, 0xed64a, 0xed83f, 0xeda53, 0xedc48, 0xede3d, 0xee050, 0xee244, 0xee439, 0xee64d,
						0xee842, 0xeea36, 0xeec4a, 0xeee3e, 0xef052, 0xef246, 0xef43a, 0xef64e, 0xef843, 0xefa37, 0xefc4b, 0xefe41,
						0xf0054, 0xf0248, 0xf043c, 0xf0650, 0xf0845, 0xf0a38, 0xf0c4d, 0xf0e42, 0xf1037, 0xf124a, 0xf143e, 0xf1651,
						0xf1846, 0xf1a3a, 0xf1c4e, 0xf1e44, 0xf2038, 0xf224b, 0xf243f, 0xf2653, 0xf2848, 0xf2a3b, 0xf2c4f, 0xf2e45,
						0xf3039, 0xf324d, 0xf3442, 0xf3636, 0xf384a, 0xf3a3d, 0xf3c51, 0xf3e46, 0xf403b, 0xf424e, 0xf4443, 0xf4638,
						0xf484c, 0xf4a3f, 0xf4c52, 0xf4e48, 0xf503c, 0xf524f, 0xf5445, 0xf5639, 0xf584d, 0xf5a42, 0xf5c35, 0xf5e49,
						0xf603e, 0xf6251, 0xf6446, 0xf663b, 0xf684f, 0xf6a43, 0xf6c37, 0xf6e4b, 0xf703f, 0xf7252, 0xf7447, 0xf763c,
						0xf7850, 0xf7a45, 0xf7c39, 0xf7e4d, 0xf8042, 0xf8254, 0xf8449, 0xf863d, 0xf8851, 0xf8a46, 0xf8c3b, 0xf8e4f,
						0xf9044, 0xf9237, 0xf944a, 0xf963f, 0xf9853, 0xf9a47, 0xf9c3c, 0xf9e50, 0xfa045, 0xfa238, 0xfa44c, 0xfa641,
						0xfa836, 0xfaa49, 0xfac3d, 0xfae52, 0xfb047, 0xfb23a, 0xfb44e, 0xfb643, 0xfb837, 0xfba4a, 0xfbc3f, 0xfbe53,
						0xfc048, 0xfc23c, 0xfc450, 0xfc645, 0xfc839, 0xfca4c, 0xfcc41, 0xfce36, 0xfd04a, 0xfd23d, 0xfd451, 0xfd646,
						0xfd83a, 0xfda4d, 0xfdc43, 0xfde37, 0xfe04b, 0xfe23f, 0xfe453, 0xfe648, 0xfe83c, 0xfea4f, 0xfec44, 0xfee38,
						0xff04c, 0xff241, 0xff436, 0xff64a, 0xff83e, 0xffa51, 0xffc46, 0xffe3a, 0x10004e, 0x100242, 0x100437,
						0x10064b, 0x100841, 0x100a53, 0x100c48, 0x100e3c, 0x10104f, 0x101244, 0x101438, 0x10164c, 0x101842, 0x101a35,
						0x101c49, 0x101e3d, 0x102051, 0x102245, 0x10243a, 0x10264e, 0x102843, 0x102a37, 0x102c4b, 0x102e3f, 0x103053,
						0x103247, 0x10343b, 0x10364f, 0x103845, 0x103a38, 0x103c4c, 0x103e42, 0x104036, 0x104249, 0x10443d, 0x104651,
						0x104846, 0x104a3a, 0x104c4e, 0x104e43, 0x105038, 0x10524a, 0x10543e, 0x105652, 0x105847, 0x105a3b, 0x105c4f,
						0x105e45, 0x106039, 0x10624c, 0x106441, 0x106635, 0x106849, 0x106a3d, 0x106c51, 0x106e47, 0x10703c, 0x10724f,
						0x107444, 0x107638, 0x10784c, 0x107a3f, 0x107c53, 0x107e48
				};

			Lunar^ lunar=gcnew Lunar();
			int index = solar->solarYear - solar_1_1[0];
			int data = (solar->solarYear << 9) | (solar->solarMonth << 5) | (solar->solarDay);
			int solar11 = 0;
			if (solar_1_1[index] > data) {
				index--;
			}
			solar11 = solar_1_1[index];
			int y = GetBitInt(solar11, 12, 9);
			int m = GetBitInt(solar11, 4, 5);
			int d = GetBitInt(solar11, 5, 0);
			long offset = SolarToInt(solar->solarYear, solar->solarMonth, solar->solarDay) - SolarToInt(y, m, d);

			int days = lunar_month_days[index];
			int leap = GetBitInt(days, 4, 13);

			int lunarY = index + solar_1_1[0];
			int lunarM = 1;
			int lunarD;
			offset += 1;

			for (int i = 0; i < 13; i++) {
				int dm = GetBitInt(days, 1, 12 - i) == 1 ? 30 : 29;
				if (offset > dm) {
					lunarM++;
					offset -= dm;
				}else {
					break;
				}
			}
			lunarD = (int) (offset);
			lunar->lunarYear = lunarY;
			lunar->lunarMonth = lunarM;
			lunar->isleap = false;
			if (leap != 0 && lunarM > leap) {
				lunar->lunarMonth = lunarM - 1;
				if (lunarM == leap + 1) {
					lunar->isleap = true;
				}
			}
			lunar->lunarDay = lunarD;
			return lunar;
		}
	//---------------------Lunar to Solar---------------------------
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dayLbl = (gcnew System::Windows::Forms::Label());
			this->enterPic = (gcnew System::Windows::Forms::PictureBox());
			this->leavePic = (gcnew System::Windows::Forms::PictureBox());
			this->todayPic = (gcnew System::Windows::Forms::PictureBox());
			this->markLeavePic = (gcnew System::Windows::Forms::PictureBox());
			this->markEnterPic = (gcnew System::Windows::Forms::PictureBox());
			this->markTodayPic = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->enterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->leavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->todayPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markLeavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markEnterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markTodayPic))->BeginInit();
			this->SuspendLayout();
			// 
			// dayLbl
			// 
			this->dayLbl->BackColor = System::Drawing::Color::Transparent;
			this->dayLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->dayLbl->Location = System::Drawing::Point(0, 0);
			this->dayLbl->Name = L"dayLbl";
			this->dayLbl->Size = System::Drawing::Size(50, 50);
			this->dayLbl->TabIndex = 0;
			this->dayLbl->Text = L"30";
			this->dayLbl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->dayLbl->MouseLeave += gcnew System::EventHandler(this, &DayControl::dayLbl_MouseLeave);
			this->dayLbl->Click += gcnew System::EventHandler(this, &DayControl::dayLbl_Click);
			this->dayLbl->MouseEnter += gcnew System::EventHandler(this, &DayControl::dayLbl_MouseEnter);
			// 
			// enterPic
			// 
			this->enterPic->BackColor = System::Drawing::Color::Transparent;
			this->enterPic->Location = System::Drawing::Point(112, 152);
			this->enterPic->Name = L"enterPic";
			this->enterPic->Size = System::Drawing::Size(50, 50);
			this->enterPic->TabIndex = 3;
			this->enterPic->TabStop = false;
			this->enterPic->Visible = false;
			// 
			// leavePic
			// 
			this->leavePic->BackColor = System::Drawing::Color::Transparent;
			this->leavePic->Location = System::Drawing::Point(180, 152);
			this->leavePic->Name = L"leavePic";
			this->leavePic->Size = System::Drawing::Size(50, 50);
			this->leavePic->TabIndex = 3;
			this->leavePic->TabStop = false;
			this->leavePic->Visible = false;
			// 
			// todayPic
			// 
			this->todayPic->BackColor = System::Drawing::Color::Transparent;
			this->todayPic->Location = System::Drawing::Point(245, 152);
			this->todayPic->Name = L"todayPic";
			this->todayPic->Size = System::Drawing::Size(50, 50);
			this->todayPic->TabIndex = 3;
			this->todayPic->TabStop = false;
			this->todayPic->Visible = false;
			// 
			// markLeavePic
			// 
			this->markLeavePic->BackColor = System::Drawing::Color::Transparent;
			this->markLeavePic->Location = System::Drawing::Point(311, 152);
			this->markLeavePic->Name = L"markLeavePic";
			this->markLeavePic->Size = System::Drawing::Size(50, 50);
			this->markLeavePic->TabIndex = 3;
			this->markLeavePic->TabStop = false;
			this->markLeavePic->Visible = false;
			// 
			// markEnterPic
			// 
			this->markEnterPic->BackColor = System::Drawing::Color::Transparent;
			this->markEnterPic->Location = System::Drawing::Point(311, 220);
			this->markEnterPic->Name = L"markEnterPic";
			this->markEnterPic->Size = System::Drawing::Size(50, 50);
			this->markEnterPic->TabIndex = 3;
			this->markEnterPic->TabStop = false;
			this->markEnterPic->Visible = false;
			// 
			// markTodayPic
			// 
			this->markTodayPic->BackColor = System::Drawing::Color::Transparent;
			this->markTodayPic->Location = System::Drawing::Point(245, 220);
			this->markTodayPic->Name = L"markTodayPic";
			this->markTodayPic->Size = System::Drawing::Size(50, 50);
			this->markTodayPic->TabIndex = 3;
			this->markTodayPic->TabStop = false;
			this->markTodayPic->Visible = false;
			// 
			// DayControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Transparent;
			this->Controls->Add(this->markTodayPic);
			this->Controls->Add(this->markEnterPic);
			this->Controls->Add(this->markLeavePic);
			this->Controls->Add(this->todayPic);
			this->Controls->Add(this->leavePic);
			this->Controls->Add(this->enterPic);
			this->Controls->Add(this->dayLbl);
			this->Name = L"DayControl";
			this->Size = System::Drawing::Size(419, 447);
			this->Load += gcnew System::EventHandler(this, &DayControl::DayControl_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->enterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->leavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->todayPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markLeavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markEnterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->markTodayPic))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void DayControl_Load(System::Object^  sender, System::EventArgs^  e) {
			
		 }
private: System::Void dayLbl_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->clickedDay();
		 }
private: System::Void dayLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->mouseEnterInControl();
		 }
private: System::Void dayLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->mouseLeaveFromControl();
		 }
};
}
