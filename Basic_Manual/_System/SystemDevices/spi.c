/****************************************Copyright (c)**************************************************
**                                     XJTU Robot Team
**-----------------------------------------File Info----------------------------------------------------
** File name:			spi0.c
** Last modified Date:  2013-3-17
** Descriptions:		
** Created by:			hanlibin
** Last modified By :  	dong	
********************************************************************************************************/

#include "basic.h"

void  SPI1_Init(void)
{
    //STM32Ƭѡ��(GPF6)�ĳ�ʼ��
	rGPFCON |= 0x1<<12;	 				//STM32��Ƭѡ��,��ͨIO����Ƭѡ��
	rGPFDAT |= 1<<6;
	
	
	//FPGAƬѡ��(GPG3)��SPI�ĳ�ʼ��
	rGPGCON |= 0xfc40;					//ʹ��SPI1,GP7Ϊʱ��,GP6ΪMOSI,GP5ΪMISO,GP3Ϊ���
	rGPGCON &=~(0x80);		   			//���ó���ͨ��IO��ģʽ���ڵ��ӻ���ʱ�����ҪƬѡ��
	rGPGDAT |= 0x8;
	rGPGUP  |= 0xE8;
	
	rSPPRE1  =   1;											    //PCLK = 50MHz,Baud rate = PCLK/2/(Prescaler value + 1)
	rSPCON1  =   (0<<5)|(1<<4)|(1<<3)|(0<<2)|(1<<1)|(0<<0);		//polling, En-SCK, master, CPOL=0, CPHA=1, normal
	rSPPIN1  =   (0<<2)|(0<<0);							        //dis-ENMUL,release;
}

/*****************************************************************************************
** �������ƣ� SPI1_SendData����
** ���������� ��FPGA����һ�����ݣ�ͬʱ���FPGA�ϴη���FPGA�Լ����ͼĴ�����ֵ������
** ��	  �룺 ��FPGA���͵�����
** ��     ���� ������������
** ע����� ����û��д��ԭ�Ӳ�������Ϊ��fpga.c�ļ��������ԭ�Ӳ���
*******************************************************************************************/
uint8  SPI1_SendData(uint8 data)
{
	uint8 i;
    rGPGDAT &= ~(0x8);	      		//GPG3��0->ѡ��FPGA
    
    while( (rSPSTA1 & 0x1) == 0 );	//�ж϶ϾݼĴ����Ƿ����
    rSPTDAT1 = data;
    while( (rSPSTA1 & 0x1) == 0 );	//д���ݵ�SPTDATn�Զ�����REDY��־,�˴�Ϊ�ж��Ƿ���
   
    rGPGDAT |= 0x8;				    //GPG3��1->�ͷ�FPGA
    
    i = rSPRDAT1;		//��FPGA���͵�ֵ
    
    return i;
}

/**********************************************************************
** �������ƣ� SPI1_SendData_stm32����
** ���������� 
** ��	  �룺 
** ��     ���� 
** ע����� 
***********************************************************************/  

uint8  SPI1_SendData_stm32(uint8 data)
{
	uint8 i;
	OS_CPU_SR  cpu_sr;
	
	OS_ENTER_CRITICAL();		  //Disable interrupts
    rGPFDAT &= ~(0x1<<6);		  //GPF6��0->Ƭѡstm32
    
    while( (rSPSTA1 & 0x1) == 0 );//�ж϶ϾݼĴ����Ƿ����
    rSPTDAT1 = data;
    while( (rSPSTA1 & 0x1) == 0 );//д���ݵ�SPTDATn�Զ�����REDY��־,�˴�Ϊ�ж��Ƿ���
   
    rGPFDAT |= 0x1<<6;			  //GPF6��1->�ͷ�stm32
    
    i = rSPRDAT1;				  //��stm32���͵�ֵ
    
    OS_EXIT_CRITICAL();			//Restore  interrupts
    return i;
}










