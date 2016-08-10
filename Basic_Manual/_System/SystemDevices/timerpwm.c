/****************************************Copyright (c)**************************************************
**                                     XJTU Robot Team
**-----------------------------------------File Info----------------------------------------------------
** File name:			pwm.c
** Last modified Date:  2009-11-27
** Descriptions:		
** Created by:			xingxing		
********************************************************************************************************/
#include "basic.h"

int32 time_flag=0;
/********************************************************************************************************
** �������ƣ�PWMInit
** �������ܣ�PWM��ʼ�� ����0��1��2��3��·PWM���ĳ�ʼ��
** ��ڲ�����
** ���ڲ�����
*********************************************************************************************************/
void  TimerPWMInit(void)
{
	//��Ƶ����
	rTCFG0	=  (DEADZONE<<16)|(PRESCALER1<<8)|(PRESCALER0<<0);
	rTCFG1	=  (DMAMODE<<20)|(MUX4<<16)|(MUX3<<12)|(MUX2<<8)|(MUX1<<4)|(MUX0<<0);
	
	//�˿�����ΪTOUT��
	rGPBCON &= (~(0xff));			
	rGPBCON |=  0xaa ;
    rGPBUP  &= (~(0xff));
    
    //0-3Ϊpwm������ڣ�4Ϊ��ʱ��
    //pwm����Ƶ����2000Hz
	rTCNTB0	=  CNTB0;
	rTCMPB0	=  CMPB0;
	
	rTCNTB1	=  CNTB1;
	rTCMPB1	=  CMPB1;
	
	rTCNTB2	=  CNTB2;
	rTCMPB2	=  CMPB2;
	
	rTCNTB3	=  CNTB3;
	rTCMPB3	=  CMPB3;
	
	rTCNTB4	=  CNTB4;

	rTCON	&= (~(0x7fff0f));//ˢ��rTCON
	rTCON	|=    0x6aaa0a  ;//�ط������������Զ���װ�룬������ؼĴ���ֵ
	rTCON	&= (~(0x222202));//����ֶ����±�־λ
	rTCON	|=    0x111101  ;//��ʱ����ʼ����
	
	UNMASKIrq( BIT_TIMER4 );	
}
/********************************************************************************************************
** �������ƣ�SetPWM()
** �������ܣ�����·PWM��0��1��2��3  
** ��ڲ�����
** ���ڲ�����
*********************************************************************************************************/
uint8 SetPWM(uint8 Num, fp64 Ratio)
{
	if( Num<=3 )
	{
		switch(Num)
		{
			case 0:
			    rTCMPB0 =(uint16) (CNTB0*Ratio);
			    break;
			case 1:
				rTCMPB1 =(uint16)(CNTB1*Ratio);
				break;
			case 2:
				rTCMPB2 =(uint16)(CNTB2*Ratio);
				break;
			case 3:
				rTCMPB3 =(uint16)(CNTB3*Ratio);
				break;
		}
		return 1;
	}
	else
    {return 0;}
}
