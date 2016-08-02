//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "im58archive.h"
#include "im58results.h"
#include "im58auto.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm10 *Form10;
int idx;
AnsiString datestring;
extern int globalID;
char progpath[254];
//---------------------------------------------------------------------------
__fastcall TForm10::TForm10(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm10::Button1Click(TObject *Sender)
{                                                                                   //"+Edit1->Text+"
//insert into every(DateTime,pressure,force,speed,turns,coef_stable,coef_fric,middle_moment,max_moment,brakeID) values('24.03.2015 20:01','1,06240437904749','85,0861862194844','0','0','0,073785803237858','0,0402052229968878','91,4130457677902','146','10')
	//this->ADOCommand1->CommandText=("INSERT INTO after10 (Jh(фмк), ФИО) VALUES ('23,23', 'asdf')");
   //	ADOCommand1->Execute();
   EndOfTest();
}
//---------------------------------------------------------------------------
void __fastcall TForm10::DBGrid1CellClick(TColumn *Column)
{
	//DBGrid1->DataSource->DataSet->RecNo;
	datestring=DBGrid1->Fields[1]->AsString;
	globalID=ADODataSet1->FieldByName("id")->Value;
	Form6->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm10::FormCreate(TObject *Sender)
{
	AnsiString ppath=ExtractFilePath(ParamStr(0));
	sprintf(progpath,"%s",ppath.c_str());
	//ADOConnection1->ConnectionString="Provider=Microsoft.ACE.OLEDB.15.0;User ID=Admin;Data Source="+ExtractFilePath	(ParamStr(0))+"archive.accdb;Mode=Share Deny None;Jet OLEDB:System database="";Jet OLEDB:Registry Path="";Jet OLEDB:Database Password="";Jet OLEDB:Engine Type=6;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password="";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False;Jet OLEDB:Support Complex Data=False;Jet OLEDB:Bypass UserInfo Validation=False;Jet OLEDB:Limited DB Caching=False;Jet OLEDB:Bypass ChoiceField Validation=False;";
   ADOConnection1->ConnectionString="Provider=Microsoft.ACE.OLEDB.12.0;Data Source="+ExtractFilePath(ParamStr(0))+"archive.mdb;Persist Security Info=False";

   try
	{
		ADOConnection1->Connected=true;
		ADOConnection1->Open();
		ADODataSet1->Active=true;
	}
	catch (Exception &e)
	{
		AnsiString errstr=e.Message;
		MessageBox(NULL,errstr.c_str(),NULL,MB_ICONERROR|MB_OK);
		Application->Terminate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm10::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key==VK_DELETE)
	{
		switch(MessageBox(NULL,"Вы действительно хотите удалить эту запись? Эту операцию нельзя отменить!","Подтвердите удаление",MB_ICONQUESTION|MB_YESNO))
		{
			case ID_YES:DelRecord();break;
			case ID_NO:break;
			default:break;
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm10::DBGrid1DblClick(TObject *Sender)
{
	//DBGrid1->DataSource->DataSet->RecNo;
	datestring=DBGrid1->Fields[1]->AsString;
	globalID=ADODataSet1->FieldByName("id")->Value;
	Form6->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm10::N1Click(TObject *Sender)
{
	//DBGrid1->DataSource->DataSet->RecNo;
	datestring=DBGrid1->Fields[1]->AsString;
	globalID=ADODataSet1->FieldByName("id")->Value;
	Form6->Show();
}
//---------------------------------------------------------------------------
void TForm10::DelRecord(void)
{
	globalID=ADODataSet1->FieldByName("id")->Value;
	this->ADOCommand1->CommandText="DELETE FROM after10 WHERE id="+IntToStr(globalID);//+" && every.id="+IntToStr(globalID);
	ADOCommand1->Execute();
	this->ADOCommand1->CommandText="DELETE FROM every WHERE id="+IntToStr(globalID);//+" && every.id="+IntToStr(globalID);
	ADOCommand1->Execute();
	this->ADODataSet1->Active=false;
	this->ADODataSet1->Active=true;
	this->DBGrid1->Enabled=false;
	this->DBGrid1->Enabled=true;
}
void __fastcall TForm10::N2Click(TObject *Sender)
{
	switch(MessageBox(NULL,"Вы действительно хотите удалить эту запись? Эту операцию нельзя отменить!","Подтвердите удаление",MB_ICONQUESTION|MB_YESNO))
	{
		case ID_YES:DelRecord();break;
		case ID_NO:break;
		default:break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm10::FormShow(TObject *Sender)
{
	this->ADODataSet1->Active=false;
	this->ADODataSet1->Active=true;
	this->DBGrid1->Enabled=false;
	this->DBGrid1->Enabled=true;
}
//---------------------------------------------------------------------------


