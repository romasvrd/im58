//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <vector>

#include "im58testsettings.h"
#include "im58main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern TTest test;
TForm5 *Form5;
extern TIniFile *initest;
extern const double BarToKg=1.01971621297793;
extern std::vector<TTest> vectorTest;
int iglob=0;
bool flagsaved;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::FormShow(TObject *Sender)
{
	flagsaved=false;
	if(PageControl1->PageCount==1)
	{
		PageControl1->Pages[0]->Free();
		for(int i=0;i<test.qty;i++)
		{
			TTest temptest;
			temptest=vectorTest[i];
			TTabSheet *TabSheet;
			TabSheet=new TTabSheet(PageControl1);
			TabSheet->PageControl = PageControl1;
			TabSheet->Caption = temptest.name;
			TabSheet->Name="Sheet"+IntToStr(i);

			TValueListEditor *ListEditor;
			ListEditor=new TValueListEditor(TabSheet);
			ListEditor->Name="List"+IntToStr(i);
			ListEditor->Align=alTop;
			ListEditor->DropDownRows=5;
			ListEditor->Height=121;
			ListEditor->Width=352;
			ListEditor->TitleCaptions->Insert(0,"Параметр");
			ListEditor->TitleCaptions->Insert(1,"Значение");
			ListEditor->ColWidths[0]=283;
			ListEditor->ScrollBars=ssNone;
			ListEditor->Parent=TabSheet;
			char asdf[5];
			//ListEditor->Values["Максимальное давление в тормозном цилиндре, кг"]=temptest.pressuremax*25*M_PI*BarToKg;
			ListEditor->Values["Рабочее давление в тормозном цилиндре, кг"]=temptest.pressure*25*M_PI*BarToKg;
			ListEditor->Values["Максимальные обороты вала, об/мин"]=temptest.rollmax;
			ListEditor->Values["Рабочие обороты (начало торможения), об/мин"]=temptest.rolltest;
			int mins=(temptest.cooltime/1000)/60;
			int secs=(temptest.cooltime/1000)-mins*60;
			sprintf(asdf,"%02d:%02d",mins,secs);
			ListEditor->Values["Время охлаждения, мин:сек"]=asdf;
			ListEditor->ItemProps["Время охлаждения, мин:сек"]->EditMask="!90:00;1;_";
		}
	}
	iglob=PageControl1->PageCount;
}
//---------------------------------------------------------------------------
int TForm5::readTestSettings(void)
{
	if(!FileExists(".\\im58_test.ini",0))
	{
		return 1;
	}
	test.qty=StrToInt(initest->ReadString("Металлокерамики","Количество",0));
	if(test.qty==0)
	{
		ShowMessage("Не указано ни одной металлокерамики. Введите хотя бы один для продолжения работы");
	}
	for(int i=0;i<test.qty;i++)
	{
		test.name=initest->ReadString("Металлокерамики",i,"undefined");
		AnsiString aTime;
		test.pressure=(initest->ReadString(test.name,"Brake pressure",0)).ToDouble();
		test.rollmax=StrToInt(initest->ReadString(test.name,"Max turns",0));
		test.rolltest=StrToInt(initest->ReadString(test.name,"Working turns",0));
		test.cooltime=StrToInt(initest->ReadString(test.name,"Cooling time",0));
		vectorTest.push_back(test);
	}
	return 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button1Click(TObject *Sender)
{
 //удалить те, что были и добавить те, которых не было
	DeleteFile(initest->FileName);
	vectorTest.clear();
	int i=0,counter=0;
	//добавить
	TTabSheet *TabSheet;
	TValueListEditor *ListEditor;
    flagsaved=true;
	for(i;i<=iglob;i++)
	{

	  a:	TabSheet=new TTabSheet(PageControl1);
		TabSheet=(TTabSheet*)this->PageControl1->FindComponent("Sheet"+IntToStr(i));
		ListEditor=new TValueListEditor(TabSheet);
		try
		{
			//пытаемся поймать список на вкладке
			if(TabSheet->FindComponent("List"+IntToStr(i)))
			{
                ListEditor=(TValueListEditor*)TabSheet->FindComponent("List"+IntToStr(i));
			  	//пишем существующие металлокерамики
				initest->WriteString("Металлокерамики",counter,TabSheet->Caption);
				AnsiString aTime;
				test.name=TabSheet->Caption;
				test.pressure=((ListEditor->Values["Рабочее давление в тормозном цилиндре, кг"]).ToDouble())/25/M_PI/BarToKg;
				test.rollmax=StrToInt(ListEditor->Values["Максимальные обороты вала, об/мин"]);
				test.rolltest=StrToInt(ListEditor->Values["Рабочие обороты (начало торможения), об/мин"]);
				aTime=ListEditor->Values["Время охлаждения, мин:сек"];
				test.cooltime=aTime.SubString(0,2)*60000+aTime.SubString(4,2)*1000;
				initest->WriteString(TabSheet->Caption,"Brake pressure",test.pressure);
				initest->WriteString(TabSheet->Caption,"Max turns",test.rollmax);
				initest->WriteString(TabSheet->Caption,"Working turns",test.rolltest);
				initest->WriteString(TabSheet->Caption,"Cooling time",test.cooltime);
				//initest->WriteString(PageControl1->Pages[i]->Caption,"Max pressure",test.pressuremax);
				initest->WriteString("Металлокерамики","Количество",this->PageControl1->PageCount);
				test.qty=counter;
				vectorTest.push_back(test);
				counter++;
			}
		}
		catch(Exception &e)
		{
			//если такого нет
			if(++i>iglob)return;
			goto a;

		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button2Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button3Click(TObject *Sender)
{
	if(this->Edit1->Text=="")
	{
		ShowMessage("Введите название керамики.");
		return;
    }
	TTabSheet *TabSheet;
	TabSheet=new TTabSheet(PageControl1);
	TabSheet->PageControl = PageControl1;
	TabSheet->Caption = Edit1->Text;
	int i=PageControl1->PageCount-1;
	a:
	try
	{
		TabSheet->Name="Sheet"+IntToStr(i);
		iglob=i;
	}
	catch(Exception &e)
	{
		i++;
		goto a;
		iglob=i;
	}
	TValueListEditor *ListEditor;
	ListEditor=new TValueListEditor(TabSheet);
	ListEditor->Values["Рабочее давление в тормозном цилиндре, кг"]=0;
	ListEditor->Values["Максимальные обороты вала, об/мин"]=0;
	ListEditor->Values["Рабочие обороты (начало торможения), об/мин"]=0;
	ListEditor->Values["Время охлаждения, мин:сек"]="00:00";
	ListEditor->Align=alTop;
	ListEditor->DropDownRows=5;
	ListEditor->Height=121;
	ListEditor->Width=352;
	ListEditor->TitleCaptions->Insert(0,"Параметр");
	ListEditor->TitleCaptions->Insert(1,"Значение");
	ListEditor->ColWidths[0]=283;
	ListEditor->ScrollBars=ssNone;
	ListEditor->Parent=TabSheet;
	ListEditor->Name="List"+IntToStr(i);
	PageControl1->ActivePageIndex=PageControl1->PageCount-1;
	ListEditor->ItemProps["Время охлаждения, мин:сек"]->EditMask="!90:00;1;_";

}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button4Click(TObject *Sender)
{
 /*	int qty=StrToInt(initest->ReadString("Металлокерамики","Количество",0));
	if((test.qty==qty)&&(test.qty<PageControl1->PageCount))
	{
		//проверяем, что активная страница не была сохранена
		vectorTest.erase(vectorTest.begin()+PageControl1->ActivePageIndex);
		initest->DeleteKey("Металлокерамики",PageControl1->ActivePageIndex);
		initest->EraseSection(PageControl1->ActivePage->Caption);
		initest->DeleteKey("Металлокерамики",PageControl1->ActivePageIndex);
		int a=StrToInt(initest->ReadString("Металлокерамики","Количество",0));
		if(a!=0) a--;
		initest->WriteString("Металлокерамики","Количество",a);
	}   */
	PageControl1->ActivePage->Free();
	//vector<TTest>(vectorTest).swap(vectorTest);
	//PageControl1->ActivePageIndex
}
//---------------------------------------------------------------------------
void __fastcall TForm5::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(flagsaved)
	{
		return;
    }
	switch(MessageBox(NULL,"Сохранить настройки?","Настройки испытаний",MB_YESNO|MB_ICONQUESTION|MB_SETFOREGROUND))
	{
		case ID_YES: Button1Click(this);break;
		case ID_NO:
		{
			for(int i=this->PageControl1->PageCount-1;i>=test.qty;i--)
			{
				//TValueListEditor ListEditor=PageControl1->Pages[i]->FindComponent("List"+i);
				//delete ListEditor;
				delete PageControl1->Pages[i];
            }
		} break;
	}
}
//---------------------------------------------------------------------------
