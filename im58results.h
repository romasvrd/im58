//---------------------------------------------------------------------------

#ifndef im58resultsH
#define im58resultsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Grids.hpp>
#include "AbPrtTrd.hpp"
#include <Data.DB.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TLabel *Label2;
	TStringGrid *sg;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TPrinterSetupDialog *PrinterSetupDialog1;
	TADODataSet *ADODataSet1;
	TDataSource *DataSource1;
	TADODataSet *ADODataSet2;
	TDataSource *DataSource2;
	TDateTimeField *ADODataSet1DateTime;
	TWideStringField *ADODataSet1���;
	TWideStringField *ADODataSet1��������;
	TIntegerField *ADODataSet1�����_���������;
	TFloatField *ADODataSet1Jh���;
	TFloatField *ADODataSet1Jh����;
	TAutoIncField *ADODataSet1id;
	TDateTimeField *ADODataSet2DateTime;
	TFloatField *ADODataSet2pressure;
	TFloatField *ADODataSet2force;
	TIntegerField *ADODataSet2speed;
	TIntegerField *ADODataSet2turns;
	TFloatField *ADODataSet2coef_stable;
	TFloatField *ADODataSet2coef_fric;
	TFloatField *ADODataSet2middle_moment;
	TFloatField *ADODataSet2max_moment;
	TSmallintField *ADODataSet2brakeID;
	TIntegerField *ADODataSet2id;
	TFloatField *ADODataSet2duration;
	TPageSetupDialog *PageSetupDialog1;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label8;
	TLabel *Label9;
	TGridPanel *GridPanel1;
	TLabel *Label10;
	TLabel *Label11;
	TWideStringField *ADODataSet1������;
	TWideStringField *ADODataSet1�������������;
	TSmallintField *ADODataSet1���_������������;
	TWideStringField *ADODataSet1�������;
	TWideStringField *ADODataSet1�����_����;
	TWideStringField *ADODataSet1���������;
	TWideStringField *ADODataSet1���������_���������;
	TLabel *Label12;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall sgMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm6(TComponent* Owner);
};
class TTestResults
{
	public:
	double ��������_�_�������;
	double ������_������;
	double ��������_������_����������;
	double ������������_����������;
	int �������_��_����������;
	double �����������_������;
	double �������_������;
	int ������������_������;
	double �����������_������������;
};

//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
