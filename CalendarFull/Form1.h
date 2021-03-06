#pragma once

#include "YearControl.h"
#include "GotoDialog.h"
#include "NumInputDialog.h"
#include "PopupForm.h"
#include "global.h";

namespace CalendarFull {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->gapX=20;
			this->gapY=5;
			this->newSize=20;
			global::timeOut=15;
		}
	private: System::Windows::Forms::ContextMenuStrip^  yearContextMenu;
	private: 
		int curYear, gapX, gapY, countTime, cx,cy,px,py, newSize;
		float fontRatio;
	private: System::Windows::Forms::NotifyIcon^  sleepNotify;

	private: System::Windows::Forms::ContextMenuStrip^  trayContextMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  showMI;
	private: System::Windows::Forms::ToolStripSeparator^  sepMI;
	private: System::Windows::Forms::PictureBox^  minLeavePic;
	private: System::Windows::Forms::PictureBox^  maxLeavePic;
	private: System::Windows::Forms::PictureBox^  closeLeavePic;
	private: System::Windows::Forms::PictureBox^  closeEnterPic;
	private: System::Windows::Forms::PictureBox^  maxEnterPic;
	private: System::Windows::Forms::PictureBox^  minenterPic;

	private: System::Windows::Forms::Label^  gotoLbl;
	private: System::Windows::Forms::Label^  yearNo;
	private: System::Windows::Forms::Label^  prevLbl;
	private: System::Windows::Forms::Label^  nextLbl;

	private: System::Windows::Forms::Label^  addLbl;



	private: System::Windows::Forms::Panel^  titlePanel;
	private: System::Windows::Forms::TextBox^  findTxt;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::PictureBox^  searchPic;
	private: System::Windows::Forms::PictureBox^  minPic;
	private: System::Windows::Forms::PictureBox^  maxPic;
	private: System::Windows::Forms::PictureBox^  closePic;
	private: System::Windows::Forms::PictureBox^  searchLeavePic;

	private: System::Windows::Forms::PictureBox^  searchEnterPic;

	private: System::Windows::Forms::ToolStripMenuItem^  exitMI;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
	private: System::Windows::Forms::Label^  todayLbl;
			 YearControl^ mainArea;
			 int sizeFlag, downFlag,newWid,newHei,downX,downY;

		void configureCalendar(){	
			this->yearNo->Text=Convert::ToString(global::curYear)+L"年";
			
			this->mainArea=gcnew YearControl(this,global::curYear,newSize);
			this->mainArea->setGapXandY(this->gapX,this->gapY);
			this->mainArea->configureYear();
			mainArea->Location = System::Drawing::Point(5*this->fontRatio,20*this->fontRatio);
			mainArea->Size = System::Drawing::Size(this->Width-10*this->fontRatio, this->Height-(20+16)*this->fontRatio);
			this->Controls->Add(mainArea);

			//configure context menu;
			for(int yy=global::curYear-20;yy<=global::curYear+20;++yy){
				ToolStripMenuItem^ newItem=gcnew ToolStripMenuItem();
				newItem->Text = Convert::ToString(yy);
				newItem->Click+=gcnew System::EventHandler(this, &Form1::contextMenuItem_Click);
				this->yearContextMenu->Items->Add(newItem);
			}
			this->yearNo->ContextMenuStrip=this->yearContextMenu;
		}

		void resetCalendar(){
			this->Controls->Remove(this->mainArea);
			this->yearContextMenu= (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
		}

		void gotoPreviousYear(){
			if(global::curYear>0) --global::curYear;
			this->resetCalendar();
			this->configureCalendar();
		}

		void gotoNextYear(){
			++global::curYear;
			this->resetCalendar();
			this->configureCalendar();
		}


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->todayLbl = (gcnew System::Windows::Forms::Label());
			this->yearContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->sleepNotify = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->trayContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->showMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sepMI = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->minLeavePic = (gcnew System::Windows::Forms::PictureBox());
			this->maxLeavePic = (gcnew System::Windows::Forms::PictureBox());
			this->closeLeavePic = (gcnew System::Windows::Forms::PictureBox());
			this->closeEnterPic = (gcnew System::Windows::Forms::PictureBox());
			this->maxEnterPic = (gcnew System::Windows::Forms::PictureBox());
			this->minenterPic = (gcnew System::Windows::Forms::PictureBox());
			this->gotoLbl = (gcnew System::Windows::Forms::Label());
			this->yearNo = (gcnew System::Windows::Forms::Label());
			this->prevLbl = (gcnew System::Windows::Forms::Label());
			this->nextLbl = (gcnew System::Windows::Forms::Label());
			this->addLbl = (gcnew System::Windows::Forms::Label());
			this->titlePanel = (gcnew System::Windows::Forms::Panel());
			this->minPic = (gcnew System::Windows::Forms::PictureBox());
			this->maxPic = (gcnew System::Windows::Forms::PictureBox());
			this->closePic = (gcnew System::Windows::Forms::PictureBox());
			this->searchPic = (gcnew System::Windows::Forms::PictureBox());
			this->findTxt = (gcnew System::Windows::Forms::TextBox());
			this->searchLeavePic = (gcnew System::Windows::Forms::PictureBox());
			this->searchEnterPic = (gcnew System::Windows::Forms::PictureBox());
			this->trayContextMenu->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minLeavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxLeavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closeLeavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closeEnterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxEnterPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minenterPic))->BeginInit();
			this->titlePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchPic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchLeavePic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchEnterPic))->BeginInit();
			this->SuspendLayout();
			// 
			// todayLbl
			// 
			this->todayLbl->AutoSize = true;
			this->todayLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->todayLbl->ForeColor = System::Drawing::Color::Red;
			this->todayLbl->Location = System::Drawing::Point(20, 262);
			this->todayLbl->Name = L"todayLbl";
			this->todayLbl->Size = System::Drawing::Size(31, 13);
			this->todayLbl->TabIndex = 1;
			this->todayLbl->Text = L"今天";
			this->todayLbl->MouseLeave += gcnew System::EventHandler(this, &Form1::todayLbl_MouseLeave);
			this->todayLbl->Click += gcnew System::EventHandler(this, &Form1::todayLbl_Click);
			this->todayLbl->MouseEnter += gcnew System::EventHandler(this, &Form1::todayLbl_MouseEnter);
			// 
			// yearContextMenu
			// 
			this->yearContextMenu->Name = L"yearContextMenu";
			this->yearContextMenu->Size = System::Drawing::Size(61, 4);
			// 
			// sleepNotify
			// 
			this->sleepNotify->ContextMenuStrip = this->trayContextMenu;
			this->sleepNotify->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"sleepNotify.Icon")));
			this->sleepNotify->Text = L"Calendar";
			this->sleepNotify->DoubleClick += gcnew System::EventHandler(this, &Form1::sleepNotify_DoubleClick);
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
			this->showMI->Click += gcnew System::EventHandler(this, &Form1::showMI_Click);
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
			this->exitMI->Click += gcnew System::EventHandler(this, &Form1::exitMI_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// minLeavePic
			// 
			this->minLeavePic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"minLeavePic.Image")));
			this->minLeavePic->Location = System::Drawing::Point(88, 121);
			this->minLeavePic->Name = L"minLeavePic";
			this->minLeavePic->Size = System::Drawing::Size(28, 30);
			this->minLeavePic->TabIndex = 4;
			this->minLeavePic->TabStop = false;
			this->minLeavePic->Visible = false;
			// 
			// maxLeavePic
			// 
			this->maxLeavePic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"maxLeavePic.Image")));
			this->maxLeavePic->Location = System::Drawing::Point(122, 121);
			this->maxLeavePic->Name = L"maxLeavePic";
			this->maxLeavePic->Size = System::Drawing::Size(28, 30);
			this->maxLeavePic->TabIndex = 4;
			this->maxLeavePic->TabStop = false;
			this->maxLeavePic->Visible = false;
			// 
			// closeLeavePic
			// 
			this->closeLeavePic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"closeLeavePic.Image")));
			this->closeLeavePic->Location = System::Drawing::Point(156, 121);
			this->closeLeavePic->Name = L"closeLeavePic";
			this->closeLeavePic->Size = System::Drawing::Size(28, 30);
			this->closeLeavePic->TabIndex = 4;
			this->closeLeavePic->TabStop = false;
			this->closeLeavePic->Visible = false;
			// 
			// closeEnterPic
			// 
			this->closeEnterPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"closeEnterPic.Image")));
			this->closeEnterPic->Location = System::Drawing::Point(156, 174);
			this->closeEnterPic->Name = L"closeEnterPic";
			this->closeEnterPic->Size = System::Drawing::Size(28, 30);
			this->closeEnterPic->TabIndex = 4;
			this->closeEnterPic->TabStop = false;
			this->closeEnterPic->Visible = false;
			// 
			// maxEnterPic
			// 
			this->maxEnterPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"maxEnterPic.Image")));
			this->maxEnterPic->Location = System::Drawing::Point(122, 174);
			this->maxEnterPic->Name = L"maxEnterPic";
			this->maxEnterPic->Size = System::Drawing::Size(28, 30);
			this->maxEnterPic->TabIndex = 4;
			this->maxEnterPic->TabStop = false;
			this->maxEnterPic->Visible = false;
			// 
			// minenterPic
			// 
			this->minenterPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"minenterPic.Image")));
			this->minenterPic->Location = System::Drawing::Point(88, 174);
			this->minenterPic->Name = L"minenterPic";
			this->minenterPic->Size = System::Drawing::Size(28, 30);
			this->minenterPic->TabIndex = 4;
			this->minenterPic->TabStop = false;
			this->minenterPic->Visible = false;
			// 
			// gotoLbl
			// 
			this->gotoLbl->AutoSize = true;
			this->gotoLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gotoLbl->ForeColor = System::Drawing::Color::Red;
			this->gotoLbl->Location = System::Drawing::Point(65, 0);
			this->gotoLbl->Name = L"gotoLbl";
			this->gotoLbl->Size = System::Drawing::Size(15, 20);
			this->gotoLbl->TabIndex = 0;
			this->gotoLbl->Text = L"↓";
			this->gotoLbl->MouseLeave += gcnew System::EventHandler(this, &Form1::gotoLbl_MouseLeave);
			this->gotoLbl->Click += gcnew System::EventHandler(this, &Form1::gotoLbl_Click);
			this->gotoLbl->MouseEnter += gcnew System::EventHandler(this, &Form1::gotoLbl_MouseEnter);
			// 
			// yearNo
			// 
			this->yearNo->AutoSize = true;
			this->yearNo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->yearNo->Location = System::Drawing::Point(14, 0);
			this->yearNo->Name = L"yearNo";
			this->yearNo->Size = System::Drawing::Size(45, 20);
			this->yearNo->TabIndex = 5;
			this->yearNo->Text = L"2008";
			// 
			// prevLbl
			// 
			this->prevLbl->AutoSize = true;
			this->prevLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->prevLbl->ForeColor = System::Drawing::Color::Red;
			this->prevLbl->Location = System::Drawing::Point(117, 0);
			this->prevLbl->Name = L"prevLbl";
			this->prevLbl->Size = System::Drawing::Size(18, 20);
			this->prevLbl->TabIndex = 0;
			this->prevLbl->Text = L"<";
			this->prevLbl->MouseLeave += gcnew System::EventHandler(this, &Form1::prevLbl_MouseLeave);
			this->prevLbl->Click += gcnew System::EventHandler(this, &Form1::prevLbl_Click);
			this->prevLbl->MouseEnter += gcnew System::EventHandler(this, &Form1::prevLbl_MouseEnter);
			// 
			// nextLbl
			// 
			this->nextLbl->AutoSize = true;
			this->nextLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->nextLbl->ForeColor = System::Drawing::Color::Red;
			this->nextLbl->Location = System::Drawing::Point(179, 0);
			this->nextLbl->Name = L"nextLbl";
			this->nextLbl->Size = System::Drawing::Size(18, 20);
			this->nextLbl->TabIndex = 0;
			this->nextLbl->Text = L">";
			this->nextLbl->MouseLeave += gcnew System::EventHandler(this, &Form1::nextLbl_MouseLeave);
			this->nextLbl->Click += gcnew System::EventHandler(this, &Form1::nextLbl_Click);
			this->nextLbl->MouseEnter += gcnew System::EventHandler(this, &Form1::nextLbl_MouseEnter);
			// 
			// addLbl
			// 
			this->addLbl->AutoSize = true;
			this->addLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->addLbl->ForeColor = System::Drawing::Color::Red;
			this->addLbl->Location = System::Drawing::Point(294, 0);
			this->addLbl->Name = L"addLbl";
			this->addLbl->Size = System::Drawing::Size(18, 20);
			this->addLbl->TabIndex = 0;
			this->addLbl->Text = L"+";
			this->addLbl->MouseLeave += gcnew System::EventHandler(this, &Form1::addLbl_MouseLeave);
			this->addLbl->Click += gcnew System::EventHandler(this, &Form1::addLbl_Click);
			this->addLbl->MouseEnter += gcnew System::EventHandler(this, &Form1::addLbl_MouseEnter);
			// 
			// titlePanel
			// 
			this->titlePanel->Controls->Add(this->minPic);
			this->titlePanel->Controls->Add(this->maxPic);
			this->titlePanel->Controls->Add(this->closePic);
			this->titlePanel->Controls->Add(this->searchPic);
			this->titlePanel->Controls->Add(this->findTxt);
			this->titlePanel->Controls->Add(this->yearNo);
			this->titlePanel->Controls->Add(this->gotoLbl);
			this->titlePanel->Controls->Add(this->prevLbl);
			this->titlePanel->Controls->Add(this->nextLbl);
			this->titlePanel->Controls->Add(this->addLbl);
			this->titlePanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->titlePanel->Location = System::Drawing::Point(0, 0);
			this->titlePanel->Name = L"titlePanel";
			this->titlePanel->Size = System::Drawing::Size(405, 20);
			this->titlePanel->TabIndex = 7;
			this->titlePanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::titlePanel_MouseMove);
			this->titlePanel->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::titlePanel_MouseDoubleClick);
			this->titlePanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::titlePanel_MouseDown);
			this->titlePanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::titlePanel_MouseUp);
			// 
			// minPic
			// 
			this->minPic->Location = System::Drawing::Point(328, 0);
			this->minPic->Name = L"minPic";
			this->minPic->Size = System::Drawing::Size(20, 20);
			this->minPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->minPic->TabIndex = 8;
			this->minPic->TabStop = false;
			this->minPic->MouseLeave += gcnew System::EventHandler(this, &Form1::minPic_MouseLeave);
			this->minPic->Click += gcnew System::EventHandler(this, &Form1::minPic_Click);
			this->minPic->MouseEnter += gcnew System::EventHandler(this, &Form1::minPic_MouseEnter);
			// 
			// maxPic
			// 
			this->maxPic->Location = System::Drawing::Point(354, 0);
			this->maxPic->Name = L"maxPic";
			this->maxPic->Size = System::Drawing::Size(20, 20);
			this->maxPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->maxPic->TabIndex = 8;
			this->maxPic->TabStop = false;
			this->maxPic->MouseLeave += gcnew System::EventHandler(this, &Form1::maxPic_MouseLeave);
			this->maxPic->Click += gcnew System::EventHandler(this, &Form1::maxPic_Click);
			this->maxPic->MouseEnter += gcnew System::EventHandler(this, &Form1::maxPic_MouseEnter);
			// 
			// closePic
			// 
			this->closePic->Location = System::Drawing::Point(380, 0);
			this->closePic->Name = L"closePic";
			this->closePic->Size = System::Drawing::Size(20, 20);
			this->closePic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->closePic->TabIndex = 8;
			this->closePic->TabStop = false;
			this->closePic->MouseLeave += gcnew System::EventHandler(this, &Form1::closePic_MouseLeave);
			this->closePic->Click += gcnew System::EventHandler(this, &Form1::closePic_Click);
			this->closePic->MouseEnter += gcnew System::EventHandler(this, &Form1::closePic_MouseEnter);
			// 
			// searchPic
			// 
			this->searchPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"searchPic.Image")));
			this->searchPic->Location = System::Drawing::Point(268, 0);
			this->searchPic->Name = L"searchPic";
			this->searchPic->Size = System::Drawing::Size(20, 20);
			this->searchPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->searchPic->TabIndex = 8;
			this->searchPic->TabStop = false;
			this->searchPic->MouseLeave += gcnew System::EventHandler(this, &Form1::searchPic_MouseLeave);
			this->searchPic->Click += gcnew System::EventHandler(this, &Form1::searchPic_Click);
			this->searchPic->MouseEnter += gcnew System::EventHandler(this, &Form1::searchPic_MouseEnter);
			// 
			// findTxt
			// 
			this->findTxt->Font = (gcnew System::Drawing::Font(L"SimSun", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->findTxt->Location = System::Drawing::Point(213, 0);
			this->findTxt->Name = L"findTxt";
			this->findTxt->Size = System::Drawing::Size(49, 22);
			this->findTxt->TabIndex = 7;
			this->findTxt->Visible = false;
			this->findTxt->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::findTxt_KeyPress);
			// 
			// searchLeavePic
			// 
			this->searchLeavePic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"searchLeavePic.Image")));
			this->searchLeavePic->Location = System::Drawing::Point(122, 225);
			this->searchLeavePic->Name = L"searchLeavePic";
			this->searchLeavePic->Size = System::Drawing::Size(28, 30);
			this->searchLeavePic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->searchLeavePic->TabIndex = 4;
			this->searchLeavePic->TabStop = false;
			this->searchLeavePic->Visible = false;
			// 
			// searchEnterPic
			// 
			this->searchEnterPic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"searchEnterPic.Image")));
			this->searchEnterPic->Location = System::Drawing::Point(88, 225);
			this->searchEnterPic->Name = L"searchEnterPic";
			this->searchEnterPic->Size = System::Drawing::Size(28, 30);
			this->searchEnterPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->searchEnterPic->TabIndex = 4;
			this->searchEnterPic->TabStop = false;
			this->searchEnterPic->Visible = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(405, 300);
			this->Controls->Add(this->titlePanel);
			this->Controls->Add(this->maxEnterPic);
			this->Controls->Add(this->closeEnterPic);
			this->Controls->Add(this->todayLbl);
			this->Controls->Add(this->searchEnterPic);
			this->Controls->Add(this->searchLeavePic);
			this->Controls->Add(this->minLeavePic);
			this->Controls->Add(this->maxLeavePic);
			this->Controls->Add(this->minenterPic);
			this->Controls->Add(this->closeLeavePic);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"日历";
			this->Deactivate += gcnew System::EventHandler(this, &Form1::Form1_Deactivate);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_mouseScroll);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove);
			this->trayContextMenu->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minLeavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxLeavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closeLeavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closeEnterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxEnterPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minenterPic))->EndInit();
			this->titlePanel->ResumeLayout(false);
			this->titlePanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->minPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->maxPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->closePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchPic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchLeavePic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->searchEnterPic))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
private: System::Void searchPic_Click(System::Object^  sender, System::EventArgs^  e) {	 
			 this->searchPic->Visible=this->findTxt->Visible;
			 this->findTxt->Visible=!this->findTxt->Visible;
			 this->findTxt->Focus();
		 }
private: System::Void searchPic_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->searchPic->Image = this->searchEnterPic->Image;
		 }
private: System::Void searchPic_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->searchPic->Image = this->searchLeavePic->Image;
		 }
private: System::Void addLbl_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->findTxt->Visible=this->searchPic->Visible;
			 this->searchPic->Visible=!this->searchPic->Visible;			 			 
			 //NumInputDialog^ numDlg=gcnew NumInputDialog();
			 //numDlg->StartPosition=FormStartPosition::CenterParent;
			 //numDlg->ShowDialog(this);
			 //if(numDlg->DialogResult==System::Windows::Forms::DialogResult::OK){
			//	 global::timeOut=Convert::ToInt32(numDlg->numTxt->Text);
			 //}
		 }
private: System::Void addLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->addLbl->ForeColor = System::Drawing::Color::Blue;
		 }
private: System::Void addLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->addLbl->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void todayLbl_Click(System::Object^  sender, System::EventArgs^  e) {
			 DetailMonth^ detail=gcnew DetailMonth(this,global::curMonth);	
			 detail->configureDetailMonth();
			 detail->StartPosition=FormStartPosition::CenterScreen;
			 detail->Show();
			 this->Hide();
		 }
private: System::Void todayLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->todayLbl->ForeColor = System::Drawing::Color::Blue;
		 }
private: System::Void todayLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->todayLbl->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void gotoLbl_Click(System::Object^  sender, System::EventArgs^  e) {	 
			 GotoDialog^ gotoDlg=gcnew GotoDialog();
			 gotoDlg->StartPosition=FormStartPosition::CenterParent;
			 gotoDlg->ShowDialog(this);
			 if(gotoDlg->DialogResult==System::Windows::Forms::DialogResult::OK){
				 //MessageBox::Show(gotoDlg->yearCmb->Text+"-"+gotoDlg->monthCmb->Text+"-"+gotoDlg->dayCmb->Text);
				 this->resetCalendar();
				 global::curYear=Convert::ToInt32(gotoDlg->yearCmb->Text);
				 this->configureCalendar();
			 }
		 }
private: System::Void gotoLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->gotoLbl->ForeColor = System::Drawing::Color::Blue;
		 }
private: System::Void gotoLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->gotoLbl->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void prevLbl_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->gotoPreviousYear();			 
		 }
private: System::Void prevLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->prevLbl->ForeColor = System::Drawing::Color::Blue;
		 }
private: System::Void prevLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->prevLbl->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void nextLbl_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->gotoNextYear();
		 }
private: System::Void nextLbl_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->nextLbl->ForeColor = System::Drawing::Color::Blue;
		 }
private: System::Void nextLbl_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->nextLbl->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void contextMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 ToolStripMenuItem^ tmpItem=safe_cast<ToolStripMenuItem^> (sender);
			 global::curYear=Convert::ToInt32(tmpItem->Text);
			 this->resetCalendar();
			 this->configureCalendar();
		 }

private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {			 
			 if(this->Width<405 && this->Height<305){
				 this->Opacity=0.5f;
			 }else{
				 this->Opacity=1.0f;
			 }			 
			 if(this->Width<405) this->Width=400;
			 if(this->Height<305) this->Height=300;				 
			 //MessageBox::Show("aa");
			 int tmpWid, tmpHei;
			 tmpWid=(int) this->Width/40;
			 tmpHei=(int) this->Height/30;
			 this->newSize=tmpWid>tmpHei ? tmpHei : tmpWid;
			 this->fontRatio=(float) this->newSize/10;
			 if(this->fontRatio<1) this->fontRatio=1.0f;
			 //set gapX, gapY
			 this->gapX=(int)(this->Width-this->newSize*28)/40;
			 this->gapY=(int)(this->Height-this->newSize*24-(20+16)*this->fontRatio)/30;
			 //header
			 //this->header->Width=this->Width;
			 this->titlePanel->Height=(int)(20*this->fontRatio);
			 this->yearNo->Height=(int)(20*this->fontRatio);
			 this->yearNo->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->gotoLbl->Height=(int)(20*this->fontRatio);
			 this->gotoLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->prevLbl->Height=(int)(20*this->fontRatio);
			 this->prevLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->nextLbl->Height=(int)(20*this->fontRatio);
			 this->nextLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->addLbl->Height=(int)(20*this->fontRatio);
			 this->addLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			 this->todayLbl->Height=(int)(20*this->fontRatio);
			 this->todayLbl->Font=(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8*this->fontRatio, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
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

			 this->addLbl->Left=this->Width-this->addLbl->Width-this->minPic->Width*3-this->fontRatio*20;
			 this->searchPic->Left=this->addLbl->Left-30*this->newSize/10;
			 this->findTxt->Left=this->searchPic->Left-this->findTxt->Width+this->searchPic->Width;
			 this->searchPic->Visible=true;
			 this->findTxt->Visible=false;

			 this->yearNo->Left=this->gapX*4;
			 this->gotoLbl->Left=this->yearNo->Left+this->yearNo->Width+10*this->fontRatio;
			 this->prevLbl->Left=this->Width/2-this->prevLbl->Width/2-80*this->newSize/20;
			 this->nextLbl->Left=this->Width/2-this->prevLbl->Width/2+80*this->newSize/20;

			 this->closePic->Left=this->Width-this->closePic->Width-5*this->fontRatio;
			 this->maxPic->Left=this->closePic->Left-this->maxPic->Width;
			 this->minPic->Left=this->maxPic->Left-this->minPic->Width;
			 //middle
			 //footer
			 this->todayLbl->Left=this->gapX*4;
			 this->todayLbl->Top=this->Height-15*this->fontRatio;		 
			 
			 this->resetCalendar();
			 this->configureCalendar();			 
			 //this->StartPosition=FormStartPosition::CenterScreen;
		 }

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {	
			 ++this->countTime;			 
			 this->cx=System::Windows::Forms::Cursor::Position.X;
			 this->cy=System::Windows::Forms::Cursor::Position.Y;
			 if(this->cx!=this->px || this->cy!=this->py )this->countTime=0;
			 if(global::timeOut==this->countTime && global::timeOut>0){
				 this->Hide();
				 this->sleepNotify->Visible=true;
				 this->timer1->Enabled=false;
				 this->countTime=0;

				 this->sleepNotify->BalloonTipText=L"这是"+Convert::ToString(global::timeOut)+L"秒后消失。";
				 //L"这是"+Convert::ToString(this->sleepTime)+L"秒后消失。";
				 this->sleepNotify->BalloonTipTitle=L"通知";
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
private: System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
			 this->timer1->Enabled=true;
			 if(global::relaodFlag<=0) return;
			 this->resetCalendar();
			 this->configureCalendar();
			 
		 }
private: System::Void Form1_Deactivate(System::Object^  sender, System::EventArgs^  e) {
			 this->timer1->Enabled=false;
			 global::relaodFlag=0;	
		 }

private: System::Void Form1_mouseScroll(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(e->Delta>0)this->gotoNextYear();else this->gotoPreviousYear();
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {			 
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
private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
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
private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {		 
			 this->downFlag=1;
			 this->downX=e->X;
			 this->downY=e->Y;			 
		 }
private: System::Void Form1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {			 
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
};
}
