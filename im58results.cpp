//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "im58recorder.h"
#include "im58results.h"
#include "im58main.h"
#include "im58auto.h"
#include <Printers.hpp>
#include "im58archive.h"
#include "im58who.h"
#include "math.h"
extern strHardware hardware;
extern rec_struct recorder;
//---------------------------------------------------------------------------
#pragma package(smart_init)
TForm6 *Form6;
#pragma resource "*.dfm"
TTestResults testresults[16];
extern TTest test;
TPrinter *printer;
extern AnsiString datestring;
//extern int dateid;
extern int globalID;
extern TTest currentTest;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm6::FormShow(TObject *Sender)
{
	//double s = SimpleRoundTo(34.12341425235,-3);
	int j=0;
	UnicodeString nullmsg="Could not convert variant of type (Null) into type (OleStr)";
	sg->Cells[0][0]="Параметр";
	//sg->Cells[0][1]=U"Давление в тормозе, (кгс/см²)";
	sg->Cells[0][1]="Осевое усилие, (кгс)";
	sg->Cells[0][2]="Скорость начала торможения, (об/мин)";
	sg->Cells[0][3]="Длительность торможения, (с)";
	sg->Cells[0][4]="Обороты за торможение, (об)";
	sg->Cells[0][5]="Коэффициент трения";
	sg->Cells[0][6]="Средний момент, (кгс·см)";
	sg->Cells[0][7]="Максимальный момент, (кгс·см)";
	sg->Cells[0][8]="Коэффициент стабильности";
	for(int i=1;i<=10;i++)
	{
		try
		{
			ADODataSet2->CommandText="select * from every where id="+IntToStr(globalID)+" AND brakeID="+IntToStr(i);
			ADODataSet2->Active=true;
			j++;
			sg->Cells[i][0]=SimpleRoundTo((double)(ADODataSet2->FieldByName("brakeID")->Value),-3);
		}
		catch (Exception &e)
		{
			sg->Cells[i][0]=0;
		}
		try
		{
			sg->Cells[i][1]=SimpleRoundTo((double)(ADODataSet2->FieldByName("force")->Value),-3);		j++;
		}
		catch (Exception &e)
		{
			sg->Cells[i][1]=0;
		}
		try
		{
			sg->Cells[i][2]=SimpleRoundTo((double)(ADODataSet2->FieldByName("speed")->Value),-3);		j++;
		}
		catch (Exception &e)
		{
			sg->Cells[i][2]=0;
		}
		try
		{
			sg->Cells[i][3]=SimpleRoundTo((double)(ADODataSet2->FieldByName("duration")->Value),-3); 	j++;
		}
		catch (Exception &e)
		{
			sg->Cells[i][3]=0;
		}
		try
		{
			sg->Cells[i][4]=SimpleRoundTo((double)(ADODataSet2->FieldByName("turns")->Value),-3); 		j++;
		}
		catch (Exception &e)
		{
			sg->Cells[i][4]=0;
		}
		try
		{
			sg->Cells[i][5]=SimpleRoundTo((double)(ADODataSet2->FieldByName("coef_fric")->Value),-3);	j++;
		}
		catch (Exception &e)
		{
			sg->Cells[i][5]=0;
		}
		try
		{
			sg->Cells[i][6]=SimpleRoundTo((double)(ADODataSet2->FieldByName("middle_moment")->Value),-3);j++;
		}
		catch (Exception &e)
		{
			sg->Cells[i][6]=0;
		}
		try
		{
			sg->Cells[i][7]=SimpleRoundTo((double)(ADODataSet2->FieldByName("max_moment")->Value),-3);	j++;
		}
		catch (Exception &e)
		{
			sg->Cells[i][7]=0;
		}
		try
		{
			sg->Cells[i][8]=SimpleRoundTo((double)(ADODataSet2->FieldByName("coef_stable")->Value),-3); j++;
		}
		catch (Exception &e)
		{
			sg->Cells[i][8]=0;
		}
			ADODataSet2->Active=false;


	}
	ADODataSet1->Active=false;
	//расчет средних значений
	ADODataSet1->CommandText="select * from after10 where id="+IntToStr(globalID);// and brakeID='"+i+"'";
	ADODataSet1->Active=true;
	char asdfq[150];
	TDateTime protocol=ADODataSet1->FieldByName("DateTime")->AsDateTime;
	AnsiString astring=FormatDateTime("«dd» MMMM yyyy",protocol);
	AnsiString astr=ADODataSet1->FieldByName("Изделие")->AsString;
	AnsiString bstr=ADODataSet1->FieldByName("Материал")->AsString;
	AnsiString cstr=ADODataSet1->FieldByName("Партия")->AsString;
	AnsiString testmode=ADODataSet1->FieldByName("Программа_испытания")->AsString;
	Label3->Caption="Определение фрикционно-износных характеристик по программе испытаний "+testmode+" на испытательном стенде ИМ-58 № "+IntToStr(hardware.hwMachineNo);
	sprintf(asdfq,"Изделие: %s  Материал: %s Партия спекания: %s",astr.c_str(),bstr.c_str(),cstr.c_str());
	this->Label4->Caption=asdfq;
	sprintf(asdfq,"ПРОТОКОЛ №______ от %sг.",astring);
	this->Label2->Caption=asdfq;
	astring=ADODataSet1->FieldByName("ФИО")->AsString;
	sprintf(asdfq,"Испытания проводил___________________  %s",astring);
	this->Label7->Caption=asdfq;
	sprintf(asdfq,"Режим испытания:   n=%d об/мин.",(int)ADODataSet1->FieldByName("Режим_испытания")->Value);
	this->Label5->Caption=asdfq;
	double fmk=ADODataSet1->FieldByName("Jh(фмк)")->Value;
	double cnmh=ADODataSet1->FieldByName("Jh(чнмх)")->Value;
	AnsiString ct=(ADODataSet1->FieldByName("Контр_тело")->AsString).c_str();
	sprintf(asdfq,"Износ керамики Jh(%s)=%.2f мкм/торм,                          Износ контр.тела Jh(%s)= %.2f мкм/торм",astr.c_str(),fmk,ct,cnmh);
	this->Label6->Caption=asdfq;
   Label1->Caption="Контр.тело: "+ADODataSet1->FieldByName("Контр_тело")->AsString+" Твердость HB:"+ADODataSet1->FieldByName("Твердость")->AsString;
	sg->Cells[11][0]="Среднее";
	//ширина по содержимому
	sg->Width-=sg->ColWidths[0];
	sg->ColWidths[0] = sg->Canvas->TextWidth(sg->Cells[0][2])+16;
	sg->Width+=sg->ColWidths[0];
	for (int i=1; i <=8;i++)
	{
		double result=0;
		for(int k=1;k<=10;k++)
		{
			result+=StrToFloat(sg->Cells[k][i]);
		}
		result/=10;
		sg->Cells[11][i]=SimpleRoundTo(result,-3);
//		sg->Cells[
	}
	AnsiString ssss=" Pуд="+FloatToStrF(sg->Cells[10][1].ToDouble()/14.2,ffGeneral,5,2);
//	sg->Cells[10][1]=ssss;
//	sg->Width-=sg->ColWidths[10];
//	sg->ColWidths[10]=sg->Canvas->TextWidth(sg->Cells[10][1])+8;
//	sg->Width+=sg->ColWidths[10];
	Label12->Caption=      ssss;
	sg->SetDesignVisible(false);
	ADODataSet1->Active=false;

}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button1Click(TObject *Sender)
{
	//Printer()->Orientation=poLandscape;
	Button1->Hide();
	Button2->Hide();
	if(PrinterSetupDialog1->Execute())
	{
		this->Print();
   	}
	Button1->Show();
	Button2->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm6::sgMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
  /*	int col,row;
	sg->MouseToCell(X,Y,col,row);
	if(row==0&&col>0&&col<11)
	{
        test.showcount=col;
		Form7->Show();
		Form7->Series1->Clear();
		Form7->Series2->Clear();
		if(!readData(test.showcount+5))
		{
			Form7->Series1->Clear();
			Form7->Series2->Clear();
			for(int i=1;i<=8;i++)
			{
				Form7->sg->Cells[1][i]=this->sg->Cells[col][i];
            }
        }

	} */
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button2Click(TObject *Sender)
{
	this->Hide();
}
//---------------------------------------------------------------------------
