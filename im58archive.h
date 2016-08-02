//---------------------------------------------------------------------------

#ifndef im58archiveH
#define im58archiveH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm10 : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TADODataSet *ADODataSet1;
	TADOConnection *ADOConnection1;
	TDataSource *DataSource1;
	TADOCommand *ADOCommand1;
	TDataSource *DataSource2;
	TADODataSet *ADODataSet2;
	TIntegerField *ADODataSet2Expr1000;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TWideStringField *ADODataSet1���;
	TAutoIncField *ADODataSet1id;
	TDateTimeField *ADODataSet1DateTime;
	TWideStringField *ADODataSet1�������;
	TWideStringField *ADODataSet1��������;
	TWideStringField *ADODataSet1������;
	TWideStringField *ADODataSet1�����_����;
	TWideStringField *ADODataSet1���������;
	TWideStringField *ADODataSet1���������_���������;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	private:	// User declarations
public:		// User declarations
	__fastcall TForm10(TComponent* Owner);
	void DelRecord(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm10 *Form10;
//---------------------------------------------------------------------------
#endif
