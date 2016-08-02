//---------------------------------------------------------------------------

#ifndef im58recorderH
#define im58recorderH
//---------------------------------------------------------------------------
#endif

void getNumFirstVol (void);
void getNumLastVol(void);
void getLastVol (void);
void getFirstPage (void);
void getLastPage(void);
void getAddrOnPage(int page, int addr);
void getFirstPageOnVol(int vol);
void getLastPageOnVol(int vol);
bool readData(int num);
void recExeCmd(int vol);
void tacho_preset(int brakespeed);
void getPreLast(int vol);
void getLast(int vol);
void findZeroLevel(int num);
void regReadValue(void);


