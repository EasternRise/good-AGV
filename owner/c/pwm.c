#include "pwm.h"

u32 Sys_Clk=8000000;



u16 pwm1_2_Freqz;
u16 pwm3_4_Freqz;

u16 TIM2_PERIOD;//��ʱ����ת������
u16 TIM4_PERIOD;

u16 CCR_VAL1 ;//��ʱ���ıȽϼĴ�����ȡֵ������ʱ����ʵʱ��ֵ���ڴ�ֵʱ����ƽ�䷴��
u16 CCR_VAL2 ;//ͬ��
u16 CCR_VAL3 ;//ͬ��
u16 CCR_VAL4 ;//ͬ��

void DIR_IO_Init(void);

void TIM_PWM_Init(void)
{
	PWM_GPIO_Config();
	PWM_Mode_Config();
	TIM4 ->CCR3=0;
	TIM4 ->CCR4=0;
	
// 	TIM2 ->CCR3=0;
// 	TIM2 ->CCR4=0;
// 	TIM4 ->CCR3=0;
// 	TIM4 ->CCR4=0;
	
}

void	DIR_GPIO_Config(void);

void DIR_IO_Init(void)
{
	
	DIR_GPIO_Config();
	
	PWM1_P;
	PWM2_P;
}

void	DIR_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	
	// ����TIM2ʱ��
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	// ����PA2 PA3Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void  PWM_GPIO_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
// 	
	// ����ʱ��
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
// 	
// 	// ����TIM2ʱ��
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
// 	
// 	// ����PA2 PA3Ϊ��������ģʽ
// 	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
// 	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
// 	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
    
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
//
	//����TIM4ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	// ���� PB8,PB9Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStruct;
void  PWM_Mode_Config(void)
{
 //TIM2 ModeConfig
// 	{
// 		TIM2_PERIOD=Sys_Clk/pwm3_4_Freqz;
// 		CCR_VAL3=CCR_VAL4=TIM2_PERIOD>>2;	
// 		
// 		TIM_TimeBaseStructure.TIM_Period=TIM2_PERIOD;
// 		TIM_TimeBaseStructure.TIM_Prescaler=72-1;
// 		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
// 		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
// 		TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);
// 	
// 		//	TIM���ģʽ��ʼ��
// 		TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;  //��ΪPWM���ģʽ
// 		TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//
// 		TIM_OCInitStruct.TIM_Pulse=CCR_VAL4;//����50%ռ�ձ�
// 		TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;//
// 		
// 		TIM_OC3Init(TIM2,&TIM_OCInitStruct);//��ʼ��TIM2��channel 3(pwm4)
// 		TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);//
// 		
// 		TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//
// 		TIM_OCInitStruct.TIM_Pulse=CCR_VAL3;//����50%ռ�ձ�
// 		
// 		TIM_OC4Init(TIM2,&TIM_OCInitStruct);//��ʼ��TIM2��channel 4(pwm3)
// 		TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
// 		
// 		TIM_Cmd(TIM2,ENABLE);//ʹ������	
// 	
// 	}
	
	//TIM4 ModeConfig
	{
		TIM4_PERIOD=Sys_Clk/pwm1_2_Freqz;		//��ʱ����������*pwm���Ƶ��=ϵͳ��ʱ������
// 		CCR_VAL1=CCR_VAL2=TIM4_PERIOD/2;		//��ʼ��ʹ�Ƚ�����ֵ������������һ�룬�õ�50%��pwm��	
		CCR_VAL1=CCR_VAL2=0;		//��ʼ��ʹ�Ƚ�����ֵ������������һ�룬�õ�50%��pwm��	
		
		// ��ʱ����ʼ��
		TIM_TimeBaseStructure.TIM_Period=TIM4_PERIOD;
		TIM_TimeBaseStructure.TIM_Prescaler=9-1;
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4, & TIM_TimeBaseStructure);
		
		TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;  //��ΪPWM���ģʽ
		TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//
		TIM_OCInitStruct.TIM_Pulse=CCR_VAL2;//����50%ռ�ձ�
		TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;//
		
		TIM_OC3Init(TIM4,&TIM_OCInitStruct);//��ʼ��TIM4��channel 3(pwm2)
		TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
		
		TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//
		TIM_OCInitStruct.TIM_Pulse=CCR_VAL1;//����50%ռ�ձ�
		
		TIM_OC4Init(TIM4,&TIM_OCInitStruct);	//��ʼ��TIM4��channel 4(pwm1)
		TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
		
		TIM_ARRPreloadConfig(TIM2, ENABLE);//�������ؼĴ���ARR
		TIM_ARRPreloadConfig(TIM4, ENABLE);//�������ؼĴ���ARR		
	
		TIM_Cmd(TIM4,ENABLE);	
		
	}
}

extern u8 col_error;

void set_mecbl(float speed)
{
	if(col_error)
	{
			ADC_MOT_DATA.float_data=0;
			Write_Database(ADC_MOT_ID);
			return;
	}
	ADC_MOT_DATA.float_data=speed;
	Write_Database(ADC_MOT_ID);
}

//�ٶȣ����ذ�PWM1
//�������ذ�PWM3
void set_mecbr(float speed)
{
	float duty=0;
	
	if(col_error)
	{
			TIM4->CCR4=0;
			return;
	}
	
	if(speed==0)
	{
		TIM4->CCR4=0;

		return;
	}
	if(speed>0)
	{
		PWM1_P;
	}
	else
	{
		speed=-speed;
		PWM1_N;
	}
	
	duty=0.9-(speed*16/3000)*0.8;
	TIM4->CCR4=(u16)(TIM4_PERIOD*duty)-1;
}

//�ٶȣ����ذ�PWM2
//�������ذ�PWM4
void set_mecf(float speed)
{
	float duty=0;
	
	if(col_error)
	{
			TIM4->CCR3=0;
			return;
	}
	
	if(speed==0)
	{
		TIM4->CCR3=0;
		return;
	}
	
	if(speed>0)
	{
		PWM2_P;
	}
	else
	{
		speed=-speed;
		PWM2_N;
	}
	
	duty=0.9-(speed*16/3000)*0.8;
	TIM4->CCR3=(u16)(TIM4_PERIOD*duty)-1;
}

void PWM1_SetDuty(u16 rate)
{
	if(rate)
		TIM_OCInitStruct.TIM_Pulse=rate*TIM4_PERIOD/1000-1;
	else 
		TIM_OCInitStruct.TIM_Pulse=0;
	TIM_OC4Init(TIM4,&TIM_OCInitStruct);
}

void PWM2_SetDuty(u16 rate)
{
	if(rate)
		TIM_OCInitStruct.TIM_Pulse=rate*TIM4_PERIOD/1000-1;
	else 
		TIM_OCInitStruct.TIM_Pulse=0;
	TIM_OC3Init(TIM4,&TIM_OCInitStruct);
}

void PWM3_SetDuty(u16 rate)
{
	if(rate)
		TIM_OCInitStruct.TIM_Pulse=rate*TIM2_PERIOD/1000-1;
	else 
		TIM_OCInitStruct.TIM_Pulse=0;
	TIM_OC4Init(TIM2,&TIM_OCInitStruct);
}

void PWM4_SetDuty(u16 rate)
{
	if(rate)
		TIM_OCInitStruct.TIM_Pulse=rate*TIM2_PERIOD/1000-1;
	else 
		TIM_OCInitStruct.TIM_Pulse=0;
    TIM_OC3Init(TIM2,&TIM_OCInitStruct);
}

// int PWM_SetDuty(u8 pwmx, float duty)
// {
//     //u32 ccrx = duty* TIM2_PERIOD-1;
// 		u32 ccrx = duty* TIM2_PERIOD;
//     
//     assert_param(pwmx>=1 && pwmx<=3);
//     assert_param(duty<=100);
// 	
//     switch (pwmx)
//     {
//         case 1: TIM4->CCR4 = ccrx; break;
//         case 2: TIM4->CCR3 = ccrx; break;
//         case 3: TIM2->CCR4 = ccrx; break;
//         case 4: TIM2->CCR3 = ccrx; break;
//         default:    break;
//     }   
// 		
//     return 1;
// }

//0 1 2�� 10 11 12
