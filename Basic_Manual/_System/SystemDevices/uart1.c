#include "all.h"
/*********************************************
**���ܣ�UART 
**��;��
**�÷�����UART������ģʽ��FIFO�ͷ�FIFO
**
**********************************************/

#define  UART1_FIFO_MOD  1

//���������ѡ��ģʽ��ʱ���õģ�����д��Ϊ�����޸Ļ�任ģʽ��ʱ�򷽱�һЩ���ѣ�
//������Ҳ����ֱ�Ӹ��Ĵ�����ֵ
//====================================================================================================
#define  UART1_FIFO_ENABLE  1																		 //
#define  UART1_FIFO_DISABLE  0																		 //

																									 //																									 //
#define  UART1_FIFO(data)     rUFCON1 &= ~(0xff);  rUFCON1 |= data									 //
																									 //
#define	 UART1_CONTROL(data)  rUCON1  &= ~(0xf)	;  rUCON1  |= data									 //
//=====================================================================================================																									 //
uint8 UART1_RxBuffer[256]={0};
uint8 UART1_RxBufferTop=0;
uint8 UART1_RxBufferEnd=0;

uint8 UART1_TxBuffer[256]={0};
uint8 UART1_TxBufferTop=0;
uint8 UART1_TxBufferEnd=0;

void UART1_Init(int baud)
{
	int i;    
			
	rGPHCON &= (~(0xf00));
	rGPHCON |= (0xa00);
    rGPHUP  &= (~(0x30));    						// The pull up function is enable
    
    rULCON1 = 0x3;									//�������ݴ���ģʽ������żУ�飬1λֹͣλ��8bit����
    rUBRDIV1=( (int)(Sys_Pclk/16./baud+0.5) -1 );   //Baud rate divisior register
	rUMCON1 = 0x00;   								//AFC disable 
	rUCON1  |= 0x000<<4  | 1<<7  |  0<<8  |  1<<9  ; //���û�����ģʽ��RX����״̬ʹ�ܣ���ʱʹ�ܣ�RXΪ���崥����TX��ƽ������PCLK

	/*
	**���ϼ��в���Ҫ�Ķ����ɸ�����Ҫ����������
	*/
	
    UART1_FIFO	 ( UART1_FIFO_ENABLE | TX_FIFO_TR_LEVEL_16  | RX_FIFO_TR_LEVEL_32 );//FIFOʹ�ܣ������ý��պͷ��ʹ������(�ֽ�)   								
    UART1_CONTROL( TX_INT_AND_POOL_MOD  |  RX_INT_AND_POOL_MOD);//���ͺͽ��ն�Ϊ�жϻ��ѯģʽ
       

    UART1_RxBufferTop=0;
	UART1_RxBufferEnd=0;

    UNMASKIrq(BIT_UART1);
    for(i=0;i<100;i++);					
    UNMASKSubIrq(BIT_SUB_RXD1);			//ע�⣺���￪��ֻ�ǽ����жϵı�־λ
    ClearSubPending( BIT_SUB_RXD1 );	//      �����жϵı�־λ������ſ�
}


/*******************************************************
**	����FIFOģʽ���FIFOģʽ��ѡ���Ӧ�ķ��ͳ���
**	��Ϊ�����жϵ�������ͬ
********************************************************/

#if  UART1_FIFO_MOD   
	void UART1_SendByte (uint8 data)	//����һ���ַ�				  /*   ------ UART���䷽��  1    ---------*/
	{	
		do
		{
			if(((rUFSTAT1 & 0x3F<<8)>>8)< 16)//FIFO�ķ��ʹ��������16�ֽ�
			{
				WrUTXH1(data);
				break;
			}
		}while(!(rUFSTAT1 & (uint16)1<<14));//�ж�FIFO�Ƿ�����
	}

#else
	//��FIFO ģʽ													  /*   ------ UART���䷽��  2    ---------*/
	void UART1_SendByte (uint8 data)	//����һ���ַ�
	{
		while(!(rUTRSTAT1 & 0x2));
		WrUTXH1(data);
	}
#endif	


void UART1_SendString(char *data)	//����һ���ַ���
{
	while(*data)
	{
		UART1_SendByte(*data++);
	}
}


void Expection_UART1(void)			//UART0 FIFO�ж�
{	
	if((rSUBSRCPND&8)!=0)
	{
		if(WIRELESS_buffer_End!=WIRELESS_buffer_Top)
		{
			WrUTXH1(WIRELESS_buffer[(WIRELESS_buffer_End++)%256]);
		}
		
		else
		{
			MASKSubIrq(BIT_SUB_TXD1);
		}
   		 	
   		ClearSubPending( BIT_SUB_TXD1 );
		ClearPending( BIT_UART1 );
	}

	if((rSUBSRCPND&4)!=0)			//�����ж�
	{
		
		int length1=rUFSTAT1&0x3f;	//�жϽ��յ������ݳ���
		int i;
		for(i=0;i<length1;i++)
		{
			UART1_RxBuffer[(UART1_RxBufferTop++)%256]=RdURXH1();//�������飬���ݴ������ȡ
		}
		ClearSubPending( BIT_SUB_RXD1 );
		ClearPending   ( BIT_UART1 );     
	}
}

