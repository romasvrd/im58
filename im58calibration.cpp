//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "im58calibration.h"
#include "im58main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;
extern TTest test;
extern TTest currentTest;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm7::FormCreate(TObject *Sender)
{
	sg1->Cells[0][0]="Установить";
	sg1->Cells[1][0]="Регистратор";
	sg1->Cells[2][0]="Динамометр";
	sg1->ColWidths[0]=sg1->Canvas->TextWidth(sg1->Cells[0][0])+16;
	sg1->ColWidths[1]=sg1->Canvas->TextWidth(sg1->Cells[1][0])+16;
	sg1->ColWidths[2]=sg1->Canvas->TextWidth(sg1->Cells[2][0])+16;
	sg1->Width=sg1->ColWidths[0]+sg1->ColWidths[1]+sg1->ColWidths[2]+6;
	for(int i=1;i<=sg1->RowCount;i++)
	{
    	sg1->Cells[0][i]=IntToStr(i*20);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm7::btn1Click(TObject *Sender)
{
	double Xtotal,Ytotal;
	for(int i=1;i<sg1->RowCount;i++)
	{
		if(sg1->Cells[1][i]!=""&&sg1->Cells[2][i]!="")
		{
			Series1->AddXY(sg1->Cells[1][i].ToDouble(),sg1->Cells[2][i].ToDouble());
			Xtotal+=sg1->Cells[1][i].ToDouble();
			Ytotal+=sg1->Cells[2][i].ToDouble();
		}

		Series2->AddXY(Xtotal,Ytotal);
		test.force_k=Ytotal/Xtotal;
		currentTest.force_k=test.force_k;
	}
	lbl1->Caption=FloatToStr(test.force_k);
}
//---------------------------------------------------------------------------

