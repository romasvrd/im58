//==============================================================================
#ifndef im58drive
#define im58drive
//==============================================================================
#endif
//==============================================================================
enum  ROTATE
{
	FORWARD=1,
	REVERSE=2
};
//==============================================================================
void start(void);
void StartMotor(int iAddress, ROTATE Rotate , int iSpeed);
void StopMotor(int iAddress);
void SetSpeedMotor(int iAddress, int iSpeed);
void GetSpeedMotor(int iAddress);
void GetSpeedAndPowerMotor(int iAddress);
void GetPowerMotor(int iAddress);
void StringToByteArray(AnsiString HexStr);
WORD CRC16 (const BYTE *nData, WORD wLength);
double CalculateSpeedMotor(double DiamRoller, double DiamWheel, double TrainSpeed);
double CalculateSpeedTrain(double DiamRoller, double DiamWheel, double MotorSpeed);
//==============================================================================



