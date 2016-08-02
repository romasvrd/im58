//---------------------------------------------------------------------------

#ifndef im58serialH
#define im58serialH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TComboBox *ComboBox2;
	TComboBox *ComboBox1;
	TButton *Button1;
	TButton *Button2;
	TComboBox *ComboBox3;
	TComboBox *ComboBox4;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TComboBox *ComboBox5;
	TComboBox *ComboBox6;
	TLabel *Label5;
	TGroupBox *GroupBox1;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TButton *Button3;
	TLabel *Label12;
	TComboBox *ComboBox7;
	TComboBox *ComboBox8;
	TLabel *Label13;
	TComboBox *ComboBox9;
	TComboBox *ComboBox10;
	TLabel *Label14;
	TEdit *Edit7;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TEdit *Edit8;
	TEdit *Edit9;
	TEdit *Edit10;
	TEdit *Edit11;
	TEdit *Edit12;
	TEdit *Edit13;
	TLabel *Baudrate;
	TLabel *Label1;
	TTimer *Timer1;
	TEdit *Edit14;
	TLabel *Label11;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	void printSettings(void);
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
void crc16 (const BYTE *nData, WORD wLength, int *crc1, int *crc2);
int comPort1Init (void);
int comPort2Init (void);
void comPort1Close (void);
void comPort2Close (void);
int readSettings (void);
int swapBytes(strSwap *sSwap);
void defaultSettings(void);
uint8_t LRC(uint8_t *str);

typedef struct
{
	AnsiString	port1Name;
	DCB port1Parameters;
	AnsiString	port2Name;
	DCB port2Parameters;
} portSettings;
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
