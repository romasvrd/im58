//---------------------------------------------------------------------------
#include <queue>
#pragma hdrstop
#include <windows.h>
#include "im58main.h"
#include "im58serial.h"
#include "im58about.h"
#include "im58drive.h"
 //di0 авария
 //1 кнопка питания нажата
// 2 контактор привода включен
extern std::queue<qStr> serialQueue1;
extern std::queue<qStr> serialQueue2;

extern strHardware hardware;
extern int crc1,crc2;
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
//==============================================================================
void StartMotor(int iAddress, ROTATE Rotate , int iSpeed)
{
	qStr strDriveStart;		//команда
	byte sAdr=iAddress;	// адрес
	byte sRot=Rotate;	// направление вращения
	byte sSpd[2];
	AnsiString tempSpd=IntToHex(iSpeed,4);
	AnsiString spd1 = "0x" + tempSpd.SubString(0, 2);
	AnsiString spd2 = "0x" + tempSpd.SubString(3, 2);
	sSpd[0]=spd1.ToInt();
	sSpd[1]=spd2.ToInt();
	strDriveStart.qBytes[0]=sAdr;
	strDriveStart.qBytes[1]=0x10;
	strDriveStart.qBytes[2]=0x00;
	strDriveStart.qBytes[3]=0x01;
	strDriveStart.qBytes[4]=0x00;
	strDriveStart.qBytes[5]=0x02;
	strDriveStart.qBytes[6]=0x04;
	strDriveStart.qBytes[7]=0x00;		//старший байт направления
	strDriveStart.qBytes[8]=sRot;		//младший байт направления
	strDriveStart.qBytes[9]=sSpd[0];	//старший байт скорости
	strDriveStart.qBytes[10]=sSpd[1];	//младший байт скорости
	crc16(strDriveStart.qBytes,11,&crc1,&crc2);
	strDriveStart.qBytes[11]=crc1;
	strDriveStart.qBytes[12]=crc2;
	strDriveStart.size=13;
	serialQueue1.push(strDriveStart);

}
//==============================================================================
void StopMotor(int iAddress)
{
	qStr strDriveStop;		//команда

	byte sAdr=iAddress;	// адрес

	// Адрес привода
	if(iAddress<10)
	{
		//sAdr = IntToHex(iAddress,2);
	}
	else
	{
		// обработать
	}
	strDriveStop.qBytes[0]=sAdr;
	strDriveStop.qBytes[1]=0x10;
	strDriveStop.qBytes[2]=0x00;
	strDriveStop.qBytes[3]=0x01;
	strDriveStop.qBytes[4]=0x00;
	strDriveStop.qBytes[5]=0x01;
	strDriveStop.qBytes[6]=0x02;
	strDriveStop.qBytes[7]=0x00;
	strDriveStop.qBytes[8]=0x20;
	crc16(strDriveStop.qBytes,9,&crc1,&crc2);
	strDriveStop.qBytes[9]=crc1;
	strDriveStop.qBytes[10]=crc2;
	strDriveStop.qBytes[11]=0x00;
	strDriveStop.qBytes[12]=0x00;
	strDriveStop.size=13;
	serialQueue1.push(strDriveStop);
}
//==============================================================================
void SetSpeedMotor(int iAddress, int iSpeed)
{
	qStr strDriveSpeed;
	byte sAdr=iAddress;
	byte sSpd[2];
	AnsiString tempSpd=IntToHex(iSpeed,4);
	AnsiString spd1 = "0x" + tempSpd.SubString(0, 2);
	AnsiString spd2 = "0x" + tempSpd.SubString(3, 2);
	sSpd[0]=spd1.ToInt();
	sSpd[1]=spd2.ToInt();
	const Kn = 20;		// корректировочный коэффициент задания скорости (! добавить его в основной программе)

   /*	if(iAddress<10)
	{
		sAdr = IntToHex(iAddress,2);
	}
	else
	{
		// обработать
	}
	sSpd = IntToHex(iSpeed-Kn,4);
	sSpd.Insert(" ",3);
	sCmd = sAdr + " " + "10 00 02 00 01 02" + " " + sSpd;   */
	strDriveSpeed.qBytes[0]=sAdr;
	strDriveSpeed.qBytes[1]=0x10;
	strDriveSpeed.qBytes[2]=0x00;
	strDriveSpeed.qBytes[3]=0x02;
	strDriveSpeed.qBytes[4]=0x00;
	strDriveSpeed.qBytes[5]=0x01;
	strDriveSpeed.qBytes[6]=0x02;
	strDriveSpeed.qBytes[7]=sSpd[0];
	strDriveSpeed.qBytes[8]=sSpd[1];
	crc16(strDriveSpeed.qBytes,9,&crc1,&crc2);
	strDriveSpeed.qBytes[9]=crc1;
	strDriveSpeed.qBytes[10]=crc2;
	strDriveSpeed.size=11;
	serialQueue1.push(strDriveSpeed);

}
//==============================================================================
void GetSpeedMotor(int iAddress)
{
	AnsiString sAdr;
	AnsiString sSpd;
	AnsiString sCmd;
	if(iAddress<10)
	{
		sAdr = IntToHex(iAddress,2);
	}
	else
	{
		// обработать
	}
	//sCmd = sAdr + " " + "03 00 24 00 01 02";  // на E7 работало так
	sCmd = sAdr + " " + "03 00 24 00 01";
	//fGet = SPEED;	// вынести из тела функции
	//TByteDynArray* cmd = StringToByteArray(sCmd);
	//return cmd;
}
//==============================================================================
void GetPowerMotor(int iAddress)
{
	AnsiString sAdr;
	AnsiString sSpd;
	AnsiString sCmd;
	if(iAddress<10)
	{
		sAdr = IntToHex(iAddress,2);
	}
	else
	{
		// обработать
	}
	//sCmd = sAdr + " " + "03 00 24 00 01 02";  // на E7 работало так
	sCmd = sAdr + " " + "03 00 27 00 01";
	//fGet = SPEED;	// вынести из тела функции
	//TByteDynArray* cmd = StringToByteArray(sCmd);
	//return cmd;
}
//==============================================================================
void GetSpeedAndPowerMotor(int iAddress)
{
	AnsiString sAdr;
	AnsiString sSpd;
	AnsiString sCmd;
	if(iAddress<10)
	{
		sAdr = IntToHex(iAddress,2);
	}
	else
	{
		// обработать
	}
	sCmd = sAdr + " " + "03 00 24 00 04";
	//fGet = SPEED;	// вынести из тела функции
	//TByteDynArray* cmd = StringToByteArray(sCmd);
	//return cmd;
}
//==============================================================================
void StringToByteArray(AnsiString HexStr)
{
	AnsiString buf;
	const CSum = 2;	//	количество байт контрольной суммы
	int idx=1;	// Индекс элемента в строке, являющегося началом очередного байта
	TByteDynArray *data = new TByteDynArray;

	// Разбор команлы по байтам
	int len = (HexStr.Length()+1)/3;	// Количество байт в строке
	BYTE* tmp = new BYTE[len];
	data->set_length(len+CSum);
	for(int i=0; i<len; i++)
	{
		buf = "0x" + HexStr.SubString(idx, 2);
		idx+=3;	//переход на три символа вперед
		tmp[i] = buf.ToInt();
		data->operator [](i) = buf.ToInt();
	}
	// Вычисление контрольной суммы
	int cs = CRC16(tmp,len);
	buf = IntToHex(cs, 4);


	// Добавление контрольной суммы в конец команды. Байты контрольный суммы
	// меняются местами
	idx=(CSum*2)-1;	// индекс начала второго байта контрольной суммы
	for(int i=len; i<len+CSum; i++)
	{
		AnsiString CSbyte = "0x" + buf.SubString(idx, 2);
		idx-=2;	//переход на два символа назад
		data->operator [](i) = CSbyte.ToInt();
	}
	//return data;
}
//==============================================================================
WORD CRC16 (const BYTE *nData, WORD wLength)
{
	static const WORD wCRCTable[] =
	{
		0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
		0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
		0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
		0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
		0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
		0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
		0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
		0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
		0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
		0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
		0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
		0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
		0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
		0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
		0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
		0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
		0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
		0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
		0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
		0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
		0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
		0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
		0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
		0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
		0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
		0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
		0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
		0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
		0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
		0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
		0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
		0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040
	};

	BYTE nTemp;
	WORD wCRCWord = 0xFFFF;

	while (wLength--)
	{
		nTemp = *nData++ ^ wCRCWord;
		wCRCWord >>= 8;
		wCRCWord ^= wCRCTable[nTemp];
	}
	return wCRCWord;
}
//==============================================================================
// Функция рассчитывает обороты двигателя для заданных диаметров катка и колеса
// вагона, а также скорости вагона.
//==============================================================================
double CalculateSpeedMotor(double DiamRoller, double DiamWheel, double TrainSpeed)
{
	// Перевод скорости в мм/мин
	double ts = (TrainSpeed * 1000 * 1000) / 60;
	// Передаточный коэффициент
	//double K = DiamWheel / DiamRoller;
	// Длина окружности катка (circumference)
	const double pi = 3.1415;
	double cf = 2 * pi * (DiamRoller/2);
	// Расстояние пройденное вагоном за один оборот двигателя
	// Растояние равно длине окружности катка
	double dist = cf;// * K;
	// Обороты двигателя для заданной скорости вагона
	double EngineRevs = ts / dist;
	return EngineRevs;
}
//==============================================================================
double CalculateSpeedTrain(double DiamRoller, double DiamWheel, double MotorSpeed)
{
	// Перевод скорости в об/мин
	//double ts = (MotorSpeed * 60) / 1000 * 1000;
	// Передаточный коэффициент
	//double K = DiamWheel / DiamRoller;
	// Длина окружности катка (circumference)
	const double pi = 3.1415;
	double cf = 2 * pi * (DiamRoller/2);
	// Расстояние пройденное вагоном за один оборот двигателя
	double dist = cf;// * K;
	// Скорость вагона для заданной скорости скорости двигателя
	//double TrainRevs = (ts * dist) / (1000*1000);
	double TrainRevs = (dist * MotorSpeed * 60) / (1000*1000);  // км/ч
	return TrainRevs;
}
//==============================================================================
void start(void)
{
	qStr strDriveStart;		//команда
	strDriveStart.qBytes[0]=hardware.hwDrive;
	strDriveStart.qBytes[1]=0x10;
	strDriveStart.qBytes[2]=0x00;
	strDriveStart.qBytes[3]=0x01;
	strDriveStart.qBytes[4]=0x00;
	strDriveStart.qBytes[5]=0x01;
	strDriveStart.qBytes[6]=0x02;
	strDriveStart.qBytes[7]=0x00;		//старший байт направления
	strDriveStart.qBytes[8]=0x01;		//младший байт направления
	crc16(strDriveStart.qBytes,9,&crc1,&crc2);
	strDriveStart.qBytes[9]=crc1;
	strDriveStart.qBytes[10]=crc2;
	strDriveStart.size=11;
	serialQueue1.push(strDriveStart);

}
