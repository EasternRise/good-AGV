#include "all.h"


//----�������ڲ��������õ��Ӻ��������ļ�����ĺ�����Ҫ����------//															//
																//
void SelectPort( uint8 addr )									//
{																//
	SPI1_SendData(0x20| addr);									//
}																//
																//
void WriteRAM( uint8 RAM_addr,uint8 Data )						//
{																//
	SPI1_SendData( 0x80 | RAM_addr );							//	
	SPI1_SendData( Data );										//
}
																//
uint8 ReadRAM_FIFO( uint8 RAM_addr )							//
{																//
	return(SPI1_SendData( 0x40|RAM_addr ));						//
}
																//
uint8 ReadRAM_STATE( uint8 RAM_addr )							//
{																//
	return(SPI1_SendData( 0x60|RAM_addr ));						//
}																//	
																//
uint8 DisConnect( void )										//
{																//
	return(SPI1_SendData(0xC0));								//
}																//	
//--------------------------------------------------------------//

/*********************************************************************************************************
** ��������	:	EnableFPGA����
** ��������	:   ѡͨFPGA��Ϣ�����
** �䡡�� 	:	FPGA��Ϣ������ID
**				
** �䡡��  :	��
** ע�����        
********************************************************************************************************/
void FGPA_Enable( uint8 ID )
{
	SPI1_SendData( ID );
}

/*********************************************************************************************************
** ��������	:	FPGA_ReadIR(  )
** ��������	:   ��ȡ����ֵ
** �䡡�� 	:	����Ķ˿ڵ�ַ������ռ��FPGA���ϵ�5,6,7�ӿ�
**				
** �䡡��  :	24λ�з�������ʾ�ĺ���ֵ
** ע�����        
********************************************************************************************************/

uint32 FPGA_ReadIR( uint8 id )
{
	OS_CPU_SR  cpu_sr;
	
	union u8to32
	{
		uint32 value;
		uint8 datas[4];
	}IR;
	

	OS_ENTER_CRITICAL();

	switch(id)
	{
		/*
		case 1:
				IR.datas[3]=0;
			
				SelectPort(5);
				ReadRAM_STATE(0);
			
				IR.datas[2]=ReadRAM_STATE(1);
				IR.datas[1]=ReadRAM_STATE(2);
				IR.datas[0]=DisConnect();
				
				
		break;
		*/
		case 2:
				IR.datas[3]=0;
				SelectPort(6);
				ReadRAM_STATE(0);
			
				IR.datas[2]=ReadRAM_STATE(1);
				IR.datas[1]=ReadRAM_STATE(2);
				IR.datas[0]=DisConnect();
		break;
		case 3:
				IR.datas[3]=0;
				SelectPort(7);
				ReadRAM_STATE(0);
			
				IR.datas[2]=ReadRAM_STATE(1);
				IR.datas[1]=ReadRAM_STATE(2);
				IR.datas[0]=DisConnect();
		break;

		default:;
		
		
	}
	OS_EXIT_CRITICAL();
			
	return IR.value;
}


/*********************************************************************************************************
** ��������	:	Read_Codewheel(  )
** ��������	:   ��ȡĳ�����̵ļ���ֵ
** �䡡�� 	:	���̵�ID��FPGA������һ����3�����̽ӿڣ�����ID range 1~3
**				
** �䡡��  :	32λ�з�������ʾ�����̼���ֵ
** ע�����        
********************************************************************************************************/
int32 FPGA_ReadEncoder( uint8 id )
{
	OS_CPU_SR  cpu_sr;
	union u8to32
	{
		int32 value;
		uint8 datas[4];
	}convert;
	
	OS_ENTER_CRITICAL();
	SelectPort(FPGA_ICUEN_ENCODER);
	switch(id)
	{
		case 1:
				ReadRAM_STATE(1);
				convert.datas[0]=ReadRAM_STATE(2);
				convert.datas[1]=ReadRAM_STATE(3);
				convert.datas[2]=ReadRAM_STATE(4);
				convert.datas[3]=DisConnect();
		break;
		case 2:
				ReadRAM_STATE(5);
				convert.datas[0]=ReadRAM_STATE(6);
				convert.datas[1]=ReadRAM_STATE(7);
				convert.datas[2]=ReadRAM_STATE(8);
				convert.datas[3]=DisConnect();
		break;
		case 3:
				ReadRAM_STATE(9);
				convert.datas[0]=ReadRAM_STATE(10);
				convert.datas[1]=ReadRAM_STATE(11);
				convert.datas[2]=ReadRAM_STATE(12);
				convert.datas[3]=DisConnect();
		break;
		case 4:
				ReadRAM_STATE(13);
				convert.datas[0]=ReadRAM_STATE(14);
				convert.datas[1]=ReadRAM_STATE(15);
				convert.datas[2]=ReadRAM_STATE(16);
				convert.datas[3]=DisConnect();
		break;
		case 5:
				ReadRAM_STATE(17);
				convert.datas[0]=ReadRAM_STATE(18);
				convert.datas[1]=ReadRAM_STATE(19);
				convert.datas[2]=ReadRAM_STATE(20);
				convert.datas[3]=DisConnect();
		break;
		case 6:
				ReadRAM_STATE(21);
				convert.datas[0]=ReadRAM_STATE(22);
				convert.datas[1]=ReadRAM_STATE(23);
				convert.datas[2]=ReadRAM_STATE(24);
				convert.datas[3]=DisConnect();
		break;
		case 7:
				ReadRAM_STATE(25);
				convert.datas[0]=ReadRAM_STATE(26);
				convert.datas[1]=ReadRAM_STATE(27);
				convert.datas[2]=ReadRAM_STATE(28);
				convert.datas[3]=DisConnect();
		break;
		default:;
		
		
	}
	OS_EXIT_CRITICAL();			
	return convert.value;
}


/*********************************************************************************************************
** ��������	:	Read_Gyro(  )
** ��������	:   ��ȡ�����ǵĽ�λ��ֵ
** �䡡�� 	:	�����ǵĶ˿ڵ�ַ��������ռ��FPGA���ϵ�UART1�ӿڣ����߶˿ڵ�ַ��ͬ����spi0_FPGA.h���Ѿ�����
**				
** �䡡��  :	32λ�з�������ʾ�������ǵĽ�λ��ֵ
** ע�����        
********************************************************************************************************/
struct Gyro_Struct FPGA_ReadGyro( void)
{
	OS_CPU_SR  cpu_sr;
	union u8to32
	{
		int32 value;
		uint8 datas[4];
	}gyro1;
	
	struct Gyro_Struct  gyro2;
	
	OS_ENTER_CRITICAL();
	SelectPort(FPGA_ICUEN_GYRO);
	ReadRAM_STATE(1);
	gyro1.datas[0]=ReadRAM_STATE(2);
	gyro1.datas[1]=ReadRAM_STATE(3);
	gyro1.datas[2]=ReadRAM_STATE(4);
	gyro1.datas[3]=ReadRAM_STATE(6);
	gyro2.count=DisConnect();
	OS_EXIT_CRITICAL();
	gyro2.value = gyro1.value;
	
	return gyro2;
}

/*********************************************************************************************************
** ��������	:	Set_PWM(  )
** ��������	:	����ĳ·PWM���Ŀ���/�رգ�Ƶ�ʣ�ռ�ձ�
** �䡡�� 	:	1.PWM��ID��;
				2.PWM����/�رձ�־;
				3.PWMƵ��;
				4.PWMռ�ձ�
**				
** �䡡��  :	��
** ע������: note1:ID range from 1 to 6
			 note2:	enable=1 ���� ����PWM���, enable=0 ���� �ر�PWM���
			 note3:freq range from 10Hz to 500kHz 
**			 note4:duty1K range from 0 to 1000��1000 stand for 100%
********************************************************************************************************/
void FPGA_SetPWM( uint8 id,uint8 enable,uint32 freq,uint16 duty1K )
{  
    OS_CPU_SR  cpu_sr;
	union u8tou16
	{
		uint16 value;
		uint8 datas[2];
	}/*num1,*/num2;
	
	//uint8 	pre_div;
	uint16 	cycle_num;
	uint16 	width_num;
/*	
	if( freq<2000 )
	{
		pre_div=2000/freq;				 	// pre_div= (int) 50M/(25K*freq)
		cycle_num=FPGA_CLK/(pre_div*freq);	// cycle_numȡֵ��25K���������������Ϊ50K����ȻС��65535
	}
	else
	{
		pre_div=1;
		cycle_num=FPGA_CLK/freq;
	}
*/	
	cycle_num = 20000;
	width_num=cycle_num*duty1K/1000;
	
	
	//num1.value=cycle_num;
	num2.value=width_num;
	OS_ENTER_CRITICAL();
	SelectPort(FPGA_ICUEN_PWM);
	WriteRAM( 0,id-1);
	WriteRAM( 1,enable);
	//WriteRAM( 2,pre_div);
	//WriteRAM( 3,num1.datas[0] ); //����cycle_num��8λ
	//WriteRAM( 4,num1.datas[1] ); //����cycle_num��8λ
	WriteRAM( 2,num2.datas[0] ); //����width_num��8λ
	WriteRAM( 3,num2.datas[1] ); //����width_num��8λ
	DisConnect();	
	OS_EXIT_CRITICAL();
}


void FPGA_SetPWM1( uint8 id,uint8 enable,uint32 freq,uint16 duty0x6000 )
{   
    OS_CPU_SR  cpu_sr;
	union u8tou16
	{
		uint16 value;
		uint8 datas[2];
	}num1,num2;
	
	uint8 	pre_div;
	uint16 	cycle_num;
	uint16 	width_num;
	
	if( freq<2000 )
	{
		pre_div=2000/freq;				 	// pre_div= (int) 50M/(25K*freq)
		cycle_num=FPGA_CLK/(pre_div*freq);	// cycle_numȡֵ��25K���������������Ϊ50K����ȻС��65535
	}
	else
	{
		pre_div=1;
		cycle_num=FPGA_CLK/freq;
	}
	
	width_num=cycle_num*duty0x6000/0x6000;
	
	
	num1.value=cycle_num;
	num2.value=width_num;
	OS_ENTER_CRITICAL();
	SelectPort(FPGA_ICUEN_PWM);
	WriteRAM( 0,id-1);
	WriteRAM( 1,enable);
	//WriteRAM( 2,pre_div);
	//WriteRAM( 3,num1.datas[0] ); //����cycle_num��8λ
	//WriteRAM( 4,num1.datas[1] ); //����cycle_num��8λ
	WriteRAM( 2,num2.datas[0] ); //����width_num��8λ
	WriteRAM( 3,num2.datas[1] ); //����width_num��8λ
	DisConnect();	
	OS_EXIT_CRITICAL();
}

void FPGA_PWM_INIT(void)
{
	OS_CPU_SR  cpu_sr;
   	//int i;
   	OS_ENTER_CRITICAL();
   	//for(i=1;i<=6;i++)
   	//{
     	FPGA_SetPWM(1,1,50,100);

     	FPGA_SetPWM(2,1,50,42);
   	//}
   	OS_EXIT_CRITICAL();
}

/*********************************************************************************************************
** ��������	:	Set_FPGA_UART_BaudRate()
** ��������	:   ����FPGA����ĳ��UART�ӿڵĲ�����
** �䡡�� 	:	1.UART�ӿڶ�Ӧ�Ķ˿ڵ�ַ(spi0_FPGA.h���ж���);
				2.Ҫ���õĲ�����
**				
** �䡡��  :	��
** ע�����  ������ range 300~115200      
********************************************************************************************************/
void FPGA_UARTSetBaudRate( uint8 port_addr,uint32 baudrate )
{   
    OS_CPU_SR  cpu_sr;
	union u16tou8
	{
		uint16 value;
		uint8 datas[2];
	}num;

	num.value= (uint16)(6250000/baudrate);	 
	OS_ENTER_CRITICAL();
	SelectPort(port_addr);
	WriteRAM( 0,0x01);
	WriteRAM( 1,num.datas[0]);
	WriteRAM( 2,num.datas[1]);
	DisConnect();
	OS_EXIT_CRITICAL();
}

/*********************************************************************************************************
** ��������	:	FPGA_UART_txd( )
** ��������	:	ͨ��FPGA���ϵ�ĳ��UART���ͳ�һ���ֽ�
** �䡡�� 	:	1.UART�ӿڵĶ�Ӧ�Ķ˿ڵ�ַ��spi0_FPGA.h���ж��壩;
				2.Ҫ���͵��ֽ�����
**				
** �䡡��  :	��
** ע�����        
********************************************************************************************************/
void FPGA_UartSendByte(uint8 port_addr, uint8 data )
{	
    OS_CPU_SR  cpu_sr;
    OS_ENTER_CRITICAL();
	SelectPort(port_addr);
	WriteRAM( 0,0x00);
	WriteRAM( 1,data);
	DisConnect();
	OS_EXIT_CRITICAL();
}


/*********************************************************************************************************
** ��������	:	FPGA_UART_rxd()
** ��������	:   ����ĳ��UART�ӿ��յ������ݻ������
** �䡡�� 	:	1.UART�ӿڵĶ�Ӧ�Ķ˿ڵ�ַ(spi0_FPGA.h���ж���);
				2.�����ݵ�17*byte����
**				
** �䡡��  :	��
** ע�����   �ú����޸�������data�����ݣd
				data[0]��ʾ������е���Ч���ȣ�0~16Ϊ����ֵ��������100 ˵�����������(��֡)
				data[1]~data[16] :16���ֽڵ����ݻ�����У�����data[1]Ϊ����յ������ݣ�������������     
********************************************************************************************************/
void FPGA_UartRead(uint8 port_addr,uint8 * data)
{   
    OS_CPU_SR  cpu_sr;
	int i;
	OS_ENTER_CRITICAL();
	SelectPort(port_addr);
	ReadRAM_FIFO(0);
	for(i=0;i<16;i++)
	{
		data[i]=ReadRAM_FIFO(i+1);
	}
	data[16]=DisConnect();
	OS_EXIT_CRITICAL();
}

#if LightBoardSetting
  /*********************************************************************************************************
** ��������	:	FPGA_UART_rxd_LB()
** ��������	:   ����ĳ��UART�ӿ��յ��ĵư�����
** �䡡�� 	:	1.UART�ӿڵĶ�Ӧ�Ķ˿ڵ�ַ(spi0_FPGA.h���ж���);
				2.�����ݵ�4*byte����
**				
** �䡡��  :	��
** ע�����   �ú����޸�������data�����ݣd
				�ư干32���ƣ�ÿ8���Ƶ�״̬�����һ��data��    
********************************************************************************************************/
void FPGA_UartReadLB(uint8 port_addr,uint8 * data)
{   
    OS_CPU_SR  cpu_sr;
    OS_ENTER_CRITICAL();
	SelectPort(port_addr);
	ReadRAM_STATE(0);
	data[0]=ReadRAM_STATE(1);
	data[1]=ReadRAM_STATE(2);
	data[2]=ReadRAM_STATE(3);
	data[3]=DisConnect();
	OS_EXIT_CRITICAL();
}

#endif

#if ManualSetting
  /*********************************************************************************************************
** ��������	:	Read_Manual
** ��������	:   ����FPGA�ӿ��յ����ֱ�����
** �䡡�� 	:	�����ݵ�16*byte����
**				
** �䡡��  :	��
** ע�����  
********************************************************************************************************/
void FPGA_ReadManual(uint8 * data)
{   
   OS_CPU_SR  cpu_sr;
	uint8 i;
	OS_ENTER_CRITICAL();
	SelectPort(5);
	ReadRAM_STATE(0);
	for(i=1;i<10;i++)
	{
		data[i]=ReadRAM_STATE(i);
	}
	data[10]=DisConnect();
	/*
	data[0]=0;
	for(i=11;i<16;i++)
		data[i]=0;
	*/	
	OS_EXIT_CRITICAL();
}

#endif

/*********************************************************************************************************
** ��������	:	FPGA_ReadUltrasonic
** ��������	:   ����FPGA�ӿ��յ��ĳ�����������
** �䡡�� 	:	�������õ���UART��
**				
** �䡡��  :	���ص�16λ�ĳ��������ľ���ֵ
** ע�����  ���Ҫ��FPGA��UART�ڣ�Ҫ�޸ĺ�������SelectPort();��ֵ
**				FIFO(1)  ��  FIFO(2) ��ֵ�ֱ��ǵ�8λ�͸�8λ
********************************************************************************************************/
//#define 	ULTRASONIC_1   	8
//#define	ULTRASONIC_2	9

uint16 FPGA_ReadUltrasonic(uint8 port)
{
	OS_CPU_SR  cpu_sr;
	union u8to16
	{
		int16 value;
		uint8 datas[2];
	}Supersonic;
	OS_ENTER_CRITICAL();
	SelectPort(port);
	ReadRAM_FIFO(0);
	ReadRAM_FIFO(1);	
	Supersonic.datas[0] = ReadRAM_FIFO(2);
	Supersonic.datas[1] = ReadRAM_FIFO(3);
	OS_EXIT_CRITICAL();
	return Supersonic.value;
}
