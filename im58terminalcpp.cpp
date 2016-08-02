//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <vcl.h>
#pragma hdrstop
#include <windows.h>
#include "im58main.h"
#include "im58terminalcpp.h"
#include "im58serial.h"
#include "im58debug.h"
#include "im58about.h"
#include "im58drive.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;  /*
TRecv *thrR;
__fastcall TRecv::TRecv(bool CreateSuspended)
	: TThread(CreateSuspended)
{

}
//---------------------------------------------------------------------------
void __fastcall TRecv::Execute()
{
	FreeOnTerminate = true;
	while (1)

	{
		Form9->readFromCom();
		if(Terminated)
		{
			return;
		}
	}
}                    */
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
