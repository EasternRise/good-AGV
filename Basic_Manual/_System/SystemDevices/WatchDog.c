#include "all.h"

#if WatchDogSetting

//100msϵͳ����Ӧ������
void WatchDog_Init()
{
	rWTCNT=0x500;//������ֵ
	rWTCON=0xff<<8|1<<5|0<<3|0<<2|1;
}

#endif