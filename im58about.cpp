//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <windows.h>
#include "im58main.h"
#include "im58serial.h"
#include "im58about.h"
#include "im58drive.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//--------------------------------------------------------------------- 
