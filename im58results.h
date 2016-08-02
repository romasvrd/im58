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
	TWideStringField *ADODataSet1ФИО;
	TWideStringField *ADODataSet1Материал;
	TIntegerField *ADODataSet1Режим_испытания;
	TFloatField *ADODataSet1Jhфмк;
	TFloatField *ADODataSet1Jhчнмх;
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
	TWideStringField *ADODataSet1Партия;
	TWideStringField *ADODataSet1Изготовленная;
	TSmallintField *ADODataSet1Год_изготовления;
	TWideStringField *ADODataSet1Изделие;
	TWideStringField *ADODataSet1Контр_тело;
	TWideStringField *ADODataSet1Твердость;
	TWideStringField *ADODataSet1Программа_испытания;
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
	double давление_в_тормозе;
	double осевое_усилие;
	double скорость_начала_торможения;
	double длительность_торможения;
	int обороты_за_торможение;
	double коэффициент_трения;
	double средний_момент;
	int максимальный_момент;
	double коэффициент_стабильности;
};

//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
