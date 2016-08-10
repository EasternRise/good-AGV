#ifndef BASIC_H
#define BASIC_H

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "def.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h"
#include "clock.h"
#include "ucos_ii.h"
#include "app_cfg.h"
#include "setting.h"


//mmu.c
#define DESC_SEC	(0x2|(1<<4))
#define CB		(3<<2)  //cache_on, write_back
#define CNB		(2<<2)  //cache_on, write_through 
#define NCB             (1<<2)  //cache_off,WR_BUF on
#define NCNB		(0<<2)  //cache_off,WR_BUF off
#define AP_RW		(3<<10) //supervisor=RW, user=RW
#define AP_RO		(2<<10) //supervisor=RW, user=RO

#define DOMAIN_FAULT	(0x0)
#define DOMAIN_CHK	(0x1) 
#define DOMAIN_NOTCHK	(0x3) 
#define DOMAIN0		(0x0<<5)
#define DOMAIN1		(0x1<<5)

#define DOMAIN0_ATTR	(DOMAIN_CHK<<0) 
#define DOMAIN1_ATTR	(DOMAIN_FAULT<<2) 

#define RW_CB		(AP_RW|DOMAIN0|CB|DESC_SEC)
#define RW_CNB		(AP_RW|DOMAIN0|CNB|DESC_SEC)
#define RW_NCNB		(AP_RW|DOMAIN0|NCNB|DESC_SEC)
#define RW_FAULT	(AP_RW|DOMAIN1|NCNB|DESC_SEC)

void MMU_Init(void);
void MMU_SetMTT(int vaddrStart,int vaddrEnd,int paddrStart,int attr);
void ChangeRomCacheStatus(int attr);

//iic.c

#define IICDEV		0x0

extern void I2CInit( void );

extern void Expection_I2C(void);

extern void TaskI2cKeys(void *pdata);






//spi1.c

extern void  	SPI1_Init(void);
extern uint8 	SPI1_SendData(uint8 data);
extern uint8  	SPI1_SendData_stm32(uint8 data);



//CAN.c

struct Data2STM32
{
	uint8 	Data_ID;
	uint8*	Data_Ptr;
	uint8	Data_Length;
	uint8	Data_Type;
};


extern struct Data2STM32 STM32_Data[];


#define		STM32_DATA_BUF_LEN  28     //����Ƕ�����Ǹ�����ĳ��ȣ���ID�ŵĸ�����ͬ


#define   	READ_ONLY			0
#define		WRITE_ONLY			1
#define		READ_WRITE			2


extern void 	STM32_RW(uint8 id);
extern uint8  	STM32_Send_Buf[][9]; 
extern uint8  	STM32_Rece_Buf[][9];


#define     STM32_NOP           0xff

//��STM32_ReadDistance()�л��õ�����Ķ���
#define    	ID_RELAY64			0
#define     ID_RELAY8           1
#define     ID_LASER_CTR        2   //���Ƽ�����Ŀ�ʼ�����  CTR��control�ļ�д
#define     ID_LASER_DATA       3   //���ؼ�����ľ���ֵ
#define     ID_ISO_MASK         4   //ʹ�ܹ����
#define		ID_IR_CTR			5   //����������ֽ�
#define     ID_IR1_DATA			6   //����1������
#define		ID_IR2_DATA			7   //����2������
#define		ID_SUP_SONIC_CTR	8   //�������������ֽ�
#define     ID_SUP_SONIC1_DATA	9   //������1������
#define     ID_SUP_SONIC2_DATA	10  //������2������
#define     ID_SUP_SONIC3_DATA	11  //������3������
#define		ID_SUP_SONIC4_DATA	12  //������4������
#define     ID_ISO_DELAY1		13
#define     ID_ISO_DELAY2		14
#define     ID_ISO_DELAY3		15
#define		ID_LIDAR_CTR		16  //�״�Ŀ��ƺ�����ID
#define		ID_LIDAR			17  
#define		ID_MOTOR1			18	//���1	
#define		ID_MOTOR2			19	//���2
#define		ID_MOTOR3			20	//���3
#define		ID_MOTOR4			21
#define		ID_MOTOR5			22	//���5  ������ĵ����ͬ
#define		ID_MOTOR6           23	
#define		ID_MaxonConWord		24
#define		ID_MaxonModeSelect	25
#define		ID_Maxon1Speed      26
#define		ID_Maxon2Speed      27

//��Щ�ǿ��Ƽ����������������룬��ÿ������Ӧһ��λ
#define  	CONTROL_LASER		(uint16)0x01
#define 	CONTROL_IR1			(uint16)0x02
#define		CONTROL_IR2			(uint16)0x04
#define		CONTROL_SONIC1		(uint16)0x08
#define		CONTROL_SONIC2		(uint16)0x10
#define		CONTROL_SONIC3		(uint16)0x20
#define		CONTROL_SONIC4		(uint16)0x40
#define		CONTROL_LIDAR		(uint16)0x80
#define		CONTROL_XXXXX3		(uint16)0x100


#define 	DEVICE_NUM			7   	//�豸�ĸ���


#define  	RELAY_LOW(port)   	((uint32)0x1)<<(port-1)  //�ú궨������ѡ��̵����ڶ�Ӧ�ĵ�32λ����Relay()�������һ����
#define     RELAY_HIGH(port)    ((uint32)0x1)<<(port-33) //�ú궨������ѡ��̵����ڶ�Ӧ�ĸ�32λ����Relay()�������һ����


#define     ISO(port)      ((uint8)0x01)<<(port-1)      //�ú궨����ISO_UNMASK() �� ISO_MASK() һ����

//�йص����CMD
#define 	STOP  0
#define 	zheng 1
#define 	fan   2

extern 	void 	STM32_Reset(void);  
extern 	void  	Relay(uint32 set_low ,uint32 set_high,uint32 clear_low,  uint32  clear_high);
extern 	void 	Relay_Clear(uint8 port);
extern 	void 	Relay_Set(uint8 port) ;   
extern 	uint8 	Relay_Read(uint8 port);
extern 	void 	ISO_UNMASK(uint8 port);
extern 	void 	ISO_MASK(uint8 port);
extern 	uint8 	ISO_Read(uint8 port);
extern 	void 	Ranging_Start(uint16 id);
extern 	void  	Ranging_Stop(uint16 id);
extern 	uint16 	STM32_ReadDistance(uint8 id);
extern  uint8   Read_Device_Statu(uint16  id);
extern  uint16  STM32_ReadLidarData(int ring_id);
extern  void    Motor_CAN(uint8 id , uint8 cmd);
extern  void    Motor_Position(uint8 circ , uint16 radian);
extern  void    arm_motor(uint8 motor, float rot);


extern 		uint32 Relay_Value[2];  //��¼�̵�����״̬
extern		uint16  ISO_Mask_Statu; //��¼������ĸ��ڱ�����
extern      uint16 ISO_Delay_Time[3];

//Maxon���

#define     MAXONENALBE         0x000F
#define     MAXONDISABLE        0x0006
#define     MAXONQUICKSTOP      0x000E
#define     MAXONSPEEDMODE      0xFE

extern void MaxonEnable(void);
extern void MaxonDisable(void);
extern void MaxonQuickstop(void);
extern void MaxonSpeedMode(void);
extern void MaxonFaultReset(void);
extern void Maxon1SetSpeed(double speed);
extern void Maxon2SetSpeed(double speed);

//timer.c
extern int32 time_flag;

#define DEADZONE	0   //�������ȵ�����
#define DMAMODE		0   //DMAģʽѡ��
//�����ʱ��Ԥ��Ƶ����
#define PRESCALER0	0   //���ڶ�ʱ��0,1            
#define PRESCALER1	0   //���ڶ�ʱ��2,3,4
//�����ʱ����Ƶ����
#define MUX0		0x0				// 1/2
#define MUX1		0x0				// 1/2
#define MUX2		0x0				// 1/2
#define MUX3		0x0				// 1/2
#define MUX4		0x3				// 1/16

#define CNTB0		12500  //0.5ms
#define CNTB1		12500
#define CNTB2		12500
#define CNTB3		12500
#define CNTB4		3125  //1ms

#define CMPB0		6238
#define CMPB1		6238
#define CMPB2		6238
#define CMPB3		6238
#define CMPB4		0

//isr.c

#define	UNMASKIrq(bit)		rINTMSK &= ~(bit)
#define	MASKIrq(bit)		rINTMSK |= (bit)
#define	UNMASKSubIrq(bit)	rINTSUBMSK &= ~(bit)
#define	MASKSubIrq(bit)		rINTSUBMSK |= (bit)
#define ClearPending(bit)	{rSRCPND = bit;rINTPND = bit;}
#define ClearSubPending(bit)rSUBSRCPND = bit

extern void ISR_Init(void);

extern uint8 Flag_Recv;


//gpio.c


extern void IO_Init(void);

extern uint8 SA_Read(uint8 port);

extern uint8 ST_Read(uint8 port);

extern void LED_Set(U8  LED_num);

extern void LED_Clear(U8  LED_num);






//uart0.c

extern void UART0_Init(int baud);
extern void UART0_SendByte (uint8 data);
extern void UART0_SendString(char *data);
extern void Expection_UART0( void );

extern uint8 UART0_RxBuffer[256];
extern uint8 UART0_RxBufferTop;
extern uint8 UART0_RxBufferEnd;

extern uint8 UART0_TxBuffer[256];
extern uint8 UART0_TxBufferTop;
extern uint8 UART0_TxBufferEnd;

extern uint8 WIRELESS_buffer[256];
extern uint8 WIRELESS_buffer_Top;
extern uint8 WIRELESS_buffer_End;
//uart1.c
//���������ѡ��ģʽ��ʱ���õģ�����д��Ϊ�����޸Ļ�任ģʽ��ʱ�򷽱�һЩ���ѣ�
//������Ҳ����ֱ�Ӹ��Ĵ�����ֵ
//====================================================================================================
																	 //
 
 																									 //
#define  TX_FIFO_TR_LEVEL_0    0<<6      	//uart0 tx fifo trigger level  ����FIFO�Ĵ������	   	 //
#define  TX_FIFO_TR_LEVEL_16   1<<6																	 //
#define  TX_FIFO_TR_LEVEL_32   2<<6																	 //
#define  TX_FIFO_TR_LEVEL_48   3<<6																	 //
																									 //																									 //
#define  RX_FIFO_TR_LEVEL_1	   0<<4		//uart0 �Ľ���FIFO�������								 //
#define  RX_FIFO_TR_LEVEL_8	   1<<4																	 //
#define  RX_FIFO_TR_LEVEL_16   2<<4																	 //
#define  RX_FIFO_TR_LEVEL_32   3<<4																	 //
																									 //																									 //
								 //

/*...................................................................................................*/																									 //
																									 //
#define  TX_DISABLE            0<<2		 //��ֹ����													 //
#define	 TX_INT_AND_POOL_MOD   1<<2		 //�жϻ��ѯģʽ										     //
#define	 TX_DMA_UART_0_2	   2<<2		 //uart0��uart2��DMA����ģʽ								 //
#define	 TX_DMA_UART_1		   3<<2		 //UART1 �� DMA ����ģʽ									 //
																									 //
#define  RX_DISABLE            0		 //��ֹ����													 //
#define	 RX_INT_AND_POOL_MOD   1		 //�жϻ��ѯģʽ										     //
#define	 RX_DMA_UART_0_2	   2		 //uart0��uart2��DMA����ģʽ							     //
#define	 RX_DMA_UART_1		   3		 //UART1 �� DMA ����ģʽ									 //
																									 //
#define	 UART0_CONTROL(data)  rUCON0  &= ~(0xf)	;  rUCON0  |= data									 //
//=====================================================================================================	

//uart1.c
extern void UART1_Init(int baud);
extern void UART1_SendByte (uint8 data);
//uart2.c

extern uint8 UART2_TxBuffer[256];

extern uint8 UART2_RxBuffer[256];

extern uint8 UART2_TxTop;

extern uint8 UART2_RxTop;

extern uint8 UART2_TxEnd;

extern uint8 UART2_RxEnd;

extern void UART2_Init(int baud);

extern void UART2_SendByte (uint8 data);

extern void UART2_SendString(char *data);

extern uint8 UART2_PopByte( void );

extern void Expection_UART2( void );


extern int UART2_RxReady( void );



//pwm.c
extern void  TimerPWMInit(void);
extern uint8 SetPWM(uint8 Num, fp64 Ratio);


//nand.c


#define TYPE_HEAD		0
#define TYPE_INT8		1
#define TYPE_UINT8		2
#define TYPE_INT16		3
#define TYPE_UINT16		4
#define TYPE_INT32		5
#define TYPE_UINT32		6
#define TYPE_INT64		7
#define TYPE_UINT64		8
#define TYPE_FP32		9
#define TYPE_FP64		10
#define TYPE_POINTFP32	11
#define TYPE_POINTFP64	12


#define NF_CLEAR_RB()    	{rNFSTAT |= (1<<2);}		//д1�����⵽RnB�ı�־
#define NF_DETECT_RB()    	{while(!(rNFSTAT&(1<<2)));}	//�ȴ���⵽RnB
#define NF_ADDR(addr)		{rNFADDR=addr;}				//д��ַ



#define TACLS		0	// 1-clk(0ns) 
#define TWRPH0		3	// 3-clk(25ns)
#define TWRPH1		0	// 1-clk(10ns)  //TACLS+TWRPH0+TWRPH1>=50ns

#define	BLK_IDXL	8
#define	BLK_IDXH	9
#define	FMT_TAG		15


							//	����1		����2
#define	READCMD0	0		//	������
#define	READCMD1	1		//	������
#define	READCMD2	0x50	//	������00B
#define	ERASECMD0	0x60	//	������
#define	ERASECMD1	0xd0	//				������
#define	PROGCMD0	0x80	//	д����
#define	PROGCMD1	0x10	//				д����
#define	QUERYCMD	0x70	//	��״̬
#define	RdIDCMD		0x90	//	��оƬID



#define	EnNandFlash()	(rNFCONT |= 1)					//ʹ��nand
#define	DsNandFlash()	(rNFCONT &= ~1)					//��ֹnand
#define	NFChipEn()		(rNFCONT &= ~(1<<1))			//ʹ��Ƭѡ
#define	NFChipDs()		(rNFCONT |= (1<<1))				//��ֹƬѡ
#define	InitEcc()		(rNFCONT |= (1<<4))				//��ʼ��ECC
#define	MEccUnlock()	(rNFCONT &= ~(1<<5))			//����MECC
#define	MEccLock()		(rNFCONT |= (1<<5))				//����MECC
#define	SEccUnlock()	(rNFCONT &= ~(1<<6))			//����SECC
#define	SEccLock()		(rNFCONT |= (1<<6))				//����SECC

#define	WrNFDat8(dat)	(rNFDATA8 = (dat))				//д8λ����
#define	WrNFDat32(dat)	(rNFDATA = (dat))				//д32λ����
#define	RdNFDat8()		(rNFDATA8)						//��8λ����
#define	RdNFDat32()		(rNFDATA)						//��32λ����

#define	WrNFCmd(cmd)	(rNFCMD = (cmd))				//д����
#define	WrNFAddr(addr)	(rNFADDR = (addr))				//д��ַ
#define	WrNFDat(dat)	WrNFDat8(dat)					//д8λ����
#define	RdNFDat()		RdNFDat8()						//��8λ����

#define	RdNFMEcc()		(rNFMECC0)	//for 8 bit nand flash, only use NFMECC0
#define	RdNFSEcc()		(rNFSECC)	//for 8 bit nand flash, only use low 16 bits

#define	RdNFStat()		(rNFSTAT)
#define	NFIsBusy()		(!(rNFSTAT&1))					//Ϊ1ʱæ
#define	NFIsReady()		(rNFSTAT&1)						//Ϊ1ʱ����


struct Nand_ValuePack
{
	uint8 Type;
	void * DataAddress;
	char * Name;
};

extern int Nand_Error;

extern void Nand_Reset(void);

extern uint32 WaitNFBusy(void);

extern void MarkBadBlk(uint32 addr);

extern void ReadPage( uint32 sector, uint8 *buf);

extern uint32 Check_Page(uint32 addr,uint8 *num);

extern void InitNandCfg( void );

extern uint32 EraseBlock(uint32 sector);

extern uint32 WritePage(U32 sector, U8 *buf);

extern uint32 ReadChipId(void);

extern void WritePartBlock(uint32 sector, uint8 *buf);

extern void RestorationNandInit(void);

//clock.c

extern void Delay10us(int time);

extern void Delay100us(int time);

extern void Delay1ms(int time);

extern void Delay10ms(int time);

extern void Delay100ms(int time);

//wacthdog.c
extern void WatchDog_Init(void);
//wireless.c
extern void WIRELESS_Setlength(char length);
extern void WIRELESS_WriteNum_X(double data);
extern void WIRELESS_WriteNum_Y(double data);
extern void WIRELESS_WriteNum_A(double data);

extern void WIRELESS_WriteInt_x(double data);
extern void WIRELESS_WriteInt_y(double data);
extern void WIRELESS_WriteInt_angle(double data);
extern int flag_running;
extern fp64  wireless_x;
extern fp64  wireless_speed;
extern int  wireless_count;
extern fp64  wireless_y;
//extern int time_count;
extern void WIRELESS_PushByte(uint8 data);

extern void WIRELESS_WriteChar(char data);
extern void WIRELESS_WriteString(char *data);
extern void WIRELESS_PushString(char *data);
extern void WIRELESS_WriteInt(int data);

#endif