#include "all.h"
#include "can.h"

/*************************************************
����: void RCC_Configuration(void)
����: ��λ��ʱ�ӿ��� ����
����: ��
����: ��
**************************************************/

float delta_y=800;
float delta_x=800;
float delta_slow=200;
float move_distance=0;
<<<<<<< HEAD
extern union fi64_to_u8 flash_save[11];
extern int Stop_time;

void init_parameter(void)
{
	Data_Load();
	AGV_speed=flash_save[0].u16_data[0];
	delta_x=flash_save[0].u16_data[1];
	delta_y=flash_save[0].u16_data[2];
	Stop_time=flash_save[0].u16_data[3];
}
=======
>>>>>>> 2e8c624a0a3a1d3839c54e5692f6a1a626c4e09e

void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ���
  RCC_DeInit();                                    //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ���پ���
  HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
  if(HSEStartUpStatus == SUCCESS)                  //�ⲿ����ʱ���Ѿ�׼���
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //����FLASHԤ�����幦�ܣ�����FLASH�Ķ�ȡ�����г����б�����÷�.λ�ã�RCC��ʼ���Ӻ������棬ʱ������֮��
    FLASH_SetLatency(FLASH_Latency_2);                    //flash��������ʱ
      	
    RCC_HCLKConfig(RCC_SYSCLK_Div1);               //����AHB(HCLK)ʱ�ӵ���==SYSCLK
    RCC_PCLK2Config(RCC_HCLK_Div1);                //����APB2(PCLK2)��==AHBʱ��
    RCC_PCLK1Config(RCC_HCLK_Div1);                //����APB1(PCLK1)��==AHB1/2ʱ��
         
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //����PLLʱ�� == �ⲿ���پ���ʱ�� * 9 = 72MHz
    RCC_PLLCmd(ENABLE);                                   //ʹ��PLLʱ��
   
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)    //�ȴ�PLLʱ�Ӿ���
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //����ϵͳʱ�� = PLLʱ��
    while(RCC_GetSYSCLKSource() != 0x08)                  //���PLLʱ���Ƿ���Ϊϵͳʱ��
    {
    }
  }

}

/*************************************************
����: void GPIO_Configuration(void��
����: GPIO����
����: ��
����: ��
**************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;        //����GPIO��ʼ���ṹ��

	//  ��GPIO A B��ʱ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	/* Configure PB.3,PB.4 as Output push-pull */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	/* Configure PC.13,PC.14 as Output push-pull */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure); 


}

void led_tag(uint8_t i)
{
	switch(i)
	{
		case 1:
			if((GPIOB->ODR & GPIO_Pin_3) == 0)
				GPIO_SetBits(GPIOB, GPIO_Pin_3);
			else
				GPIO_ResetBits(GPIOB, GPIO_Pin_3); 
			break;
		case 2:
			if((GPIOB->ODR & GPIO_Pin_4) == 0)
				GPIO_SetBits(GPIOB, GPIO_Pin_4);
			else
				GPIO_ResetBits(GPIOB, GPIO_Pin_4); 
			break;
		case 3:
			if((GPIOC->ODR & GPIO_Pin_13) == 0)
				GPIO_SetBits(GPIOC, GPIO_Pin_13);
			else
				GPIO_ResetBits(GPIOC, GPIO_Pin_13); 
			break;
		case 4:
			if((GPIOC->ODR & GPIO_Pin_14) == 0)
				GPIO_SetBits(GPIOC, GPIO_Pin_14);
			else
				GPIO_ResetBits(GPIOC, GPIO_Pin_14); 
			break;
	}
}

void LedInit(void)
{
    GPIO_Configuration();
    LED1_on;
		LED2_on;
		LED3_on;
		LED4_on;
}

void PwmInit(void)
{
		pwm1_2_Freqz=5000;
		TIM_PWM_Init();
		DIR_IO_Init();
}

//**********************************************************��ʵ���Ӳ���
float mycoeff_arg[3][3]={0};
extern float a_OR;

extern float wheel_r;

void build_co_arg (void)
{
	/*
 mycoeff_arg[0][0]=sin (a_OR+wheel_i_R[0][2])/wheel_r ;
 mycoeff_arg[0][1]=cos (a_OR+wheel_i_R[0][2])/wheel_r ;   */
	/* mycoeff_arg[1][0]=sin (a_OR+wheel_i_R[1][2])/wheel_r ;
 mycoeff_arg[1][1]=cos (a_OR+wheel_i_R[1][2])/wheel_r ;  */ 
 	
/* mycoeff_arg[2][0]=sin (a_OR+wheel_i_R[2][2])/wheel_r ;
 mycoeff_arg[2][1]=cos (a_OR+wheel_i_R[2][2])/wheel_r ;*/
 

 mycoeff_arg[0][0]=sin (PI/2+1.0/180*PI  )/wheel_r ;
 mycoeff_arg[1][0]=sin (11.0/6*PI-0.0/180*PI)/wheel_r ;
 mycoeff_arg[2][0]=sin (7.0/6*PI-1.0/180*PI) /wheel_r ;
	
 mycoeff_arg[1][1]=cos (-0.0/180*PI+11.0/6*PI)/wheel_r ;
 mycoeff_arg[0][1]=cos (-0.0/180*PI+PI/2)/wheel_r ;
 mycoeff_arg[2][1]=cos (-0.0/180*PI+7.0/6*PI+1.1/180*PI)/wheel_r ;

//��ʽ��mycoeff_arg[0][2]=-1*wheel_i_R[0][0]*cos(wheel_i_R[0][2]-wheel_i_R[0][1])/wheel_r ;
 mycoeff_arg[0][2]=-1*wheel_i_R[0][0]*cos(0.0)/wheel_r ;
 mycoeff_arg[1][2]=-1*wheel_i_R[1][0]*cos(0.0)/wheel_r ;
 mycoeff_arg[2][2]=-1*wheel_i_R[2][0]*cos(0.0)/wheel_r ;

}


//**********************************************************��ʵ���Ӳ���

void InitAll(void)
{
    
	RCC_Configuration();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//��ʱ����ʼ��
	move_timer_cfg();
	leave_timer_cfg();
	
	LedInit();
  SysTick_init();

	//camer1 camer2 adc
	Can1_Init();	//canͨ��   
    
	//�ӽ���ͷ
  SA_Init();   
	IO_IT_config();
	
	//LCD��
  USART3_Init();
	//��������
	Compass_Init();
	
	//���
  PwmInit();
	set_mecf(0);
	set_mecbl(0);
	set_mecbr(0);
	
	//�����ٶȷֽ�����ʼ��
	build_co_arg ();
<<<<<<< HEAD
	//������ʼ����
	init_parameter();
=======
>>>>>>> 2e8c624a0a3a1d3839c54e5692f6a1a626c4e09e
	//��ʼ������	
  LED1_off;   
	LED2_off;
	LED3_off;
	LED4_off;  
}

extern int Stop_time;


void LCD_Welcom (void)
{
	char str_target[20]={"\0"};
  u8 temp;
  int i,j;
  int t_row=0;
  int t_line=0;
  int target_point[2][6]={0};
 // str_target[0]=' ';
	i=0;

//	first_blood=0;
  while(1)
	{
			LCD_Clear();
			LCD_SetXY(0,0);
			LCD_WriteString("AGV WORLD WELCOM");
			
			LCD_SetXY(0,1);
			LCD_WriteString("PLEASE ENTER TARGET PORT");
			
			LCD_SetXY(0,2);
			LCD_WriteString(" SEPRATE BY BLANK ");
		
		  LCD_SetXY(0,3);
		  LCD_WriteString(str_target);
			
			LCD_SetXY(0,4);
			LCD_WriteString("PRESS OK TO GO");
			
			LCD_SetXY(0,5);
			LCD_WriteString("PRESS BACK TO SETTING");
		  
			refresh();
			delay(LCD_DELAY);
		
		  if(KeyReady)
        {
			     KeyReady=0;	//�尴����־λ
            switch(KeyValue)
            {
                case 1://1
                    if(i<14)
                        str_target[i++]='1';
                break;
                case 2://2
                    if(i<14)
                        str_target[i++]='2';
                break;
                case 3://3
                    if(i<14)
                        str_target[i++]='3';
                break;
                case 4://4
                    if(i<14)
                        str_target[i++]='4';
                break;
                case 7://5
                    if(i<14)
                        str_target[i++]='5';
                break;
                case 8://6
                    if(i<14)
                        str_target[i++]='6';
                break;
                case 9://7
                    if(i<14)
                        str_target[i++]='7';
                break;
                case 10://8
                    if(i<14)
                        str_target[i++]='8';
                break;
                case 13://9
                    if(i<14)
                        str_target[i++]='9';
                break;
                case 14://0
                    if(i<14)
                        str_target[i++]='0';
                break;
                case 15://.
                    if(i<14)
                    {
                        str_target[i++]='.';
                    }
                break;
				        case 16://-
                    if(i<14)
                    {
                        str_target[i++]='-';
                    }
                break;
                case 17://del
                    if(i>0)
                    {
                        str_target[--i]='\0';
                    }
                break;
                case 18://ok   ִ�����г���
                    for(j=0;j<i;j++)// 
                    {
                        if(str_target[j]=='.')
                        {
                            t_line=1;
                        }
                        else if(str_target[j]=='-')
                        {
                            t_line=0;t_row+=1;
                        }
												else
												{
													target_point[t_row][t_line]=target_point[t_row][t_line]*10+(str_target[j]-'0');
												}
												//t_number=t_row;
										}
										
										for(int j=0;j<=t_row;j++)
										{
	//										first_blood=0;	
											my_test(target_point[j][0],target_point[j][1]);
											delay(Stop_time);
										}
										
										break;
                
             case 5://cancel     ִ�в˵�����
                    ShowMenuList();
						        temp=1;
						        while(temp)
										{
												if (KeyReady==1)
												{ 
														KeyReady=0;
													if (KeyValue==5)
														temp=0;
													
													KeyNumOperate(KeyValue);	
														
												}
												refresh();
												
												delay(10);
										}
										break;
				     default:	break;
            }
        }
	}
}

