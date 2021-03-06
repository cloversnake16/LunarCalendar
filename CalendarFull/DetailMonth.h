#pragma once

#include "DayControl.h"
#include "NumInputDialog.h"
#include "global.h"
#include "PopupForm.h"
#include "GotoDialog.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace CalendarFull {

	/// <summary>
	/// Summary for DetailMonth
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class DetailMonth : public System::Windows::Forms::Form
	{
	public:
		DetailMonth(void)
		{
			//
			//TODO: Add the constructor code here
			//				
		}
		
		DetailMonth(Form^ newAddr, int curMonth){
			this->parentAddr=newAddr;
			global::curMonth=curMonth;
			InitializeComponent();	
			this->dayArray=gcnew ArrayList();
			this->lineArray=gcnew ArrayList();
		}
		
	private: System::Windows::Forms::Label^  gotoLbl;	
	private: System::Windows::Forms::PictureBox^  minLeavePic;
	private: System::Windows::Forms::PictureBox^  maxLeavePic;
	private: System::Windows::Forms::PictureBox^  minenterPic;
	private: System::Windows::Forms::PictureBox^  maxEnterPic;
	private: System::Windows::Forms::PictureBox^  closeLeavePic;
	private: System::Windows::Forms::PictureBox^  closeEnterPic;
	private: System::Windows::Forms::PictureBox^  minPic;
	private: System::Windows::Forms::PictureBox^  maxPic;
	private: System::Windows::Forms::PictureBox^  searchPic;
	private: System::Windows::Forms::TextBox^  findTxt;

	private: System::Windows::Forms::Label^  addLbl;
	private: System::Windows::Forms::PictureBox^  closePic;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  searchEnterPic;
	private: System::Windows::Forms::PictureBox^  searchLeavePic;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;

	private: System::Windows::Forms::Label^  todayLbl;

	public: 
			 Form^ parentAddr;			
		void configureDetailMonth(){	
			this->monthMarkLbl->Text=Convert::ToString(global::curMonth)+L"月";

			String^ yearStr;
			String^ monthStr;
			yearStr=L"年"; monthStr=L"月";
			this->backLbl->Text="<"+Convert::ToString(global::curYear)+yearStr;
			array<String^>^ dayArray=gcnew array<String^>(7);
			dayArray[0]=L"日";
			dayArray[1]=L"一";
			dayArray[2]=L"二";
			dayArray[3]=L"三";
			dayArray[4]=L"四";
			dayArray[5]=L"五";
			dayArray[6]=L"六";
			
			Label^ tmp;
			//configure day label
			for(int i=0;i<7;++i){
				tmp=gcnew Label();
				tmp->Size=System::Drawing::Size(this->newSize,(int)(this->newSize*3/4));
				//tmp->BorderStyle=System::Windows::Forms::BorderStyle::FixedSingle;
				tmp->Location=System::Drawing::Point(this->gapX*2+i*(this->newSize+this->gapX),20*this->fontRatio);
				if(this->fontRatio<=0) this->fontRatio=1;
				tmp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8*this->fontRatio, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				tmp->AutoSize=false;
				tmp->ForeColor = System::Drawing::Color::Blue;	
				tmp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				tmp->Text=dayArray[i];
				this->dayArray->Add(tmp);
				this->Controls->Add(tmp);
			}

			int dayNum=this->numberOfDay(global::curYear,global::curMonth,1);
			DayControl^ dayControl;
			int dx,dy,rn,cn,startX, startY;
			for(int dd=0;dd<DateTime::DaysInMonth(global::curYear,global::curMonth);++dd){	
				dayControl=gcnew DayControl(global::curYear,global::curMonth,dd+1,this->newSize);			
				dayControl->configureDay();
				
				rn=(dd+dayNum)%7;
				cn=(int)(dd+dayNum)/7;
				dx=rn*(this->newSize+this->gapX)+this->gapX*2;
				dy=cn*(this->newSize+this->gapY)+this->newSize*3/4+20*this->fontRatio+4;		

				if(dd==0 || rn==0){startX=dx; startY=dy;}
				
				if(rn==6 || dd==DateTime::DaysInMonth(global::curYear,global::curMonth)-1){
					Panel^ line=gcnew Panel();
					line->BackColor = System::Drawing::Color::White;
					line->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;	
					startY=startY-2;
					line->Location = System::Drawing::Point(startX, startY);
					line->Size = System::Drawing::Size(dx-startX+this->newSize,1);
					this->lineArray->Add(line);
					this->Controls->Add(line);
				}

				dayControl->Location=System::Drawing::Point(dx, dy);
				dayControl->AutoSize=false;
				
				this->dayArray->Add(dayControl);
				this->Controls->Add(dayControl);	
			}
		}

		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DetailMonth()
		{
			if (components)
			{
				delete components;
			}
		}

	private :
		float fontRatio;
		int downFlag, downX, downY, sizeFlag, newWid, newHei;
		int countTime, cx,cy,px,py,gapX,gapY, newSize;
		ArrayList^ dayArray,^lineArray;

		void resetDayControl(){		
			if(this->dayArray==nullptr || this->lineArray==nullptr) return;
			IEnumerator^ dayEnums=this->dayArray->GetEnumerator();			
			while(dayEnums->MoveNext()){
				Control^ tmpDay=safe_cast<Control^> (dayEnums->Current);
				this->Controls->Remove(tmpDay);
			}
			IEnumerator^ lineEnum=this->lineArray->GetEnumerator();			
			while(lineEnum->MoveNext()){
				Panel^ line=safe_cast<Panel^> (lineEnum->Current);
				this->Controls->Remove(line);
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

		void gotoPreviousMonth(){
			 if(global::curYear>1){				
			 	if(global::curMonth<=1){
			 		global::curMonth=12;
					--global::curYear;
			 	}else{
			 		--global::curMonth;
			 	}
			 }			 
			 this->resetDayControl();
			 this->configureDetailMonth();
		}

		void gotoNextMonth(){
			 if(global::curMonth>=12){
				 ++global::curYear;
				 global::curMonth=1;
			 }else{
				 ++global::curMonth;
			 }			 
			 this->resetDayControl();
			 this->configureDetailMonth();
		}
    private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::NotifyIcon^  sleepNotify;
	private: System::Windows::Forms::ContextMenuStrip^  trayContextMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  showMI;
	private: System::Windows::Forms::ToolStripSeparator^  sepMI;
	private: System::Windows::Forms::ToolStripMenuItem^  exitMI;	
	private: System::Windows::Forms::Panel^  titlePanel;
	private: System::Windows::Forms::Label^  backLbl;


	private: System::Windows::Forms::Label^  monthMarkLbl;
	private: System::Windows::Forms::Label^  prevMonth;
	private: System::Windows::Forms::Label^  nextMonth;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		
		
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(DetailMonth::typeid));
			this->titlePanel = (gcnew System::Windows::Forms::Panel());
			this->minPic = (gcnew System::Windows::Forms::PictureBox());
			this->monthMarkLbl = (gcnew System::Windows::Forms::Label());
			this->maxPic = (gcnew System::Windows::Forms::PictureBox());
			this->searchPic = (gcnew System::Windows::Forms::PictureBox());
			this->prevMonth = (gcnew System::Windows::Forms::Label());
			this->nextMonth = (gcnew System::Windows::Forms::Label());
			this->findTxt = (gcnew System::Windows::Forms::TextBox());
			this->gotoLbl = (gcnew System::Windows::Forms::Label());
			this->addLbl = (gcnew System::Windows::Forms::Label());
			this->backLbl = (gcnew System::Windows::Forms::Label());
			this->closePic = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->sleepNotify = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->trayContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->showMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sepMI = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->minLeavePic = (gcnew System::Windows::Forms::PictureBox());
			this->maxLeavePic = (gcnew System::Windows::Forms::PictureBox());
			this->minenterPic = (gcnew System::Windows::Forms::PictureBox());
			this->maxEnterPic = (gcnew System::Windows::Forms::PictureBox());
			this->closeLeavePic = (gcnew System::Windows::Forms::PictureBox());
			this->closeEnterPic = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->searchEnterPic = (gcnew System::Windows::Forms::PictureBox());
			this->searchLeavePic = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->todayLbl = (gcnew System::Windows::Forms::Label());
			this->titlePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closePic))->BeginInit();
			this->trayContextMenu->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minLeavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxLeavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minenterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxEnterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closeLeavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closeEnterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchEnterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchLeavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->BeginInit();
			this->SuspendLayout();
			// 
			// titlePanel
			// 
			this->titlePanel->BackColor = System::Drawing::SystemColors::Control;
			this->titlePanel->Controls->Add(this->minPic);
			this->titlePanel->Controls->Add(this->monthMarkLbl);
			this->titlePanel->Controls->Add(this->maxPic);
			this->titlePanel->Controls->Add(this->searchPic);
			this->titlePanel->Controls->Add(this->prevMonth);
			this->titlePanel->Controls->Add(this->nextMonth);
			this->titlePanel->Controls->Add(this->findTxt);
			this->titlePanel->Controls->Add(this->gotoLbl);
			this->titlePanel->Controls->Add(this->addLbl);
			this->titlePanel->Controls->Add(this->backLbl);
			this->titlePanel->Controls->Add(this->closePic);
			this->titlePanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->titlePanel->Location = System::Drawing::Point(0, 0);
			this->titlePanel->Name = L"titlePanel";
			this->titlePanel->Size = System::Drawing::Size(405, 20);
			this->titlePanel->TabIndex = 0;
			this->titlePanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &DetailMonth::titlePanel_MouseMove);
			this->titlePanel->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &DetailMonth::titlePanel_MouseDoubleClick);
			this->titlePanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &DetailMonth::titlePanel_MouseDown);
			this->titlePanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &DetailMonth::titlePanel_MouseUp);
			// 
			// minPic
			// 
			this->minPic->Location = System::Drawing::Point(321, 0);
			this->minPic->Name = L"minPic";
			this->minPic->Size = System::Drawing::Size(20, 20);
			this->minPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->minPic->TabIndex = 21;
			this->minPic->TabStop = false;
			this->minPic->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::minPic_MouseLeave);
			this->minPic->Click += gcnew System::EventHandler(this, &DetailMonth::minPic_Click);
			this->minPic->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::minPic_MouseEnter);
			// 
			// monthMarkLbl
			// 
			this->monthMarkLbl->AutoSize = true;
			this->monthMarkLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->monthMarkLbl->ForeColor = System::Drawing::Color::Red;
			this->monthMarkLbl->Location = System::Drawing::Point(142, 0);
			this->monthMarkLbl->Name = L"monthMarkLbl";
			this->monthMarkLbl->Size = System::Drawing::Size(43, 20);
			this->monthMarkLbl->TabIndex = 0;
			this->monthMarkLbl->Text = L"10月";
			this->monthMarkLbl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// maxPic
			// 
			this->maxPic->Location = System::Drawing::Point(347, 0);
			this->maxPic->Name = L"maxPic";
			this->maxPic->Size = System::Drawing::Size(20, 20);
			this->maxPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->maxPic->TabIndex = 22;
			this->maxPic->TabStop = false;
			this->maxPic->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::maxPic_MouseLeave);
			this->maxPic->Click += gcnew System::EventHandler(this, &DetailMonth::maxPic_Click);
			this->maxPic->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::maxPic_MouseEnter);
			// 
			// searchPic
			// 
			this->searchPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"searchPic.Image")));
			this->searchPic->Location = System::Drawing::Point(278, 0);
			this->searchPic->Name = L"searchPic";
			this->searchPic->Size = System::Drawing::Size(20, 20);
			this->searchPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->searchPic->TabIndex = 23;
			this->searchPic->TabStop = false;
			this->searchPic->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::searchPic_MouseLeave);
			this->searchPic->Click += gcnew System::EventHandler(this, &DetailMonth::searchPic_Click);
			this->searchPic->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::searchPic_MouseEnter);
			// 
			// prevMonth
			// 
			this->prevMonth->AutoSize = true;
			this->prevMonth->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->prevMonth->ForeColor = System::Drawing::Color::Red;
			this->prevMonth->Location = System::Drawing::Point(113, 0);
			this->prevMonth->Name = L"prevMonth";
			this->prevMonth->Size = System::Drawing::Size(19, 20);
			this->prevMonth->TabIndex = 0;
			this->prevMonth->Text = L"<";
			this->prevMonth->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->prevMonth->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::prevMonth_MouseLeave);
			this->prevMonth->Click += gcnew System::EventHandler(this, &DetailMonth::prevMonth_Click);
			this->prevMonth->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::prevMonth_MouseEnter);
			// 
			// nextMonth
			// 
			this->nextMonth->AutoSize = true;
			this->nextMonth->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->nextMonth->ForeColor = System::Drawing::Color::Red;
			this->nextMonth->Location = System::Drawing::Point(197, 0);
			this->nextMonth->Name = L"nextMonth";
			this->nextMonth->Size = System::Drawing::Size(19, 20);
			this->nextMonth->TabIndex = 0;
			this->nextMonth->Text = L">";
			this->nextMonth->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->nextMonth->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::nextMonth_MouseLeave);
			this->nextMonth->Click += gcnew System::EventHandler(this, &DetailMonth::nextMonth_Click);
			this->nextMonth->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::nextMonth_MouseEnter);
			// 
			// findTxt
			// 
			this->findTxt->Font = (gcnew System::Drawing::Font(L"SimSun", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->findTxt->Location = System::Drawing::Point(223, 0);
			this->findTxt->Name = L"findTxt";
			this->findTxt->Size = System::Drawing::Size(49, 22);
			this->findTxt->TabIndex = 20;
			this->findTxt->Visible = false;
			this->findTxt->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &DetailMonth::findTxt_KeyPress);
			// 
			// gotoLbl
			// 
			this->gotoLbl->AutoSize = true;
			this->gotoLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gotoLbl->ForeColor = System::Drawing::Color::Red;
			this->gotoLbl->Location = System::Drawing::Point(96, 0);
			this->gotoLbl->Name = L"gotoLbl";
			this->gotoLbl->Size = System::Drawing::Size(15, 20);
			this->gotoLbl->TabIndex = 3;
			this->gotoLbl->Text = L"↓";
			this->gotoLbl->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::gotoLbl_MouseLeave);
			this->gotoLbl->Click += gcnew System::EventHandler(this, &DetailMonth::gotoLbl_Click);
			this->gotoLbl->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::gotoLbl_MouseEnter);
			// 
			// addLbl
			// 
			this->addLbl->AutoSize = true;
			this->addLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->addLbl->ForeColor = System::Drawing::Color::Red;
			this->addLbl->Location = System::Drawing::Point(304, 0);
			this->addLbl->Name = L"addLbl";
			this->addLbl->Size = System::Drawing::Size(18, 20);
			this->addLbl->TabIndex = 11;
			this->addLbl->Text = L"+";
			this->addLbl->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::addLbl_MouseLeave);
			this->addLbl->Click += gcnew System::EventHandler(this, &DetailMonth::addLbl_Click);
			this->addLbl->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::addLbl_MouseEnter);
			// 
			// backLbl
			// 
			this->backLbl->AutoSize = true;
			this->backLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->backLbl->ForeColor = System::Drawing::Color::Red;
			this->backLbl->Location = System::Drawing::Point(32, 0);
			this->backLbl->Name = L"backLbl";
			this->backLbl->Size = System::Drawing::Size(70, 20);
			this->backLbl->TabIndex = 0;
			this->backLbl->Text = L"<2008年";
			this->backLbl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->backLbl->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::backLbl_MouseLeave);
			this->backLbl->Click += gcnew System::EventHandler(this, &DetailMonth::backLbl_Click);
			this->backLbl->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::backLbl_MouseEnter);
			// 
			// closePic
			// 
			this->closePic->Location = System::Drawing::Point(373, 0);
			this->closePic->Name = L"closePic";
			this->closePic->Size = System::Drawing::Size(20, 20);
			this->closePic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->closePic->TabIndex = 24;
			this->closePic->TabStop = false;
			this->closePic->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::closePic_MouseLeave);
			this->closePic->Click += gcnew System::EventHandler(this, &DetailMonth::closePic_Click);
			this->closePic->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::closePic_MouseEnter);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &DetailMonth::timer1_Tick);
			// 
			// sleepNotify
			// 
			this->sleepNotify->ContextMenuStrip = this->trayContextMenu;
			this->sleepNotify->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"sleepNotify.Icon")));
			this->sleepNotify->Text = L"Calendar";
			this->sleepNotify->DoubleClick += gcnew System::EventHandler(this, &DetailMonth::sleepNotify_DoubleClick);
			// 
			// trayContextMenu
			// 
			this->trayContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->showMI, this->sepMI, 
				this->exitMI});
			this->trayContextMenu->Name = L"trayContextMenu";
			this->trayContextMenu->Size = System::Drawing::Size(101, 54);
			// 
			// showMI
			// 
			this->showMI->Name = L"showMI";
			this->showMI->Size = System::Drawing::Size(100, 22);
			this->showMI->Text = L"显示";
			this->showMI->Click += gcnew System::EventHandler(this, &DetailMonth::showMI_Click);
			// 
			// sepMI
			// 
			this->sepMI->Name = L"sepMI";
			this->sepMI->Size = System::Drawing::Size(97, 6);
			// 
			// exitMI
			// 
			this->exitMI->Name = L"exitMI";
			this->exitMI->Size = System::Drawing::Size(100, 22);
			this->exitMI->Text = L"出口";
			this->exitMI->Click += gcnew System::EventHandler(this, &DetailMonth::exitMI_Click);
			// 
			// minLeavePic
			// 
			this->minLeavePic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"minLeavePic.Image")));
			this->minLeavePic->Location = System::Drawing::Point(934, 523);
			this->minLeavePic->Name = L"minLeavePic";
			this->minLeavePic->Size = System::Drawing::Size(28, 30);
			this->minLeavePic->TabIndex = 8;
			this->minLeavePic->TabStop = false;
			this->minLeavePic->Visible = false;
			// 
			// maxLeavePic
			// 
			this->maxLeavePic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"maxLeavePic.Image")));
			this->maxLeavePic->Location = System::Drawing::Point(968, 523);
			this->maxLeavePic->Name = L"maxLeavePic";
			this->maxLeavePic->Size = System::Drawing::Size(28, 30);
			this->maxLeavePic->TabIndex = 9;
			this->maxLeavePic->TabStop = false;
			this->maxLeavePic->Visible = false;
			// 
			// minenterPic
			// 
			this->minenterPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"minenterPic.Image")));
			this->minenterPic->Location = System::Drawing::Point(934, 576);
			this->minenterPic->Name = L"minenterPic";
			this->minenterPic->Size = System::Drawing::Size(28, 30);
			this->minenterPic->TabIndex = 10;
			this->minenterPic->TabStop = false;
			this->minenterPic->Visible = false;
			// 
			// maxEnterPic
			// 
			this->maxEnterPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"maxEnterPic.Image")));
			this->maxEnterPic->Location = System::Drawing::Point(968, 576);
			this->maxEnterPic->Name = L"maxEnterPic";
			this->maxEnterPic->Size = System::Drawing::Size(28, 30);
			this->maxEnterPic->TabIndex = 5;
			this->maxEnterPic->TabStop = false;
			this->maxEnterPic->Visible = false;
			// 
			// closeLeavePic
			// 
			this->closeLeavePic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"closeLeavePic.Image")));
			this->closeLeavePic->Location = System::Drawing::Point(1002, 523);
			this->closeLeavePic->Name = L"closeLeavePic";
			this->closeLeavePic->Size = System::Drawing::Size(28, 30);
			this->closeLeavePic->TabIndex = 6;
			this->closeLeavePic->TabStop = false;
			this->closeLeavePic->Visible = false;
			// 
			// closeEnterPic
			// 
			this->closeEnterPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"closeEnterPic.Image")));
			this->closeEnterPic->Location = System::Drawing::Point(1002, 576);
			this->closeEnterPic->Name = L"closeEnterPic";
			this->closeEnterPic->Size = System::Drawing::Size(28, 30);
			this->closeEnterPic->TabIndex = 7;
			this->closeEnterPic->TabStop = false;
			this->closeEnterPic->Visible = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(172, 176);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(28, 30);
			this->pictureBox1->TabIndex = 19;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(206, 176);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(28, 30);
			this->pictureBox2->TabIndex = 18;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Visible = false;
			// 
			// searchEnterPic
			// 
			this->searchEnterPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"searchEnterPic.Image")));
			this->searchEnterPic->Location = System::Drawing::Point(138, 227);
			this->searchEnterPic->Name = L"searchEnterPic";
			this->searchEnterPic->Size = System::Drawing::Size(28, 30);
			this->searchEnterPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->searchEnterPic->TabIndex = 12;
			this->searchEnterPic->TabStop = false;
			this->searchEnterPic->Visible = false;
			// 
			// searchLeavePic
			// 
			this->searchLeavePic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"searchLeavePic.Image")));
			this->searchLeavePic->Location = System::Drawing::Point(172, 227);
			this->searchLeavePic->Name = L"searchLeavePic";
			this->searchLeavePic->Size = System::Drawing::Size(28, 30);
			this->searchLeavePic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->searchLeavePic->TabIndex = 14;
			this->searchLeavePic->TabStop = false;
			this->searchLeavePic->Visible = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(138, 123);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(28, 30);
			this->pictureBox3->TabIndex = 16;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Visible = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(172, 123);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(28, 30);
			this->pictureBox4->TabIndex = 15;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Visible = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(138, 176);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(28, 30);
			this->pictureBox5->TabIndex = 13;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Visible = false;
			// 
			// pictureBox6
			// 
			this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox6.Image")));
			this->pictureBox6->Location = System::Drawing::Point(206, 123);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(28, 30);
			this->pictureBox6->TabIndex = 17;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Visible = false;
			// 
			// todayLbl
			// 
			this->todayLbl->AutoSize = true;
			this->todayLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->todayLbl->ForeColor = System::Drawing::Color::Red;
			this->todayLbl->Location = System::Drawing::Point(33, 278);
			this->todayLbl->Name = L"todayLbl";
			this->todayLbl->Size = System::Drawing::Size(31, 13);
			this->todayLbl->TabIndex = 2;
			this->todayLbl->Text = L"今天";
			this->todayLbl->MouseLeave += gcnew System::EventHandler(this, &DetailMonth::todayLbl_MouseLeave);
			this->todayLbl->Click += gcnew System::EventHandler(this, &DetailMonth::todayLbl_Click);
			this->todayLbl->MouseEnter += gcnew System::EventHandler(this, &DetailMonth::todayLbl_MouseEnter);
			// 
			// DetailMonth
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(405, 300);
			this->Controls->Add(this->todayLbl);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->searchEnterPic);
			this->Controls->Add(this->searchLeavePic);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->titlePanel);
			this->Controls->Add(this->minLeavePic);
			this->Controls->Add(this->closeEnterPic);
			this->Controls->Add(this->maxLeavePic);
			this->Controls->Add(this->minenterPic);
			this->Controls->Add(this->maxEnterPic);
			this->Controls->Add(this->closeLeavePic);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"DetailMonth";
			this->Text = L"日历";
			this->Deactivate += gcnew System::EventHandler(this, &DetailMonth::DetailMonth_Deactivate);
			this->Load += gcnew System::EventHandler(this, &DetailMonth::DetailMonth_Load);
			this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &DetailMonth::DetailMonth_MouseScroll);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &DetailMonth::DetailMonth_MouseUp);
			this->Activated += gcnew System::EventHandler(this, &DetailMonth::DetailMonth_Activated);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &DetailMonth::DetailMonth_FormClosed);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &DetailMonth::DetailMonth_MouseDown);
			this->Resize += gcnew System::EventHandler(this, &DetailMonth::DetailMonth_Resize);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &DetailMonth::DetailMonth_MouseMove);
			this->titlePanel->ResumeLayout(false);
			this->titlePanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closePic))->EndInit();
			this->trayContextMenu->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minLeavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxLeavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minenterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxEnterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closeLeavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closeEnterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchEnterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchLeavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void DetailMonth_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 Application::Exit();
		 } 

private: System::Void backLbl_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Hide();
			 global::relaodFlag=1;
			 this->parentAddr->Show();
			 this->timer1->Enabled=false;
		 }
private: System::Void backLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->backLbl->ForeColor=System::Drawing::Color::Blue;
		 }
private: System::Void backLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->backLbl->ForeColor=System::Drawing::Color::Red;
		 }

private: System::Void searchPic_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->findTxt->Visible=this->searchPic->Visible;
			 this->searchPic->Visible=!this->searchPic->Visible;
			 this->findTxt->Focus();
			 //PopupForm^ pp=gcnew PopupForm(System::Windows::Forms::Cursor::Position.X,System::Windows::Forms::Cursor::Position.Y);	
			 //pp->StartPosition=FormStartPosition::Manual;
			 //pp->ShowDialog(this);
			 //if(pp->DialogResult==System::Windows::Forms::DialogResult::OK){
			 //	this->resetDayControl();
			 //	this->configureDetailMonth();
			 // }			 
		 }
private: System::Void searchPic_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->searchPic->Image=this->searchEnterPic->Image;
		 }
private: System::Void searchPic_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->searchPic->Image=this->searchLeavePic->Image;
		 }

private: System::Void prevMonth_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->gotoPreviousMonth();
		 }
private: System::Void prevMonth_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->prevMonth->ForeColor=System::Drawing::Color::Blue;
		 }
private: System::Void prevMonth_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->prevMonth->ForeColor=System::Drawing::Color::Red;
		 }

private: System::Void nextMonth_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->gotoNextMonth();
		 }
private: System::Void nextMonth_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->nextMonth->ForeColor=System::Drawing::Color::Blue;
		 }
private: System::Void nextMonth_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->nextMonth->ForeColor=System::Drawing::Color::Red;
		 }

private: System::Void addLbl_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->searchPic->Visible=this->findTxt->Visible;
			 this->findTxt->Visible=!this->findTxt->Visible;
			 this->findTxt->Focus();
			 //NumInputDialog^ numDlg=gcnew NumInputDialog();
			 //numDlg->StartPosition=FormStartPosition::CenterParent;
			 //numDlg->ShowDialog(this);
			 //if(numDlg->DialogResult==System::Windows::Forms::DialogResult::OK){
			//	 global::timeOut=Convert::ToInt32(numDlg->numTxt->Text);
			 //}
		 }
private: System::Void addLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->addLbl->ForeColor=System::Drawing::Color::Blue;
		 }
private: System::Void addLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->addLbl->ForeColor=System::Drawing::Color::Red;
		 }

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 ++this->countTime;			 
			 this->cx=System::Windows::Forms::Cursor::Position.X;
			 this->cy=System::Windows::Forms::Cursor::Position.Y;
			 if(this->cx!=this->px || this->cy!=this->py )this->countTime=0;
			 if(global::timeOut==this->countTime && global::timeOut>0){
				 //MessageBox::Show(Convert::ToString(this->sleepTime)+"-"+Convert::ToString(this->countTime));
				 this->Hide();
				 this->sleepNotify->Visible=true;
				 this->timer1->Enabled=false;
				 this->countTime=0;

				 this->sleepNotify->BalloonTipText=L"这是"+Convert::ToString(global::timeOut)+L"秒后消失。";
				 //L"这是"+Convert::ToString(this->sleepTime)+L"秒后消失。";
				 this->sleepNotify->BalloonTipTitle=L"您好吗";
				 //L"您好吗";
				 this->sleepNotify->ShowBalloonTip(2000);
			 }
			 this->px=this->cx;this->py=this->cy;
		 }

private: System::Void showMI_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Visible=true;
			 this->sleepNotify->Visible=false;
			 this->timer1->Enabled=true;
		 }
private: System::Void exitMI_Click(System::Object^  sender, System::EventArgs^  e) {
			 Application::Exit();
		 }
private: System::Void sleepNotify_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
			 this->Visible=true;
			 this->sleepNotify->Visible=false;
			 this->timer1->Enabled=true;
		 }

private: System::Void DetailMonth_Resize(System::Object^  sender, System::EventArgs^  e) {
			 if(this->Width<405 && this->Height<305){
				 this->Opacity=0.5f;
			 }else{
				 this->Opacity=1.0f;
			 }			 
			 if(this->Width<405) this->Width=400;
			 if(this->Height<305) this->Height=300;	

			 int tmpWid, tmpHei,realHei;
			 realHei=this->Height-24;
			 tmpWid=(int) this->Width/7;
			 tmpHei=(int) realHei/8;
			 this->newSize=tmpWid>tmpHei ? tmpHei : tmpWid;
			 //MessageBox::Show(Convert::ToString(this->newSize));
			 this->fontRatio=(float)this->newSize/33;
			 if(this->fontRatio<1.0) this->fontRatio=1.0f;
			
			 //set gapX, gapY
			 this->gapX=(int)(this->Width-this->newSize*7)/10;
			 this->gapY=4;
			 //header
			 this->titlePanel->Height=(int)(20*this->fontRatio);
			 this->backLbl->Height=(int)(20*this->fontRatio);
			 this->backLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->gotoLbl->Height=(int)(20*this->fontRatio);
			 this->gotoLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->prevMonth->Height=(int)(20*this->fontRatio);
			 this->prevMonth->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->nextMonth->Height=(int)(20*this->fontRatio);
			 this->nextMonth->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->monthMarkLbl->Height=(int)(20*this->fontRatio);
			 this->monthMarkLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->addLbl->Height=(int)(20*this->fontRatio);
			 this->addLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->todayLbl->Height=(int)(20*this->fontRatio);
			 this->todayLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->findTxt->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->findTxt->Width=(int)(this->findTxt->Height*1.5);
			 this->findTxt->Top=(int)((this->titlePanel->Height-this->findTxt->Height)/2);

			 this->searchPic->Width=(int)(15*this->fontRatio);
			 this->searchPic->Height=this->searchPic->Width;
			 this->searchPic->Top=(int)(this->titlePanel->Height-this->searchPic->Height)/2;
			 this->minPic->Width=(int)(15*this->fontRatio);
			 this->minPic->Height=this->minPic->Width;
			 this->minPic->Top=(int)(this->titlePanel->Height-this->minPic->Height)/2;
			 this->maxPic->Width=(int)(15*this->fontRatio);
			 this->maxPic->Height=this->maxPic->Width;
			 this->maxPic->Top=(int)(this->titlePanel->Height-this->maxPic->Height)/2;
			 this->closePic->Width=(int)(15*this->fontRatio);
			 this->closePic->Height=this->closePic->Width;
			 this->closePic->Top=(int)(this->titlePanel->Height-this->closePic->Height)/2;

			 this->addLbl->Left=this->Width-this->minPic->Width*3-this->fontRatio*25;
			 this->searchPic->Left=this->addLbl->Left-20*this->fontRatio;
			 this->findTxt->Left=this->searchPic->Left-this->findTxt->Width+this->searchPic->Width;
			 this->searchPic->Visible=true;
			 this->findTxt->Visible=false;

			 this->backLbl->Left=this->gapX*2;
			 this->gotoLbl->Left=(int)(this->backLbl->Left+this->backLbl->Width);
			 this->prevMonth->Left=(int)(this->Width/2)-(int)(this->prevMonth->Width/2)-(int)(25*this->fontRatio);
			 this->monthMarkLbl->Left=(int)(this->Width/2)-(int)(this->monthMarkLbl->Width/2);
			 this->nextMonth->Left=(int)(this->Width/2)-(int)(this->nextMonth->Width/2)+(int)(25*this->fontRatio);

			 this->closePic->Left=this->Width-this->closePic->Width-5*this->fontRatio;
			 this->maxPic->Left=this->closePic->Left-this->maxPic->Width;
			 this->minPic->Left=this->maxPic->Left-this->minPic->Width;
			 
			 this->todayLbl->Left=this->gapX*2;
			 this->todayLbl->Top=this->Height-this->todayLbl->Height-10-2*this->fontRatio;
			 
			 this->resetDayControl();
			 this->configureDetailMonth();
		 }
private: System::Void DetailMonth_Activated(System::Object^  sender, System::EventArgs^  e) {
			 this->timer1->Enabled=true;
		 }
private: System::Void DetailMonth_Deactivate(System::Object^  sender, System::EventArgs^  e) {
			 this->timer1->Enabled=false;
		 }

private: System::Void gotoLbl_Click(System::Object^  sender, System::EventArgs^  e) {	 
			 GotoDialog^ gotoDlg=gcnew GotoDialog();
			 gotoDlg->StartPosition=FormStartPosition::CenterParent;
			 gotoDlg->ShowDialog(this);
			 if(gotoDlg->DialogResult==System::Windows::Forms::DialogResult::OK){
				 //MessageBox::Show(gotoDlg->yearCmb->Text+"-"+gotoDlg->monthCmb->Text+"-"+gotoDlg->dayCmb->Text);
				 global::curYear=Convert::ToInt32(gotoDlg->yearCmb->Text);
				 global::curMonth=Convert::ToInt32(gotoDlg->monthCmb->Text);
				 this->resetDayControl();
				 this->configureDetailMonth();
			 }
		 }
private: System::Void gotoLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->gotoLbl->ForeColor = System::Drawing::Color::Blue;
		 }
private: System::Void gotoLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->gotoLbl->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void DetailMonth_MouseScroll(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(e->Delta>0)this->gotoNextMonth();else this->gotoPreviousMonth();
		 }
private: System::Void DetailMonth_Load(System::Object^  sender, System::EventArgs^  e) {
			 //this->Width=800;
			 this->minPic->Image=this->minLeavePic->Image;
			 this->maxPic->Image=this->maxLeavePic->Image;
			 this->closePic->Image=this->closeLeavePic->Image;
		 }
private: System::Void minPic_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->WindowState= System::Windows::Forms::FormWindowState::Minimized;
		 }
private: System::Void minPic_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->minPic->Image=this->minLeavePic->Image;
		 }
private: System::Void minPic_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->minPic->Image=this->minenterPic->Image;
		 }
private: System::Void maxPic_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->WindowState==System::Windows::Forms::FormWindowState::Normal)
				this->WindowState= System::Windows::Forms::FormWindowState::Maximized;
			 else if(this->WindowState==System::Windows::Forms::FormWindowState::Maximized)
				this->WindowState= System::Windows::Forms::FormWindowState::Normal;
		 }
private: System::Void maxPic_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->maxPic->Image=this->maxLeavePic->Image;
		 }
private: System::Void maxPic_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->maxPic->Image=this->maxEnterPic->Image;
		 }
private: System::Void closePic_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void closePic_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->closePic->Image=this->closeLeavePic->Image;
		 }
private: System::Void closePic_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->closePic->Image=this->closeEnterPic->Image;
		 }
private: System::Void findTxt_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 if(e->KeyChar==(char)13){
				 if(this->findTxt->Text->Length<=0){
						MessageBox::Show(L"请输入整数。");
						return;
					 }
					 if(!this->isInteger(this->findTxt->Text)){
						 MessageBox::Show(L"请输入整数。");
						 this->findTxt->Text="";
						 return;
					 }
					 if(Convert::ToInt32(this->findTxt->Text)<=0){
						 MessageBox::Show(L"请从1到99的整数输入。");
						 this->findTxt->Text="";
						 return;
					 }
					 global::timeOut=Convert::ToInt32(this->findTxt->Text);
					 this->findTxt->Visible=false;
					 this->searchPic->Visible=true;
					 MessageBox::Show(L"这是"+this->findTxt->Text+L"秒后消失",L"通知",System::Windows::Forms::MessageBoxButtons::OK,System::Windows::Forms::MessageBoxIcon::Information);
				 }
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
private: System::Void titlePanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->downFlag=1;
			 this->downX=e->X;
			 this->downY=e->Y;
			 this->Cursor=System::Windows::Forms::Cursors::SizeAll;
		 }
private: System::Void titlePanel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->downFlag=0;
			 this->downX=0;
			 this->downY=0;
			 this->Cursor=System::Windows::Forms::Cursors::Default;
		 }
private: System::Void titlePanel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (this->downFlag<=0){
				 this->Cursor=System::Windows::Forms::Cursors::Default;	
				 return;
			 }
			 this->Left=this->Left+e->X-this->downX;
			 this->Top=this->Top+e->Y-this->downY;
			 this->Cursor=System::Windows::Forms::Cursors::SizeAll;
		 }
private: System::Void titlePanel_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(this->WindowState==System::Windows::Forms::FormWindowState::Normal)
				this->WindowState= System::Windows::Forms::FormWindowState::Maximized;
			 else if(this->WindowState==System::Windows::Forms::FormWindowState::Maximized)
				this->WindowState= System::Windows::Forms::FormWindowState::Normal;
		 }
private: System::Void DetailMonth_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->downFlag=1;
			 this->downX=e->X;
			 this->downY=e->Y;			 
		 }
private: System::Void DetailMonth_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(this->downFlag==1){
				 if(this->sizeFlag==1){						 
					 if(Math::Abs(this->downX-e->X)>=5){
						 this->newWid=Windows::Forms::Cursor::Position.X-this->Left;
						 this->Width=newWid;
					 }
				 }else if(this->sizeFlag==2){	
					 if(Math::Abs(this->downY-e->Y)>=5){
						 this->newHei=Windows::Forms::Cursor::Position.Y-this->Top;	
						 this->Height=newHei;
					 }					 
				 }
			 }
			 this->Cursor=System::Windows::Forms::Cursors::Default;
			 this->downFlag=0;
			 this->sizeFlag=0;
			 this->downX=0;
			 this->downY=0; 
		 }
private: System::Void DetailMonth_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(this->downFlag==0 && this->WindowState!=System::Windows::Forms::FormWindowState::Maximized){
				if((this->Width-5<=e->X && this->Width>=e->X) ){
					 this->Cursor=System::Windows::Forms::Cursors::SizeWE;
					 this->sizeFlag=1;
				 }else if(this->Height-5<=e->Y && this->Height>=e->Y){
					 this->Cursor=System::Windows::Forms::Cursors::SizeNS;
					 this->sizeFlag=2;
				 }else if((this->Width-5<=e->X && this->Width>=e->X) && (this->Height-5<=e->Y && this->Height>=e->Y)){
					 this->Cursor=System::Windows::Forms::Cursors::SizeNWSE;
					 this->sizeFlag=3;
				 }else{
					 this->Cursor=System::Windows::Forms::Cursors::Default;
				 }				 
			 }		
		 }
private: System::Void todayLbl_Click(System::Object^  sender, System::EventArgs^  e) {
			 global::curMonth=((DateTime^)(DateTime::Now))->Month;
			 this->resetDayControl();
			 this->configureDetailMonth();
		 }
private: System::Void todayLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->todayLbl->ForeColor = System::Drawing::Color::Blue;
		 }
private: System::Void todayLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->todayLbl->ForeColor = System::Drawing::Color::Red;
		 }
};
}
