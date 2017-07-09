#pragma once

ref class global
{
public:
	global(void);
	static int timeOut;
	static int curYear=((System::DateTime^)System::DateTime::Now)->Year;
	static int curMonth=((System::DateTime^)System::DateTime::Now)->Month;
	static int curDay=((System::DateTime^)System::DateTime::Now)->Day;
	static int relaodFlag;
	static bool enableFlag;
	//global::curYear=((System::DateTime^)System::DateTime::Now)->Year;
	//		global::curMonth=
	//		global::curDay=;
};
