#include "all.h"

//#define USART1_DR_Address ((u32)0x40013804)     //USART1-DR ��ַ

//volatile uint8_t USART1_RxBuffer[RxBufferSize];
volatile float USART3_TxBuffer[TxBufferSize];

		u32 KeyValue;
		u8	KeyReady=0;	//���յ��������ݱ�־
		u8  ChangK=0;


//UART3��Ӧ�����ϵ�uart2
void UART3_init(u32 bound){
    //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART3 GPIOʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
 	USART_DeInit(USART3);  //��λ����3
// 	 //USART1_TX   PA.9
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//     GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
	//USART3_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PA9
//    
//     //USART1_RX	  PA.10
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//     GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10
		//USART3_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PA10

   //Usart3 NVIC ����

   NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
   NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
//   //Usart3 NVIC ����
// 	 NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
// 	 NVIC_Init(&NVIC_InitStructure);
	
   //USART ��ʼ������

		USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

//    USART_Init(USART1, &USART_InitStructure); //��ʼ������
//    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
//		USART_ClearFlag(USART1,USART_FLAG_TC);
//    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
		
		USART_Init(USART3, &USART_InitStructure); 
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
//		USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
		USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
}

void UART3_SendByte(uint8_t ch)
{
  USART_SendData(USART3, (uint8_t) ch);
  while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}



void USART3_NVIC_Config(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//?????3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//????3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ????
		NVIC_Init(&NVIC_InitStructure);	//??????????VIC???
}


void USART3_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//??USART3 GPIO??
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		USART_DeInit(USART3);  //????3

		//USART3_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//??????
    GPIO_Init(GPIOB, &GPIO_InitStructure); //???PA9

		//USART3_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//????
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //???PA10
}


void USART3_MODE_Config(void)
{
  USART_InitTypeDef USART_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
  USART_Init(USART3,&USART_InitStructure);   
  USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
  
  USART_Cmd(USART3,ENABLE);
  USART_ClearFlag(USART3, USART_FLAG_TC);
}
void USART3_DMA_TX_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel2); 												// 
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART3->DR);			//DMA??1???
	
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)USART3_TxBuffer;		//DMA????
	DMA_InitStructure.DMA_BufferSize = TxBufferSize;						//??????

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						//???? USART???
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//????????
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//????????
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//?????????8?
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//????????8???
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							//??????DMA_Mode_Circular	DMA_Mode_Normal
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;					//?????
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//DMA?????????????? 
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);							//
	
}



void USART3_Init(void)
{
// 	USART_InitTypeDef USART_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;
	USART3_NVIC_Config();
	USART3_GPIO_Config();
	USART3_MODE_Config();
	USART3_DMA_TX_Config();
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
// 	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
//  DMA_Cmd(DMA1_Channel2, ENABLE);
//	USART1_DMA_TX_NVIC_Config();
}

void DMA_Enable(void)
{ 
	
	DMA_Cmd(DMA1_Channel2, DISABLE );  //??USART1 TX DMA1 ??????   
 	DMA_SetCurrDataCounter(DMA1_Channel2,4);//DMA???DMA?????
 	DMA_Cmd(DMA1_Channel2, ENABLE);  //??USART1 TX DMA1 ?????? 
}	 

double key_test;
char *key_name="KP";



void USART3_IRQHandler(void)
{
// 		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
// 		USART_ClearFlag(USART3,USART_FLAG_RXNE);
//  		USART_ClearFlag(USART3,USART_FLAG_TC);
//		u32 KeyValue;
	
    //LED_Toggle(2);
	
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
			KeyValue = USART_ReceiveData(USART3);
			KeyReady=1;
		
    }
	
	
	if(KeyValue == 6)
	{
//		rt_mb_send(&Mb_Emergency, KeyValue);
		ChangK=1;
	}
    else
//		rt_mb_send(&Mb_Key, KeyValue);
    
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);  
}
