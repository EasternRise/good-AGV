/****************************************Copyright (c)**************************************************
**                                     XJTU Robot Team
**-----------------------------------------File Info----------------------------------------------------
** File name:			iic.c
** Last modified Date:  20010-1-2
** Descriptions:		
** Created by:			�ԭ|��	
********************************************************************************************************/
#include "basic.h"
/***************************************************************
*�������ƣ�I2CInit(void)
*������	��ʼ��I2c�ӿڣ�������7th\8th\9th����
		�ĳ�ʼ������ͬʱ������IIC�жϷ���
*****************************************************************/
void I2CInit( void )
{
    rGPECON 	&= ~0xf0000000;
    rGPECON 	|=  0xa0000000;              //GPE15:IICSDA , GPE14:IICSCL ����IIC�Ķ˿�
    rGPEUP  	|=  0xc000;                  //Pull-up disable    ����������
    
    rIICADD		= 0x10;                    	//2440 slave address = [7:1] �ӻ���ַ
	rIICCON		= 0xe0 | IICDEV;
	rIICSTAT	= 0x10;    
	                                     	//IIC bus data output enable(Rx/Tx)   ���ܺͷ��͵�ʹ��
	UNMASKIrq( BIT_IIC );					//��I2C�ж�
}

/***************************************************************
*�������ƣ�I2CInit(void)
*������	��ʼ��I2c�ӿڣ�������11th����
		�ĳ�ʼ������ͬʱ������IIC�жϷ���
*****************************************************************/
void Expection_I2C(void)
{
	static uint8 KEYBOARD_Value[1];
	static int IIC_Stat=0;
	switch(IIC_Stat)
	{
		case 0:
			rIICCON       = 0xe0 | IICDEV; 		//resume IIC
			IIC_Stat=1;
		break;
		case 1:
			KEYBOARD_Value[0]   = rIICDS;		//������ֵ
			rIICCON       = 0xe0 | IICDEV; 		//resume IIC 
			IIC_Stat=2;
		break;
		case 2:
			rIICSTAT	  = 0x50;
			rIICDS		  = KEYBOARD_Value[0];	//���ؼ���ֵ
			rIICCON       = 0xe0 | IICDEV; 		//resume IIC 
			IIC_Stat=3;
		break;
		case 3:
			rIICSTAT	  = 0x10;
			rIICCON       = 0xe0 | IICDEV; 		//resume IIC 
			IIC_Stat=0;
			OSMboxPost(I2cMbox,KEYBOARD_Value);	//����TaskI2cKeys()
		break;
	}
	ClearPending( BIT_IIC ); 
}
/*********************************************************************************************************
**                            End Of File
*********************************************************************************************************/