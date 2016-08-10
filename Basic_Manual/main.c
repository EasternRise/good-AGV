#include "all.h"

//�����¼����ƿ�
OS_EVENT *I2cMbox;
OS_EVENT *MenuMbox;
OS_EVENT *AppStartMbox;
OS_EVENT *AppKey1Mbox;
OS_EVENT *AppKey2Mbox;
OS_EVENT *ArmMbox;
OS_EVENT *AutoMbox;

#if ShortcutSetting
OS_EVENT *SCKey1Mbox;
OS_EVENT *SCKey2Mbox;
#endif

#if LidarSetting
OS_EVENT *LidarMbox;
#endif

OS_EVENT *McMbox;
OS_EVENT *RouteMbox;

#if WirelessSetting
OS_EVENT *WirelessMbox;
#endif

//Ϊ�����������ջ
OS_STK	TaskI2cKeysStk		[TaskStkLengh];
OS_STK  TaskLcdDisplayStk  	[TaskStkLengh];
OS_STK  TaskLcdRefreshStk  	[TaskStkLengh];
OS_STK	TaskPathSelStk		[TaskStkLengh];
OS_STK  TaskRouteStk        [TaskStkLengh];
OS_STK  TaskArmStk          [TaskStkLengh];
OS_STK  TaskAutoStk			[TaskStkLengh];
OS_STK  TaskSonicStk		[TaskStkLengh];
OS_STK  TaskAutoSwitchStk	[TaskStkLengh];
OS_STK  TaskRetryStk		[TaskStkLengh];




#if WirelessSetting
OS_STK  TaskWirelessStk     [TaskStkLengh];
#endif


#if ManualSetting
OS_STK	TaskManualStk		[TaskStkLengh];
#endif

#if LidarSetting
OS_STK  TaskLidarStk        [TaskStkLengh];
#endif


int Main(void)
{
	CLOCK_Init(CLKMODE_400M);	//ϵͳʱ�ӳ�ʼ��
	MMU_Init();					//�ڴ����Ԫ��ʼ��
	ISR_Init();					//�жϷ�������ʼ��
	 
	UART0_Init(9600);			//UART0��ʼ��
	UART1_Init(115200);			//UART1��ʼ��
	UART2_Init(115200);			//UART2��ʼ��
		
	IO_Init();					//IO��ʼ��
	SPI1_Init();				//SPI��ʼ��
	I2CInit();					//I2C��ʼ��
	//FPGA_PWM_INIT();			//FPGA�ϵ�PWM����ʼ��
#if LightBoardSetting
	LightBoardInit();			//�ư��ʼ��
#endif
	STM32_Reset();
	InitNandCfg();				//NandFlash��ʼ��
	
	
	
	
	#if WatchDogSetting
	WatchDog_Init();			//���Ź���ʼ��
	#endif
	
    OSInit ();	 				//����ϵͳ��ʼ��
    
///////////////////////////���Ͻ����ײ�/////////////////////////////

	GYRO_NandInit();			//��ȡ�����ǲ���
    ENCODER_NandInit();			//��ȡ���̲���
	Mecanum_NandInit();			//��ȡȫ���ֲ���
	PID_NandInit();				//��ȡPID����
	
	
	
	BackDataInit();
		#if WalkGroundEnable
	Info_NandInit();
		#else
	Fix_Init();
		#endif
	
	OSTimeSet(0);				//ϵͳʱ������
	
/////////////////////////////ע������/////////////////////////////////

	I2cMbox		= 	OSMboxCreate((void *)0);	//����iic�õ��ļ�����Ϣ�������ֵ�ĺ���TaskI2cKeys.c
	MenuMbox	= 	OSMboxCreate((void *)0);	//������ʾ�˵�·��
	AppStartMbox=	OSMboxCreate((void *)0);	//���ڿ����û�����
	AppKey1Mbox	= 	OSMboxCreate((void *)0);	//���û����򴫵ݼ�ֵ
	AppKey2Mbox	= 	OSMboxCreate((void *)0);	//���ڰ������
	
	RouteMbox	=	OSMboxCreate((void *)0);	//��������·��
	ArmMbox     = 	OSMboxCreate((void *)0);
	AutoMbox    =   OSMboxCreate((void *)0);

	
	#if LidarSetting
	LidarMbox   =   OSMboxCreate((void *)0);	
	#endif

////////////////////////////////ע������//////////////////////////////

	OSTaskCreate (TaskI2cKeys,	(void *)0, &TaskI2cKeysStk[TaskStkLengh - 1], 	I2cKeysPrio);			//��ֵ��������
	OSTaskCreate (TaskPathSel,	(void *)0, &TaskPathSelStk[TaskStkLengh  - 1], 	PathSelPrio );			//�û�������������
	
	#if LidarSetting
    OSTaskCreate (TaskLidar,(void *)0, &TaskLidarStk[TaskStkLengh - 1], TaskLidarPrio);
	#endif
	
	#if ManualSetting
    OSTaskCreate (TaskManual,	(void *)0, &TaskManualStk[TaskStkLengh  - 1], ManualPrio );
	#endif
	 
	OSTaskCreate (TaskLcdDisplay,(void *)0, &TaskLcdDisplayStk[TaskStkLengh - 1],	TaskLcdDisplayPrio);	//�˵���ʾ����
   	OSTaskCreate (TaskLcdRefresh,(void *)0, &TaskLcdRefreshStk[TaskStkLengh - 1],	TaskLcdRefreshPrio);	//Һ��ˢ������
	
	OSTaskCreate (TaskRoute,	 (void *)0, &TaskRouteStk[TaskStkLengh  - 1], 		RoutePrio );			//��������
	OSTaskCreate (TaskArm,       (void *)0, &TaskArmStk[TaskStkLengh -1],			ArmPrio);
    OSTaskCreate (TaskAuto,      (void *)0, &TaskAutoStk[TaskStkLengh-1],			AutoPrio);
	OSTaskCreate (TaskSuperSonic,(void *)0, &TaskSonicStk[TaskStkLengh - 1],		SonicPrio);
	//OSTaskCreate (TaskAutoSwitch,(void *)0, &TaskAutoSwitchStk[TaskStkLengh-1],		AutoSwitchPrio);
	//OSTaskCreate (TaskRetry,     (void *)0, &TaskRetryStk[TaskStkLengh-1],			RetryPrio);

///////////////////////////////////////////////////////////////////	


    TimerPWMInit();				//��ʱ����PWM����ʼ���� ��������������
    OSStart (); 
	
	return 0;
}







