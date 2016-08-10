#include "update.h"
int clk=0;
unsigned int real_time=0;//ms ��ʱ��λ

void TIM1_INIT(void)
{
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  
	
	  TIM_TimeBaseStructure.TIM_Period = 1000; 
    TIM_TimeBaseStructure.TIM_Prescaler = 79; 
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); 
	
	  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;   
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);
	
		TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM1,ENABLE);   
}

void TIM1_UP_IRQHandler(void)
{
	TIM_ClearFlag(TIM1, TIM_FLAG_Update); 
	Encoder_Update();//��������ֻ����һ������
	GPS_Update();	//GPSֻ����һ������

	if(clk==1)
	{
		LED1_on;
	}
	else if(clk==250)
	{
		
		LED1_off;
		//��������Ǳ�ͷ����������������Ƿ��д�
		if(Gyro_Error_Flag==0)
		{
				DMA_check();
		}
	}
	else if(clk>=500)
	{
		clk=0;
	}
	
	clk++;
	real_time++;
}
