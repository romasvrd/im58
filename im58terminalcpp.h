//---------------------------------------------------------------------------

#ifndef im58terminalcppH
#define im58terminalcppH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TRichEdit *RichEdit1;
	TEdit *EditCmd;
	TSpeedButton *SpeedButton1;
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
/*class TRecv : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall TRecv(bool CreateSuspended);
};          */
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
