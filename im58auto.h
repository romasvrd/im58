//---------------------------------------------------------------------------

#ifndef im58autoH
#define im58autoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "_GClass.hpp"
#include "AbRMeter.hpp"
#include <Vcl.Mask.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "AbLED.hpp"
#include "AbSwitch.hpp"
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TRichEdit *RichEdit1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *AltF41;
	TButton *Button1;
	TAb180Meter *Ab180Meter1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TLabel *Label4;
	TButton *Сохранить;
	TButton *Button2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMaskEdit *MaskEdit1;
	TAbLED *AbLED1;
	TAbLED *AbLED2;
	TAbLED *AbLED3;
	TAbToggleSwitch *AbToggleSwitch2;
	TLabel *Label5;
	TComboBox *ComboBox1;
	TButton *Button4;
	TAbToggleSwitch *AbToggleSwitch1;
	TLabel *Label6;
	TTimer *Timer1;
	TMaskEdit *MaskEdit2;
	TTimer *Timer2;
	TAbToggleSwitch *AbToggleSwitch3;
	TAbLED *AbLED4;
	TChart *Chart1;
	TButton *Очистить;
	TLineSeries *Series1;
	TLineSeries *Series2;
	TMenuItem *N5;
	TButton *Button3;
	TTimer *Timer3;
	void __fastcall N2Click(TObject *Sender);
	void __fastcall AltF41Click(TObject *Sender);
	void __fastcall l(TObject *Sender);
	void __fastcall СохранитьClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall AbToggleSwitch2Click(TObject *Sender);
	void __fastcall AbLED2StatusChanged(TObject *Sender);
	void __fastcall StringGrid2SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall AbToggleSwitch1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall AbToggleSwitch3StatusChanged(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall AbLED3StatusChanged(TObject *Sender);


    private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
		void heightsBefore(void);
		void heightsAfter(void);

};
//---------------------------------------------------------------------------
		void tacho_reset(void);
		void tacho_result(void);
		void EndOfTest(void);
extern PACKAGE TForm4 *Form4;

//---------------------------------------------------------------------------
#endif
