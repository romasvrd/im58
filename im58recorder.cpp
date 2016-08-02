//---------------------------------------------------------------------------

#pragma hdrstop

#include "im58recorder.h"
#include <queue>
#pragma hdrstop
#include <windows.h>
#include <math.h>
#include "im58main.h"
#include "im58serial.h"
#include "im58auto.h"
#include "im58results.h"
#include <conio.h>
#include <tlhelp32.h>
#include <fstream>
#include <cstdlib>
#include <cstddef>
#include <DateUtils.hpp>
#include <locale>
#include "im58archive.h"
#include <Psapi.h>
#pragma comment(lib,"Psapi.lib")
#include      <ComObj.hpp>
#include      <utilcls.h>
extern HANDLE hPort2;
extern HANDLE ComPort2;
extern int tacho_type;
int DrawExcel(AnsiString filename);
extern TTestResults testresults[16];
extern strHardware hardware;
extern std::queue<qStr> serialQueue2;
qStr strRec;
extern int crc1,crc2;
rec_struct recorder;
HANDLE hMonitor;
extern HANDLE hRec;
extern DWORD WINAPI thRec(LPVOID);
extern portSettings portSet;
using namespace std;
extern const double BarToKg;
extern std::queue<qString> textqueue;
extern TTest test;
extern bool polzunok;
extern bool fulltest;
extern HANDLE hThread;
extern TTest currentTest;
qString str;
extern bool result_flag;
extern int startspeed;
extern bool readyrec,readystream,readybutton;
double coeff_fric(double latency, double loading);
double coeff_stable(double latency, double maxmoment);
extern	SYSTEMTIME date;
extern char progpath[254];
extern int globalID;
void thMonitor(HANDLE hViewer,bool last_volume,int vol);
double zeromoment=0;
double zeroaxis=0;
bool findzero;
bool DiagramPrepared=false;
vector<diagramStruct> vDiagram;
diagramStruct sDiagram;
extern bool port2Closed;
//---------------------------------------------------------------------------
#pragma package(smart_init)
class DecimalPoint: public std::numpunct<char>
{
	public:
	explicit DecimalPoint(char_type point, size_t refs=0):
	std::numpunct<char>(refs),_point(point)
	{

	}

	protected:
	virtual char_type do_decimal_point() const
	{
		return _point;
	}
	private:
	char_type _point;
};
//------------------------------------------------------------------------------
void getNumFirstVol (void)
{
 	strRec.qBytes[0]=hardware.hwReg;
	strRec.qBytes[1]=109;	//служебная функция 109 - работа с dffs
	strRec.qBytes[2]=0x01;	//get_last_volume
	crc16(strRec.qBytes,3,&crc1,&crc2);
	strRec.qBytes[3]=crc2;
	strRec.qBytes[4]=crc1;
	strRec.size=5;
	serialQueue2.push(strRec);
}
//------------------------------------------------------------------------------
void getNumLastVol (void)
{
	strRec.qBytes[0]=hardware.hwReg;
	strRec.qBytes[1]=109;	//служебная функция 109 - работа с dffs
	strRec.qBytes[2]=0x02;	//get_last_volume
	crc16(strRec.qBytes,3,&crc1,&crc2);
	strRec.qBytes[3]=crc2;
	strRec.qBytes[4]=crc1;
	strRec.size=5;
	serialQueue2.push(strRec);
}
//------------------------------------------------------------------------------
void getFirstPage (void)
{
	strRec.qBytes[0]=hardware.hwReg;
	strRec.qBytes[1]=109;
	strRec.qBytes[2]=0x03;
	memcpy(&strRec.qBytes[3],recorder.lastVolumeBytes,4);
	crc16(strRec.qBytes,7,&crc1,&crc2);
	strRec.qBytes[7]=crc2;
	strRec.qBytes[8]=crc1;
	strRec.size=9;
	serialQueue2.push(strRec);
}
//------------------------------------------------------------------------------
void getLastPage (void)
{
	strRec.qBytes[0]=hardware.hwReg;
	strRec.qBytes[1]=109;
	strRec.qBytes[2]=0x04;
	memcpy(&strRec.qBytes[3],recorder.lastVolumeBytes,4);
	crc16(strRec.qBytes,7,&crc1,&crc2);
	strRec.qBytes[7]=crc2;
	strRec.qBytes[8]=crc1;
	strRec.size=9;
	serialQueue2.push(strRec);
}
//------------------------------------------------------------------------------
void getLastVol (void)
{
	strRec.qBytes[0]=hardware.hwReg;
	strRec.qBytes[1]=0x66;	//служебная функция 109 - работа с dffs
	memcpy(&strRec.qBytes[2],recorder.firstPageBytes,4);
	strRec.qBytes[6]=0x21;
	strRec.qBytes[7]=0x00;
	crc16(strRec.qBytes,8,&crc1,&crc2);
	strRec.qBytes[8]=crc2;
	strRec.qBytes[9]=crc1;
	strRec.size=10;
	serialQueue2.push(strRec);
}
//------------------------------------------------------------------------------
void getAddrOnPage(int page, int addr)
{	//мы должны считать страницу полностью. Каждый раз мы считываем по 21 байт данных,
	//соответственно, адрес с каждым запросом должен увеличиваться на 0x21.
	//И так до конца страницы


	AnsiString tempAddr=IntToHex(page,4);
	AnsiString tAddr1 = "0x" + tempAddr.SubString(0, 2);
	AnsiString tAddr2 = "0x" + tempAddr.SubString(3, 2);

	AnsiString tempPage=IntToHex(addr,4);
	AnsiString tPage1 = "0x" + tempPage.SubString(0, 2);
	AnsiString tPage2 = "0x" + tempPage.SubString(3, 2);

	strRec.qBytes[0]=hardware.hwReg;
	strRec.qBytes[1]=0x66;	//служебная функция 109 - работа с dffs
	strRec.qBytes[2]=tAddr2.ToInt();
	strRec.qBytes[3]=tAddr1.ToInt();
	strRec.qBytes[4]=tPage2.ToInt();
	strRec.qBytes[5]=tPage1.ToInt();
	strRec.qBytes[6]=0x21;
	strRec.qBytes[7]=0x00;
	crc16(strRec.qBytes,8,&crc1,&crc2);
	strRec.qBytes[8]=crc2;
	strRec.qBytes[9]=crc1;
	strRec.size=10;
	serialQueue2.push(strRec);
}
//------------------------------------------------------------------------------
void getFirstPageOnVol (int vol)
{

	AnsiString tempVol=IntToHex(vol,8);
	AnsiString tVol1 = "0x" + tempVol.SubString(0, 2);
	AnsiString tVol2 = "0x" + tempVol.SubString(3, 2);
	AnsiString tVol3 = "0x" + tempVol.SubString(5, 2);
	AnsiString tVol4 = "0x" + tempVol.SubString(7, 2);
	strRec.qBytes[0]=hardware.hwReg;
	strRec.qBytes[1]=109;
	strRec.qBytes[2]=0x03;
	strRec.qBytes[3]=tVol4.ToInt();
	strRec.qBytes[4]=tVol3.ToInt();
	strRec.qBytes[5]=tVol2.ToInt();
	strRec.qBytes[6]=tVol1.ToInt();
	crc16(strRec.qBytes,7,&crc1,&crc2);
	strRec.qBytes[7]=crc2;
	strRec.qBytes[8]=crc1;
	strRec.size=9;
	serialQueue2.push(strRec);
}
//------------------------------------------------------------------------------
void getLastPageOnVol (int vol)
{
	AnsiString tempVol=IntToHex(vol,8);
	AnsiString tVol1 = "0x" + tempVol.SubString(0, 2);
	AnsiString tVol2 = "0x" + tempVol.SubString(3, 2);
	AnsiString tVol3 = "0x" + tempVol.SubString(5, 2);
	AnsiString tVol4 = "0x" + tempVol.SubString(7, 2);
	strRec.qBytes[0]=hardware.hwReg;
	strRec.qBytes[1]=109;
	strRec.qBytes[2]=0x04;
	strRec.qBytes[3]=tVol4.ToInt();
	strRec.qBytes[4]=tVol3.ToInt();
	strRec.qBytes[5]=tVol2.ToInt();
	strRec.qBytes[6]=tVol1.ToInt();
	crc16(strRec.qBytes,7,&crc1,&crc2);
	strRec.qBytes[7]=crc2;
	strRec.qBytes[8]=crc1;
	strRec.size=9;
	serialQueue2.push(strRec);
}
//------------------------------------------------------------------------------
void tacho_preset(int brakespeed)
{
	if(tacho_type==TACHO_VEHA_T)
	{
//уставка
	AnsiString tempSpd=IntToHex((int)(brakespeed/2),4);
	AnsiString tSpd1 = "0x" + tempSpd.SubString(0, 2);
	AnsiString tSpd2 = "0x" + tempSpd.SubString(3, 2);

	strRec.qBytes[0]=hardware.hwTacho;
	strRec.qBytes[1]=0x10;//write to multiple registers
	strRec.qBytes[2]=0x00;
	strRec.qBytes[3]=0x00;//нач.адрес
	strRec.qBytes[4]=0x00;
	strRec.qBytes[5]=0x06;//кол-во слов
	strRec.qBytes[6]=0x0C;//кол-во байт
	strRec.qBytes[7]=tSpd1.ToInt();
	strRec.qBytes[8]=tSpd2.ToInt();//скорость
	strRec.qBytes[9]=0x00;
	strRec.qBytes[10]=0x00;//знаки после запятой
	strRec.qBytes[11]=0x00;
	strRec.qBytes[12]=0x01;//множитель
	strRec.qBytes[13]=tSpd1.ToInt();
	strRec.qBytes[14]=tSpd2.ToInt();//скорость
	strRec.qBytes[15]=0x00;
	strRec.qBytes[16]=0x00;//знаки после запятой
	strRec.qBytes[17]=0x00;
	strRec.qBytes[18]=0x01;//множитель
	crc16(strRec.qBytes,19,&crc1,&crc2);
	strRec.qBytes[19]=crc1;
	strRec.qBytes[20]=crc2;
	strRec.size=21;
	serialQueue2.push(strRec);
//дельта
	tempSpd=IntToHex((int)((brakespeed/2)-1),4);
	tSpd1 = "0x" + tempSpd.SubString(0, 2);
	tSpd2 = "0x" + tempSpd.SubString(3, 2);

	strRec.qBytes[0]=hardware.hwTacho;
	strRec.qBytes[1]=0x10;//write to multiple registers
	strRec.qBytes[2]=0x00;
	strRec.qBytes[3]=0x06;//нач.адрес
	strRec.qBytes[4]=0x00;
	strRec.qBytes[5]=0x06;//кол-во слов
	strRec.qBytes[6]=0x0C;//кол-во байт
	strRec.qBytes[7]=tSpd1.ToInt();
	strRec.qBytes[8]=tSpd2.ToInt();//скорость
	strRec.qBytes[9]=0x00;
	strRec.qBytes[10]=0x00;//знаки после запятой
	strRec.qBytes[11]=0x00;
	strRec.qBytes[12]=0x01;//множитель
	strRec.qBytes[13]=tSpd1.ToInt();
	strRec.qBytes[14]=tSpd2.ToInt();//скорость
	strRec.qBytes[15]=0x00;
	strRec.qBytes[16]=0x00;//знаки после запятой
	strRec.qBytes[17]=0x00;
	strRec.qBytes[18]=0x01;//множитель
	crc16(strRec.qBytes,19,&crc1,&crc2);
	strRec.qBytes[19]=crc1;
	strRec.qBytes[20]=crc2;
	strRec.size=21;
	serialQueue2.push(strRec);
    }
}
//---------------------------------------------------------------------------
void thMonitor(HANDLE hViewer,bool last_volume,int vol)
{

	DWORD code;
	AnsiString errStr;
	double a;
	WaitForSingleObject(hViewer,INFINITE);   	//функция вернет управление, когда процесс завершится
	GetExitCodeProcess(hViewer,&code);          //получаем код процесса
	switch(code)
	{
		case 1: errStr="Запрос данных прерван пользователем";
		case 0: break;
		case -1:errStr="Указаны неверные параметры при обращении к ArcDataViewer.exe. Обрабитесь к разработчику программы";break;
		case -2:errStr="Ошибка открытия порта. Проверьте настройки программы и NPort"; break;
		case -3:errStr="Ошибка чтения из устройства";  break;
		case -4:errStr="Ошибка создания выходного файла";break;
		case -5:errStr="Ошибка записи в файл";   break;
		case -6:errStr="Ошибка экспорта в выходной файл";break;
		case -7:errStr="Запрашиваемые данные не найдены в архиве";break;
		case -8:errStr="Неизвестная ошибка ArcDataViewer"; break;
		default:errStr="Неизвестная ошибка"; break;

	}
	CloseHandle(hViewer);
	hViewer=0;
	//polzunok=false;
	if(Form9->Visible==true) Form9->ProgressBar1->State=pbsPaused;
	if(code==0)
	{
		if(last_volume==true)
		{
			readData(-1);
		}
		else
		{
			findZeroLevel(vol);
		}
	}
	else
	{
		errStr+="\r\nПовторить запрос данных?";
		switch(MessageBox(NULL,errStr.c_str(),NULL,MB_ICONERROR|MB_YESNO))
		{
			case ID_YES:recExeCmd(-1); break;
			case ID_NO:
				if(fulltest)
				{
                   	ShowMessage("Испытание приостановлено");
					Form4->Button3Click(Form4);
					break;
				}

		}
	}
}
//------------------------------------------------------------------------------
bool readData(int num)
{
	ifstream data;
	vDiagram.clear();
	double dfirstpress=0;
	double middle_axis=0;
	double middle_moment=0;
	char out[255];
	int count=0;
	int i=0;
	double firstpress,finishpress;
	WideString filename;
	filename=progpath;
	if(num==-1)
	{
		filename+="Diagrams\\signal"+IntToStr(test.brakecount)+".txt";
	}
	else
	{
		filename+="Diagrams\\signal"+IntToStr(num)+".txt";
	}
		//рисуем график
		DrawExcel(filename);
		//поднять флаг, что мы готовы рисовать график. Обработка флага по таймеру на формах
		DiagramPrepared=true;
		//тут поток будет ждать, пока флаг не сбросится. Когда форма нарисует график, поток возобновится и удалит временный график
		while (DiagramPrepared)
		{
			Sleep(1);
		}
		if(num!=-1)
		{
			return true;
		}
//		dfirstpress=Form9->Series1->MinXValue();
//		dfirstpress=series1->MinXValue();
		sDiagram=vDiagram.front();
		firstpress=sDiagram.idx;

//		a=Form9->Series1->MaxXValue();
//		a=series1->MaxXValue();
		sDiagram=vDiagram.back();
		finishpress=sDiagram.idx;
		if(!fulltest)
		{
			sprintf(out,"\r\nПробное торможение:");
		}
		else
		{
			if(test.brakecount>5)
			{
				sprintf(out,"\r\nЗачетное торможение %d:",test.brakecount-5);
			}
			else
			{
				sprintf(out,"\r\nПритирочное торможение %d:",test.brakecount);
			}
		}
		for(int i=30;i<=Form4->Series1->XValues->Count-30;i++)
		{
			middle_axis+=Form4->Series1->YValue[i];
			middle_moment+=Form4->Series2->YValue[i];
			count++;
		}
		str.string=out;
		str.bold=true;
		textqueue.push(str);
		str.bold=false;
	//расчет максимального осевого усилия
		double max=0;
		int t=0;
		for(t=hardware.timeoffset-2;t<=Form4->Series1->XValues->Count-hardware.timeoffset-2;t++)
		{
			if(Form4->Series1->YValue[t]>max)
			{
				max=Form4->Series1->YValue[t];
            }
		}
		//double max_axis=*max_element(Form4->Series1->YValue[30],Form4->Series1->XValues->Count-30);
		sprintf(out,"Максимальное осевое усилие %.3f кгс",max);//Form4->Series1->MaxYValue());
		str.string=out;
		textqueue.push(str);
	//расчет среднего осевого усилия

		middle_axis/=count;
		testresults[test.brakecount].осевое_усилие=middle_axis;
		sprintf(out,"Среднее осевое усилие %.3f кгс",testresults[test.brakecount].осевое_усилие);
		str.string=out;
		textqueue.push(str);
//		 if(Form9->Visible)	Form9->Label7->Caption=middle_axis;
	//расчет давления в тормозе
		testresults[test.brakecount].давление_в_тормозе=testresults[test.brakecount].осевое_усилие/14.2;//25/M_PI/BarToKg;
		sprintf(out,"Давление в тормозе Pуд %.2f кгс/см^2",testresults[test.brakecount].давление_в_тормозе);
		str.string=out;
		textqueue.push(str);
//		 if(Form9->Visible)	Form9->Label9->Caption=testresults[test.brakecount].давление_в_тормозе;
	//скорость начала торможения
		testresults[test.brakecount].скорость_начала_торможения=startspeed;
		sprintf(out,"Скорость начала торможения %d об/мин",startspeed);
		str.string=out;
		textqueue.push(str);
	//расчет длительности торможения
		recorder.braketime=finishpress-firstpress-hardware.timestop;
		testresults[test.brakecount].длительность_торможения=recorder.braketime;
		AnsiString tlat="Длительность торможения "+FloatToStr(recorder.braketime)+" с";
		str.string=tlat;
		textqueue.push(str);
	//обороты за торможение
		sprintf(out,"Обороты за торможение %d об",testresults[test.brakecount].обороты_за_торможение);
		str.string=out;
		textqueue.push(str);
		//подставка(нулевой уровень) - последнее значение
		//lastmoment=Form4->Series2->YValues->Last();
	//средний момент
		//middle_moment=(middle_moment+(lastmoment*count))/count;
		middle_moment/=count;
		testresults[test.brakecount].средний_момент=middle_moment;
		sprintf(out,"Средний момент %.f кгс·см",testresults[test.brakecount].средний_момент);
		str.string=out;
		textqueue.push(str);
//		if(Form9->Visible)	Form9->Label8->Caption=testresults[test.brakecount].средний_момент;
	//максимальный момент
		//подставка(нулевой уровень) - последнее значение
		//lastmoment=Form4->Series2->YValues->Last();
		double maxmom=0;
		for(int i=hardware.timeoffset-2;i<=Form4->Series2->XValues->Count-hardware.timeoffset-2;i++) //эксель считает с 1, тчарт с 1, поэтому чтобы обратиться к 100-му отсчету в экселе, надо писать 98
		{
			if(Form4->Series2->YValue[i]>maxmom)
			{
				maxmom=Form4->Series2->YValue[i];
            }
		}
		testresults[test.brakecount].максимальный_момент=maxmom;
		sprintf(out,"Максимальный момент %d кгс·см",testresults[test.brakecount].максимальный_момент);
		str.string=out;
		textqueue.push(str);
	//коэффициент трения
		testresults[test.brakecount].коэффициент_трения=coeff_fric(testresults[test.brakecount].длительность_торможения,testresults[test.brakecount].осевое_усилие);
		sprintf(out,"Коэффициент трения %.3f",testresults[test.brakecount].коэффициент_трения);
		str.string=out;
		textqueue.push(str);
//		if(Form9->Visible)	Form9->Label6->Caption=testresults[test.brakecount].коэффициент_трения;
	//коэффициент стабильности
		testresults[test.brakecount].коэффициент_стабильности=coeff_stable(testresults[test.brakecount].длительность_торможения,testresults[test.brakecount].максимальный_момент);
		sprintf(out,"Коэффициент стабильности %.3f",testresults[test.brakecount].коэффициент_стабильности);
		str.string=out;
		textqueue.push(str);
		data.close();
		if(test.brakecount>5)
		{
			char datetime[50];
			sprintf(datetime,"%02d.%02d.%04d %02d:%02d",date.wDay,date.wMonth,date.wYear,date.wHour,date.wMinute);
			try
			{
				Form10->ADOCommand1->CommandText=
				"UPDATE [every] SET[Pressure]='"+
				FloatToStr(testresults[test.brakecount].давление_в_тормозе)+"',[force]='"+
				FloatToStr(testresults[test.brakecount].осевое_усилие)+"',[speed]='"+
				FloatToStr(testresults[test.brakecount].скорость_начала_торможения)+"',[duration]='"+
				FloatToStr(testresults[test.brakecount].длительность_торможения)+"',[turns]='"+
				FloatToStr(testresults[test.brakecount].обороты_за_торможение)+"',[coef_stable]='"+
				FloatToStr(testresults[test.brakecount].коэффициент_стабильности)+"',[coef_fric]='"+
				FloatToStr(testresults[test.brakecount].коэффициент_трения)+"',[middle_moment]='"+
				FloatToStr(testresults[test.brakecount].средний_момент)+"',[max_moment]='"+
				FloatToStr(testresults[test.brakecount].максимальный_момент)+"' where id="+globalID+" AND brakeID="+(test.brakecount-5);
           		Form10->ADOCommand1->Execute();
			}
			catch(Exception &e)
			{
				ShowMessage("Ошибка записи в базу данных");
			}
		}
	//возвращаем управление ком-портом
		comPort2Init();
		test.brakecount++;

       	readyrec=true;
		if(fulltest&&/*test.brakecount!=6&&test.brakecount!=16&&*/readystream==true)
		{
			ResumeThread(hThread);
		}
		if(!fulltest&&readystream==true)//если мы проводим один цикл испытания, и цикл завершился - убить поток
		{
			Form9->Button1->Enabled=true;
			Form9->Button6->Enabled=true;
			Form9->ComboBox2->Enabled=true;
			if(hThread)
			{
				TerminateThread(hThread,0);
				CloseHandle(hThread);
				hThread=0;
			}
		}      //в единичном цикле - убивается поток авт.цикла, поэтому охлаждение идет до бесконечности
		return true;
}
//---------------------------------------------------------------------------
double coeff_fric(double latency, double loading)
{
//	double seconds=(latency.SubString(0,2)*60000+latency.SubString(4,2)*1000)/1000;
	double coeff=53/((loading/14.2)*latency);
	return coeff;
}
//---------------------------------------------------------------------------
double coeff_stable(double latency, double maxmoment)
{
//	double seconds=(latency.SubString(0,2)*60000+latency.SubString(4,2)*1000)/1000;
	double coeff=2370/(maxmoment*latency);
	return coeff;
}
//---------------------------------------------------------------------------
void getPreLast(int vol)
{
	char cmd[254];
	char path[254];
	char asdf[254];
    	STARTUPINFO siCmd = {sizeof(siCmd)};
	PROCESS_INFORMATION piCmd;
	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize=sizeof(ProcessEntry);
	HANDLE hSnap;
	HANDLE hProcess;
	uint16_t pid;
	char out[254];//запрос последнего тома
	sprintf(out,"%s","Запрос предпоследнего тома");
	str.string=out;
	textqueue.push(str);
	sprintf(cmd,".\\ArcDataViewer.exe %s %d 8 n 1 3 txt .\\Diagrams\\pre_signal%d.txt read_volume %d",portSet.port2Name,portSet.port2Parameters.BaudRate,test.brakecount,vol-1);
	AnsiString aCmd=cmd;
	if(
		CreateProcess
		(
			NULL,			//lpApplicationName
			aCmd.c_str(), 	//lpCommandLine
			NULL,           //lpProcessAttributes
			NULL,           //lpThreadAttributes
			FALSE,   		//bInheritHandles
			0,             	//dwCreationFlags
			NULL,           //lpEnvironment
			NULL,           //lpCurrentDirectory
			&siCmd,         //lpStartupInfo
			&piCmd   		//lpProcessInformation
		)
	)
	{
		hProcess=piCmd.hProcess;
		if(hProcess!=NULL)
		{
			thMonitor(hProcess,false,vol);
			return;
		}
	}
	if(Form9->Visible==true)
	{
		Form9->ProgressBar1->State=pbsPaused;
		ShowMessage("Ошибка запуска ArcDataViewer");
	}
}
//---------------------------------------------------------------------------
void getLast(int vol)
{

	char asdf[254];
	char cmd[254];
	char path[254];
	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize=sizeof(ProcessEntry);
	STARTUPINFO siCmd = {sizeof(siCmd)};
	PROCESS_INFORMATION piCmd;
	HANDLE hSnap=0;
	HANDLE hProcess=0;
	uint16_t pid;//запрос последнего тома
	char out[254];
	sprintf(out,"Запрос тома %d",vol);
	str.string=out;
	textqueue.push(str);
	sprintf(cmd,".\\ArcDataViewer.exe %s %d 8 n 1 3 txt .\\Diagrams\\signal%d.txt read_volume %d",portSet.port2Name,portSet.port2Parameters.BaudRate,test.brakecount,vol);
	AnsiString aCmd=cmd;
	if(
		CreateProcess
		(
			NULL,			//lpApplicationName
			aCmd.c_str(), 	//lpCommandLine
			NULL,           //lpProcessAttributes
			NULL,           //lpThreadAttributes
			FALSE,   		//bInheritHandles
			0,             	//dwCreationFlags
			NULL,           //lpEnvironment
			NULL,           //lpCurrentDirectory
			&siCmd,         //lpStartupInfo
			&piCmd   		//lpProcessInformation
		)
	)
	{
		hProcess=piCmd.hProcess;
		if(hProcess!=NULL)
		{
			thMonitor(hProcess,true,vol);
			return;
		}
	}

	if(Form9->Visible==true)
	{
		Form9->ProgressBar1->State=pbsPaused;
		ShowMessage("Ошибка запуска ArcDataViewer");
	}
	//}
}
//---------------------------------------------------------------------------
void findZeroLevel(int vol)
{
	zeroaxis=0;
	zeromoment=0;
	vDiagram.clear();
	double dfirstpress=0;
	double middle_axis=0;
	double middle_moment=0;
	double doubleDateTime1;
	double doubleDateTime2;
	double value1=0;
	double value2=0;
	char out[255];
	WideString filename;
	filename=progpath;
	filename+="Diagrams\\pre_signal"+IntToStr(test.brakecount)+".txt";
	//рисуем график
	int count=DrawExcel(filename);
	//поднять флаг, что мы готовы рисовать график. Обработка флага по таймеру на формах
		DiagramPrepared=true;
		//тут поток будет ждать, пока флаг не сбросится. Когда форма нарисует график, поток возобновится и удалит временный график
		while (DiagramPrepared)
		{
			Sleep(1);
		}
		count=Form4->Series1->XValues->Count-1;
		int nonzeroax=0;
		int nonzeromom=0;
		//расчет нулевого уровня осевого усилия
		for(int i=count;i>=count-30;i--)
		{
			if(Form4->Series1->YValues->operator [](i)!=0)
			{
				zeroaxis+=Form4->Series1->YValues->operator [](i);
				nonzeroax++;
            }
		}
		zeroaxis/=nonzeroax;
		sprintf(out,"Нулевой уровень осевого усилия %.3f ",zeroaxis);//Form4->Series1->MaxYValue());
		str.string=out;
		textqueue.push(str);
		//расчет нулевого уровня тормозного момента
		for(int i=count;i>=count-30;i--)
		{
			if(Form4->Series2->YValues->operator [](i)!=0)
			{
				zeromoment+=Form4->Series2->YValues->operator [](i);
				nonzeromom++;
            }
		}
		zeromoment/=nonzeromom;
		sprintf(out,"Нулевой уровень момента %.3f ",zeromoment);//Form4->Series1->MaxYValue());
		str.string=out;
		textqueue.push(str);
		getLast(vol);
}
//------------------------------------------------------------------------------
void recExeCmd(int vol)
{
	if(port2Closed==true)
	{
		comPort2Init();
	}
	recorder.lastVolume=0;
	tacho_result();
	tacho_result();
	tacho_result();
	tacho_result();
	tacho_result();
	int volumes[5]={0};
	char out[255];
	//узнаем последний том
	if(vol==-1)
	{
		do
		{
			getNumLastVol();
			Sleep(200);
			vol=recorder.lastVolume+1;
		}
		while (vol<=1);
			
		sprintf(out,"Последний том %d\r\n",vol);  //ну хули делать, если у них регистратор считает с 0, а датавьюер с 1?!
		str.string=out;
		textqueue.push(str);
		//закрываем порт
		comPort2Close();
		//запрос предпоследнего тома
		zeromoment=0;
		if(findzero)
		{
			getPreLast(vol);
		}
		else
		{
			getLast(vol);
		}
		zeromoment=0;
		return;
	}
	comPort2Close();
	//запрос последнего тома
	getLast(vol);
	zeromoment=0;
}
//------------------------------------------------------------------------------
int DrawExcel(AnsiString filename)
{
	double doubleDateTime1,doubleDateTime2;
	char dataheader[83];
	bool dataheaderfull=false;
	sprintf(dataheader,"%s","XКанал1XКанал2XЧастотаXПолнаямощностьXАктивнаямощностьXРеактивнаямощностьXКосинусФи");
	ifstream data;
	char a[100]={0x00};
	int i=0;
	int x=0;
	double value1=0;
	double value2=0;
	FormatSettings.DecimalSeparator=',';
	setlocale(LC_NUMERIC,"ru_RU.cp1251");
	data.open(filename.c_str());//("signal.txt");
	if(!data.fail())
	{
		DecimalPoint *comma = new DecimalPoint(',');
		std::locale mylocale(std::locale(""), comma);
		data.imbue(mylocale);

		while(!data.eof())   					//читаем данные, пока файл не закончится
		{

			while(!dataheaderfull)
			{
				data>>a[i];
				i++;
				if(strcmp(a,dataheader)==0)
				{
                    dataheaderfull=true;
				}
			}
//			else
			{

				//данные об одном измерении с 1 канала
				data>>doubleDateTime1;
//				dt1=doubleDateTime1;
				data>>value1;
				//данные об одном измерении со 2 канала
				data>>doubleDateTime2;
//				dt2=doubleDateTime2;
				data>>value2;
				x++;
			}

			if(value1>=1000)
			{
				value1=hardware.pressuremax*M_PI*BarToKg;
			}
			if(value2>=1000)
			{
				value2=hardware.pressuremax*M_PI*BarToKg;
			}
				//заполнение вектора данных измерений
			sDiagram.value1=value1-zeroaxis;
			sDiagram.value2=value2-zeromoment;
			sDiagram.idx=((double)(x-1))/(double)10;
			vDiagram.push_back(sDiagram);

		}
	}
	data.close();
	return x-1;
}
//---------------------------------------------------------------------------
void regReadValue(void)
{
//	if(hPort2)
//	{
//		SuspendThread(hPort2);
//	}
	qStr str;
	unsigned long dwBytesWritten,dwBytesRead;
	str.qBytes[0]=hardware.hwReg;
	str.qBytes[1]=0x04;
	str.qBytes[2]=0x00;
	str.qBytes[3]=0x00;
	str.qBytes[4]=0x00;
	str.qBytes[5]=0x06;
	crc16(str.qBytes,6,&crc1,&crc2);
	str.qBytes[6]=0x71;
	str.qBytes[7]=0xEA;
	str.size=8;
	serialQueue2.push(str);
}

