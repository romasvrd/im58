//---------------------------------------------------------------------------

#pragma hdrstop
#include <windows.h>
#include "Registry.hpp"
#include <vcl.h>
#include "im58main.h"
#include "im58serial.h"
#include "im58about.h"
#include "im58drive.h"
#include "im58recorder.h"
#include "IniFiles.hpp"
#include <io.h>
#include "im58auto.h"
#include <DateUtils.hpp>
#include "im58hello.h"
#include "im58results.h"
#include <queue>
#include <iostream>
#include <sstream>
int x_arr[2]={0};
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
extern strHardware hardware;
extern TEvents events;
extern rec_struct recorder;
extern TTest test;
extern HANDLE hThread;
extern DWORD WINAPI thThread(void*);
extern std::queue<qString> textqueue;
extern char progpath[254];
qString serialstring;
#define w 0
int dataCountOut1=w,dataCountIn1=w,dataCountErr1=w,dataCountOut2=w,dataCountIn2=w,dataCountErr2=w;
//---------------------------------------------------------------------------
#include <queue>
to_iee754_t regValue[2];
HANDLE ComPort1;
HANDLE ComPort2;
HANDLE hPort1;
HANDLE hPort2;
using namespace std;
char line[255];
portSettings portSet;
extern uint16_t firstVol,lastVol,firstPage,lastPage;
std::queue<qStr> serialQueue1;
std::queue<qStr> serialQueue2;
extern std::queue<AnsiString> qGui;
DWORD WINAPI thPort1(LPVOID);
DWORD WINAPI thPort2(LPVOID);
#define BUFSIZE 255     //ёмкость буфера
extern  TTestResults testresults[16];
bool port1Closed=true;
bool port2Closed=true;
BYTE temp[4];
const double onebit = 1.2239;
int crc1,crc2,vout1,vout2;
uint64_t datacount=0;
TIniFile *Ini = new TIniFile(".\\im58_settings.ini");
bool fullheader=false;
strSwap sSwap;
bool inputState=false;
bool current_turns=false;
bool result_flag;
extern bool change;
bool Read1(void);
bool Read2(void);
//TStringList *sl1;
//TStringList *sl2;
extern int tacho_type;
extern bool ReadRegChannels;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
 	defaultSettings();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
    AnsiString KeyName = "\\Hardware\\DeviceMap\\SerialComm";
	TStringList *SerialCommValues = new TStringList();
	ComboBox1->Items->Clear();
	TRegistry *Registry = new TRegistry;
	try
	{
		Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->OpenKeyReadOnly( KeyName );
		Registry->GetValueNames( SerialCommValues );
		for(int i=0; i<SerialCommValues->Count; i++)
		{
			ComboBox1->Items->Add(Registry->ReadString(SerialCommValues->Strings[i]));
			ComboBox4->Items->Add(Registry->ReadString(SerialCommValues->Strings[i]));
		}

	}
	__finally
	{
		delete Registry;
		delete SerialCommValues;
		if (ComboBox1->ItemIndex<0)
		{
			ComboBox1->ItemIndex=0;
			ComboBox4->ItemIndex=0;
		}
		printSettings();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender)
{
	defaultSettings();
}
//------------------------------------------------------------------------------
DWORD WINAPI thPort1(LPVOID)
{
	unsigned long dwBytesWritten;
	qStr cmdstr;
	byte cmd[24];
	int errcount;
	bool err=false;
	int crc1,crc2;
	while (1)
	{
         if(inputState==true)
		{
			test.readIOStatus();  		//считать входы
        }

	while(!serialQueue1.empty())                 //если очередь не пустая
		{
			errcount=0;
			memset(cmd,0x00,24);
			cmdstr=serialQueue1.front();  			//получаем начало очереди
			memcpy(cmd,cmdstr.qBytes,cmdstr.size);	        //берем из неё байты на отправку
			do
			{
				do
				{
					WriteFile(ComPort1,cmd,cmdstr.size,&dwBytesWritten,NULL);		//отправляем
					dataCountOut1++;
					if(!Read1())
					{
						errcount++;
						err=true;
					}
					else
					{
						err=false;
                       	break;
					}
				}
				while (errcount<5);
				if(errcount>=5&&err==true)
				{
					crc16(cmd,6,&crc1,&crc2);//пересчитываю црц
				}

			}
			while (errcount<10&&err==true);
			if(err&&errcount>=10)
			{
//				ShowMessage("Ошибка связи на порте 1");
//				Form4->Button3Click(Form4);
//				comPort1Close();
			serialQueue1.pop();	//если очередь не пустая, удаляем из неё один элемент
            }
			serialQueue1.pop();	//если очередь не пустая, удаляем из неё один элемент
		}
		Sleep(50);
	}
}
//------------------------------------------------------------------------------
DWORD WINAPI thPort2(LPVOID)
{
	unsigned long dwBytesWritten;
	qStr cmdstr;
	int errcount;
	byte cmd[24];
	bool err=false;
	int crc1,crc2;
	while (1)
	{

		if(current_turns)
		{
			tacho();
		}
		if(ReadRegChannels)
		{
			regReadValue();
        }
		while(!serialQueue2.empty())                 //если очередь не пустая
		{
			errcount=0;
			memset(cmd,0x00,24);
			cmdstr=serialQueue2.front();  			//получаем начало очереди
			memcpy(cmd,cmdstr.qBytes,cmdstr.size);	        //берем из неё байты на отправку
			do
			{
				do
				{
					WriteFile(ComPort2,cmd,cmdstr.size,&dwBytesWritten,NULL);		//отправляем
					dataCountOut2++;
					if(!Read2())
					{
						errcount++;
						err=true;
					}
					else
					{
						err=false;
                       	break;
					}
				}
				while (errcount<5);
				if(errcount>=5&&err==true)
				{
					crc16(cmd,6,&crc1,&crc2);//пересчитываю црц
				}

			}
			while (errcount<10&&err==true);
			if(err&&errcount>=10)
			{
				serialQueue2.pop();	//если очередь не пустая, удаляем из неё один элемент
//				ShowMessage("Ошибка связи на порте 2");
//				Form4->Button3Click(Form4);
//				comPort2Close();
            }
			serialQueue2.pop();	//если очередь не пустая, удаляем из неё один элемент
		}
		Sleep(50);
	}
}
//------------------------------------------------------------------------------
bool Read2(void)
{
		int crc1,crc2;
	byte data_in[BUFSIZE]; //приёмный буфер
	UnicodeString s="IN  ";
	unsigned long temp;	//переменная temp используется в качестве заглушки
	memset(data_in,NULL,sizeof(data_in));
	Sleep(55); //чтобы дождаться прихода всех байтов
	ReadFile(ComPort2, &data_in, 255, &temp, NULL);     //прочитать байты из порта в буфер программы
	//разбираем пакет
//	for (int i = 0; i < temp; i++)
//	{
//		s+="0x"+IntToHex(data_in[i],1)+" ";
//	}
	if(temp<=3||data_in==NULL)
	{
				memset(data_in,NULL,sizeof(data_in));
		dataCountErr2++;
		ReadFile(ComPort2, &data_in, 4096, &temp, NULL); //очистить очередь
		return false;
	}
	crc16(data_in,temp-2,&crc1,&crc2);
	if(((crc1!=data_in[temp-2]||crc2!=data_in[temp-1])&&(crc2!=data_in[temp-2]||crc1!=data_in[temp-1]))&&tacho_type==TACHO_VEHA_T)
	{
		s+="[ERR CRC]";
//		sl2->Add(s); 	//запись в лог
//		try
//		{
//			sl2->SaveToFile((UnicodeString)progpath+"port2log.txt");
//		}
//		catch(Exception &e)
//		{
//
//		}
		memset(data_in,NULL,sizeof(data_in));
		dataCountErr2++;
		ReadFile(ComPort2, &data_in, 4096, &temp, NULL); //очистить очередь
		return false;  //если первый байт расчитанной хэш-суммы не совпадает с первым байтом принятой хэш-суммы - не обрабатываем такой пакет
	}
	dataCountIn2++;
	s+="[OK]";
//	sl2->Add(s); 	//запись в лог
//	try
//	{
//		sl2->SaveToFile((UnicodeString)progpath+"port2log.txt");
//	}
//	catch(Exception &e)
//	{
//
//	}
	if (data_in[0]==hardware.hwReg)
	{
		//пришел ответ от регистратора. смотрим, что за функция
		switch(data_in[1])
		{
			case 109:
			switch(data_in[2])
			{
				case 1:
				{
					memcpy(sSwap.in,&data_in[3],4);
					recorder.firstVolume=swapBytes(&sSwap);
					memcpy(recorder.firstVolumeBytes,sSwap.in,4);
					sprintf(line,"Первый том %d\r\n",recorder.firstVolume+1);
					Form9->Memo1->SetSelText(line);
					break;
				}
				case 2:
				{
					memcpy(sSwap.in,&data_in[3],4);
					recorder.lastVolume=swapBytes(&sSwap);
					memcpy(recorder.lastVolumeBytes,sSwap.in,4);
					sprintf(line,"Последний том %d\r\n",recorder.lastVolume+1);
					if(Form9->Visible)Form9->Memo1->SetSelText(line);
					break;
				}
			}
			break;
			case 0x04:
			{
				if(data_in[2]==0x0C)		//мгновенные значения на измерительных каналах
				{   						//значения приходят в формате ieee754 big endian
					regValue[0].b[3]=data_in[3];
					regValue[0].b[2]=data_in[4];
					regValue[0].b[1]=data_in[5];
					regValue[0].b[0]=data_in[6];
					regValue[1].b[3]=data_in[7];
					regValue[1].b[2]=data_in[8];
					regValue[1].b[1]=data_in[9];
					regValue[1].b[0]=data_in[10];
				}
			}
			default:break;
		}
	}
	else if(data_in[0]==hardware.hwTacho&&data_in[1]==0x04)
	{
		if(current_turns)  //текущие обороты
		{
			AnsiString aresult="0x"+IntToHex(data_in[5],2)+IntToHex(data_in[6],2);
			test.rolls=aresult.ToInt();
		}
		else	//количество оборотов
		if(result_flag)
		{
			AnsiString aresult="0x"+IntToHex(data_in[5],2)+IntToHex(data_in[6],2);
			testresults[test.brakecount].обороты_за_торможение=aresult.ToInt();
		}
	}
	else if((data_in[0]==':')&&(tacho_type==TACHO_MERADAT)&&temp==15)
	{
		try
		{
			int8_t dIn[10];
			sprintf(dIn,&data_in[1]);
			int8_t lrc=LRC(dIn);
			AnsiString aresult=(AnsiString)(char*)data_in;
			aresult=aresult.SubString(8,4);
//			if(aresult!="0000")
//			{
				try
				{
					unsigned int x=0;
					std::stringstream ss;
					ss << std::hex << aresult.c_str();
					ss >> x;
					x_arr[1]=x;
					if((x_arr[1]>=x_arr[0]+200)||x_arr[1]<=x_arr[0]-200)
					{

					}
					else
					{
						test.rolls=x;
					}
					x_arr[0]=x_arr[1];
				}
				catch(Exception &e)
				{
					int a=0;
				}
//			}
		}
		catch(Exception &e)
		{
            int b=0;
        }
	}
	ReadFile(ComPort2, &data_in, 4096, &temp, NULL); //очистить очередь
	return true;
}
 //------------------------------------------------------------------------------
bool Read1(void)
{
	int crc1,crc2;
	UnicodeString s="IN  ";
	unsigned char data_in[BUFSIZE];
	DWORD temp;	//переменная temp используется в качестве заглушки
	memset(data_in,NULL,sizeof(data_in));
	Sleep(50); //чтобы дождаться прихода всех байтов
	ReadFile(ComPort1, &data_in, 16, &temp, NULL);     //прочитать байты из порта в буфер программы
	for (int i = 0; i < temp; i++)
	{
		s+="0x"+IntToHex(data_in[i],1)+" ";
	}
	//проверка контрольной суммы
	if(temp<=3||data_in==NULL)
	{
		s+="[ERR SIZE]";
//		sl1->Add(s); 	//запись в лог
//		try
//		{
//			sl1->SaveToFile((UnicodeString)progpath+"port1log.txt");
//		}
//		catch(Exception &e)
//		{
//			int a=0;
//		}
		memset(data_in,NULL,sizeof(data_in));
		dataCountErr1++;
		ReadFile(ComPort1, &data_in, 4096, &temp, NULL); //очистить очередь
		return false;
	}
	crc16(data_in,temp-2,&crc1,&crc2);
	if(crc1!=data_in[temp-2]||crc2!=data_in[temp-1])	//если первый байт расчитанной хэш-суммы не совпадает с первым байтом принятой хэш-суммы - не обрабатываем такой пакет
	{
		s+="[ERR CRC]";
//		sl1->Add(s); 	//запись в лог
//		try
//		{
//			sl1->SaveToFile((UnicodeString)progpath+"port1log.txt");
//		}
//		catch(Exception &e)
//		{
//				int a=0;
//		}
		memset(data_in,NULL,sizeof(data_in));
		dataCountErr1++;
		ReadFile(ComPort1, &data_in, 4096, &temp, NULL); //очистить очередь
		return false;
	}
	dataCountIn1++;
	s+="[OK]";
//	sl1->Add(s); 	//запись в лог
//	try
//	{
//		sl1->SaveToFile((UnicodeString)progpath+"port1log.txt");
//	}
//	catch(Exception &e)
//		{
//				int a=0;
//		}
	//разбираем пакет
	if (data_in[0]==hardware.hwDInputs)
	{
		byte state[2][16];
		int32_t intstate[2];
		itoa(data_in[3],state[0],2);//получаем двоичный код наоборот
		itoa(data_in[4],state[1],2);
		intstate[0]=atoi(state[0]);			//получаем двоичный код
		intstate[1]=atoi(state[1]);
		sprintf(state[0],"%08d",intstate[0]);//добиваем двоичный код нулями
		sprintf(state[1],"%08d",intstate[1]);
		//обрабатываем первый байт
		if(state[0][7]=='1')
		{
			//авария
			Form9->CheckBox1->Checked=true;
			Form4->AbLED3->Checked=true;
			Form9->AbLED3->Checked=true;
			if(hThread)
			{
				TerminateThread(hThread,0);
				CloseHandle(hThread);
				hThread=0;
			}
		}
		else
		{
			Form9->CheckBox1->Checked=false;
			Form9->AbLED3->Checked=false;
			Form4->AbLED3->Checked=false;
		}
		if(state[0][6]=='1')
		{
		   //питание 220
			Form9->CheckBox2->Checked=true;
			Form4->AbLED1->Checked=true;
			Form9->AbLED1->Checked=true;
		}
		else
		{
			Form9->CheckBox2->Checked=false;
			Form4->AbLED1->Checked=false;
			Form9->AbLED1->Checked=false;
		}
		if(state[0][5]=='1')
		{
			//питание привода
			events.DriveVoltageEvent=true;
		}
		else
		{
			events.DriveVoltageEvent=false;
		}
		if(state[0][4]=='1') Form9->CheckBox4->Checked=true;
		else	Form9->CheckBox4->Checked=false;
		if(state[0][3]=='1') Form9->CheckBox5->Checked=true;
		else	Form9->CheckBox5->Checked=false;
		if(state[0][2]=='1') Form9->CheckBox6->Checked=true;
		else	Form9->CheckBox6->Checked=false;
		if(state[0][1]=='1') Form9->CheckBox7->Checked=true;
		else	Form9->CheckBox7->Checked=false;
		if(state[0][0]=='1') Form9->CheckBox8->Checked=true;
		else	Form9->CheckBox8->Checked=false;
		//обрабатываем второй байт
		if(state[1][7]=='1') Form9->CheckBox9->Checked=true;
		else	Form9->CheckBox9->Checked=false;
		if(state[1][6]=='1') Form9->CheckBox10->Checked=true;
		else	Form9->CheckBox10->Checked=false;
		if(state[1][5]=='1') Form9->CheckBox11->Checked=true;
		else	Form9->CheckBox11->Checked=false;
		if(state[1][4]=='1')
		Form9->CheckBox12->Checked=true;
		else	Form9->CheckBox12->Checked=false;
		if(state[1][3]=='1') Form9->CheckBox13->Checked=true;
		else	Form9->CheckBox13->Checked=false;
		if(state[1][2]=='1') Form9->CheckBox14->Checked=true;
		else	Form9->CheckBox14->Checked=false;
		if(state[1][1]=='1') Form9->CheckBox15->Checked=true;
		else	Form9->CheckBox15->Checked=false;
		if(state[1][0]=='1') Form9->CheckBox16->Checked=true;
		else	Form9->CheckBox16->Checked=false;
	}
	ReadFile(ComPort1, &data_in, 4096, &temp, NULL); //очистить очередь
	return true;                                       //увеличиваем счётчик байтов
}
//---------------------------------------------------------------------------
int swapBytes(strSwap *str)
{
	int result;
	for(int i=0;i<=3;i++)
	{
		str->out[i]=str->in[3-i];

	}
	str->Aout="0x"
	+IntToHex(str->out[0],2)
	+IntToHex(str->out[1],2)
	+IntToHex(str->out[2],2)
	+IntToHex(str->out[3],2);
	//memcpy(ieee754.bytes,sSwap.dst,4);
	//x=ieee754.value;
   //	uint32_t out;
	if(str->Aout!="0x0") result=str->Aout.ToInt();
	else result=0;
	//y++;
	//Form9->Series1->AddXY(result,y,"",clRed); //Обратите внимание, что в свойствах
						//графики нумеруются с 1, а в программе - с 0

return result; //функция возвращает обработанную структуру
}
//------------------------------------------------------------------------------
void crc16 (const BYTE *nData, WORD wLength ,int *crc1,int *crc2)
{

    static const uint16_t table[256] =
    {
        0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
        0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
        0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
        0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
        0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
        0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
        0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
		0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
        0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
        0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
        0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
        0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
        0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
        0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
        0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
        0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
        0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
        0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
        0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
        0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
        0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
        0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
        0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
        0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
        0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
        0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
        0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
        0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
        0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
        0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
        0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
        0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
    };

    uint16_t crc = 0xffff; //Start Value for the CRC16-IBM

    while (wLength--)
    {
        uint8_t x = *nData++ ^ crc;

        crc = (crc>>8) ^ table[x];
	}


	AnsiString buf =IntToHex(crc,4);
	// Добавление контрольной суммы в конец команды. Байты контрольный суммы
	// меняются местами
	int idx=3;	// индекс начала второго байта контрольной суммы

		AnsiString CSbyte = "0x" + buf.SubString(idx, 2);
		idx-=2;	//переход на два символа назад
		*crc1= CSbyte.ToInt();
		CSbyte = "0x" + buf.SubString(idx, 2);
		*crc2= CSbyte.ToInt();
}
//---------------------------------------------------------------------------
int comPort1Init (void)
{

	 uint8_t result=0;
 // объявляем переменную, содержащую параметры порта
	DCB dcbSerialParams = {0};
//объявление строки с именем порта. Само в чар оно преобразовывать не умеет.
	LPCTSTR sPortName = portSet.port1Name.c_str();
//Работа с последоавательными портами в Windows проходит как с файлом.
//Открываем первый ком порт для записи/чтения:
	ComPort1=CreateFile(sPortName,GENERIC_READ | GENERIC_WRITE, 0,
			 NULL, OPEN_EXISTING, NULL, NULL);
 // - GENERIC_READ | GENERIC_WRITE - доступ к порту на чтение/записть
 // - 0 - порт не может быть общедоступным (shared)
 // - NULL - дескриптор порта не наследуется, используется дескриптор безопасности по умолчанию
 // - OPEN_EXISTING - порт должен открываться как уже существующий файл
 // - FILE_FLAG_OVERLAPPED - этот флаг указывает на использование асинхронных операций
 // - NULL - указатель на файл шаблона не используется при работе с портами

//проверяем работоспособность
	if(ComPort1==INVALID_HANDLE_VALUE)
	{
		if(GetLastError()==ERROR_FILE_NOT_FOUND)
		{
			result=1;
			//ShowMessage("serial port does not exist.\r\n");
		}
		else
		{
			result=2;
			//ShowMessage("some other error occurred.\r\n");
		}
		Form9->AbDBLED4->LED->ColorOff=clRed;
		Form9->AbDBLED4->Flashing=true;
		return result;
	}
//	else Form1->RichEdit1->SetSelText("port COM4 successfully opened...\r\n");
//настраиваем параметры соединения
//На msdn советуют сначала получить параметры, а затем менять их.
//Мы ещё только учимся, поэтому делаем как просят.
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(ComPort1, &dcbSerialParams))
	{
		result=3;
		//ShowMessage("getting state error\r\n");
	}
	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout         = MAXDWORD; // <- Здесь какое минимальное можно выставить?
	CommTimeOuts.ReadTotalTimeoutMultiplier  = 0;
	CommTimeOuts.ReadTotalTimeoutConstant    = 0;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant   = 1000;
	SetCommTimeouts(ComPort1, &CommTimeOuts);
	dcbSerialParams.BaudRate=portSet.port1Parameters.BaudRate;//CBR_9600;
	dcbSerialParams.ByteSize=portSet.port1Parameters.ByteSize;//8
	dcbSerialParams.StopBits=portSet.port1Parameters.StopBits;//ONESTOPBIT;
	dcbSerialParams.Parity=portSet.port1Parameters.Parity;//NOPARITY;
  //	dcbSerialParams.fNull=false;
	if(!SetCommState(ComPort1, &dcbSerialParams))
	{
		result=4;
		Form9->AbDBLED4->LED->ColorOff=clRed;
		Form9->AbDBLED4->Flashing=true;
	   //	ShowMessage("error setting serial port state\r\n");
	}
	else
	{
	   //	Form1->RichEdit1->SetSelText("port COM4 is ready.\r\n");
//		if(!sl1)sl1=new TStringList(Form2);
//		sl1->Add("=====================OPEN=====================");
		Form9->AbDBLED4->Checked=true;
		hPort1=CreateThread(NULL,0,thPort1,NULL,0,NULL);
		result=0;
		port1Closed=false;
		events.AutoConnectEvent=true;
	}
	return result;
}
//------------------------------------------------------------------------------
int comPort2Init (void)
{

	 uint8_t result=0;
 // объявляем переменную, содержащую параметры порта
	DCB dcbSerialParams = {0};
//объявление строки с именем порта. Само в чар оно преобразовывать не умеет.
	LPCTSTR sPortName = portSet.port2Name.c_str();
//Работа с последоавательными портами в Windows проходит как с файлом.
//Открываем первый ком порт для записи/чтения:
	ComPort2=CreateFile(sPortName,GENERIC_READ | GENERIC_WRITE, 0,
			 NULL, OPEN_EXISTING, NULL, NULL);
 // - GENERIC_READ | GENERIC_WRITE - доступ к порту на чтение/записть
 // - 0 - порт не может быть общедоступным (shared)
 // - NULL - дескриптор порта не наследуется, используется дескриптор безопасности по умолчанию
 // - OPEN_EXISTING - порт должен открываться как уже существующий файл
 // - FILE_FLAG_OVERLAPPED - этот флаг указывает на использование асинхронных операций
 // - NULL - указатель на файл шаблона не используется при работе с портами

//проверяем работоспособность
	if(ComPort2==INVALID_HANDLE_VALUE)
	{
		if(GetLastError()==ERROR_FILE_NOT_FOUND)
		{
			result=1;
			//ShowMessage("serial port does not exist.\r\n");
		}
		else
		{
			result=2;
			//ShowMessage("some other error occurred.\r\n");
		}
		Form9->AbDBLED5->LED->ColorOff=clRed;
		Form9->AbDBLED5->Flashing=true;
		return result;
	}
//	else Form1->RichEdit1->SetSelText("port COM4 successfully opened...\r\n");
//настраиваем параметры соединения
//На msdn советуют сначала получить параметры, а затем менять их.
//Мы ещё только учимся, поэтому делаем как просят.
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(ComPort2, &dcbSerialParams))
	{
		result=3;
		//ShowMessage("getting state error\r\n");
	}
	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout         = MAXDWORD; // <- Здесь какое минимальное можно выставить?
	CommTimeOuts.ReadTotalTimeoutMultiplier  = 0;
	CommTimeOuts.ReadTotalTimeoutConstant    = 0;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant   = 1000;
	SetCommTimeouts(ComPort2, &CommTimeOuts);
	dcbSerialParams.BaudRate=portSet.port2Parameters.BaudRate;
	dcbSerialParams.ByteSize=portSet.port2Parameters.ByteSize;
	dcbSerialParams.StopBits=portSet.port2Parameters.StopBits;
	dcbSerialParams.Parity=portSet.port2Parameters.Parity;
	if(!SetCommState(ComPort2, &dcbSerialParams))
	{
		result=4;
	   //	ShowMessage("error setting serial port state\r\n");
	}
	else
	{
//		if(!sl2)sl2=new TStringList(Form2);
//		sl2->Add("=====================OPEN=====================");
		hPort2=CreateThread(NULL,0,thPort2,NULL,0,NULL);
		result=0;
		port2Closed=false;
		Form9->AbDBLED5->Checked=true;
		events.AutoConnectEvent=true;
	   //	Form9->AbToggleSwitch5->StatusInt=1;
	}
	return result;
}
//------------------------------------------------------------------------------
void comPort1Close (void)
{
	if(hPort1)
	{
		TerminateThread(hPort1,0);
		CloseHandle(hPort1);
		hPort1=0;
	}
	CloseHandle(ComPort1);
	ComPort1=0;
	port1Closed=true;
	Form9->AbDBLED4->Checked=false;
	events.AutoConnectEvent=false;
	Form9->AbDBLED6->Flashing=false;
	Form9->AbDBLED6->Checked=false;
//	if(sl1) sl1->Add("=====================CLOSE=====================");
}
//----------------------------------------------------------------------------
void comPort2Close (void)
{
	if(hPort2)
	{
		TerminateThread(hPort2,0);
		CloseHandle(hPort2);
		hPort2=0;
	}
	CloseHandle(ComPort2);
	ComPort2=0;
	port2Closed=true;
	Form9->AbDBLED5->Checked=false;
	events.AutoConnectEvent=false;
//	if(sl2) sl2->Add("=====================CLOSE=====================");
 }
 //--------------------------------------------------------------------------
 void __fastcall TForm2::Button2Click(TObject *Sender)
{
	if((wcscmp(ComboBox1->Text.w_str(),L"undefined")==0)||(wcscmp(ComboBox4->Text.w_str(),L"undefined")==0))
	switch(MessageBox(NULL,"Вы не указали номера портов. Сохранить текущие настройки?","Внимание!",MB_YESNO|MB_ICONQUESTION))
	{
		case ID_YES: break;
		case ID_NO: return;
		default: return;
	}
	portSet.port1Name=(AnsiString)ComboBox1->Text;
	portSet.port1Name=(AnsiString)ComboBox4->Text;
	portSet.port1Parameters.BaudRate=StrToInt(ComboBox2->Text);
	portSet.port1Parameters.ByteSize=StrToInt(ComboBox6->Text);
	portSet.port1Parameters.StopBits=StrToInt(ComboBox9->Text);
	if(wcscmp(ComboBox7->Text.w_str(),L"None")==0) portSet.port1Parameters.Parity=0;
	else if(wcscmp(ComboBox7->Text.w_str(),L"Odd")==0) portSet.port1Parameters.Parity=1;
	else if(wcscmp(ComboBox7->Text.w_str(),L"Even")==0) portSet.port1Parameters.Parity=2;
	else if(wcscmp(ComboBox7->Text.w_str(),L"Mark")==0) portSet.port1Parameters.Parity=3;
	else if(wcscmp(ComboBox7->Text.w_str(),L"Space")==0) portSet.port1Parameters.Parity=4;
	portSet.port2Parameters.BaudRate=StrToInt(ComboBox3->Text);
	portSet.port2Parameters.ByteSize=StrToInt(ComboBox5->Text);
	portSet.port2Parameters.StopBits=StrToInt(ComboBox10->Text);
	if(wcscmp(ComboBox8->Text.w_str(),L"None")==0) portSet.port1Parameters.Parity=0;
	else if(wcscmp(ComboBox8->Text.w_str(),L"Odd")==0) portSet.port1Parameters.Parity=1;
	else if(wcscmp(ComboBox8->Text.w_str(),L"Even")==0) portSet.port1Parameters.Parity=2;
	else if(wcscmp(ComboBox8->Text.w_str(),L"Mark")==0) portSet.port1Parameters.Parity=3;
	else if(wcscmp(ComboBox8->Text.w_str(),L"Space")==0) portSet.port1Parameters.Parity=4;
	hardware.hwDInputs=StrToInt(Edit1->Text);
	hardware.hwDAC=StrToInt(Edit2->Text);
	hardware.hwReg=StrToInt(Edit3->Text);
	hardware.hwTacho=StrToInt(Edit4->Text);
	hardware.hwDOutputs=StrToInt(Edit5->Text);
	hardware.hwDrive=StrToInt(Edit6->Text);
	hardware.pressuremax=(Edit7->Text).ToDouble();
//	hardware.timeoffset=(Edit14->Text).ToDouble()*10;

	Ini->WriteString("Port 1","Port",ComboBox1->Text);
	Ini->WriteString("Port 1","Baudrate",ComboBox2->Text);
	Ini->WriteString("Port 1","Data bits",ComboBox6->Text);
	Ini->WriteString("Port 1","Parity",ComboBox7->Text);
	Ini->WriteString("Port 1","Stop bits",ComboBox9->Text);
	Ini->WriteString("Port 2","Port",ComboBox4->Text);
	Ini->WriteString("Port 2","Baudrate",ComboBox3->Text);
	Ini->WriteString("Port 2","Data bits",ComboBox5->Text);
	Ini->WriteString("Port 2","Parity",ComboBox8->Text);
	Ini->WriteString("Port 2","Stop bits",ComboBox10->Text);
	Ini->WriteString("Addresses","Inputs",Edit1->Text);
	Ini->WriteString("Addresses","Outputs",Edit2->Text);
	Ini->WriteString("Addresses","DAC",Edit3->Text);
	Ini->WriteString("Addresses","Tachometer",Edit4->Text);
	Ini->WriteString("Addresses","Recorder",Edit5->Text);
	Ini->WriteString("Addresses","Drive",Edit6->Text);
	Ini->WriteString("Common","Max pressure",Edit7->Text);
	//Ini->WriteString("Common","Time offset",Edit14->Text);
	ShowMessage("Чтобы изменения вступили в силу, перезапустите программу");
	this->Close();
}
//---------------------------------------------------------------------------
int readSettings(void)
{
	if(!FileExists(".\\im58_settings.ini",0))//проверка, есть ли файл настроек
	{
		return 1;
	}
	portSet.port1Name=(Ini->ReadString("Port 1","Port","undefined")).c_str();
	portSet.port1Parameters.BaudRate=StrToInt(Ini->ReadString("Port 1","Baudrate",9600));
	portSet.port1Parameters.ByteSize=StrToInt(Ini->ReadString("Port 1","Data bits",8));
	if(wcscmp((Ini->ReadString("Port 1","Parity","None")).w_str(),L"None")==0) portSet.port1Parameters.Parity=0;
	else if(wcscmp(Ini->ReadString("Port 1","Parity","None").w_str(),L"Odd")==0) portSet.port1Parameters.Parity=1;
	else if(wcscmp(Ini->ReadString("Port 1","Parity","None").w_str(),L"Even")==0) portSet.port1Parameters.Parity=2;
	else if(wcscmp(Ini->ReadString("Port 1","Parity","None").w_str(),L"Mark")==0) portSet.port1Parameters.Parity=3;
	else if(wcscmp(Ini->ReadString("Port 1","Parity","None").w_str(),L"Space")==0) portSet.port1Parameters.Parity=4;
	switch(StrToInt(Ini->ReadString("Port 1","Stop bits",0)*10))
	{
		case 10:portSet.port1Parameters.StopBits=0;break;
		case 15:portSet.port1Parameters.StopBits=1;break;
		case 20:portSet.port1Parameters.StopBits=2;break;
		default:portSet.port1Parameters.StopBits=0;break;
	};
	portSet.port2Name=(Ini->ReadString("Port 2","Port","undefined")).c_str();
	portSet.port2Parameters.BaudRate=StrToInt(Ini->ReadString("Port 2","Baudrate",9600));
	portSet.port2Parameters.ByteSize=StrToInt(Ini->ReadString("Port 2","Data bits",8));
	if(wcscmp((Ini->ReadString("Port 2","Parity","None")).w_str(),L"None")==0) portSet.port2Parameters.Parity=0;
	else if(wcscmp(Ini->ReadString("Port 2","Parity","None").w_str(),L"Odd")==0) portSet.port2Parameters.Parity=1;
	else if(wcscmp(Ini->ReadString("Port 2","Parity","None").w_str(),L"Even")==0) portSet.port2Parameters.Parity=2;
	else if(wcscmp(Ini->ReadString("Port 2","Parity","None").w_str(),L"Mark")==0) portSet.port2Parameters.Parity=3;
	else if(wcscmp(Ini->ReadString("Port 2","Parity","None").w_str(),L"Space")==0) portSet.port2Parameters.Parity=4;
	switch(StrToInt(Ini->ReadString("Port 2","Stop bits",0)*10))
	{
		case 10:portSet.port2Parameters.StopBits=0;break;
		case 15:portSet.port2Parameters.StopBits=1;break;
		case 20:portSet.port2Parameters.StopBits=2;break;
		default:portSet.port2Parameters.StopBits=0;break;
	};
	hardware.hwDInputs=StrToInt(Ini->ReadString("Addresses","Inputs",0x01));
	hardware.hwDOutputs=StrToInt(Ini->ReadString("Addresses","Outputs",0x05));
	hardware.hwDAC=StrToInt(Ini->ReadString("Addresses","DAC",0x02));
	hardware.hwTacho=StrToInt(Ini->ReadString("Addresses","Tachometer",0x04));
	hardware.hwReg=StrToInt(Ini->ReadString("Addresses","Recorder",0x03));
	hardware.hwDrive=StrToInt(Ini->ReadString("Addresses","Drive",0x1F));
	hardware.pressuremax=(Ini->ReadString("Common","Max pressure",0)).ToDouble();
	if(hardware.pressuremax!=0)hardware.k=16/hardware.pressuremax;
	hardware.timeoffset=(Ini->ReadString("Common","Time offset",0)).ToDouble()*10;
	hardware.timestop=(Ini->ReadString("Common","Time stop",0)).ToDouble();
	hardware.hwMachineNo=(Ini->ReadString("Common","MachineNo",0)).ToInt();
	if(strcmp(portSet.port1Name.c_str(),"undefined")==0
	||strcmp(portSet.port2Name.c_str(),"undefined")==0)
	{
		//если нет имени 1 или 2 порта возвращаем 1
		return 2;
	}
	else return 0;
}
//---------------------------------------------------------------------------
void TForm2::printSettings(void)
{

	ComboBox1->Text=portSet.port1Name;
	ComboBox2->Text=portSet.port1Parameters.BaudRate;
	ComboBox6->Text=portSet.port1Parameters.ByteSize;
	switch(portSet.port1Parameters.Parity)
	{
		case 0: ComboBox7->Text="None";break;
		case 1: ComboBox7->Text="Odd";break;
		case 2: ComboBox7->Text="Even";break;
		case 3: ComboBox7->Text="Mark";break;
		case 4: ComboBox7->Text="Space";break;
		default: ComboBox7->Text="undefined";break;
	}
	switch(portSet.port1Parameters.StopBits)
	{
		case 0:ComboBox9->Text="1";break;
		case 1:ComboBox9->Text="1.5";break;
		case 2:ComboBox9->Text="2";;break;
		default:ComboBox9->Text="1";break;
	};
	ComboBox4->Text=portSet.port2Name;
	ComboBox3->Text=portSet.port2Parameters.BaudRate;
	ComboBox5->Text=portSet.port2Parameters.ByteSize;
	switch(portSet.port2Parameters.Parity)
	{
		case 0: ComboBox8->Text="None"; break;
		case 1: ComboBox8->Text="Odd"; break;
		case 2: ComboBox8->Text="Even"; break;
		case 3: ComboBox8->Text="Mark";break;
		case 4: ComboBox8->Text="Space"; break;
		default:  ComboBox7->Text="undefined";break;
	}
	switch(portSet.port2Parameters.StopBits)
	{
		case 0:ComboBox10->Text="1";break;
		case 1:ComboBox10->Text="1.5";break;
		case 2:ComboBox10->Text="2";;break;
		default:ComboBox10->Text="1";break;
	};
	Edit1->Text="0x"+IntToHex(hardware.hwDInputs,2);
	Edit2->Text="0x"+IntToHex(hardware.hwDOutputs,2);
	Edit3->Text="0x"+IntToHex(hardware.hwDAC,2);
	Edit4->Text="0x"+IntToHex(hardware.hwTacho,2);
	Edit5->Text="0x"+IntToHex(hardware.hwReg,2);
	Edit6->Text="0x"+IntToHex(hardware.hwDrive,2);
	Edit7->Text=hardware.pressuremax;

}
//---------------------------------------------------------------------------
void defaultSettings (void)
{
	portSet.port1Parameters.BaudRate=9600;
	portSet.port1Parameters.ByteSize=8;
	portSet.port1Parameters.StopBits=0;
	portSet.port1Parameters.Parity=None;
	portSet.port2Parameters.BaudRate=9600;
	portSet.port2Parameters.ByteSize=8;
	portSet.port2Parameters.StopBits=0;
	portSet.port2Parameters.Parity=None;
	hardware.hwDInputs=0x01;
	hardware.hwDAC=0x02,
	hardware.hwReg=0x03,
	hardware.hwTacho=0x04,
	hardware.hwDOutputs=0x05,
	hardware.hwDrive=0x1F;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
	Edit8->Text=IntToStr(dataCountOut1);
	Edit9->Text=IntToStr(dataCountIn1);
	Edit10->Text=IntToStr(dataCountErr1);
	Edit11->Text=IntToStr(dataCountOut2);
	Edit12->Text=IntToStr(dataCountIn2);
	Edit13->Text=IntToStr(dataCountErr2);
}
//---------------------------------------------------------------------------
unsigned char digchar(unsigned char v)
{
    v-='0';
    if(v>41) return v-39; /* a .. f */
    if(v>9) return v-7;   /* A .. F */
    return v;             /* 0 .. 9 */
}
//---------------------------------------------------------------------------
uint8_t LRC(uint8_t *str)
{
	uint8_t val=0;
	while(*str)
     {
         val+=(digchar(*str)<<4)|digchar(str[1]);
         str+=2;
     }
	 return (unsigned char)(-((signed char)val));
}

