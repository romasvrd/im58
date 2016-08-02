//---------------------------------------------------------------------------
					/*����������� ����� ���������� � �������, ������� �������� ������, �������� ������� ���������*/

//                   �������� ������ ������� �������, �������� ������ 380, 220, �������� ��������� (��� �������� ���������), �������� �������� � �������. ���� ������� �����������, ����� ����������
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
		ShowMessage("��������� ��������� ����������");
		return;
	}
	int a=ComboBox1->ItemIndex;
	if((!save)&&a!=-1)
	{
		switch(MessageBox(NULL,"�� �� ��������� ���������. ���������?",NULL,MB_ICONQUESTION|MB_YESNOCANCEL))
		{
			case ID_YES: this->���������Click(this); break;
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
				���������->Enabled=false;
				ResumeThread(hThread);
				break;
			}

		}
		Button1->Enabled=false;
		���������->Enabled=false;
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
			sprintf(string,"�������� � ��������� �������� ������ ���� � �������� [0..%3d] ���\r\n",a);
			error=true;
			break;
		}
		if(currentTest.rollmax<=0||currentTest.rollmax>=9001)
		{
			sprintf(string,"������������ ������� ������ ���������� � �������� [100..9000] ��/���\r\n");
			error=true;
			break;
		}
		if(currentTest.rolltest<=0||currentTest.rolltest>=9001)
		{
			sprintf(string,"������� ������� ������ ���������� � �������� [100..9000]\r\n");
			error=true;
			break;
		}
		if(currentTest.cooltime<=0||currentTest.cooltime>=1800000)
		{
			sprintf(string,"����� ���������� ������ ���������� � �������� [0� 1�..30� 0�\r\n");
			error=true;
			break;
		}
		if(!this->AbLED2->Checked)
		{
			sprintf(string,"�������� ������� �������\r\n");
			error=true;
			break;
		}
		if(!this->AbLED1->Checked)
		{
			sprintf(string,"�������� ������� � ������\r\n");
			error=true;
			break;
		}
		if(this->ComboBox1->ItemIndex==-1)
		{
			sprintf(string,"�������� ��� ���������������\r\n");
			error=true;
			break;
		}
		break;
		if(!tacho_checkconnect(TACHO_MERADAT))
		{
			sprintf(string,"��� ���������� � ����������");
			error=true;
			break;
		}
		if(!tacho_checkconnect(TACHO_VEHA_T))
		{
			sprintf(string,"��� ���������� � ������� ����");
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
		���������->Enabled=false;
		ComboBox1->Enabled=false;
		ResumeThread(hThread);
    	return;
	}
	if(!ResumeTest)  	//���� ������ ����� ���������, � �� ���������� �������������
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
  sh.pFrom = rmd.c_str(); //��������� ����������
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
	this->���������->Enabled=false;
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

	   //����� ����������
		if(currentTest.brakecount>=1&&currentTest.brakecount<6)
		{
			sprintf(string,"������� ������������� ���� %d",currentTest.brakecount);
			if(currentTest.brakecount>1&&currentTest.brakecount<6)
			{
				if(((testresults[test.brakecount-1].������������_����������<20)
				||(testresults[test.brakecount-1].������������_����������>24)))
				{
					ShowMessage("������������� ������, ����� ������������ ���������� ���������� 22�2 �, ������� ���������, � ����� �����");
					asdf=true;
					Form4->Button1->Enabled=true;
					Form4->���������->Enabled=true;
					Form4->ComboBox1->Enabled=true;
					SuspendThread(hThread);
				}
				else
				{
					//ShowMessage("��� ������� ���������� ������������ ��������� ������� �����");
					//���������� ��������� ��������
					switch(MessageBox(NULL,"������������ ���������� � �������� �����. ��������� �������� � ������� � ����� �� 10 ����������?","������������ ���������� � �����",MB_ICONQUESTION|MB_YESNO|MB_SETFOREGROUND))
					{
						case ID_YES:
						{
							test.brakecount=6;
							currentTest.brakecount=6;
							sprintf(string,"������� �������� ���� %d",currentTest.brakecount-5);
							flagbefore=true;
						}
						break;
						case ID_NO:
						{
							ShowMessage("��� ������� ���������� ������������ ���������� ������� �����");
						}break;
					}
					asdf=true;
					Form4->Button1->Enabled=true;
					Form4->���������->Enabled=true;
					Form4->ComboBox1->Enabled=true;
					SuspendThread(hThread);
				}
			}

		}

		else if(currentTest.brakecount==6||currentTest.brakecount==16)
		{
			//SuspendThread(hThread);
			Form4->Button1->Enabled=true;
			Form4->���������->Enabled=true;
			Form4->ComboBox1->Enabled=true;
			asdf=true;
			flagbefore=true;
			SuspendThread(hThread);
		}
		else if(((testresults[test.brakecount-1].������������_����������<20)
		||(testresults[test.brakecount-1].������������_����������>24))&&fulltest&&!ResumeTest)
		{
			switch(MessageBox(NULL,"������������ ���������� ����� �� ������� 22�2 ���. ������� �������������� ��������?","������������ ���������� �� � �����",MB_ICONWARNING|MB_YESNO|MB_SYSTEMMODAL))
			{
				case ID_YES:    part=OutOfRange;
								Form4->Button3Click(Form4);
								Form4->Button1->Enabled=true;
								Form4->���������->Enabled=true;
								SuspendThread(hThread);
								break;
				case ID_NO:		break;
			}
		}
		else
		{
			sprintf(string,"������� �������� ���� %d",currentTest.brakecount-5);
		}
		if(!fulltest)
		{
			sprintf(string,"%s","������� ������� ����");
		}
		//������ � ������� ��� ������, ����� ������ �� ������ �������
		string4.string=string;
		string4.bold=true;
		textqueue.push(string4);
		sprintf(string,"%02d:%02d:%02d:%03d �������� ������� ������� � �������...",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		string4.bold=false;
		textqueue.push(string4);
		while(!test.checkForAir())  //�������� �������� � �������
		{
			sprintf(string,"�������� ���� 4.5 ���.");
			string4.string=string;
			string4.bold=false;
			textqueue.push(string4);
			part=NoAir;
			Form4->Button3Click(Form4);//��������� �����
			SuspendThread(hThread);
		}
	//������ ������ �������
		part=acceleration;
		volume=-1;
	//��������� ������
	GetLocalTime(&time);
			sprintf(string,"�������� � �����");
			string4.string=string;
			string4.bold=false;
			textqueue.push(string4);
		sprintf(string,"%02d:%02d:%02d:%03d ������ �������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		string4.bold=false;
		textqueue.push(string4);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		Sleep(500);
	//������������� �������� � ��������� ��������
		GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ��������� ���������� ������ %.3f ���",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,currentTest.pressure*25*M_PI*BarToKg);
		string4.string=string;
		string4.bold=false;
		textqueue.push(string4);
		currentTest.setCurrent(1,currentTest.pressure);
		currentTest.setCurrent(1,currentTest.pressure);
		currentTest.setCurrent(1,currentTest.pressure);
		currentTest.setCurrent(1,currentTest.pressure);
		currentTest.setCurrent(1,currentTest.pressure);
		Sleep(100);
	//�������� ��������� �����
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ��������� ��������� �����",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		currentTest.clutch(true);
		currentTest.clutch(true);
		currentTest.clutch(true);
		Sleep(100);

	//������������ ������ �� n ��������
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ������ ������� �� %d ��������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,currentTest.rollmax);
		string4.string=string;
		textqueue.push(string4);
		SetSpeedMotor(hardware.hwDrive,currentTest.rollmax/1.7);
		SetSpeedMotor(hardware.hwDrive,currentTest.rollmax/1.7);
		SetSpeedMotor(hardware.hwDrive,currentTest.rollmax/1.7);
		Sleep(1000);
		StartMotor(hardware.hwDrive,1,currentTest.rollmax/1.7);
		StartMotor(hardware.hwDrive,1,currentTest.rollmax/1.7);
		StartMotor(hardware.hwDrive,1,currentTest.rollmax/1.7);
	//����, ���� ������ �����������
		while(test.rolls<currentTest.rollmax)
		{
			Sleep(10);
		}
	   //������ �����������
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ���������� ����������� �������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
	//���������� ���������
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ���������� ��������� �����",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		currentTest.clutch(false);
		currentTest.clutch(false);
		currentTest.clutch(false);
		currentTest.clutch(false);
		currentTest.clutch(false);
	//���������� �������
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ���������� �������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		StopMotor(hardware.hwDrive);
		StopMotor(hardware.hwDrive);
		StopMotor(hardware.hwDrive);
	//����, ���� ������ ������ �� ������� ��������
		while(test.rolls>currentTest.rolltest)
		{
			Sleep(100);
		}
	//������ �����������
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ���������� ������� �������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		//���������� ������� �� ���������
		tacho_reset();
		tacho_reset();
		tacho_reset();
	//������ ����������
		part=braking;
	//������ ����������
	GetLocalTime(&time);

		sprintf(string,"%02d:%02d:%02d:%03d ������ ����������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		startspeed=Form4->Ab180Meter1->Digit;
		currentTest.brake(true);
		currentTest.brake(true);
		currentTest.brake(true);

		//����, ���� ������� �����������
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
	//������� �����������
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ��� ����������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
	//��������� ������
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ������ �������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
		currentTest.brake(false);
	//��������� ��������
		current_turns=false;
        Sleep(1500);
		//������ �������� � �������
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ������ ������� �� ��������� �������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		currentTest.setCurrent(1,0);
		currentTest.setCurrent(1,0);
		currentTest.setCurrent(1,0);
		currentTest.setCurrent(1,0);
		currentTest.setCurrent(1,0);
	//�������� ������
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d �������� ������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
		string4.string=string;
		textqueue.push(string4);
		//hRec=CreateThread(NULL,0,thRec,NULL,0,NULL);
		volume=-1;
		ResumeThread(hRec);
	//������ ������ ������ �������� ����� ���� ����������� ��� ������������ ����� 10 ��������
		Sleep(200);
		tacho_result();
		tacho_result();
		tacho_result();
	//���������� �� ����� t
	GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ���������� �� ����� %d �",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,currentTest.cooltime/1000);
		string4.string=string;
		textqueue.push(string4);
		currentTest.cooler(true);
		//Sleep(currentTest.cooltime);
		//������ ����������. ���������� ���� �����, ��������� ������ ��������� �������
		//����� ����� ����� �� 0, ���������� �����
		coolerready=false;
		Form4->Timer2->Enabled=true;
		while(coolerready==false)
		{
			Sleep(10);
		}
		GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ���������� ���������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
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
	//������� ���������� �������
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
				//���� ��� ���� ��������� ��������� - �������� ������ � ���������� �����

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
void __fastcall TForm4::���������Click(TObject *Sender)
{
	AnsiString aTime;
	currentTest.pressure=(Edit1->Text.ToDouble())/25/M_PI/BarToKg;
	currentTest.rollmax=StrToInt(Edit2->Text);
	currentTest.rolltest=StrToInt(Edit3->Text);
	aTime=MaskEdit1->Text;
	currentTest.cooltime=aTime.SubString(0,2)*60000+aTime.SubString(4,2)*1000;  //����� ���������� � ������������
	initest->WriteString(currentTest.name,"Brake pressure",currentTest.pressure);
	initest->WriteString(currentTest.name,"Max turns",currentTest.rollmax);
	initest->WriteString(currentTest.name,"Working turns",currentTest.rolltest);
	initest->WriteString(currentTest.name,"Cooling time",currentTest.cooltime);
//� ����� ������� � ��������
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	//if(asdf)ResumeThread(hThread);
	save=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormShow(TObject *Sender)
{
	String s="��-58 �"+IntToStr(hardware.hwMachineNo)+" �������������� �����";
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
	���������->Enabled=true;
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
//� ����� ������� � ��������
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	try
	{
		Form10->ADOCommand1->CommandText=
		"UPDATE [after10] SET[�����_���������]='"+
		IntToStr(currentTest.rolltest)+
		"',[���������_���������]='"+
		currentTest.name+"' where id="+globalID;
		Form10->ADOCommand1->Execute();
	}
	catch(Exception &e)
	{
		ShowMessage("������ ������ � ���� ������");
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::AbToggleSwitch2Click(TObject *Sender)
{
	SYSTEMTIME time;
	if(!this->AbLED2->Checked)
	{
	GetLocalTime(&time);
		//�������� ������� �������
	sprintf(string,"%02d:%02d:%02d:%03d ��������� ������� �������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
	Form4->RichEdit1->Lines->Add(string);
	//Form4->StatusBar1->Panels[0].Items[1]->Text=string;
	test.drive(true);
	}
	else
	{  		//�������� ������� �������
		GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ���������� ������� �������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
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
		"UPDATE [after10] SET[�����_���������]='"+
		IntToStr(currentTest.rolltest)+"',[Jh(���)]='"+
		obr+"',[Jh(����)]='"+
		contr+"' where id="+globalID;
		Form10->ADOCommand1->Execute();
	}
	catch(Exception &e)
	{
		ShowMessage("������ ������ � ���� ������");
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
			sprintf(string,"%02d:%02d:%02d:%03d �������� ����� %s",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,portSet.port1Name.c_str());
			Form4->RichEdit1->Lines->Add(string);
			if(comPort1Init()!=0)
			{
				sprintf(string, "%s","�� ������� ������� ����");
				Form4->RichEdit1->Lines->Add(string);
				return;
			}
		}
		if(port2Closed)
		{
			GetLocalTime(&time);
			sprintf(string,"%02d:%02d:%02d:%03d �������� ����� %s",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,portSet.port2Name.c_str());
			Form4->RichEdit1->Lines->Add(string);
			if(comPort2Init()!=0)
			{
				sprintf(string, "%s","�� ������� ������� ����");
				Form4->RichEdit1->Lines->Add(string);
				return;
			}
		}
		GetLocalTime(&time);
		sprintf(string,"%02d:%02d:%02d:%03d ����� �����������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
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
		sprintf(string,"%02d:%02d:%02d:%03d ���������� ���������",time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
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
		ShowMessage("���������� �����");
		return;
    }
	//���� ����������  �3
	if(AbToggleSwitch3->StatusInt==1)
	{
		//test.setDOuts(0x02,0xFF);
		test.cooler(true);
		RichEdit1->Lines->Add("���������� ��������");
	}
	else
	{
		test.cooler(false);
		RichEdit1->Lines->Add("���������� �����������");
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
		case idle: ShowMessage("�� �������� �� ���� ������ ���������");break;
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
			test.clutch(false);  //��������� ���������
			StopMotor(hardware.hwDrive);
			StopMotor(hardware.hwDrive);
			StopMotor(hardware.hwDrive);
			Form4->Button1->Enabled=true;
			Form4->���������->Enabled=true;
			Timer3->Enabled=true;
			ShowMessage("�� ������� ���������� ������ ����� ��������� ����. ����� ������ ������, ������� �����");
			break;
		}
		case braking:
		{
			Form4->Button1->Enabled=true;
			Form4->���������->Enabled=true;
			SuspendThread(hThread);
			Button3->Enabled=false;
			pause=true;
			Timer3->Enabled=true;
			ShowMessage("�� ������� ���������� ������ ����� ��������� ����. ����� ������ ������, ������� �����");
			break;
		}
		case cooling:
		{
			Form4->Button1->Enabled=true;
			Form4->���������->Enabled=true;
			Button3->Enabled=false;
			pause=true;
			ShowMessage("�� ���������� ����������/������� ������ ������� ����� ��� ������� ���������� ����� ����������");
			break;
		}
		case OutOfRange:
		{
			Form4->Button1->Enabled=true;
			Form4->���������->Enabled=true;
			Button3->Enabled=false;
			pause=true;
			ShowMessage("������� ���������, ������� ���������, ����� �����");
			break;
		}
		case NoAir:
		{
			Form4->Button1->Enabled=true;
			Form4->���������->Enabled=true;
			ShowMessage("�������� ���� 4.5 ���. ��������� �������� � �������, ����� ������� ����� ��� �����������.");
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
		string4.string="����� ��������� ������";
		string4.bold=true;
		textqueue.push(string4);
	}
}
//---------------------------------------------------------------------------
