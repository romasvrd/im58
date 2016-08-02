//---------------------------------------------------------------------------
#pragma hdrstop
#include "im58main.h"
#include "im58serial.h"
#include "im58about.h"
#include "im58drive.h"
#include "im58recorder.h"
#include "im58hello.h"
#include "im58auto.h"
#include "im58testsettings.h"
#include "im58results.h"
#include "im58who.h"
#include "im58heights.h"
#include "im58archive.h"
extern HANDLE hThread;
extern HANDLE hRead1;
extern HANDLE hRead2;
extern HANDLE hSend1;
extern HANDLE hSend2;
extern DWORD WINAPI thSend1(LPVOID);
extern bool inputState;
extern bool port1Closed,port2Closed;
extern TTest test;
extern TTest currentTest;
extern int globalID;
bool ResumeTest=false;
int ResumeBrakeCount;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "_GClass"
#pragma link "AbLED"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Form9->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Form8->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Form5->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	Form2->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	test.clutch(false);
	test.drive(false);
	test.setCurrent(1,0);
	if(!port1Closed)comPort1Close();
	if(!port2Closed)comPort2Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Form10->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	Application->Terminate();
//	Form3->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
	Form10->ADODataSet2->Active=true;
	int id=Form10->ADODataSet2Expr1000->AsInteger;//он сам назвал поле так. В нем хранится ид последней записи
	Form10->ADODataSet2->Active=false;
	ADODataSet1->CommandText="select * from every where id="+IntToStr(id)+" order by brakeID asc";
	ADODataSet1->Active=true;
	ADODataSet2->CommandText="select * from widths where id="+IntToStr(id);
	ADODataSet2->Active=true;
	for(int i=1;i<=10;i++)
	{
		if(ADODataSet1->FieldByName("speed")->Value==0)
		{
			//если в какой-то записи какое-то поле, напр.скорость, содержит 0, значит
			//это и последующее торможение не проводилось. Предлагаем начать с него
			switch(MessageBox(NULL,"Последнее испытание не завершено. Желаете продолжить?","Есть незавершенное испытание",MB_ICONQUESTION|MB_YESNO|MB_SYSTEMMODAL))
			{
				case ID_YES:
					globalID=id;
					ResumeTest=true;
					ResumeBrakeCount=ADODataSet1->FieldByName("brakeID")->Value;
					ADODataSet1->Active=false;

					currentTest.brakecount=ResumeBrakeCount+5;
					test.brakecount=ResumeBrakeCount+5;

					//получение толщин образцов после притирки, измеренных в последнем испытании

						for(int j=1;j<=Form3->StringGrid1->RowCount;j++)
						{
							Form3->StringGrid1->Cells[1][j]=ADODataSet2->FieldByName("wobr"+IntToStr(i))->Value;
						}


						for(int j=1;j<=Form3->StringGrid2->RowCount;j++)
						{
							Form3->StringGrid2->Cells[1][j]=ADODataSet2->FieldByName("wc"+IntToStr(i))->Value;
						}

					Form4->RichEdit1->Lines->Add("Испытание будет возобновлено с зачетного торможения №"+IntToStr(ResumeBrakeCount)+". \r\nУстановите связь, включите привод, выберите программу испытания и нажмите Старт.");
					ADODataSet2->Active=false;
					Form4->Show();
					return;
				case ID_NO:
					ADODataSet1->Active=false;
					return;
			}
		}
		else
		{
			ADODataSet1->RecNo++;
        }
	}
}
//---------------------------------------------------------------------------

