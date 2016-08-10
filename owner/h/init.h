#ifndef _INIT_H
#define _INIT_H
	#include "stm32f10x.h"

	void RCC_Configuration(void);
	void GPIO_Configuration(void);	
	void led_tag(uint8_t i);
    
    void InitAll(void);
    void PwmInit(void);
		void LCD_Welcom (void);
	
	/*
	LED1��	SysTick.c��ÿ������һ��
	LED2:	��ʾ������ĳһ�߼�ģʽ
	LED3:	���յ�������������������������б�
			���յ�����������������ϵ�ǰ״̬
            ��ʱ��û�з��ͳɹ�����
	LED4��	������DMA����
			can���߽���������涨�ĸ�ʽ��ͬ
			���ͳ����⣬void Write_Database(ID_NUMDEF ID_NUM)
            ����дflash
	*/
	#define LED1_on GPIO_ResetBits(GPIOB,GPIO_Pin_3)
	#define LED2_on GPIO_ResetBits(GPIOB,GPIO_Pin_4)
	#define LED3_on GPIO_ResetBits(GPIOC,GPIO_Pin_13)
	#define LED4_on GPIO_ResetBits(GPIOC,GPIO_Pin_14)
	
	#define LED1_off GPIO_SetBits(GPIOB,GPIO_Pin_3)
	#define LED2_off GPIO_SetBits(GPIOB,GPIO_Pin_4)
	#define LED3_off GPIO_SetBits(GPIOC,GPIO_Pin_13)
	#define LED4_off GPIO_SetBits(GPIOC,GPIO_Pin_14)
	
	//3�� pwm1����
	#define PWM1_P GPIO_SetBits(GPIOA,GPIO_Pin_3)
	#define PWM1_N GPIO_ResetBits(GPIOA,GPIO_Pin_3)
	
	//4�� pwm2����
	#define PWM2_P GPIO_SetBits(GPIOA,GPIO_Pin_2)
	#define PWM2_N GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#endif
