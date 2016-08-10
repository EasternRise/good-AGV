#include "all.h"

void ISR_Handle (void);

uint8 Flag_Recv=0;

//�жϷ�������ʼ��
void ISR_Init(void)
{
	pISR_TIMER4		= (uint32)ISR_Handle;
    pISR_UART0      = (uint32)ISR_Handle;
    pISR_UART2		= (uint32)ISR_Handle;
    pISR_IIC		= (uint32)ISR_Handle;
#if CANSetting
	pISR_EINT1		= (uint32)ISR_Handle;
#endif

    rINTMOD			= 0x0;	  			//All=IRQ mode
    
    MASKIrq( BIT_ALLMSK );	  			//All interrupt is masked.
    MASKSubIrq( BIT_SUB_ALLMSK );
    
    rGPFCON &= ~0xc;					//�����ⲿ�ж�1����
    rGPFCON |=   0x8;
    rGPFUP  |=   0x2; 
    
    rEXTINT0 &= ~0x70;					//�ⲿ�ж�1�½��ش���
    rEXTINT0 |= 0x20;

	ClearPending( BIT_ALLMSK );
	ClearSubPending( BIT_SUB_ALLMSK );
	
#if CANSetting
	UNMASKIrq( BIT_EINT1 );				//���ⲿ�ж�1
#endif
}

//�жϷ�����
//��OS_CPU_IRQ_ISR����ֱ�ӵ��򱾺���������ж�ʱֱ�����ƫ��������
void ISR_Handle (void)
{
	rINTOFFSET=0;
	
   	switch(rINTOFFSET)
   	{
#if CANSetting
   		case 1:							//�ⲿ�ж�1��MCP2515�ж�
   			Flag_Recv=1;
   			ClearPending( BIT_EINT1 );
   		break;
#endif
   		case 14:						//��ʱ��4�жϣ�ÿ1msһ��
			OSTimeTick();				//���ķ���ʹ����������̬
			Expection_FLS();			//ȫ����Ϣˢ��
			ClearPending( BIT_TIMER4 ); 
   		break;
   		case 27:
   			Expection_I2C();			//IIC�ж�
   			ClearPending( BIT_IIC ); 
   		break;
   		case 28:
   			Expection_UART0();			//UART0�ж�
   		break;
   		case 15:
   			Expection_UART2();			//UART2�ж�
   			ClearPending( BIT_UART2 ); 
   			ClearSubPending(BIT_SUB_ERR2);
   			ClearSubPending( BIT_SUB_RXD2 );
   		break;
   		default:
   			ClearPending(BIT_ALLMSK);
   		break;
	}
}
