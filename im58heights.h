//---------------------------------------------------------------------------

#ifndef im58heightsH
#define im58heightsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TStringGrid *StringGrid2;
	TButton *Button5;
	TADOCommand *ADOCommand1;
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall StringGrid2SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);


private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
