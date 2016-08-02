//---------------------------------------------------------------------------
					/*фактическое время торможения с графика, поднять скорость обмена, задавать уставки тахометру*/

//                   добавить кнопку питание привода, лампочку выдано 380, 220, исзодное состояние (все цилиндры выключены), проверка начальны х условий. Если условия соблюдаются, можно стартовать
#include <vcl.h>
#include <math.h>
#pragma hdrstop
#include "im58main.h"
#include "im58serial.h"
#include "im58about.h"
#include "im58drive.h"
#include "im58recorder.h"
#include "im58hello.h"
#include "im58auto.h"
#include "im58archive.h"
#include "im58results.h"
#include "im58heights.h"
#include <Windows.h>
#include <queue>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "_GClass"
#pragma link "AbRMeter"
#pragma link "AbLED"
#pragma link "AbSwitch"
#pragma resource "*.dfm"
extern bool ResumeTest;
extern int ResumeBrakeCount;
extern TEvents events;
extern AnsiString fio;
extern	SYSTEMTIME date;
TForm4 *Form4;
extern TTest test;
extern strHardware hardware;
char string[255];
extern portSettings portSet;
HANDLE hThread;
HANDLE hRec;
HANDLE hHeights;
//HANDLE hTachoCurrent4;
DWORD WINAPI thRec(void*);
DWORD WINAPI thThread(LPVOID);
//DWORD WINAPI thTachoCurrent4(void*);
DWORD WINAPI thHeights(void*);
extern const double BarToKg;
extern TTestResults testresults[16];
int index;
TIniFile *initest = new TIniFile(".\\im58_test.ini");
extern bool port1Closed,port2Closed,inputState;
extern std::queue<qStr> serialQueue2;
qStr qTacho;
extern int crc1,crc2;
extern bool current_turns,result_flag;
bool flagTachoCurrent4;
extern std::vector<TTest> vectorTest;
TTest currentTest;
std::queue<qString> textqueue;
bool fulltest=false;
bool change=true;
bool flagbefore=false;
int startspeed;
bool readystream=false;
bool readyrec=false;
bool readybutton=false;
bool buttonfinish=false;
bool streamfinish=false;
bool asdf=false;
double obr=0;
double contr=0;
extern bool port1Closed;
extern bool port2Closed;
int volume=0;
extern int globalID;
int timeparameter=0;
char tasdf[5];
int tmins,tsecs,cooltime;
extern bool findzero;
bool KillMePlease;
extern char progpath[254];
bool pause=false;
bool starttimer=false;
bool coolerready=false;
bool save=false;
enum  eParts
{
	idle=1,acceleration,braking,cooling,OutOfRange,NoAir
};
eParts part;
extern  int tacho_type;
extern bool ReadRegChannels;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	Chart1->LeftAxis->Automatic=true;
	Chart1->BottomAxis->Automatic=true;
	KillMePlease=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::N2Click(TObject *Sender)
{
	Hide();
	Form1->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::AltF41Click(TObject *Sender)
{
	this->Close();
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::l(TObject *Sender)
{
	if(Timer2->Enabled==true)
	{
		ShowMessage("Дождитесь окончания охлаждения");
		return;
	}
	int a=ComboBox1->ItemIndex;
	if((!save)&&a!=-1)
	{
		switch(MessageBox(NULL,"Вы не сохранили настройки. Сохранить?",NULL,MB_ICONQUESTION|MB_YESNOCANCEL))
		{
			case ID_YES: this->СохранитьClick(this); break;
			case ID_NO: break;
			case ID_CANCEL: return;
		}
	}
	if(pause)
	{
		Button3->Enabled=true;
		switch(part)
		{
			case braking:
			{
					ResumeThread(hThread);
					break;
			}
			case cooling:
			case NoAir:
			{
				ResumeThread(hThread);
				break;
			}
			case acceleration:
			{
				if(!hThread)
				{
					hThread=CreateThread(NULL,0,thThread,NULL,0,NULL);
				}
				else
				{
                    ResumeThread(hThread);
                }
				break;
			}
			case OutOfRange:
			{
				Сохранить->Enabled=false;
				ResumeThread(hThread);
				break;
			}

		}
		Button1->Enabled=false;
		Сохранить->Enabled=false;
		Button3->Enabled=true;
		pause=false;
		return;
    }

	bool error=false;
	while(1)
	{
		if(currentTest.pressure<=0||currentTest.pressure>=hardware.pressuremax)
		{
			int a=	hardware.pressuremax*25*M_PI*BarToKg;
			sprintf(string,"Давление в тормозном цилиндре должно быть в пределах [0..%3d] кгс\r\n",a);
			error=true;
			break;
		}
		if(currentTest.rollmax<=0||currentTest.rollmax>=9001)
		{
			sprintf(string,"Максимальные обороты должны находиться в пределах [100..9000] об/мин\r\n");
			error=true;
			break;
		}
		if(currentTest.rolltest<=0||currentTest.rolltest>=9001)
		{
			sprintf(string,"Рабочие обороты должны находиться в пределах [100..9000]\r\n");
			error=true;
			break;
		}
		if(currentTest.cooltime<=0||currentTest.cooltime>=1800000)
		{
			sprintf(string,"Время охлаждения должно находиться в пределах [0м 1с..30м 0с\r\n");
			error=true;
			break;
		}
		if(!this->AbLED2->Checked)
		{
			sprintf(string,"Включите питание привода\r\n");
			error=true;
			break;
		}
		if(!this->AbLED1->Checked)
		{
			sprintf(string,"Включите питание с пульта\r\n");
			error=true;
			break;
		}
		if(this->ComboBox1->ItemIndex==-1)
		{
			sprintf(string,"Выберите тип металлокерамики\r\n");
			error=true;
			break;
		}
		break;
		if(!tacho_checkconnect(TACHO_MERADAT))
		{
			sprintf(string,"Нет соединения с тахометром");
			error=true;
			break;
		}
		if(!tacho_checkconnect(TACHO_VEHA_T))
		{
			sprintf(string,"Нет соединения с модулем ВЕХА");
			error=true;
			break;
		}
	}
	if(error==true)
	{
		ShowMessage(string);
		return;
	}
	if(asdf)
	{
		Button1->Enabled=false;
		Сохранить->Enabled=false;
		ComboBox1->Enabled=false;
		ResumeThread(hThread);
    	return;
	}
	if(!ResumeTest)  	//если начато новое испытание, а не продолжено незаконченное
	{
		currentTest.brakecount=1;
		test.brakecount=1;
		for(int i=1;i<=Form3->StringGrid1->ColCount;i++)
		{
			for(int j=1;j<=Form3->StringGrid1->RowCount;j++)
			{
				Form3->StringGrid1->Cells[i][j]=0;
			}
		}
		for(int i=1;i<=Form3->StringGrid2->ColCount;i++)
		{
			for(int j=1;j<=Form3->StringGrid2->RowCount;j++)
			{
				Form3->StringGrid2->Cells[i][j]=0;
			}
		}
	}

	fulltest=true;
	Form4->Series1->Clear();
	Form4->Series2->Clear();
	contr=0;
	obr=0;
	AnsiString rmd=progpath;
	rmd+="Diagrams\\";
  SHFILEOPSTRUCT sh;
  sh.hwnd=Form1->Handle;
  sh.wFunc = FO_DELETE;
  sh.pFrom = rmd.c_str(); //удаляемая директория
  sh.pTo = NULL;
  sh.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;
  sh.hNameMappings = 0;
  sh.lpszProgressTitle = NULL;
  SHFileOperation(&sh);
  CreateDirectory(rmd.c_str(),0);
	if(hThread)
	{
		ResumeThread(hThread);
	}
	else
	{
		hThread=CreateThread(NULL,0,thThread,NULL,0,NULL);
	}
	Button1->Enabled=false;
	this->Сохранить->Enabled=false;
	ComboBox1->Enabled=false;
	//hHeights=CreateThread(NULL,0,thHeights,NULL,0,NULL);
}
//---------------------------------------------------------------------------
DWORD WINAPI thThread(LPVOID)
{
	qString string4;
	SYSTEMTIME time;
	while(1)
	{
		readyrec=false;
		readystream=false;
		readybutton=false;
		streamfinish=false;
		buttonfinish=false;
		current_turns=true;
		findzero=true;

	   //номер торможения
		if(currentTest.brakecount>=1&&currentTest.brakecount<6)
		{
			sprintf(string,"Запущен приработочный цикл %d",currentTest.brakecount);
			if(currentTest.brakecount>1&&currentTest.brakecount<6)
			{
				if(((testresults[test.brakecount-1].длительность_торможения<20)
				||(testresults[test.brakecount-1].длительность_торможения>24)))
				{
					ShowMessage("Отрегулируйте усилие, чтобы длительность торможения составляла 22±2 с, нажмите Сохранить, а затем Старт");
					asdf=true;
					Form4->Button1->Enabled=true;
					Form4->Сохранить->Enabled=true;
					Form4->ComboBox1->Enabled=true;
					SuspendThread(hThread);
				}
				else
				{
					//ShowMessage("Для запуска следующего притирочного испытания нажмите Старт");
					//предложить закончить притирку
					switch(MessageBox(NULL,"Длительность торможения в пределах нормы. Закончить притирку и перейти к циклу из 10 торможений?","Длительность торможения в норме",MB_ICONQUESTION|MB_YESNO|MB_SETFOREGROUND))
					{
						case ID_YES:
						{
							test.brakecount=6;
							currentTest.brakecount=6;
							sprintf(string,"Запущен зачётный цикл %d",currentTest.brakecount-5);
							flagbefore=true;
						}
						break;
						case ID_NO:
						{
							ShowMessage("Для запуска следующего притирочного торможения нажмите Старт");
						}break;
					}
					asdf=true;
					Form4->Button1->Enabled=true;
					Form4->Сохранить->Enabled=true;
					Form4->ComboBox1->Enabled=true;
					SuspendThread(hThread);
				}
			}

		}

		else if(currentTest.brakecount==6||currentTest.brakecount==16)
		{
			//SuspendThread(hThread);
			Form4->Button1->Enabled=true;
			Form4->Сохранить->Enabled=true;
			Form4->ComboBox1->Enabled=true;
			asdf=true;
			flagbefore=true;
			SuspendThread(hThread);
		}
		else if(((testresults[test.brakecount-1].длительность_торможения<20)
		||(testresults[test.brakecount-1].длительность_торможения>24))&&fulltest&&!ResumeTest)
		{
			switch(MessageBox(NULL,"Длительность торможения вышла за пределы 22±2 сек. Желаете отрегулировать давление?","Длительность торможения не в норме",MB_ICONWARNING|MB_YESNO|MB_SYSTEMMODAL))
			{
				case ID_YES:    part=OutOfRange;
								Form4->Button3Click(Form4);
								Form4->Button1->Enabled=true;
								Form4->Сохранить->Enabled=true;
								SuspendThread(hThread);
								break;
				case ID_NO:		break;
			}
		}
		else
		{
			sprintf(string,"Запущен зачётный цикл %d",currentTest.brakecount-5);
		}
		if(!fulltest)
		{
			sprintf(string,"%s","Запущен пробный цикл");
		}
		//пихаем в очередь эту строку, будем писать ее жирным шрифтом
		string4.string=string;
		string4.bold=true;
		textqueue.push(string4);
		sprintf(string,"%02d:%02d:%02d:%03d Проверка наличия воздуха в системе...",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		string4.bold=false;
		textqueue.push(string4);
		while(!test.checkForAir())  //проверка давления в системе
		{
			sprintf(string,"Давление ниже 4.5 бар.");
			string4.string=string;
			string4.bold=false;
			textqueue.push(string4);
			part=NoAir;
			Form4->Button3Click(Form4);//иммитация паузы
			SuspendThread(hThread);
		}
	//начало стадии разгона
		part=acceleration;
		volume=-1;
	//отключить тормоз
	GetLocalTime(&time);
			sprintf(string,"Давление в норме");
			string4.string=string;
			string4.bold=false;
			textqueue.push(string4);
		sprintf(string,"%02d:%02d:%02d:%03d Отпуск тормоза",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		string4.bold=false;
		textqueue.push(string4);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		Sleep(500);
	//устанавливаем давление в тормозном цилиндре
		GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Установка тормозного усилия %.3f кгс",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,currentTest.pressure*25*M_PI*BarToKg);
		string4.string=string;
		string4.bold=false;
		textqueue.push(string4);
		currentTest.setCurrent(1,currentTest.pressure);
		currentTest.setCurrent(1,currentTest.pressure);
		currentTest.setCurrent(1,currentTest.pressure);
		currentTest.setCurrent(1,currentTest.pressure);
		currentTest.setCurrent(1,currentTest.pressure);
		Sleep(100);
	//включаем сцепление муфты
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Включение сцепления муфты",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		currentTest.clutch(true);
		currentTest.clutch(true);
		currentTest.clutch(true);
		Sleep(100);

	//раскручиваем привод до n оборотов
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Запуск привода до %d оборотов",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,currentTest.rollmax);
		string4.string=string;
		textqueue.push(string4);
		SetSpeedMotor(hardware.hwDrive,currentTest.rollmax/1.7);
		SetSpeedMotor(hardware.hwDrive,currentTest.rollmax/1.7);
		SetSpeedMotor(hardware.hwDrive,currentTest.rollmax/1.7);
		Sleep(1000);
		StartMotor(hardware.hwDrive,1,currentTest.rollmax/1.7);
		StartMotor(hardware.hwDrive,1,currentTest.rollmax/1.7);
		StartMotor(hardware.hwDrive,1,currentTest.rollmax/1.7);
	//ждем, пока привод раскрутится
		while(test.rolls<currentTest.rollmax)
		{
			Sleep(10);
		}
	   //привод раскрутился
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Достигнуты необходимые обороты",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
	//отключение сцепления
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Отключение сцепления муфты",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		currentTest.clutch(false);
		currentTest.clutch(false);
		currentTest.clutch(false);
		currentTest.clutch(false);
		currentTest.clutch(false);
	//отключение привода
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Отключение привода",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		StopMotor(hardware.hwDrive);
		StopMotor(hardware.hwDrive);
		StopMotor(hardware.hwDrive);
	//ждем, пока привод дойдет до рабочих оборотов
		while(test.rolls>currentTest.rolltest)
		{
			Sleep(100);
		}
	//привод раскрутился
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Достигнуты рабочие обороты",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		//сбрасываем счетчик на тахометре
		tacho_reset();
		tacho_reset();
		tacho_reset();
	//стадия торможения
		part=braking;
	//Запуск торможения
	GetLocalTime(&time);

		sprintf(string,"%02d:%02d:%02d:%03d Начало торможения",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		startspeed=Form4->Ab180Meter1->Digit;
		currentTest.brake(true);
		currentTest.brake(true);
		currentTest.brake(true);

		//ждем, пока маховик остановится
		a:
		while(test.rolls>0)
		{
			Sleep(100);
		}
		for(int i=0;i<=10;i++)
		{
			if(test.rolls!=0)
			{
				goto a;
			}
			Sleep(50);
        }
	//маховик остановился
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Вал остановлен",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
	//отключить тормоз
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Отпуск тормоза",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
	//отключить тахометр
		current_turns=false;
        Sleep(1500);
		//убрать давление в системе
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Выпуск воздуха из тормозной системы",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		currentTest.setCurrent(1,0);
		currentTest.setCurrent(1,0);
		currentTest.setCurrent(1,0);
		currentTest.setCurrent(1,0);
		currentTest.setCurrent(1,0);
	//Загрузка архива
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Загрузка данных",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		//hRec=CreateThread(NULL,0,thRec,NULL,0,NULL);
		volume=-1;
		ResumeThread(hRec);
	//просим ввести высоты образцов после пяти притирочных или остановиться после 10 зачетных
		Sleep(200);
		tacho_result();
		tacho_result();
		tacho_result();
	//охлаждение на время t
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Охлаждение на время %d с",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,currentTest.cooltime/1000);
		string4.string=string;
		textqueue.push(string4);
		currentTest.cooler(true);
		//Sleep(currentTest.cooltime);
		//начать охлаждение. Остановить этот поток, запустить таймер обратного отсчета
		//когда время дойдёт до 0, продолжить поток
		coolerready=false;
		Form4->Timer2->Enabled=true;
		while(coolerready==false)
		{
			Sleep(10);
		}
		GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Охлаждение завершено",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		currentTest.cooler(false);
		currentTest.cooler(false);
		currentTest.cooler(false);
		currentTest.cooler(false);
		currentTest.cooler(false);
		if(currentTest.brakecount==5||currentTest.brakecount==15)
		{
			//flagbefore=true;
		}
		currentTest.brakecount++;
		readystream=true;
	//сколько получилось оборотв
		if(currentTest.brakecount!=6&&currentTest.brakecount!=16)
		{
			if(fulltest&&!readyrec)
			{
				SuspendThread(hThread);
			}
			if(!fulltest)
			{
				if(readyrec)
				{
					if(!pause)Form9->Button1->Enabled=true;
					Form9->ComboBox2->Enabled=true;
					Form9->Button6->Enabled=true;
				}
				//если это было единичное испытание - включить кнопки и остановить поток

				KillMePlease=true;
				SuspendThread(hThread);
			}
			if(readyrec&&flagbefore)
			{
				SuspendThread(hThread);
			}
		}
		if(pause)
		{
			Form4->Button1->Enabled=true;
			SuspendThread(hThread);
		}
		if(!readyrec)
		{
            SuspendThread(hThread);
        }
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::СохранитьClick(TObject *Sender)
{
	AnsiString aTime;
	currentTest.pressure=(Edit1->Text.ToDouble())/25/M_PI/BarToKg;
	currentTest.rollmax=StrToInt(Edit2->Text);
	currentTest.rolltest=StrToInt(Edit3->Text);
	aTime=MaskEdit1->Text;
	currentTest.cooltime=aTime.SubString(0,2)*60000+aTime.SubString(4,2)*1000;  //время торможения в милисекундах
	initest->WriteString(currentTest.name,"Brake pressure",currentTest.pressure);
	initest->WriteString(currentTest.name,"Max turns",currentTest.rollmax);
	initest->WriteString(currentTest.name,"Working turns",currentTest.rolltest);
	initest->WriteString(currentTest.name,"Cooling time",currentTest.cooltime);
//и пишем уставку в тахометр
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	//if(asdf)ResumeThread(hThread);
	save=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormShow(TObject *Sender)
{
	String s="ИМ-58 №"+IntToStr(hardware.hwMachineNo)+" автоматический режим";
	Form4->Caption=s;
	Form3->StringGrid2->Top=Form3->StringGrid1->Top+Form3->StringGrid1->Height-2;
   	if(ComboBox1->Items->Count==0)
	{
		int i=0;
		do
		{
			//currentTest=vectorTest[i];
			ComboBox1->Items->Add(vectorTest[i].name);
			i++;
		}
		while(i<vectorTest.size());
		ComboBox1->ItemIndex=-1;
	}
	inputState=true;
	if(!hRec)
	{
		hRec=CreateThread(NULL,0,thRec,NULL,CREATE_SUSPENDED,NULL);
	}
	if(!hThread)
	{
		hThread=CreateThread(NULL,0,thThread,NULL,CREATE_SUSPENDED,NULL);
	}
	flagTachoCurrent4=true;
	Timer1->Enabled=true;
	ReadRegChannels=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button2Click(TObject *Sender)
{
	if(hThread)
	{
		TerminateThread(hThread,0);
		CloseHandle(hThread);
		hThread=0;
	}
	test.clutch(false);
	test.drive(false);
	test.brake(false);
	Sleep(1000);
	test.setCurrent(1,0);
	Button1->Enabled=true;
	Сохранить->Enabled=true;
	ComboBox1->Enabled=true;
	asdf=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::N4Click(TObject *Sender)
{
	Hide();
	Form9->Visible=true;
}
//---------------------------------------------------------------------------
DWORD WINAPI thRec(void*)
{
	while(1)
	{
		recExeCmd(volume);
		SuspendThread(hRec);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button4Click(TObject *Sender)
{
	Series1->Clear();
	Series2->Clear();
}
//---------------------------------------------------------------------------
void tacho_reset(void)
{
	if(tacho_type==TACHO_VEHA_T)
	{
		qTacho.qBytes[0]=hardware.hwTacho;
		qTacho.qBytes[1]=0x05;	//write single coil
		qTacho.qBytes[2]=0x00;
		qTacho.qBytes[3]=0x0E; 	//14 - counter reset
		qTacho.qBytes[4]=0xFF;
		qTacho.qBytes[5]=0x00;
		crc16(qTacho.qBytes,6,&crc1,&crc2);
		qTacho.qBytes[6]=0xED;
		qTacho.qBytes[7]=0xAC;
		qTacho.size=8;
		serialQueue2.push(qTacho);
	}
}
//---------------------------------------------------------------------------
void tacho_result(void)
{
	if(tacho_type==TACHO_VEHA_T)
	{
		current_turns=false;
		Sleep(200);
		result_flag=true;
		Sleep(200);
		qTacho.qBytes[0]=hardware.hwTacho;
		qTacho.qBytes[1]=0x04;	//read input registers
		qTacho.qBytes[2]=0x00;
		qTacho.qBytes[3]=0x0F; 	//15 - tacho.result.turn_counter
		qTacho.qBytes[4]=0x00;
		qTacho.qBytes[5]=0x02; 	//bytes qty
		crc16(qTacho.qBytes,6,&crc1,&crc2);
		qTacho.qBytes[6]=0x41;
		qTacho.qBytes[7]=0x9D;
		qTacho.size=8;
		serialQueue2.push(qTacho);
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm4::ComboBox1Change(TObject *Sender)
{
	save=true;
	int temp=currentTest.brakecount;
	currentTest=vectorTest[ComboBox1->ItemIndex];
	//test.brakecount=currentTest.brakecount;
	currentTest.brakecount=temp;
	Edit1->Text=currentTest.pressure*25*M_PI*BarToKg;
	Edit2->Text=currentTest.rollmax;
	Edit3->Text=currentTest.rolltest;
	char asdf[5];
	int mins=(currentTest.cooltime/1000)/60;
	int secs=(currentTest.cooltime/1000)-mins*60;
	sprintf(asdf,"%02d:%02d",mins,secs);
	MaskEdit1->Text=asdf;
//и пишем уставку в тахометр
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	try
	{
		Form10->ADOCommand1->CommandText=
		"UPDATE [after10] SET[Режим_испытания]='"+
		IntToStr(currentTest.rolltest)+
		"',[Программа_испытания]='"+
		currentTest.name+"' where id="+globalID;
		Form10->ADOCommand1->Execute();
	}
	catch(Exception &e)
	{
		ShowMessage("Ошибка записи в базу данных");
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::AbToggleSwitch2Click(TObject *Sender)
{
	SYSTEMTIME time;
	if(!this->AbLED2->Checked)
	{
	GetLocalTime(&time);
		//включаем питание привода
	sprintf(string,"%02d:%02d:%02d:%03d Включение питания привода",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
	Form4->RichEdit1->Lines->Add(string);
	//Form4->StatusBar1->Panels[0].Items[1]->Text=string;
	test.drive(true);
	}
	else
	{  		//включаем питание привода
		GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Отключение питания привода",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		Form4->RichEdit1->Lines->Add(string);
		//Form4->StatusBar1->Panels[0].Items[1]->Text=string;
		test.drive(false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::AbLED2StatusChanged(TObject *Sender)
{
	this->AbToggleSwitch2->Checked=this->AbLED2->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::StringGrid2SetEditText(TObject *Sender, int ACol, int ARow,
		  const UnicodeString Value)
{
  	double one,two;
	if(!((Form3->StringGrid2->Cells[1][ARow]=="")||(Form3->StringGrid2->Cells[2][ARow]=="")))
	{
		one=(Form3->StringGrid2->Cells[1][ARow]).ToDouble();
		two=(Form3->StringGrid2->Cells[2][ARow]).ToDouble();
		Form3->StringGrid2->Cells[3][ARow]=two-one;
	}
}
//---------------------------------------------------------------------------
void EndOfTest(void)
{
	part=idle;
	test.setCurrent(1,0);
	char datetime[50];
	sprintf(datetime,"%02d.%02d.%04d %02d:%02d",date.wDay,date.wMonth,date.wYear,date.wHour,date.wMinute);
	try
	{
		Form10->ADOCommand1->CommandText=
		"UPDATE [after10] SET[Режим_испытания]='"+
		IntToStr(currentTest.rolltest)+"',[Jh(фмк)]='"+
		obr+"',[Jh(чнмх)]='"+
		contr+"' where id="+globalID;
		Form10->ADOCommand1->Execute();
	}
	catch(Exception &e)
	{
		ShowMessage("Ошибка записи в базу данных");
	}
	Form4->Hide();
	Form6->Show();
	comPort1Close();
	comPort2Close();
	currentTest.brakecount=1;
	test.brakecount=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormHide(TObject *Sender)
{
	test.clutch(false);
	test.drive(false);
	test.cooler(false);
	test.brake(false);
	Timer1->Enabled=false;
	Timer2->Enabled=false;
	test.setCurrent(1,0);
	Sleep(100);
	inputState=false;
	Timer1->Enabled=false;
	asdf=false;
	if(!port1Closed)
	{
		comPort1Close();
	}
	if(!port2Closed)
	{
		comPort2Close();
	}
	if(hThread)
	{
		TerminateThread(hThread,0);
		CloseHandle(hThread);
		hThread=0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::AbToggleSwitch1Click(TObject *Sender)
{
	SYSTEMTIME time;
	if(!events.AutoConnectEvent)
	{
 		if(port1Closed)
		{
			GetLocalTime(&time);
			sprintf(string,"%02d:%02d:%02d:%03d Открытие порта %s",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,portSet.port1Name.c_str());
			Form4->RichEdit1->Lines->Add(string);
			if(comPort1Init()!=0)
			{
				sprintf(string, "%s","Не удалось открыть порт");
				Form4->RichEdit1->Lines->Add(string);
				return;
			}
		}
		if(port2Closed)
		{
			GetLocalTime(&time);
			sprintf(string,"%02d:%02d:%02d:%03d Открытие порта %s",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,portSet.port2Name.c_str());
			Form4->RichEdit1->Lines->Add(string);
			if(comPort2Init()!=0)
			{
				sprintf(string, "%s","Не удалось открыть порт");
				Form4->RichEdit1->Lines->Add(string);
				return;
			}
		}
		GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Связь установлена",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		Form4->RichEdit1->Lines->Add(string);
		events.AutoConnectEvent=true;
	}
	else
	{
		if(!port1Closed)
		{
			comPort1Close();
		}
		if(!port2Closed)
		{
			comPort2Close();
		}
		GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d Соединение разорвано",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		Form4->RichEdit1->Lines->Add(string);
		events.AutoConnectEvent=false;
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
	if(flagTachoCurrent4)
	{
		Form4->Ab180Meter1->Digit=test.rolls;
		Form4->Ab180Meter1->SignalSettings->Name2=test.rolls;
	}
	if(flagbefore)
	{
		flagbefore=false;
		Form3->Show();
	}
	if(KillMePlease)
	{
		TerminateThread(hThread,0);
		CloseHandle(hThread);
		hThread=0;
		KillMePlease=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Timer2Timer(TObject *Sender)
{
	part=cooling;
	cooltime=(currentTest.cooltime/1000)-timeparameter;
	if(cooltime==0)
	{
		timeparameter=0;
		coolerready=true;
    	Timer2->Enabled=false;
    }
	tmins=(cooltime)/60;
	tsecs=(cooltime)-tmins*60;
	sprintf(tasdf,"%02d:%02d",tmins,tsecs);
	MaskEdit2->Text=tasdf;
	if(Form9->Visible==true)Form9->MaskEdit2->Text=tasdf;
	timeparameter++;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::AbToggleSwitch3StatusChanged(TObject *Sender)
{
	if(port1Closed)
	{
		ShowMessage("Установите связь");
		return;
    }
	//реле охдаждения  к3
	if(AbToggleSwitch3->StatusInt==1)
	{
		//test.setDOuts(0x02,0xFF);
		test.cooler(true);
		RichEdit1->Lines->Add("Охлаждение запущено");
	}
	else
	{
		test.cooler(false);
		RichEdit1->Lines->Add("Охлаждение остановлено");
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm4::N5Click(TObject *Sender)
{
	TStringList *sl=new TStringList(Form4);

	sl->Add("\r\n"+FormatDateTime("dd.MM.yyyy hh:mm:ss",Now()));
	for(int i=0;i<=RichEdit1->Lines->Count;i++)
	{
		sl->Add(Form4->RichEdit1->Lines->operator [](i));
	}
	sl->SaveToFile((UnicodeString)progpath+"log.txt");
	delete sl;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button3Click(TObject *Sender)
{
	switch(part)
	{
		case idle: ShowMessage("Не запущена ни одна стадия испытаний");break;
		case acceleration:
		{
			Button3->Enabled=false;
			pause=true;
			//Button1->Enabled=true;
			TerminateThread(hThread,0);
			CloseHandle(hThread);
			hThread=0;
			test.clutch(false);
			test.clutch(false);
			test.clutch(false);  //отпустить сцепление
			StopMotor(hardware.hwDrive);
			StopMotor(hardware.hwDrive);
			StopMotor(hardware.hwDrive);
			Form4->Button1->Enabled=true;
			Form4->Сохранить->Enabled=true;
			Timer3->Enabled=true;
			ShowMessage("Вы сможете продолжить работу после остановки вала. Когда будете готовы, нажмите Старт");
			break;
		}
		case braking:
		{
			Form4->Button1->Enabled=true;
			Form4->Сохранить->Enabled=true;
			SuspendThread(hThread);
			Button3->Enabled=false;
			pause=true;
			Timer3->Enabled=true;
			ShowMessage("Вы сможете продолжить работу после остановки вала. Когда будете готовы, нажмите Старт");
			break;
		}
		case cooling:
		{
			Form4->Button1->Enabled=true;
			Form4->Сохранить->Enabled=true;
			Button3->Enabled=false;
			pause=true;
			ShowMessage("По завершению охлаждения/запроса данных нажмите Старт для запуска следующего цикла торможения");
			break;
		}
		case OutOfRange:
		{
			Form4->Button1->Enabled=true;
			Form4->Сохранить->Enabled=true;
			Button3->Enabled=false;
			pause=true;
			ShowMessage("Внесите изменения, нажмите Сохранить, затем Старт");
			break;
		}
		case NoAir:
		{
			Form4->Button1->Enabled=true;
			Form4->Сохранить->Enabled=true;
			ShowMessage("Давление ниже 4.5 бар. Проверьте давление в системе, затем нажмите Старт для продолжения.");
			Button3->Enabled=false;
			pause=true;
			Button1->Enabled=true;
			Button2->Enabled=true;
			Form9->Button1->Enabled=true;
			break;
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Timer3Timer(TObject *Sender)
{
	if(test.rolls==0&&part!=cooling)
	{
        Button1->Enabled=true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormCreate(TObject *Sender)
{
	part=idle;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::AbLED3StatusChanged(TObject *Sender)
{
	qString string4;
	if(this->AbLED3->StatusInt==1)
	{
		string4.string="Нажат аварийный грибок";
		string4.bold=true;
		textqueue.push(string4);
	}
}
//---------------------------------------------------------------------------
