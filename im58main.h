//---------------------------------------------------------------------------

#ifndef im58mainH
#define im58mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Outline.hpp>
#include <Vcl.Samples.DirOutln.hpp>
#include "_GClass.hpp"
#include "AbHSlide.hpp"
#include "AbCBitBt.hpp"
#include "AbSwitch.hpp"
#include "AbRMeter.hpp"
#include "AbMTrend.hpp"
#include "AbTrend.hpp"
#include "AbLED.hpp"
#include "AbDBCtrls.hpp"
#include "AbVInd.hpp"
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeeFunci.hpp>
#include <Vcl.Mask.hpp>


typedef struct
{
	int size;
	byte qBytes[24];
} qStr;
typedef struct
{
	byte in[4];
	byte out[4];
	AnsiString Aout;
	int Iout;
} strSwap;

typedef struct
{
	int
	hwMachineNo,
	hwDInputs,
	hwDAC,
	hwReg,
	hwTacho,
	hwDOutputs,
	hwDrive,
	timeoffset;
	double pressuremax,
	timestop,
	k,
	b;
 }
 strHardware;

typedef struct
{
	uint32_t firstVolume;
	uint32_t lastVolume;
	uint32_t firstPage;
	uint32_t lastPage;
	byte lastVolumeBytes[4];
	byte firstVolumeBytes[4];
	byte firstPageBytes[4];
	byte lastPageBytes[4];
	uint16_t addr;
	uint16_t page;
	double braketime;
	double starttime;
	double finishtime;
} rec_struct;

typedef struct
{
	AnsiString string;
	bool bold;
} qString;

typedef struct
{
	double value1;
	double value2;
	double idx;
} diagramStruct;



//---------------------------------------------------------------------------
class TForm9 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *AltF41;
	TMenuItem *N2;
	TMenuItem *COM1;
	TMenuItem *N6;
	TMenuItem *N7;
	TAbToggleSwitch *AbToggleSwitch1;
	TAbHSlider *AbHSlider1;
	TAbHSlider *AbHSlider2;
	TAbToggleSwitch *AbToggleSwitch3;
	TEdit *Edit2;
	TEdit *Edit1;
	TAbToggleSwitch *AbToggleSwitch4;
	TAbDBLED *AbDBLED4;
	TAbToggleSwitch *AbToggleSwitch5;
	TAbDBLED *AbDBLED5;
	TButton *Button2;
	TEdit *Edit3;
	TLabel *Label12;
	TGroupBox *GroupBox7;
	TAbToggleSwitch *AbToggleSwitch10;
	TAbDBLED *AbDBLED6;
	TMemo *Memo1;
	TButton *Button4;
	TProgressBar *ProgressBar1;
	TChart *Chart1;
	TButton *Очистить;
	TLineSeries *Series1;
	TLabel *Label1;
	TLabel *Label13;
	TAbToggleSwitch *AbToggleSwitch6;
	TAbToggleSwitch *AbToggleSwitch7;
	TLabel *Label3;
	TLabel *Label5;
	TAb180Meter *Ab180Meter1;
	TLabel *Label4;
	TAbToggleSwitch *AbToggleSwitch112;
	TLabel *Label30;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TCheckBox *CheckBox7;
	TCheckBox *CheckBox8;
	TCheckBox *CheckBox9;
	TCheckBox *CheckBox10;
	TCheckBox *CheckBox11;
	TCheckBox *CheckBox12;
	TCheckBox *CheckBox13;
	TCheckBox *CheckBox14;
	TCheckBox *CheckBox15;
	TCheckBox *CheckBox16;
	TGroupBox *GroupBox6;
	TMenuItem *N4;
	TMenuItem *N8;
	TComboBox *ComboBox1;
	TMenuItem *N9;
	TMenuItem *N10;
	TLineSeries *Series2;
	TAbLED *AbLED3;
	TAbLED *AbLED1;
	TGroupBox *GroupBox8;
	TButton *Button1;
	TButton *Button3;
	TLabel *Label2;
	TLabel *Label11;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TMaskEdit *MaskEdit1;
	TComboBox *ComboBox2;
	TRichEdit *RichEdit1;
	TButton *Button5;
	TButton *Button6;
	TAbLED *AbLED2;
	TAbToggleSwitch *AbToggleSwitch2;
	TMaskEdit *MaskEdit2;
	TTimer *Timer1;
	TButton *Button7;
	TButton *Button8;
	TEdit *Edit7;
	TLabel *lbl1;
	TLabel *Label6;
	TEdit *Edit8;
	void __fastcall AltF41Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall AbHSlider1ValueChange(TObject *Sender);
	void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall AbHSlider2ValueChange(TObject *Sender);
	void __fastcall Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall AbToggleSwitch6StatusChanged(TObject *Sender);
	void __fastcall AbToggleSwitch7StatusChanged(TObject *Sender);
	void __fastcall AbToggleSwitch8Changed(TObject *Sender);
	void __fastcall AbToggleSwitch1StatusChanged(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall AbToggleSwitch10StatusChanged(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall ОчиститьClick(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall AbToggleSwitch112StatusChanged(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall COM1Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall AbToggleSwitch2Click(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall AbLED2StatusChanged(TObject *Sender);
	void __fastcall AbDBLED4StatusChanged(TObject *Sender);
	void __fastcall AbDBLED5StatusChanged(TObject *Sender);
	void __fastcall AbToggleSwitch4Click(TObject *Sender);
	void __fastcall AbToggleSwitch5Click(TObject *Sender);
	void __fastcall AbDBLED6StatusChanged(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall AbToggleSwitch10Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
		private:	// User declarations
public:		// User declarations
	__fastcall TForm9(TComponent* Owner);

};
class TTest
{
	public:
	int qty;
	AnsiString name;
	double pressure;
	bool checkForAir(void);
	void readIOStatus(void);
	int cooltime;
	int rolls;
	int rollmax;
	int rolltest;
	int brakespeed;
	int diskrete;
	bool pressbutton;
	double force_k;	//коэффициент К на тормозном цилиндре
	void setCurrent(bool chanel, double voltage);
	void setDOuts(uint8_t relay, uint8_t status);
    void brake(bool status); 	//тормоз
	void cooler(bool status);   //охлаждение
	void clutch (bool status);	//сцепление
	void drive (bool status);
	int brakecount;
	int showcount;
};
class TConvert
{
	public:
    double MaToBar(double value);
	double MaToKg(double value);
	double BarToMa(double value);
	double BarToKg_conv(double value);
	double KgToMa(double value);
	double KgToBar(double value);
};
class TEvents
{
	public:
	bool AutoConnectEvent;
	bool DriveVoltageEvent;
};
typedef union
{
    float f;
	unsigned char b[4];
} to_iee754_t;

#define TACHO_MERADAT 0
#define TACHO_VEHA_T 1

void stoprolling(void);
void tacho (void);
bool tacho_checkconnect(int tacho_type);
//---------------------------------------------------------------------------
extern PACKAGE TForm9 *Form9;
//---------------------------------------------------------------------------
#endif
