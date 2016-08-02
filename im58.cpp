//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "im58auto.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("im58main.cpp", Form9);
USEFORM("im58results.cpp", Form6);
USEFORM("im58who.cpp", Form8);
USEFORM("im58testsettings.cpp", Form5);
USEFORM("im58serial.cpp", Form2);
USEFORM("im58hello.cpp", Form1);
USEFORM("im58archive.cpp", Form10);
USEFORM("im58about.cpp", AboutBox);
USEFORM("im58auto.cpp", Form4);
USEFORM("im58heights.cpp", Form3);
//---------------------------------------------------------------------------
extern char progpath[254];
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		DeleteFile((UnicodeString)progpath+"port1log.txt");
		DeleteFile((UnicodeString)progpath+"port2log.txt");
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "Инерционный стенд ИМ-58";
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->CreateForm(__classid(TForm9), &Form9);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TForm5), &Form5);
		Application->CreateForm(__classid(TForm6), &Form6);
		Application->CreateForm(__classid(TForm4), &Form4);
		Application->CreateForm(__classid(TForm8), &Form8);
		Application->CreateForm(__classid(TForm10), &Form10);
		Application->CreateForm(__classid(TForm3), &Form3);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			TStringList *sl=new TStringList(Form4);
			for(int i=0;i<=Form4->RichEdit1->Lines->Count;i++)
			{
				sl->Add(Form4->RichEdit1->Lines->operator [](i));
			}
			sl->SaveToFile((UnicodeString)progpath+"log.txt");
			delete sl;
			Application->ShowException(&exception);

		}
	}
	return 0;
}
//---------------------------------------------------------------------------
