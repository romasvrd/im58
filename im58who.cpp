//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include "im58who.h"
#include "im58auto.h"
#include "im58archive.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm8 *Form8;
AnsiString fio;
	SYSTEMTIME date;
	int globalID;
//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
	: TForm(Owner)
{
	GetLocalTime(&date);
}
//---------------------------------------------------------------------------
void __fastcall TForm8::FormShow(TObject *Sender)
{
	char str[50];

    GetLocalTime(&date);
	sprintf(str,"Испытания ИМ-58\r\n%02d.%02d.%04d %02d:%02d",date.wDay,date.wMonth,date.wYear,date.wHour,date.wMinute);
   	this->Label1->Caption=str;

}
//---------------------------------------------------------------------------
void __fastcall TForm8::Button1Click(TObject *Sender)
{
char datetime[50];
	sprintf(datetime,"%02d.%02d.%04d %02d:%02d",date.wDay,date.wMonth,date.wYear,date.wHour,date.wMinute);
	if(Edit1->Text!=""&&Edit2->Text!=""&&Edit3->Text!=""&&Edit4->Text!=""&&Edit5->Text!=""&&Edit6->Text!="")
	{
		Form10->ADODataSet2->Active=false;
		fio=Edit1->Text;
		ADOCommand1->CommandText=
		"INSERT INTO [after10]([DateTime],[ФИО],[Изделие],[Материал],[Партия],[Контр_тело],[Твердость]) VALUES('"+
		(AnsiString)datetime+"','"+
		fio+"','"+
		Edit2->Text+"','"+
		Edit3->Text+"','"+
		Edit4->Text+"','"+
		Edit5->Text+"','"+
		Edit6->Text+"')";
		ADOCommand1->Execute();
		Sleep(10);
        Form10->ADODataSet2->Active=true;
		globalID=Form10->ADODataSet2Expr1000->AsInteger;//он сам назвал поле так. В нем хранится ид последней записи
		for(int i=1;i<=10;i++)
		{
			ADOCommand1->CommandText="INSERT INTO [every] ([DateTime],[brakeID],[id]) VALUES('"+
			(AnsiString)datetime+"','"+i+"','"+globalID+"')";
			ADOCommand1->Execute();
		}
		ADOCommand1->CommandText="INSERT INTO [widths]([id]) VALUES('"+IntToStr(globalID)+"')";
		ADOCommand1->Execute();
		this->Hide();
		Form4->Show();
	}
	else ShowMessage("Введены не все данные");
}
//---------------------------------------------------------------------------
void __fastcall TForm8::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key==VK_RETURN)
	{
        Button1Click(this);
    }
}
//---------------------------------------------------------------------------

