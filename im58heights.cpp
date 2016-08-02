//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "im58heights.h"
#include "im58auto.h"
#include "im58archive.h"
#include "im58main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
extern TTest currentTest;
extern bool readystream;
extern bool readyrec;
extern bool readybutton;
extern HANDLE hThread;
extern double obr;
extern double contr;
extern bool buttonfinish;
extern bool streamfinish;
extern int globalID;
//extern bool flagafter;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button5Click(TObject *Sender)
{
	String cmd;
	uint8_t error=0;
	obr=0;
	contr=0;
	//���� ������ ������ 5 ����������� ����������, ���������� �������
	if(currentTest.brakecount<=6)
	{
		for(int i=1;i<=8;i++)
		{
			if(Form3->StringGrid1->Cells[1][i]=="")
			{
				error=1;
			}
			if(StrToFloat(Form3->StringGrid1->Cells[1][i])<=0)
			{
				error=5;
			}
		}
		for(int i=1;i<=6;i++)
		{
			if(Form3->StringGrid2->Cells[1][i]=="")
			{
				error=2;
			}
			if(StrToFloat(Form3->StringGrid2->Cells[1][i])<=0)
			{
				error=6;
			}
		}
	}
	else
		{
		for(int i=1;i<=8;i++)
		{
			if(Form3->StringGrid1->Cells[2][i]=="")
			{
				error=3;
			}
			if(StrToFloat(Form3->StringGrid1->Cells[2][i])<=0)
			{
				error=7;
			}
		}
		for(int i=1;i<=6;i++)
		{
			if(Form3->StringGrid2->Cells[2][i]=="")
			{
				error=4;
			}
			if(StrToFloat(Form3->StringGrid2->Cells[2][i])<=0)
			{
				error=8;
			}
		}
	}
	switch(error)
	{
		case 0:break;
		case 1:ShowMessage("��������� �� ��� ���� h' ��� ��������");return;
		case 2:ShowMessage("��������� �� ��� ���� h' ��� ����������� ���");return;
		case 3:ShowMessage("��������� �� ��� ���� h\" ��� ��������");return;
		case 4:ShowMessage("��������� �� ��� ���� h\" ��� ����������� ���");return;
		case 5:ShowMessage("������ �������� h' ������ ���� �������������");return;
		case 6:ShowMessage("������ ����������� ��� h' ������ ���� �������������");return;
		case 7:ShowMessage("������ �������� h\" ������ ���� �������������");return;
		case 8:ShowMessage("������ ����������� ��� h\" ������ ���� �������������");return;
	}
	if(error==0&&currentTest.brakecount<=6)
	{
		cmd=
		"UPDATE [widths] SET ";
		for(int i=1;i<=8;i++) 	//� ����� �������� ������ sql-������
		{
			cmd+="[wobr"+IntToStr(i)+"]";
			if(i==8)
			{
				//� ��������� �������� ������� �� �����
				cmd+="='"+StringGrid1->Cells[1][i]+"'";
			}
			else
			{
				cmd+="='"+StringGrid1->Cells[1][i]+"',";
			}
		}
		cmd+=" where id="+IntToStr(globalID)+"";
		Form10->ADOCommand1->CommandText=cmd;  	//��� ����, ����� ��� ��������� ���� ������ �������� �������� ������ ���������� � ���������� update.
		Form10->ADOCommand1->Execute();         //���� ������� ������� ������, ������� �, � �������� � � ������������ - �� ��

		cmd=
		"UPDATE [widths] SET ";
		for(int i=1;i<=6;i++) 	//� ����� �������� ������ sql-������
		{
			cmd+="[wc"+IntToStr(i)+"]";
			if(i==6)
			{
				cmd+="='"+StringGrid1->Cells[1][i]+"'";
			}
			else
			{
				//� ����� ������� �� �����
				cmd+="='"+StringGrid1->Cells[1][i]+"',";
			}
		}
		cmd+=" where id="+IntToStr(globalID);
		Form10->ADOCommand1->CommandText=cmd;
		Form10->ADOCommand1->Execute();

		ShowMessage("��� ������� �������������� ����� �� 10 ���������� ������� �����");
		if(currentTest.brakecount==6&&readyrec&&readystream) ResumeThread(hThread);
		else readybutton=true;
		this->Hide();
	}
	if(error==0&&currentTest.brakecount>6)
	{
		for(int i=1;i<=8;i++)
		{
			if(StringGrid1->Cells[3][i]<=0)
			{
				ShowMessage("������ ������� "+IntToStr(i)+" ����� ��������� ������ ���� ������, ��� �� ���������");
				return;
			}
		}
		for(int i=1;i<=6;i++)
		{
			if(StringGrid2->Cells[3][i]<=0)
			{
				ShowMessage("������ ������������ ���� "+IntToStr(i)+" ����� ��������� ������ ���� ������, ��� �� ���������");
				return;
			}
		}
		for(int i=1;i<=8;i++)
		{
			obr+=StrToFloat(Form3->StringGrid1->Cells[3][i]);
		}
		obr/=0.08;
		for(int i=1;i<=6;i++)
		{
			contr+=StrToFloat(Form3->StringGrid2->Cells[3][i]);
		}
		contr/=0.06;

		buttonfinish=true;
		EndOfTest();
		this->Hide();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormShow(TObject *Sender)
{
	if(currentTest.brakecount==6)
	{
		ShowMessage("����������� 5 ����������� ����������. �������� ������\
		�������� � ����������� ��� ����������� � ��������� ������� h'\
		� ������� � ������� \"������\"");
	}
	if(currentTest.brakecount==16)
	{
		ShowMessage("����������� 10 �������� ����������. �������� ������\
		�������� � ����������� ��� ����������� � ��������� ������� h\"\
		� ������� � ������� \"������\"");
	}
	StringGrid1->Cells[0][0]="�������";
	StringGrid1->Cells[0][1]="1";
	StringGrid1->Cells[0][2]="2";
	StringGrid1->Cells[0][3]="3";
	StringGrid1->Cells[0][4]="4";
	StringGrid1->Cells[0][5]="5";
	StringGrid1->Cells[0][6]="6";
	StringGrid1->Cells[0][7]="7";
	StringGrid1->Cells[0][8]="8";
	StringGrid1->Cells[1][0]="h'";
	StringGrid1->Cells[2][0]="h\"";
	StringGrid1->Cells[3][0]="dh";
	StringGrid2->Cells[0][0]="�����. ����";
	StringGrid2->Cells[0][1]="1";
	StringGrid2->Cells[0][2]="2";
	StringGrid2->Cells[0][3]="3";
	StringGrid2->Cells[0][4]="4";
	StringGrid2->Cells[0][5]="5";
	StringGrid2->Cells[0][6]="6";
	StringGrid2->Cells[1][0]="h'";
	StringGrid2->Cells[2][0]="h\"";
	StringGrid2->Cells[3][0]="dh";
	StringGrid1->ColWidths[0]=StringGrid2->Canvas->TextWidth(StringGrid2->Cells[0][0])+15;
	StringGrid2->ColWidths[0]=StringGrid1->ColWidths[0];
}
//---------------------------------------------------------------------------
void __fastcall TForm3::StringGrid1SetEditText(TObject *Sender, int ACol, int ARow,
		  const UnicodeString Value)
{
	double one,two;
	if(!((Form3->StringGrid1->Cells[1][ARow]=="")||(Form3->StringGrid1->Cells[2][ARow]=="")))
	{
		one=StrToFloat(Form3->StringGrid1->Cells[1][ARow]);
		two=StrToFloat(Form3->StringGrid1->Cells[2][ARow]);
		Form3->StringGrid1->Cells[3][ARow]=one-two;
	}

}//---------------------------------------------------------------------------

void __fastcall TForm3::StringGrid2SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
	double one,two;
	if(!((Form3->StringGrid2->Cells[1][ARow]=="")||(Form3->StringGrid2->Cells[2][ARow]=="")))
	{
		one=StrToFloat(Form3->StringGrid2->Cells[1][ARow]);
		two=StrToFloat(Form3->StringGrid2->Cells[2][ARow]);
		Form3->StringGrid2->Cells[3][ARow]=one-two;
	}
}
//---------------------------------------------------------------------------

