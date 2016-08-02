//---------------------------------------------------------------------------
#include <vcl.h>
#include <queue>
#include <vector>
#include <windows.h>
#include <math.h>
#include "im58main.h"
#include "im58serial.h"
#include "im58about.h"
#include "im58drive.h"
#include "im58recorder.h"
#include "im58hello.h"
#include "im58who.h"
#include "im58testsettings.h"
#include "im58auto.h"
#pragma hdrstop
#include <conio.h>
#include <tlhelp32.h>
#include <iostream.h>
#include <math.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "_GClass"
#pragma link "AbHSlide"
#pragma link "AbCBitBt"
#pragma link "AbSwitch"
#pragma link "AbRMeter"
#pragma link "AbMTrend"
#pragma link "AbTrend"
#pragma link "AbLED"
#pragma link "AbDBCtrls"
#pragma link "AbVInd"
#pragma resource "*.dfm"
TForm9 *Form9;
strHardware hardware;
extern bool port1Closed;
extern bool port2Closed;
extern int crc1,crc2;
extern rec_struct recorder;
extern bool findzero;
extern HANDLE hMonitor;
extern HANDLE hViewer;
extern DWORD WINAPI thMonitor(LPVOID);
extern bool inputState;
extern bool current_turns;
TTest test;
const double BarToKg=1.01971621297793;
extern std::queue<qStr> serialQueue1;
extern std::queue<qStr> serialQueue2;
using namespace std;
std::vector<TTest> vectorTest;
extern TTest currentTest;
extern DWORD WINAPI thRec(void*);
extern DWORD WINAPI thThread(LPVOID);
extern HANDLE hThread;
extern HANDLE hRec;
extern std::queue<qString> textqueue;
bool polzunok;
extern bool fulltest;
extern bool result_flag;
extern int volume;
TConvert convert;
//extern TLineSeries *series1;
//extern TLineSeries *series2;
extern bool DiagramPrepared;
extern vector<diagramStruct> vDiagram;
extern diagramStruct sDiagram;
TEvents events;
extern char progpath[254];
int tacho_type;
extern HANDLE ComPort2;
extern HANDLE hPort1;
extern HANDLE hPort2;
bool ReadRegChannels=false;
extern to_iee754_t regValue[2];
//���� �� ������ � com-������ �� ������:
//http://how2.org.ua/%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5/
//%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0-%D1%81-com-%D0%BF%D0%BE%D1%80%D1%82%D0%BE%D0%BC-%D0%BD%D0%B0-c-%D0%B2-windows.html

//---------------------------------------------------------------------------
__fastcall TForm9::TForm9(TComponent* Owner)
	: TForm(Owner)
{
	String s;
	tacho_type=TACHO_VEHA_T;
	test.pressbutton=false;
	Chart1->BottomAxis->Automatic=true;
	Chart1->LeftAxis->Automatic=true;
	hardware.b=4;
	test.brakecount=0;
 	hardware.hwDInputs=0x01;
	hardware.hwDAC=0x02,
	hardware.hwReg=0x03,
	hardware.hwTacho=0x04,
	hardware.hwDOutputs=0x05,
	hardware.hwDrive=0x1F;
	recorder.braketime=0;
	recorder.starttime=0;
	recorder.finishtime=0;
	if(!FileExists(".\\ArcDataViewer.exe")) ShowMessage("����������� ���� ArcDataViewer.exe \r\n�������������� ��������� ��� ���������� � ������������");
	if(!FileExists(".\\ArcDataViewer.ini")) ShowMessage("����������� ���� ArcDataViewer.ini \r\n�������������� ��������� ��� ���������� � ������������");
	if(!FileExists(".\\ArcModbusDll.dll")) ShowMessage("����������� ���� ArcModbusDll.dll \r\n�������������� ��������� ��� ���������� � ������������");
	switch(readSettings())
	{
		case 0:

			s=Form1->Caption;
			s+=" �"+IntToStr(hardware.hwMachineNo);
			Form1->Caption=s;
			break;
		case 1:
			switch(MessageBox(NULL,"����� ������� ������ ���������� ������� ������ ������. ������� ���������?","����������� ���� ������������ im58_settings.ini",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND))
			{
				case ID_YES: Form2->ShowModal();return;
				default: return;
			}
		case 2:
			switch(MessageBox(NULL,"����� ������� ������ ���������� ������� ������ ������. ������� ���������?","�� ������� ������ ������",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND))
			{
				case ID_YES: Form2->ShowModal();return;
				default: return;
			}

	}
	switch(Form5->readTestSettings())
	{
		case 0:break;
		case 1: ShowMessage("����� ������� ������ �� �������� ������ ��������� ���������");
		case 2: ShowMessage("����������� ���� im58_test.ini\r\n �������������� ��������� ��� ���������� � ������������");
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm9::AltF41Click(TObject *Sender)
{
	this->Close();
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::N2Click(TObject *Sender)
{
	Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::N7Click(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbHSlider1ValueChange(TObject *Sender)
{
	Edit1->Text=AbHSlider1->Value;
	SetSpeedMotor(hardware.hwDrive,AbHSlider1->Value/1.7);
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key==VK_RETURN)
	{
		if(StrToInt(Edit1->Text)>9000)
		{
			ShowMessage("�������� �� ������ ��������� 9000");
			return;
        }
		this->AbHSlider1->Value=StrToInt(Edit1->Text);
		int speed;
		char u[6];
		uint8_t i;
		sprintf(u,"%s",(AnsiString)Edit1->Text);
		//������ �� �����, ����� ����� ��� ������� �� ����� ���������� �����
		for(i=0;i<7;i++)
		{
			if(u[i]==',') u[i]='.';
		}
		speed=(atoi(u))/1.7;
		SetSpeedMotor(hardware.hwDrive,speed);      //����� 0
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbHSlider2ValueChange(TObject *Sender)
{
	if(test.diskrete==0)
	{
		test.pressure=SimpleRoundTo((double)(AbHSlider2->Value),-3);///(double)10;
		Edit2->Text=test.pressure;
		test.setCurrent(1,((test.pressure)-4)/hardware.k);
	}
	else if (test.diskrete==1)
	 {
		test.pressure=SimpleRoundTo((double)(AbHSlider2->Value),-3);///(double)10);
		Edit2->Text=test.pressure;
		test.setCurrent(1,test.pressure);
	 }
	 else if (test.diskrete==2)
	 {
		test.pressure=SimpleRoundTo((double)AbHSlider2->Value/(double)25/M_PI/BarToKg,-3);
		Edit2->Text=AbHSlider2->Digit;
		test.setCurrent(1,test.pressure);
	 }
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key==VK_RETURN)
	{

		double voltage;
		char u[6];
		uint8_t i;
		sprintf(u,"%s",(AnsiString)Edit2->Text);
		//������ �� �����, ����� ����� ��� ������� �� ����� ���������� �����
		for(i=0;i<7;i++)
		{
			if(u[i]==',') u[i]='.';
		}
       	voltage=atof(u);
		this->AbHSlider2->Value=voltage;//::StrToFloat(Edit2->Text);
	}
}
//---------------------------------------------------------------------------
void TTest::readIOStatus(void)
{
	qStr strIO;
	strIO.qBytes[0]=0x01;
	strIO.qBytes[1]=0x02;
	strIO.qBytes[2]=0x00;
	strIO.qBytes[3]=0x00;
	strIO.qBytes[4]=0x00;
	strIO.qBytes[5]=0x10;
	strIO.qBytes[6]=0x79;
	strIO.qBytes[7]=0xc6;
	strIO.size=8;
	serialQueue1.push(strIO);
}
//---------------------------------------------------------------------------
void TTest::setCurrent(bool chanel, double voltage)
{
	//�� �� ��������� ������� � ����, ����� � ������
	voltage*=hardware.k;
	voltage+=4;


	qStr strVout;
	char temp[4];
	int voltagesend,vout1,vout2;
	//����� �������� ��� � ������������
	int vint=voltage*1000;

	AnsiString voltagetemp =IntToHex(vint,4);
	AnsiString vbyte1 = "0x" + voltagetemp.SubString(0, 2);
	AnsiString vbyte2 = "0x" + voltagetemp.SubString(3, 2);
	vout1=vbyte1.ToInt();
	vout2=vbyte2.ToInt();
	//��� ������ �������� �� ��������� modbus rtu.
	//������ ������ - �����
	//������ - ������� (06h - write single register)
	//������ � ������ - �����
	//��������� � ����� - ���������� � hex
	//5 � 6 - ����������� �����
	strVout.qBytes[0]=0x02;
	strVout.qBytes[1]=0x06;
	strVout.qBytes[2]=0x00;
	strVout.qBytes[3]=0x00;
	strVout.qBytes[4]=vout1;
	strVout.qBytes[5]=vout2;
	crc16(strVout.qBytes,6,&crc1,&crc2); //���������� ����������� �����
	//�������� ����������� �����, ������ � � ��� �����
	strVout.qBytes[6]=crc1;
	strVout.qBytes[7]=crc2;
	strVout.size=8;
	serialQueue1.push(strVout);
}
//---------------------------------------------------------------------------
void TTest::setDOuts(uint8_t channel, uint8_t status)
{
	qStr strDO;
	strDO.qBytes[0]=0x05;		//����� ������ � ��������� �������� - 5
	strDO.qBytes[1]=0x05;		//�������
	strDO.qBytes[2]=0x00;		//����� ������ ����
	strDO.qBytes[3]=channel;	//����� ����
	strDO.qBytes[4]=status;		//���-����
	strDO.qBytes[5]=0x00; 		//������� ��� ����
	crc16(strDO.qBytes,6,&crc1,&crc2); //���������� ����������� �����
	//�������� ����������� �����, ������ � � ��� �����
	strDO.qBytes[6]=crc1;
	strDO.qBytes[7]=crc2;
	strDO.size=8;
	serialQueue1.push(strDO);	//������ � �������

}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbToggleSwitch6StatusChanged(TObject *Sender)
{
//������ �2
	if(AbToggleSwitch6->StatusInt==1)
	{
		 test.brake(true);
		//test.setDOuts(0x01,0xFF);
	}
	else
	{
		test.brake(false);
		//test.setDOuts(0x01,0x00);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbToggleSwitch7StatusChanged(TObject *Sender)
{
	//���� ����������  �3
	if(AbToggleSwitch7->StatusInt==1)
	{
		//test.setDOuts(0x02,0xFF);
		test.cooler(true);
	}
	else
	{
		test.cooler(false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbToggleSwitch8Changed(TObject *Sender)
{
int i=0,n=0;
	uint8_t status;

	if(AbToggleSwitch3->StatusInt==1)
	{
		status=0xFF;
	}
	else
	{
		status=0x00;
	}
	qStr strReg;
	strReg.qBytes[0]=0x03;		//����� ������������ - 3
	strReg.qBytes[1]=0x05;		//modbus-�������
	strReg.qBytes[2]=0x00;		//e����� ������ �������
	strReg.qBytes[3]=0x08;		//����� �������
	strReg.qBytes[4]=status;	//��������
	strReg.qBytes[5]=0x00;  	//����� ��������(������ ����� 0)
crc16(strReg.qBytes,6,&crc1,&crc2); //���������� ����������� �����
	//�������� ����������� �����, ������ � � ��� �����
	strReg.qBytes[6]=crc1;
	strReg.qBytes[7]=crc2;
	strReg.size=8;
	serialQueue2.push(strReg);	//������ � �������

}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbToggleSwitch1StatusChanged(TObject *Sender)
{
	//���� ��������� ����� �1
	if(AbToggleSwitch1->StatusInt==1)
	{
		//test.setDOuts(0x00,0xFF);
		test.clutch(true);
	}
	else
	{
		test.clutch(false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbToggleSwitch10StatusChanged(TObject *Sender)
{
	//����� ������ �� ����������. ������ im58_serial, ���� ������ 1, �� ���������� �����
	//���� 0 - ���
	if(AbToggleSwitch10->StatusInt==1)
	{
		if(AbDBLED4->Checked==false)
		{
			ShowMessage("�������� COM-���� 1");
			AbToggleSwitch10->StatusInt=0;
			inputState=false;
		}
		else
		{
			inputState=true;
			AbDBLED6->Flashing=true;
			AbDBLED6->Checked=true;
		}
	}
	if(AbToggleSwitch10->StatusInt==0)
	{
		inputState=false;
		AbDBLED6->Flashing=false;
		AbDBLED6->Checked=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button3Click(TObject *Sender)
{
	TerminateThread(hThread,0);
	CloseHandle(hThread);
	hThread=0;
	Button1->Enabled=true;
	ComboBox2->Enabled=true;
	Button6->Enabled=true;
	test.brake(false);
	Sleep(1000);
	test.clutch(false);
	test.drive(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button1Click(TObject *Sender)
{
	char string[255];
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
			sprintf(string,"�������� ������� � ������ �� ������\r\n");
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
	if(error)
	{
		ShowMessage(string);
		error=false;
		return;
	}
	currentTest.brakecount=0;
	test.brakecount=0;
	Series1->Clear();
	Series2->Clear();
	current_turns=true;
	fulltest=false;
	Button1->Enabled=false;
	ComboBox2->Enabled=false;
	Button6->Enabled=false;
	//hThread=CreateThread(NULL,0,thThread,NULL,0,NULL);
   	if(!hThread)
	{
		hThread=CreateThread(NULL,0,thThread,NULL,0,NULL);
	}
	else ResumeThread(hThread);
	if(!hRec)
	{
		hRec=CreateThread(NULL,0,thRec,NULL,0,NULL);
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button2Click(TObject *Sender)
{
	if(Edit3->Text=="")
	{
		ShowMessage("������� ����� ����");
		return;
	}
	if(AbDBLED5->Checked==true)
	{
		findzero=false;
		volume=StrToInt(Edit3->Text);
		if(!hRec)
		{
			hRec=CreateThread(NULL,0,thRec,NULL,0,NULL);
		}
		else ResumeThread(hRec);
		Form9->ProgressBar1->State=pbsNormal;
		Form9->ProgressBar1->Style=pbstMarquee;
    }
	else
	{
		ShowMessage("�������� COM-���� 2");
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button4Click(TObject *Sender)
{
	if(AbDBLED5->Checked==true)
	{
		volume=-1;
		findzero=false;
		if(!hRec)
		{
			hRec=CreateThread(NULL,0,thRec,NULL,0,NULL);
		}
		else ResumeThread(hRec);
        Form9->ProgressBar1->State=pbsNormal;
		Form9->ProgressBar1->Style=pbstMarquee;

	}
	else
	{
		ShowMessage("�������� COM-���� 2");
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::��������Click(TObject *Sender)
{
	Series1->Clear();
}
//---------------------------------------------------------------------------
void stoprolling (void)
{
	Form9->ProgressBar1->State=pbsPaused;
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button5Click(TObject *Sender)
{
/*	TDateTime start=Series1->MinXValue();
	TDateTime stop=Series1->MaxXValue();
    TDateTime brake=stop-start;
		recorder.braketime=Series1->MaxXValue()-Series1->MinXValue();//����� �� ������� ��� ������, ����� ��������� ����� �� ���������� �������
		TDateTime braking=recorder.braketime;
		Form9->Label8->Caption=braking.TimeString(); */
	this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button6Click(TObject *Sender)
{
	AnsiString aTime;
	currentTest.pressure=(Edit4->Text.ToDouble())/25/M_PI/BarToKg;
	currentTest.rollmax=StrToInt(Edit5->Text);
	currentTest.rolltest=StrToInt(Edit6->Text);
	aTime=MaskEdit1->Text;
	currentTest.cooltime=aTime.SubString(0,2)*60000+aTime.SubString(4,2)*1000;
//� ����� ������� � ��������
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
}
//---------------------------------------------------------------------------
void tacho(void)
{
	// [04][04][00][06][00][02][91][9F]
		qStr strTacho;
	if(tacho_type==TACHO_VEHA_T)
	{
		strTacho.qBytes[0]=hardware.hwTacho;
		strTacho.qBytes[1]=0x04;
		strTacho.qBytes[2]=0x00;
		strTacho.qBytes[3]=0x06;
		strTacho.qBytes[4]=0x00;
		strTacho.qBytes[5]=0x02;
		crc16(strTacho.qBytes,6,&crc1,&crc2);
		strTacho.qBytes[6]=0x91;
		strTacho.qBytes[7]=0x9F;
		strTacho.size=8;
		serialQueue2.push(strTacho);
	}
	else if(tacho_type==TACHO_MERADAT)
	{
//		�������� ������� �12���1 �������� ������ �� ��������� modbus ascii
//		��������� ���������� � :
//		����� ���� �����(2 �������)			//04
//		������� (2 �������)  				//03
//		����� �������� (4 �������)    		//0000
//		���������� ���� (4 �������)			//0001
//		����������� ����� LRC (2 �������)  	//f8
		uint8_t cmd_char[17]={NULL};
		sprintf(cmd_char,"%02d0300000001",hardware.hwTacho);
		uint8_t lrc=LRC(cmd_char);
		sprintf(strTacho.qBytes,":%s%X\r\n",cmd_char,lrc);
		strTacho.size=17;
		serialQueue2.push(strTacho);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbToggleSwitch112StatusChanged(TObject *Sender)
{
	if(AbToggleSwitch112->StatusInt==1)
	{
		StartMotor(hardware.hwDrive,1,this->AbHSlider1->Value);
		current_turns=true;
	}
	else
	{
		StopMotor(hardware.hwDrive);
		current_turns=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::N8Click(TObject *Sender)
{
	this->Hide();
	Form1->Show();
}
//---------------------------------------------------------------------------
void TTest::clutch(bool status)
{
	if(status==true)
	{
		test.setDOuts(0x00,0xFF);
	}
	else
	{
		test.setDOuts(0x00,0x00);
	}
}
//---------------------------------------------------------------------------
void TTest::brake(bool status)
{
	if(status==true)
	{
		test.setDOuts(0x01,0xFF);
	}
	else
	{
		test.setDOuts(0x01,0x00);
	}
}
//---------------------------------------------------------------------------
void TTest::cooler(bool status)
{
	if(status==true)
	{
		test.setDOuts(0x02,0xFF);
	}
	else
	{
		test.setDOuts(0x02,0x00);
	}
}
//---------------------------------------------------------------------------
void TTest::drive(bool status)
{
	if(status==true)
	{
		test.setDOuts(0x06,0xFF);
	}
	else
	{
		test.setDOuts(0x06,0x00);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::ComboBox1Change(TObject *Sender)
{
	//������� ��������� ������� � ������ ����������� ����� ����� �
	//� ������ ������ ������, �.�. ������ ���� ������� ��������� ������� ���������
	double value;
	//�� ��� � ��
	if((test.diskrete==1)&&(wcscmp(ComboBox1->Text.c_str(),L"��")==0))
	{
		test.diskrete=0;
		//����� � �����������
		AbHSlider2->SignalSettings->Name1=("��� �� ���, ��");
		//AbHSlider2->Value*=hardware.k;
		//AbHSlider2->Value+=4;    //�������� 20 ��
		//AbHSlider2->Digit=AbHSlider2->Value*10;
		AbHSlider2->SignalSettings->DigitalTo=200;
		AbHSlider2->SignalSettings->ValueTo=20;
		AbHSlider2->Value=convert.BarToMa(AbHSlider2->Value);
		AbHSlider2->SignalSettings->ValueFrom=4;
		AbHSlider2->SignalSettings->DigitalFrom=40;
		AbHSlider2->ScaleSettings->Steps=8;
		return;
	}
	//�� ��� � ��
	if((test.diskrete==2)&&(wcscmp(ComboBox1->Text.c_str(),L"��")==0))
	{

		test.diskrete=0;
		//����� � �����������
		AbHSlider2->SignalSettings->Name1=("��� �� ���, ��");
		//AbHSlider2->Value*=hardware.k;
		//AbHSlider2->Value+=4;    //�������� 20 ��
		AbHSlider2->Value=convert.KgToMa(AbHSlider2->Value);
		//AbHSlider2->Digit=AbHSlider2->Value*10;
		AbHSlider2->SignalSettings->ValueFrom=4;
		AbHSlider2->SignalSettings->ValueTo=20;
		AbHSlider2->SignalSettings->DigitalFrom=40;
		AbHSlider2->SignalSettings->DigitalTo=200;
		AbHSlider2->ScaleSettings->Steps=8;
		return;
	}
	//�� �� � ����
	if((test.diskrete==0)&&(wcscmp(ComboBox1->Text.c_str(),L"���")==0))
	{
		test.diskrete=1;
		//����� � �����������
		AbHSlider2->SignalSettings->Name1=("��������, ���");
     	//AbHSlider2->Value+=4;    //�������� 20 ��
		//AbHSlider2->Digit=AbHSlider2->Value*10;
		AbHSlider2->SignalSettings->DigitalFrom=0;
		AbHSlider2->SignalSettings->DigitalTo=50;
		AbHSlider2->SignalSettings->ValueFrom=0;
		AbHSlider2->SignalSettings->ValueTo=5;
		AbHSlider2->ScaleSettings->Steps=5;
		AbHSlider2->Value=convert.MaToBar(AbHSlider2->Value);
		return;
	}
	//�� �� � ���
	if((test.diskrete==0)&&(wcscmp(ComboBox1->Text.c_str(),L"���")==0))
	{
		test.diskrete=2;
		//����� � �����������
		AbHSlider2->SignalSettings->Name1=("������ ������, ���");
		//AbHSlider2->Value*=hardware.k;
		//AbHSlider2->Value+=4;    //�������� 20 ��
		AbHSlider2->SignalSettings->DigitalFrom=0;
		AbHSlider2->SignalSettings->DigitalTo=500;
		AbHSlider2->SignalSettings->ValueFrom=0;
		AbHSlider2->SignalSettings->ValueTo=500;
		AbHSlider2->ScaleSettings->Steps=5;
		AbHSlider2->Value=convert.MaToKg(AbHSlider2->Value);
		return;
	}
	//�� ��� � ����
	if((test.diskrete==2)&&(wcscmp(ComboBox1->Text.c_str(),L"���")==0))
	{
		test.diskrete=1;
		//����� � �����������
		AbHSlider2->SignalSettings->Name1=("��������, ���");
		AbHSlider2->Value=convert.KgToBar(AbHSlider2->Value);
		//AbHSlider2->Value+=4;    //�������� 20 ��
		//AbHSlider2->Digit=AbHSlider2->Value*10;
		AbHSlider2->SignalSettings->DigitalFrom=0;
		AbHSlider2->SignalSettings->DigitalTo=50;
		AbHSlider2->SignalSettings->ValueFrom=0;
		AbHSlider2->SignalSettings->ValueTo=5;
		AbHSlider2->ScaleSettings->Steps=5;
		return;
	}
	//�� ��� � ���
	if((test.diskrete==1)&&(wcscmp(ComboBox1->Text.c_str(),L"���")==0))
	{
		test.diskrete=2;
		//����� � �����������
		AbHSlider2->SignalSettings->Name1=("������ ������, ���");
		//AbHSlider2->Value*=hardware.k;
		//AbHSlider2->Value+=4;    //�������� 20 ��
		AbHSlider2->SignalSettings->DigitalFrom=0;
		AbHSlider2->SignalSettings->DigitalTo=500;
		AbHSlider2->SignalSettings->ValueFrom=0;
		AbHSlider2->SignalSettings->ValueTo=500;
		AbHSlider2->Value=convert.BarToKg_conv(AbHSlider2->Value);
		AbHSlider2->Digit=AbHSlider2->Value;
		AbHSlider2->ScaleSettings->Steps=5;
      	return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::COM1Click(TObject *Sender)
{
	Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::N4Click(TObject *Sender)
{
	Form5->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::N10Click(TObject *Sender)
{
	this->Hide();
	Form8->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button10Click(TObject *Sender)
{
	tacho_reset();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button11Click(TObject *Sender)
{
	result_flag=true;
	current_turns=false;
	Sleep(500);
	tacho_result();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::FormShow(TObject *Sender)
{
	//tacho();
	current_turns=true;
	ReadRegChannels=true;
 	if(!hRec)
	{
		hRec=CreateThread(NULL,0,thRec,NULL,CREATE_SUSPENDED,NULL);
	}
	if(ComboBox2->Items->Count==0)
	{
		int i=0;
		do
		{
			//currentTest=vectorTest[i];
			ComboBox2->Items->Add(vectorTest[i].name);
			i++;
		}
		while(i<vectorTest.size());
		ComboBox2->ItemIndex=-1;
	}
	Chart1->LeftAxis->Automatic=true;
	Chart1->BottomAxis->Automatic=true;
	Series1->Clear();
	Series2->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm9::ComboBox2Change(TObject *Sender)
{
	currentTest=vectorTest[ComboBox2->ItemIndex];
	Edit4->Text=currentTest.pressure*25*M_PI*BarToKg;
	Edit5->Text=currentTest.rollmax;
	Edit6->Text=currentTest.rolltest;
	char asdf[5];
	int mins=(currentTest.cooltime/1000)/60;
	int secs=(currentTest.cooltime/1000)-mins*60;
	sprintf(asdf,"%02d:%02d",mins,secs);
	MaskEdit1->Text=asdf;
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
	tacho_preset(currentTest.rolltest);
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbToggleSwitch2Click(TObject *Sender)
{
		if(!this->AbLED2->Checked)
		{
			test.drive(true);
		}
		else
		{
			test.drive(false);
		}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::FormHide(TObject *Sender)
{
	ReadRegChannels=false;
	test.setCurrent(1,0);
	test.clutch(false);
	test.drive(false);
	test.cooler(false);
	test.brake(false);
	if(!port1Closed)
	{
		comPort1Close();
	}
	if(!port2Closed)
	{
		comPort2Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbLED2StatusChanged(TObject *Sender)
{
	Form9->AbToggleSwitch2->Checked=Form9->AbLED2->Checked;
	if(this->AbLED2->Checked==true)
	{
		this->AbToggleSwitch2->Checked=true;
		AbToggleSwitch2->StatusInt=1;
	}
	else
	{
		this->AbToggleSwitch2->Checked=false;
		AbToggleSwitch2->StatusInt=0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbDBLED4StatusChanged(TObject *Sender)
{
	this->AbToggleSwitch4->Checked=AbDBLED4->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbDBLED5StatusChanged(TObject *Sender)
{
	this->AbToggleSwitch5->Checked=AbDBLED5->Checked;
	AbToggleSwitch5->StatusInt=AbDBLED5->StatusInt;
}
//---------------------------------------------------------------------------

void __fastcall TForm9::AbToggleSwitch4Click(TObject *Sender)
{
	if(!AbDBLED4->Checked)
	{
		comPort1Init();
	}
	else
	{
		AbDBLED4->LED->ColorOff=clBtnFace;
		this->AbDBLED4->Checked=false;
		comPort1Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::AbToggleSwitch5Click(TObject *Sender)
{
	if(!AbDBLED5->Checked)
	{
		comPort2Init();
	}
	else
	{
		comPort2Close();
		AbDBLED5->LED->ColorOff=clBtnFace;
		this->AbDBLED5->Checked=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::AbDBLED6StatusChanged(TObject *Sender)
{
	AbToggleSwitch10->Checked=AbDBLED6->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Timer1Timer(TObject *Sender)
{
		if(Form4&&Form9)
		{
		Edit7->Text=FloatToStr(regValue[0].f);
		Edit8->Text=FloatToStr(regValue[1].f);
		Form9->CheckBox3->Checked=events.DriveVoltageEvent;
		Form9->AbLED2->Checked=events.DriveVoltageEvent;
		Form4->AbLED2->Checked=events.DriveVoltageEvent;
		Form4->AbToggleSwitch1->Checked=events.AutoConnectEvent;
	qString thString;
	if(!textqueue.empty())                 //���� ������� �� ������
	{		//�������� ������ �������
		thString=textqueue.front();
		if(thString.bold==true)
		{
			Form9->RichEdit1->SelAttributes->Style=Form9->RichEdit1->SelAttributes->Style<<fsBold;
			Form9->RichEdit1->Lines->Add(thString.string);
			Form9->RichEdit1->SelAttributes->Style=Form9->RichEdit1->SelAttributes->Style>>fsBold;
			Form4->RichEdit1->SelAttributes->Style=Form4->RichEdit1->SelAttributes->Style<<fsBold;
			Form4->RichEdit1->Lines->Add(thString.string);
			Form4->RichEdit1->SelAttributes->Style=Form9->RichEdit1->SelAttributes->Style>>fsBold;

		}
		else
		{
			Form9->RichEdit1->Lines->Add(thString.string);
			Form4->RichEdit1->Lines->Add(thString.string);
		}
		//�������������
		SendMessage(Form9->RichEdit1->Handle, WM_VSCROLL, MAKEWPARAM(SB_BOTTOM,0), 0);
		SendMessage(Form4->RichEdit1->Handle, WM_VSCROLL, MAKEWPARAM(SB_BOTTOM,0), 0);
		thString.string=NULL;
		thString.bold=false;
		textqueue.pop();	//���� ������� �� ������, ������� �� �� ���� �������
	}
	Ab180Meter1->Digit=test.rolls;
	Ab180Meter1->SignalSettings->Name2=test.rolls;
	if(DiagramPrepared)
	{
		Series1->Clear();
		Series2->Clear();
		Form4->Series1->Clear();
		Form4->Series2->Clear();
		for(int i=0;i<=vDiagram.size()-1;i++)
		{
			sDiagram=vDiagram[i];
			Series1->AddXY(sDiagram.idx,sDiagram.value1);
			Series2->AddXY(sDiagram.idx,sDiagram.value2);
			//Form9->RichEdit1->Lines->Add(IntToStr(i)+" "+FloatToStr(sDiagram.value2)+" "+FormatDateTime("hh:mm:ss:zzz",sDiagram.datetime));
			Form4->Series1->AddXY(sDiagram.idx,sDiagram.value1);
			Form4->Series2->AddXY(sDiagram.idx,sDiagram.value2);
		}
		Chart1->UndoZoom();
		Form4->Chart1->UndoZoom();
		DiagramPrepared=false;
	}
    }
}
//---------------------------------------------------------------------------
double TConvert::MaToBar(double value)
{
	double result=value-4;
	result/=hardware.k;
	return result;
}
//---------------------------------------------------------------------------

double TConvert::MaToKg(double value)
{
	double result=MaToBar(value)*25*M_PI*BarToKg;
	return result;
}
//---------------------------------------------------------------------------
double TConvert::KgToMa(double value)
{
	double result=KgToBar(value);
	result=BarToMa(result);
	return result;
}
//---------------------------------------------------------------------------
double TConvert::KgToBar(double value)
{
	double result=value/25/M_PI/BarToKg;
	return result;
}
//---------------------------------------------------------------------------
double TConvert::BarToMa(double value)
{
	double result=value*hardware.k;
	result+=4;
	return result;
}
//---------------------------------------------------------------------------
double TConvert::BarToKg_conv(double value)
{
   double result=value*25*M_PI*BarToKg;
   return result;
}
//---------------------------------------------------------------------
void __fastcall TForm9::AbToggleSwitch10Click(TObject *Sender)
{
	if(AbToggleSwitch10->StatusInt==1)
	{
		if(AbDBLED4->Checked==false)
		{
			ShowMessage("�������� COM-���� 1");
			AbToggleSwitch10->StatusInt=0;
			inputState=false;
			return;
		}
		else
		{
			inputState=true;
			AbDBLED6->Flashing=true;
			AbDBLED6->Checked=true;
		}
	}
	if(AbToggleSwitch10->StatusInt==0)
	{
		inputState=false;
		AbDBLED6->Flashing=false;
		AbDBLED6->Checked=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button7Click(TObject *Sender)
{
//		�������� ������� �12���1 �������� ������ �� ��������� modbus ascii
//		��������� ���������� � :
//		����� ���� �����(2 �������)			//04
//		������� (2 �������)  				//03
//		����� �������� (4 �������)    		//0000
//		���������� ���� (4 �������)			//0001
//		����������� ����� LRC (2 �������)  	//f8
		qStr strTacho;
		uint8_t cmd_char[17]={NULL};
		uint16_t hex=0;
		AnsiString shex;
			unsigned long dwBytesWritten;
		int i;
		unsigned long temp;
		char data_in[255];
		for (hex = 0; hex < 0x7FFF; hex++)
		{
		memset(data_in,NULL,255);
		Sleep(50);
			shex=IntToHex(hex,4);
			sprintf(cmd_char,"%02d03%s0001",hardware.hwTacho,shex.c_str());
			uint8_t lrc=LRC(cmd_char);
			sprintf(strTacho.qBytes,":%s%X\r\n",cmd_char,lrc);
			WriteFile(ComPort2,strTacho.qBytes,17,&dwBytesWritten,NULL);
			Sleep(50);
				ReadFile(ComPort2, &data_in, 255, &temp, NULL);
			AnsiString aresult=(AnsiString)(char*)data_in;
			aresult=aresult.SubString(8,4);
			if(aresult!="FFFF")
			{
				int a=0;
            }
		}
}
//---------------------------------------------------------------------------
bool tacho_checkconnect(int tacho_type)
{
	int crc1,crc2;
	unsigned long dwBytesWritten,dwBytesRead;
	qStr strTacho;
	byte data_in[24];
	//������������ ������ ���-�����, ����� ��� �� ������ �������� �����
	if(hPort2)
	{
		SuspendThread(hPort2);
	}
  	ReadFile(ComPort2, &data_in, 255, &dwBytesRead, NULL); //�������� �������� ����� ���-�����
	if(tacho_type==TACHO_VEHA_T)
	{
		strTacho.qBytes[0]=hardware.hwTacho;
		strTacho.qBytes[1]=0x04;
		strTacho.qBytes[2]=0x00;
		strTacho.qBytes[3]=0x06;
		strTacho.qBytes[4]=0x00;
		strTacho.qBytes[5]=0x02;
		crc16(strTacho.qBytes,6,&crc1,&crc2);
		strTacho.qBytes[6]=crc1;
		strTacho.qBytes[7]=crc2;
		WriteFile(ComPort2,strTacho.qBytes,8,&dwBytesWritten,NULL);
		Sleep(100);
		ReadFile(ComPort2, &data_in, 255, &dwBytesRead, NULL);
		char checkString[3];
		checkString[0]=hardware.hwTacho;
		checkString[1]=0x04;
		checkString[2]=0x04;
		if(strncmp(checkString,data_in,3)==0)
		{
			ReadFile(ComPort2, &data_in, 255, &dwBytesRead, NULL);
			ResumeThread(hPort2);
			return true;
		}
		else
		{
			ReadFile(ComPort2, &data_in, 255, &dwBytesRead, NULL);
			ResumeThread(hPort2);
			return false;
		}
	}
	else if(tacho_type==TACHO_MERADAT)
	{
//		�������� ������� �12���1 �������� ������ �� ��������� modbus ascii
//		��������� ���������� � :
//		����� ���� �����(2 �������)			//04
//		������� (2 �������)  				//03
//		����� �������� (4 �������)    		//0000
//		���������� ���� (4 �������)			//0001
//		����������� ����� LRC (2 �������)  	//f8
		uint8_t cmd_char[17]={NULL};
		sprintf(cmd_char,"%02d0300000001",hardware.hwTacho);
		uint8_t lrc=LRC(cmd_char);
		sprintf(strTacho.qBytes,":%s%X\r\n",cmd_char,lrc);
		WriteFile(ComPort2,strTacho.qBytes,17,&dwBytesWritten,NULL);
		Sleep(100);
		ReadFile(ComPort2, &data_in, 255, &dwBytesRead, NULL);
		AnsiString checkString=":"+IntToHex(hardware.hwTacho,2)+"0302";
		if(strncmp(checkString.c_str(),data_in,7)==0)
		{
			ReadFile(ComPort2, &data_in, 255, &dwBytesRead, NULL);
			ResumeThread(hPort2);
			return true;
		}
		else
		{
			ReadFile(ComPort2, &data_in, 255, &dwBytesRead, NULL);
			ResumeThread(hPort2);
			return false;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm9::Button8Click(TObject *Sender)
{
tacho_reset();
}
//---------------------------------------------------------------------------
/*
 * �������� ������� ������� � �������
 */
bool TTest::checkForAir(void)
{
	test.setCurrent(1,hardware.pressuremax);  					//���������� �������� 500 ��� � ��������       500/25/M_PI/BarToKg
	Sleep(1000);
	test.brake(true);							//�������� ������ (��������� ����)
	Sleep(3000);                             	//���� //rsv:28.07.2016 �������� ������������ � ����� � ���������� ��������
	double v_ref=350;							//350 - ��������� �������� � ���(� ������������), 75 - ������� ����������� ��������(���������� ���� 78.54, ����� ���������� - 72.11)
	if(regValue[0].f<=v_ref)
	{
		test.brake(false);
		Sleep(2000);
		test.setCurrent(1,0);
		Sleep(500);
		//���� �������� ������, ��� 350 ��(4.5 ���) - ������ ������ �� ���������� ������� � �������
		return false;
	}
	else
	{
		test.brake(false);
		Sleep(2000);
		test.setCurrent(1,0);
		Sleep(500);
		return true;
	}

}

