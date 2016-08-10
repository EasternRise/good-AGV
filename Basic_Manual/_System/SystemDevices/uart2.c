#include "All.h"

void UART2_Init(int baud)
{
	int i;    

	
	rGPHCON &= (~(0xf000));
	rGPHCON |= (0xa000);
    rGPHUP  &= (~(0xc0));    						// The pull up function is enable

    rULCON2 = 0x3;									//����żУ�飬1λֹͣλ��8bit����
    rUCON2  = 0x385;   								//�շ���Ϊ�жϻ��ѯģʽ���ǻ�дģʽ�������ɳ����жϣ����ܳ�ʱ�жϣ����ͽ����ж�Ϊ��ƽ��ѡ��PCLK
    rUFCON2 = 0x11;   								//FIFOʹ�ܣ��Զ����㣬����8Byte����
    rUMCON2 = 0x00;   								//AFC disable 
    rUBRDIV2=( (int)(Sys_Pclk/16./baud+0.5) -1 );   //Baud rate divisior register
  
    UNMASKIrq(BIT_UART2);   
    for(i=0;i<100;i++);
    UNMASKSubIrq(BIT_SUB_RXD2);
    ClearSubPending(BIT_SUB_RXD2);
}

void UART2_SendByte (uint8 data)	//����һ���ַ�
{
	while(!(rUTRSTAT2 & 0x2));
	WrUTXH2(data);
}

void UART2_SendString(char *data)	//����һ���ַ���
{
	while(*data)
	{
		UART2_SendByte(*data++);
	}
}

void Expection_UART2(void)
{
	//int length,i=0,j;
	if((rSUBSRCPND&BIT_SUB_TXD2)!=0)
	{
		MASKSubIrq(BIT_SUB_TXD2);
	}

	if((rSUBSRCPND&BIT_SUB_RXD2)!=0)			//�����ж�
	{

		LidarBuffer[LidarBufferTop]=RdURXH2();			
		LidarBufferTop++;
		
		ClearSubPending( BIT_SUB_RXD2 );
		ClearPending( BIT_UART2 );     
	}
}

uint8 UART2_PopByte()
{
	return 0;
}

int UART2_RxReady()
{
	return 0;
}

