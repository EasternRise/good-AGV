#include "all.h"
long int time_test=0;
long int time=0;
long int time1=0;
long int time2=0;
long int time3=0;
long int time_H_hit=0;
long int time_L_hit=0;
long int f_hit_time=0;
u8 P_flag=0;
long int time_round=0;
u32 timeflag[400]={0};
u32 i=0;
u8 flag=0,packet_flag=0,bal_flag=0;
u8 start_stepper_flag = 0;
u8 sa_status=0xff,st_status=0xff;
extern int start_init;
/*scan the status of the on-offs,from num 1 to num 13.num-0-to-num-8 stands for 8 touching on_offs
 *num-8-to-num-13 stands for 5 untouching on-offs;
 * 1 - off
 - 0 - on
 use the bit 0 to bit 12,leave alone bit 13,bit 14 and bit 15;
 */
void READ(void)
{
	u8 sa_temp=0x00;
	u8 st_temp=0x00;
	
  st_temp|=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)<<0;
	st_temp|=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)<<1;
	st_temp|=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)<<2;
	st_temp|=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)<<3;
	st_temp|=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)<<4;
	st_temp|=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)<<5;
	st_temp|=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)<<6;

	st_temp|=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)<<7;
	
	sa_temp|=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)<<0;
	sa_temp|=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10)<<1;
	sa_temp|=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11)<<2;
	sa_temp|=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12)<<3;
	sa_temp|=GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)<<4;
	if((sa_status != sa_temp)||(st_status != st_temp))
	{
		sa_status = sa_temp;
		st_status = st_temp;
//		S_SWITCH_FUNC();
	}
}


/*************************************************
����: void RCC_Configuration(void)
����: ��λ��ʱ�ӿ��� ����
����: ��
����: ��
**************************************************/
// void RCC_Configuration(void)
// {
//   ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ���
//   RCC_DeInit();                                    //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
//   RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ���پ���
//   HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
//   if(HSEStartUpStatus == SUCCESS)                  //�ⲿ����ʱ���Ѿ�׼���
//   {
// //     FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б�����÷�.λ�ã�RCC��ʼ���Ӻ������棬ʱ������֮��
// //     FLASH_SetLatency(FLASH_Latency_2);                    //flash��������ʱ
//       	
//     RCC_HCLKConfig(RCC_SYSCLK_Div1);               //����AHB(HCLK)ʱ�ӵ���==SYSCLK
//     RCC_PCLK2Config(RCC_HCLK_Div1);                //����APB2(PCLK2)��==AHBʱ��
//     RCC_PCLK1Config(RCC_HCLK_Div1);                //����APB1(PCLK1)��==AHB1/2ʱ��
//          
//     RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //����PLLʱ�� == �ⲿ���پ���ʱ�� * 9 = 72MHz
//     RCC_PLLCmd(ENABLE);                                   //ʹ��PLLʱ��
//    
//     while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //�ȴ�PLLʱ�Ӿ���
//     {
//     }
//     RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //����ϵͳʱ�� = PLLʱ��
//     while(RCC_GetSYSCLKSource() != 0x08)                  //���PLLʱ���Ƿ���Ϊϵͳʱ��
//     {
//     }
//   }

// }

/*************************************************
����: void GPIO_Configuration(void��
����: GPIO����
����: ��
����: ��
**************************************************/
void IO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;        //����GPIO��ʼ���ṹ��

  //  ��GPIO A B C D��ʱ�� 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

 /* Configure PA as Output push-pull ***********GPIO_Pin_0 | GPIO_Pin_1 |  GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_15 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	


  /* Configure PB6  PB7 as Output push-pull */ 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);

 /* Configure PC as Output push-pull ***********GPIO_Pin_6 | GPIO_Pin_7|GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7|GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12 ; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void IO_IT_config(void)
{
	EXTI_InitTypeDef EXTI_initstruct;
	NVIC_InitTypeDef NVIC_initstruct;
	EXTI_DeInit();

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource12);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource11);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource10);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
	
	EXTI_initstruct.EXTI_Line=EXTI_Line12|EXTI_Line11|EXTI_Line10|EXTI_Line15;
	EXTI_initstruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_initstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_initstruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_initstruct);

	EXTI_initstruct.EXTI_Line=EXTI_Line2;
	EXTI_initstruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_initstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_initstruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_initstruct);

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_initstruct.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_initstruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_initstruct.NVIC_IRQChannelSubPriority=1;
	NVIC_initstruct.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_initstruct);
	
	NVIC_initstruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_initstruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_initstruct.NVIC_IRQChannelSubPriority=2;
	NVIC_initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_initstruct);
	
	NVIC_initstruct.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_initstruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_initstruct.NVIC_IRQChannelSubPriority=0;
	NVIC_initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_initstruct);
}

//0.1ms ����һ��
// void TIM3_Configuration(void)
// {
// 	TIM_TimeBaseInitTypeDef TIM_Instruction;
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
// 	TIM_Instruction.TIM_Period=9;
// 	TIM_Instruction.TIM_Prescaler=719;
// 	TIM_Instruction.TIM_ClockDivision=0;
// 	TIM_Instruction.TIM_CounterMode=TIM_CounterMode_Up;
// 	TIM_TimeBaseInit(TIM3, &TIM_Instruction);
// }

// void TIM3_NVIC_Configuration(void)
// {
// 	NVIC_InitTypeDef NVIC_Initstruct;
// 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
// 	NVIC_Initstruct.NVIC_IRQChannel=TIM3_IRQn;
// 	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=0;
// 	NVIC_Initstruct.NVIC_IRQChannelSubPriority=0;
// 	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
// 	NVIC_Init(&NVIC_Initstruct);
// }


void EXTI2_IRQHandler(void)
{
	
	 EXTI->PR = EXTI_Line2;
		
		
}

extern float Init_Rot1,Init_Rot2;
float Factor = 0;
float Length = 54.5;
void EXTI15_10_IRQHandler(void)
{
			

	if((EXTI->PR & EXTI_Line15) != (uint32_t)RESET)   // EXTI_GetITStatus(EXTI_Line15)    SA1
	{

		EXTI->PR = EXTI_Line15;      //EXTI_ClearITPendingBit(EXTI_Line15)



	}
	

	
	
	if((EXTI->PR & EXTI_Line12) != (uint32_t)RESET)   
 	{
		EXTI->PR = EXTI_Line12;		//EXTI_ClearITPendingBit(EXTI_Line12)
		

	}

	
	
	if((EXTI->PR & EXTI_Line11) != (uint32_t)RESET)  // EXTI_GetITStatus(EXTI_Line11)
	{
		EXTI->PR = EXTI_Line11;   //EXTI_ClearITPendingBit(EXTI_Line11)

	}


	if((EXTI->PR & EXTI_Line10) != (uint32_t)RESET)  // EXTI_GetITStatus(EXTI_Line10)
	{
		EXTI->PR = EXTI_Line10; //EXTI_ClearITPendingBit(EXTI_Line10)

 

	}
}


// void TIM_Config(void)
// {
// 	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
// 	TIM_ARRPreloadConfig(TIM3,ENABLE);
// 	TIM3_Configuration();
// 	TIM3_NVIC_Configuration();
// 	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
// 	TIM_Cmd(TIM3,ENABLE);
// }


// void TIM3_IRQHandler(void)
// {
// 	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
// 	{
// 		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
// 	}
// }
