/****************************************Copyright (c)**************************************************
**                                     XJTU Robot Team
**-----------------------------------------File Info----------------------------------------------------
** File name:			CAN.c
** Last modified Date:  2013-4-30
** Descriptions:		����ļ���Ҫ������ARMͨ��STM32��CAN����������ͨ�ŵ�һЩ����ӿڡ�
** Created by:			dong		
********************************************************************************************************/
#include "basic.h"

/************************************************************************************************
**д��ǰ�棺���Ե��õ�һЩ������
**			1.void STM32_Reset(void)   ����STM32��һ���ǿ�����ʼ��ʱ��
**
**			2.void  Relay(uint32 set_low ,uint32 set_high,uint32 clear_low,  uint32  clear_high)
**			    ���������������ͬʱ��λ������ĳ�����̵����������÷������溯������ʱ�Ľ���
**				ʹ��ʾ������set 12  13 �ں�clear 15 ��44��62�ڣ����������� 
**              Relay(RELAY_LOW(3)|RELAY_LOW(7),0,RELAY_LOW(15),RELAY_HIGH(44)|RELAY_HIGH(62));
**				����ֻ���ã�RELAY_LOW(xx1) xx1��1��32   ��  RELAY_HIGH(xx2)  xx2��33��64 
** 
**			3.void Relay_Clear(uint8 port)  ������1~64
**			4.void Relay_Set(uint8 port)    ������1~64
**			
**			5.uint8 Relay_Read(uint8 port)  �������Ͳ��ý����˰ɣ��÷�����ǰһ��  ������1~64
**			6.void ISO_UNMASK(uint16 port)  ʹ�ܹ�����ĳЩ�ڣ������Զ�ִ�У�����:ISO(port),port :1~16
**											��ѡ������磺ISO(1) | ISO(2) | ..Ҳ����������
**			7.void ISO_MASK(uint16 port)    �Թ���ƺ�û�ã���ΪֻҪʹ�ܹ����ֻҪ��ִ���궯���󣬻��Զ�����
**			8.uint8 ISO_Read(uint8 port)   ֻ�ܶ����ؼ�¼��ISO��״̬��ʵ����ʲô���������Ϊû�й���ķ�������
**											������1~16
**			9.void Ranging_Start(uint8 id)  ĳ��������ʼ��࣬���忴����
**			10.void  Ranging_Stop(uint8 id) ֹͣ���
**							�����ɶ�ѡ ����  CONTROL_LASER | CONTROL_IR1 |CONTROL_SONIC1...Ҳ����
**											9.10 ��ѡ�Ĳ���Ϊ��
**												 �����ࣺ   CONTROL_LASER�� 	//���� 
**												 �����ࣺ   CONTROL_IR1   	//����1
**															  CONTROL_IR2		//����2
**												 ��������ࣺ CONTROL_SONIC1 	//������1
**											 				  CONTROL_SONIC2	//������2
**											 				  CONTROL_SONIC3	//������3
**															  CONTROL_SONIC4
**			11.uint8 Read_Device_Statu(uint16  id) 	 ��ȡĳ���豸��״̬���ж������Ƿ�һֱ���ϴ�
**												������9  10 һ�������������ܶ�ѡ
**			12.uint16 STM32_ReadDistance(uint8 id)   ���ز��ֵ
**									    ��ѡ�Ĳ���Ϊ��������ֻ��Ψһ������"��"������
**													 �����ࣺ   ID_LASER_DATA��
**													 �����ࣺ   ID_IR1_DATA  
**																  ID_IR2_DATA
**													 ��������ࣺ ID_SUP_SONIC1_DATA 
**													 			  ID_SUP_SONIC2_DATA
**													 			  ID_SUP_SONIC3_DATA
**			13.void Motor_CAN(uint8 id , uint8 cmd)  ����������� id ��ȡֵΪ 1  2
**													cmd  �� ȡֵΪ  STOP zheng ��  fan ��  ��һ�º궨��ɣ��Ҳ�֪ȡʲô���ֺ�
**		�ϲ���õľ���Щ������
*************************************************************************************************/


/*
**struct Data2STM32
**{
	uint8 	Data_ID;
	uint8*	Data_Ptr;
	uint8	Data_Length;
	uint8	Data_Type;
**}; ��basic.h�ж�����

**
** 	�ýṹ�������Ԫ�ض������£�
** 	Data_ID :	��STM32������һ���ṹ�����飬ID�ž���������±�
** 	Data_Ptr:	Ҫ���ͻ���յ����ݻ��������׵�ַ
**	Data_Length:���ݵĳ���
**	Data_Type:	���ݵ����ͣ�����д������д����ֻ�Ǻ�STM32�ĳ�����϶��ѣ�û���õ�
*/



/*
**����Ķ�ά��������壺
**STM32_DATA_BUF_LEN  	�������һ���м���Ҫ���������
**       9  			�������ÿ���������9�ֽ�
**��Ȼ���������飬���ǽṹ����ֻ���¼�õ��ĵ�ַ��
**���磺IDΪ0�����ݣ������� WRITE_ONLY�����԰� STM32_Send_Buf �ĵ�ַ����ID0 �� Data_Ptr
**������д��ARMΪ���
*/
uint8  STM32_Send_Buf[STM32_DATA_BUF_LEN][9]; 
uint8  STM32_Rece_Buf[STM32_DATA_BUF_LEN][9];


struct Data2STM32 STM32_Data[STM32_DATA_BUF_LEN]=
    {
		{ID_RELAY64,		(uint8*)STM32_Send_Buf[0 ],8,WRITE_ONLY},   //����64λ�ļ̵���������
		{ID_RELAY8, 		(uint8*)STM32_Send_Buf[1 ],1,WRITE_ONLY},   //����8λ�ļ̵���������
		{ID_LASER_CTR,		(uint8*)STM32_Send_Buf[2 ],1,WRITE_ONLY},   //������Ŀ�ʼ������Ŀ����ֽ�
        {ID_LASER_DATA,		(uint8*)STM32_Rece_Buf[3 ],3,READ_ONLY },   //��ȡ16λ�ļ�����ľ���ֵ����3���ֽ�Ϊ1���������£�Ϊ0�����ݲ������µ�
		{ID_ISO_MASK,		(uint8*)STM32_Send_Buf[4 ],1,WRITE_ONLY},   //�������ϵ�STM32����ʹ���ź�
		{ID_IR_CTR,			(uint8*)STM32_Send_Buf[5 ],1,WRITE_ONLY},   //�����Ŀ�ʼ������������ֽ�
		{ID_IR1_DATA,   	(uint8*)STM32_Rece_Buf[6 ],3,READ_ONLY },   //����1�ľ���ֵ����3���ֽ�Ϊ1���������£�Ϊ0�����ݲ������µ�
		{ID_IR2_DATA,		(uint8*)STM32_Rece_Buf[7 ],3,READ_ONLY },   //����2�ľ���ֵ��
		{ID_SUP_SONIC_CTR,	(uint8*)STM32_Send_Buf[8 ],1,WRITE_ONLY},   //�������Ŀ�ʼ������������ֽڣ�0 1 2λ�ֱ�Ϊ������1 2 3�Ŀ���λ
		{ID_SUP_SONIC1_DATA,(uint8*)STM32_Rece_Buf[9 ],3,READ_ONLY },   //������1�ľ���ֵ����3���ֽ�Ϊ1���������£�Ϊ0�����ݲ������µ�
		{ID_SUP_SONIC2_DATA,(uint8*)STM32_Rece_Buf[10],3,READ_ONLY },   //������2�ľ���ֵ��
		{ID_SUP_SONIC3_DATA,(uint8*)STM32_Rece_Buf[11],3,READ_ONLY },   //������3�ľ���ֵ��
		{ID_SUP_SONIC4_DATA,(uint8*)STM32_Rece_Buf[12],3,READ_ONLY },   //������3�ľ���ֵ��
		
				
		{ID_ISO_DELAY1,		(uint8*)STM32_Send_Buf[13],2,WRITE_ONLY}, 	//������巢�͵���ʱ�����ݣ�����12����˵����Ҫ��3��Ҷ�ӣ�������Ҫ3����ʱ������
		{ID_ISO_DELAY2,		(uint8*)STM32_Send_Buf[14],2,WRITE_ONLY},	//��3��������16λ����ʱʱ��
		{ID_ISO_DELAY3,		(uint8*)STM32_Send_Buf[15],2,WRITE_ONLY},
		{ID_LIDAR_CTR	,	(uint8*)STM32_Send_Buf[16],1,WRITE_ONLY}, 	
		{ID_LIDAR		,	(uint8*)STM32_Rece_Buf[17],5,READ_ONLY }, 
		
		{ID_MOTOR1		,	(uint8*)STM32_Send_Buf[18],4,WRITE_ONLY}, 	//���1 ,��3�����ֻ������ת��ֹͣ��3��״̬
		{ID_MOTOR2		,	(uint8*)STM32_Send_Buf[19],4,WRITE_ONLY}, 	//���2
		{ID_MOTOR3		,	(uint8*)STM32_Send_Buf[20],4,WRITE_ONLY}, 	//���3
		{ID_MOTOR4		,	(uint8*)STM32_Send_Buf[21],4,WRITE_ONLY},
		
		{ID_MOTOR5		,	(uint8*)STM32_Send_Buf[22],4,WRITE_ONLY},    //���5		��һ��8λ��ת����Ȧ����������8λ��ת���ĽǶ� 0~3600�ȣ�����0.1��
		{ID_MOTOR6		,	(uint8*)STM32_Send_Buf[23],4,WRITE_ONLY},
		
		{ID_MaxonConWord,   (uint8*)STM32_Send_Buf[24],2,WRITE_ONLY},   //Maxon���������()
		{ID_MaxonModeSelect,(uint8*)STM32_Send_Buf[25],1,WRITE_ONLY},   //Maxon���ѡģʽ
		{ID_Maxon1Speed,    (uint8*)STM32_Send_Buf[26],4,WRITE_ONLY},   //Maxon���1���ٶ�
		{ID_Maxon2Speed,    (uint8*)STM32_Send_Buf[27],4,WRITE_ONLY}    //Maxon���2���ٶ�
	};

/*
**Ҫ�㣺ARMͨ��12.5M��SPI�������ϵ�STM32�������ݻ����Ȼ��STM32�ٰ���Щ����ͨ��CAN����������			
**ͨ�Ź���1.ÿ�ζ���ARM��������������
**			2.�ȷ�Data_ID,����STM32��Ҫ�������ʲô�豸������
**			3.�ٸ��ݾ���������Ҫ���ͻ���յ����ݴ����
*/

/*********************************************************************************************
**�������ƣ�STM32_RW(id) STM32��д
**����������id   
**���ܲ���������һ����Ҫ20us���ң�Ҳ����˵����һ��32�ֽڵ�����Ҫ20us��ʱ��
**			���д󲿷�ʱ��������ʱ�ȴ��ϣ��������ʱ���ٴ���֤�����ܻᷢ��
**			�ܸĽ��ĵط����Ǿ͸İɣ���Ӧ��SPI�ٶ�Ϊ12.5M��
**********************************************************************************************/

void STM32_RW(uint8 id)
{
	OS_CPU_SR  cpu_sr;
	int i=0;
	uint8  Length_Temp;
	uint8* rece_data_ptr,*send_data_ptr;
	Length_Temp = STM32_Data[id].Data_Length;
	
	send_data_ptr = (uint8*)STM32_Send_Buf[id];
	rece_data_ptr = (uint8*)STM32_Rece_Buf[id];
		
	/*
	**�ȷ������ݵ�ID��ȥ���öԷ��жϽ������Ķ���
	*/
	OS_ENTER_CRITICAL();
	
	SPI1_SendData_stm32(STM32_Data[id].Data_ID);
	for(i=0;i<250;i++);   	//��ʱһ�£���STM32�������ݣ�i��ֵ��Ϊ70Ҳ���ԣ�Ϊ�˸����ȶ�������150
	while(Length_Temp--)
	{
		(*rece_data_ptr++)  =  SPI1_SendData_stm32(*send_data_ptr++);
		for(i=0;i<250;i++); //��ʱ
	}
	
	OS_EXIT_CRITICAL();
	for(i=0;i<250;i++);		//��ʱ	
}

/*****************************************************************************************
**�������ƣ�STM32_Send8
**����������id Ҫ���͵��豸ID  data��Ҫ���͵�����   
**�������������Է���8λ��64λ�����ݣ����Ƕ�Ӧ��ID��Ҫ�ͷ��͵����ݳ�����Ϻ�
**           ��Ҫ�Ǹ��̵������õġ��ϲ㺯����ñ���ã���ΪSTM32ֻ��Զ�Ӧ������
**           �����ã������ÿ��ܻ����𲻱�Ҫ�Ļ���
**           
******************************************************************************************/
void STM32_Send8(uint8 id  ,  uint8 data)
{
	uint8* dptr;
	dptr  =  STM32_Send_Buf[id];
	*dptr =  data;
	STM32_RW(id);
}



void STM32_Send16(uint8 id , uint16 data)
{
//    uint8 *dptr;
    union
    {
    	uint8 	data[2];
    	uint16	value;
    }Send16;
    Send16.value = data;
    
	STM32_Send_Buf[id][0]  = Send16.data[0];//�Ͱ�λ
	STM32_Send_Buf[id][1]  = Send16.data[1];//�߰�λ
	
//	dptr = (uint16*)STM32_Send_Buf[2];     //��ָ�������
//	*(uint16*)dptr =  data;

	STM32_RW(id);
}

void STM32_Send32(uint8 id , uint32 data)
{
    union
    {
    	uint8 	data[4];
    	uint32	value;
    }Send32;
    Send32.value = data;
    
	STM32_Send_Buf[id][0]  = Send32.data[0];
	STM32_Send_Buf[id][1]  = Send32.data[1];
	STM32_Send_Buf[id][2]  = Send32.data[2];
	STM32_Send_Buf[id][3]  = Send32.data[3];

	STM32_RW(id);
}

//ע����������������64λ���ݲ���ô֧�֣���ò�Ҫ��64λ����������
//������������32λ������
void STM32_Send64(uint8 id  ,  uint32* data)   
{
	uint8* dptr,i;
	union 
	{
		uint32 data[2];
		uint8  value[8];
	}Send64;
	dptr = STM32_Data[id].Data_Ptr;
	Send64.data[0] = *data;
	Send64.data[1] = *(++data);
	
	for(i=0;i<8;i++)
	{
		*(dptr++) = Send64.value[i];
	}

	STM32_RW(id);
}



/****************************************************************************
**�������ƣ�STM32_Reset
**������������
**�������أ���   
**����������������ذ��ϵ�STM32һ���жϣ�STM32�������Լ�
*****************************************************************************/                                                                      
void STM32_Reset(void)
{
    int i;
    rGPFDAT &= ~(0x1<<4);       //������
    rGPFDAT |= (0x1<<4);        //������
    for(i=0;i<300;i++);         //��ʱһС��
    rGPFDAT &= ~(0x1<<4);       //����
}



/******************************************************************************************
** �����ǹ��ڼ̵���������
**      		�̵��������ֿ��Ƶķ�ʽ��UART  CAN����8λ��CAN����64λ
**                      1.UART:ÿ��ֻ����һ���ڣ�
                          ��ʽ����7λ��0��ʾ��� ��1��ʾ��λ
**	                      0��5 ��6λ��ʾ��Ӧ�˿ڵĺ��룬��6λû���õ�
**		                2.CAN����8λ��   
**                        ��ʽ����UARTһ����ֻ�Ǵ��䷽ʽ��ͬ
**                      3.CAN����64λ��
**                        ÿ�ı�һ���̵����ڵ�״̬��������е�״̬������ȥ
**            ��������һ�ַ�ʽ�ǰ�״̬��¼��һ��64λ�ı����С�	
********************************************************************************************/

#define  RELAY_CAN  1   //����ʵ�����ѡ����UART����CAN����,һ����CANÿ�δ���8λ

uint32 Relay_Value[2];  //��¼�̵�����״̬
//=========================================================
//��UART��������
void Relay_Set_Uart(uint8 port)
{
	uint8 temp;
	Relay_Value[(port-1)/32] |= (uint32)1<<((port-1)%32);  //��״̬������Relay_Value[]��	
	temp = 1<<7 | (port-1);
	UART0_SendByte(temp);			
}

void Relay_Clear_Uart(uint8 port)
{
	uint8 temp;
	Relay_Value[(port-1)/32] &= ~((uint32)1<<((port-1)%32));	
	temp = 0<<7 | (port-1);
	UART0_SendByte(temp);
}
//==========================================================
//��CAN����1�ֽ�����	        
void Relay_Set_Can8(uint8 port)
{
	uint8 temp;
	Relay_Value[(port-1)/32] |= (uint32)1<<((port-1)%32); 	
	temp = 1<<7 | (port-1);
	STM32_Send8(ID_RELAY8,temp);			
}

void Relay_Clear_Can8(uint8 port)
{
	uint8 temp;
	Relay_Value[(port-1)/32] &= ~((uint32)1<<((port-1)%32));	
	temp = 0<<7 | (port-1);
	STM32_Send8(ID_RELAY8,temp);
}

//=================================================================
/************************************************************************************************
** ��������	:	Relay
** ��������	:   set  �� clear ĳ���̵����˿ڣ�����ͬʱ����������
** �䡡�� 	    :	�ĸ�������1.set_low  ��Ҫset�Ķ˿ڣ�����˿ں�С��32�����������
**				              2.set_high ��Ҫset�Ķ˿ڣ�����˿ںŴ���32С��64�����������
**                            3.clear_low��Ҫclear�Ķ˿ڣ����С����32�����������
**                            4.clear_low��Ҫclear�Ķ˿ڣ��������32С��64�����������
**                  low �� high ��32Ϊ�ֽ���
**          ʹ��ʾ������set 12  13 �ں�clear 15 ��44��62�ڣ�
**          ���������� Relay(RELAY_LOW(3)|RELAY_LOW(7),0,RELAY_LOW(15),RELAY_HIGH(44)|RELAY_HIGH(62))
** �䡡��       :	
** ע������    :ѡ��˿����������궨�壺 RELAY_LOW(port) 
**************************************************************************************************/
void  Relay(uint32 set_low ,uint32 set_high,uint32 clear_low,  uint32  clear_high)
{
	
	Relay_Value[0] |=  set_low;
    Relay_Value[1] |=  set_high;

	Relay_Value[0] &=  ~clear_low;
    Relay_Value[1] &=  ~clear_high;

	STM32_Send64(ID_RELAY64,Relay_Value);
}

void Relay_Set_Can64(uint8 port)
{
    if(port<33 && port >0)
        Relay(RELAY_LOW(port),0,0,0);
    else if(port>32 && port < 65)
        Relay(0,RELAY_HIGH(port),0,0);			
}

void Relay_Clear_Can64(uint8 port)
{
    if(port<33 && port >0)
        Relay(0,0,RELAY_LOW(port),0);
    else if(port>32 && port < 65)
        Relay(0,0,0,RELAY_HIGH(port));	
}
//==========================================================
//���̵�������
uint8 Relay_Read(uint8 port)
{
	uint8 value;
    if(port >0 && port <33)
    {
        if(Relay_Value[0] & (uint32)1<<(port-1))
            value = 1;
        else 
            value = 0;
    }else if(port >32 && port<65){
        if(Relay_Value[1] & (uint32)1<<(port-33))
            value = 1;
        else 
            value = 0;
    }
    return  value;
}

/********************************************************************
** �������ƣ�Relay_Set()  ��  Relay_Clear()
** �����������Ӧ�ļ̵�����˿ں� ��1��64
** �����������
** ע����������ͨ�õĺ����ӿڣ���õ������
**********************************************************************/

void Relay_Clear(uint8 port)
{
#if RELAY_CAN
     Relay_Clear_Can8(port);
#else 
     Relay_Clear_Uart(port);
#endif
}

void Relay_Set(uint8 port)
{
#if RELAY_CAN
     Relay_Set_Can8(port);
#else 
     Relay_Set_Uart(port);
#endif
}



/********************************************************************
** �������ƣ�UNMASK_Relay()  ��  MASK_Relay()
** ���������������ϵĽӽ����صĶ˿ں�
** �����������
** �������������Կ��ƹ����Ľӽ������Ƿ�򿪣������Զ��Խӽ����ص�
**            ���ܽ��з�Ӧ
** �÷�     ������Ҫ���� 2,3�ڣ��� MASK_ISO(ISO(2) | ISO(3))   //ISO(port)�Ǹ��궨��
**********************************************************************/
uint16  ISO_Mask_Statu = 0;

//ʹ������������ֻҪ�ӽ���Ӵ����ص�ĳ�������ﵽ��
//������ϵ�STM32����������Ӧ��������Ҫ��������
void  ISO_UNMASK(uint8 port)
{
    ISO_Mask_Statu  |=  port;
    STM32_Send16(ID_ISO_MASK,ISO_Mask_Statu);
}

//���Σ�����ʹ����������
void ISO_MASK(uint8 port)
{
    ISO_Mask_Statu  &=  ~port;
    STM32_Send16(ID_ISO_MASK,ISO_Mask_Statu);
}
//�����1��ʹ�ܣ������������Լ���������������Ӧ
uint8 ISO_Read(uint8 port)
{
	if(ISO_Mask_Statu & (uint16)1<<(port-1))
		return  1;
	else 
		return  0;
}


//�������������ISO����ʱʱ��ģ�
//port ��ȡֵ��Χ�� 1  2  3��delay_time ����ʱ��ʱ��

uint16 ISO_Delay_Time[3];

void ISO_Delay(uint8 port , uint16 delay_time)
{
	STM32_Send16(ID_ISO_DELAY1+port-1 , delay_time);
}

/********************************************************************
** �������ƣ�STM32_ReadDistance
** ���������Ҫ��ȡ���豸��ID   
			 ��ѡ�Ĳ���Ϊ��
			 �����ࣺ   ID_LASER_DATA��
			 �����ࣺ   ID_IR1_DATA  ID_IR2_DATA
			 ��������ࣺ ID_SUP_SONIC1_DATA 
			 			  ID_SUP_SONIC2_DATA
			 			  ID_SUP_SONIC3_DATA									
** ������������ؾ���ֵ
** ����������
** ע�����ÿ��ͨ�Ż᷵��3���ֽڵ�����
**           ���У�ǰ�����ֽ�Ϊuint16�ľ���ֵ����3���ֽ�Ϊ0��1 ��
**           Ϊ0���ʾ������벻�����µģ����ǻ������ã���ΪҪ�Ǿ���仯����Ļ��Ϳ�����
**           Ϊ1���ʾ����ֵ�����µģ���������ֵ����uint16�ľ���ֵ
**			������ʱû��ʹ�õ�������־ֵ
**********************************************************************/
uint16 STM32_ReadDistance(uint8 id)
{
    uint8   flag ,*ptr;
    union 
    {
        uint8   data[2];
        uint16  value;
    }distance;

	STM32_RW(id);                            //������
    ptr = STM32_Data[id].Data_Ptr;
    distance.data[0] = *ptr ;
    distance.data[1] = *(ptr+1) ;

    flag =   *(ptr+2);   //�ѵ������ֽڵ�ֵ����flag

//    if (flag ==1)      //�����־λ��ʱ���ܣ�������Ҫʹ��
        return distance.value;
//    else 
//        return 0;
}


/********************************************************************
** �������ƣ�Ranging_Start   Ranging_Stop  ��˼�ǣ���࿪ʼ��ranging�Ǵ��е����  ==��
** ���������Ҫ���Ƶ��豸��ID   
			 ��ѡ�Ĳ���Ϊ��
			 �����ࣺ   CONTROL_LASER��
			 �����ࣺ   CONTROL_IR1  CONTROL_IR2
			 ��������ࣺ CONTROL_SONIC1 
			 			  CONTROL_SONIC2
			 			  CONTROL_SONIC3									
** ������������ؾ���ֵ
** ��������������Ҫ����ʱ��ſ�ʼ��࣬����CAN���ߵ�ռ����
**     ע�⣺���������ID ��������ǲ�һ����
**********************************************************************/
volatile uint16 	Device_Statu;  	//��¼�����豸��״̬��ֻ����ARM���ã����ᴫ��STM32
									//��������������������ʵ��ʾ����ͬһ����������д��Ϊ�˴�����
volatile uint8  	CAN_Device_Control[3] = {0};  //�������ÿ���ֽڼ�¼һ���豸��״̬���������л�ֹͣ
												  //�����������豸�������࣬���⣬������

struct Struct_CAN_Device
{
	uint8  	Device_DataID;		//�豸��ID������������Ϊ�������ݵ��豸��ID�Ų�����
	uint8	Device_ControlID;
	uint8* 	Control_Ptr;    //ָ������Ŀ���״̬��ָ�룬
};

//�����Ƕ��壬�����Ǹ�ֵ��ֻ�ڽ�����������������ʹ��
struct Struct_CAN_Device  
CAN_Device[DEVICE_NUM] = {
					{ID_LASER_DATA		,	ID_LASER_CTR, 		(uint8*)&CAN_Device_Control[0]	},
					{ID_IR1_DATA		,	ID_IR_CTR, 			(uint8*)&CAN_Device_Control[1]	},
					{ID_IR2_DATA		,	ID_IR_CTR,			(uint8*)&CAN_Device_Control[1]	},
					{ID_SUP_SONIC1_DATA	,	ID_SUP_SONIC_CTR,	(uint8*)&CAN_Device_Control[2]	},
					{ID_SUP_SONIC2_DATA	,	ID_SUP_SONIC_CTR,	(uint8*)&CAN_Device_Control[2]	},
					{ID_SUP_SONIC3_DATA	,	ID_SUP_SONIC_CTR,	(uint8*)&CAN_Device_Control[2]	},
					{ID_SUP_SONIC4_DATA	,	ID_SUP_SONIC_CTR,	(uint8*)&CAN_Device_Control[2]	}
				};



void  Ranging_Start(uint16 id)
{
	uint8  i;
	Device_Statu |= id;
	CAN_Device_Control[0] |= (uint8)(id & 1);
	CAN_Device_Control[1] |= (uint8)((id>>1) & 0x3);
	CAN_Device_Control[2] |= (uint8)((id>>3) & 0xf);
	
	for(i=0; i < DEVICE_NUM ; i++){
		if((id >> i) & (uint16)1 ){   //���ѡ���˶�Ӧ��ID
		    STM32_Send8(CAN_Device[i].Device_ControlID , *(CAN_Device[i].Control_Ptr));
		    //ÿ�η��Ϳ�ʼ�����������һ��ֵ���Ǹ�ֵû���ã���Ϊ�����
		    //STM32�ķ����������� 
		    STM32_ReadDistance(CAN_Device[i].Device_DataID);                 
		}
	}
}


void  Ranging_Stop(uint16 id)
{
	uint8  i;
	Device_Statu &= ~id;
	CAN_Device_Control[0] &= ~(uint8)(id & 1);
	CAN_Device_Control[1] &= ~(uint8)((id>>1) & 0x3);
	CAN_Device_Control[2] &= ~(uint8)((id>>3) & 0xf);
	
	for(i=0; i < DEVICE_NUM ; i++){
		if((id >> i) & (uint16)1 ){   //�������˶�Ӧ��ID
		    STM32_Send8(CAN_Device[i].Device_ControlID , *(CAN_Device[i].Control_Ptr));
		    //ÿ�η��ͽ��������������һ��ֵ���Ǹ�ֵû���ã���Ϊ�����
		    //STM32�ķ����������� 
		    STM32_ReadDistance(CAN_Device[i].Device_DataID);                 
		}
	} 
}


uint8 Read_Device_Statu(uint16  id)
{
	if((Device_Statu & id) >0 )
		return 1;
	else
		return 0;
}


/*********************************************************************************************
** �������ƣ�Motor_CAN
** ���������id  cmd  
			 ��ѡ�Ĳ���Ϊ�iid :1,2
						   cmd :STOP zheng  fan //zheng  �� fan �ĸ����ְ�	
** ������������ؾ���ֵ
**********************************************************************************************/
uint8  MOTOR_STATU[4];


void Motor_CAN(uint8 id , uint8 cmd)
{
	MOTOR_STATU[id-1]  =  cmd;
	STM32_Send8( ID_MOTOR1+id-1 , MOTOR_STATU[id-1]);
}

uint8 Motor_CAN_Statu(uint8 id )
{	
	return  MOTOR_STATU[id-1];
}

//���������Կ��Ƶ��ת��Ȧ���ͽǶ�
void Motor_Position(uint8 circ , uint16 radian)
{
	//uint8 *ptr;
	union
    {
    	uint8 	data[2];
    	uint16	value;
    }Send16;
    
	
	STM32_Send_Buf[ID_MOTOR5][0]  = circ;
	Send16.value = radian;
	STM32_Send_Buf[ID_MOTOR5][1]  = Send16.data[0];
	STM32_Send_Buf[ID_MOTOR5][2]  = Send16.data[1];
	
	STM32_RW(ID_MOTOR5); 
}



/**
  * @brief  �����ص��ã�����ĳ�����תһ��Ȧ��
  * @note   
  * @param  motor:  ID_MOTOR1 ~ ID_MOTOR6
            rot:    Ҫת��Ȧ����ע�������Ǹ�����
  * @retval None
  */    

void arm_motor(uint8 motor, float rot)
{
    #define  M_FHB 1  /* faulhaber motor */
    #define  M_COM 0  /* common motor */
        
    /* ��������ͺ͵����˳��Ҫһһ��Ӧ */
    static uint8 m_type[] = {M_FHB, M_COM, M_COM, M_FHB,  M_COM,  M_FHB}; 
    
    union uPosType
    {
        uint8 d[4];    /* data */
        int v;      /* value */
    }uPos;          /* union position */
    
    if(motor>ID_MOTOR6 || motor<ID_MOTOR1)
    {
        /* add code here to report error */
        return;
    }
    
    if(m_type[motor-ID_MOTOR1] == M_FHB)
    {/* faulhaber motor */
        uPos.v = (int)(rot*2048*14);
    }
    else if(m_type[motor-ID_MOTOR1] == M_COM)
    {/* common motor */
        uPos.v = (int)(rot*2000);
    }
    
    /* send goal position data by can bus */
    STM32_Send_Buf[motor][0] = uPos.d[0];
    STM32_Send_Buf[motor][1] = uPos.d[1];
    STM32_Send_Buf[motor][2] = uPos.d[2];
    STM32_Send_Buf[motor][3] = uPos.d[3];
    
    STM32_RW(motor); 
}



/*********************************************************************************************
** �������ƣ�STM32_ReadLidarData(int ring_id)
** ���������
** ���������
**********************************************************************************************/
uint16 STM32_ReadLidarData(int ring_id)
{
    uint8   *ptr;
    //uint8 flag;
    extern fp64 Lidar_ResultX[50],Lidar_ResultY[50];
    union 
    {
        uint8   data[2];
        uint16  value;
    }distance;

	STM32_RW(ID_LIDAR);
	
    ptr = STM32_Data[ID_LIDAR].Data_Ptr;
    distance.data[0] = *ptr ;
    distance.data[1] = *(ptr+1) ;
	Lidar_ResultX[ring_id]=distance.value;

    distance.data[0] = *(ptr+2) ;
    distance.data[1] = *(ptr+3) ;
	Lidar_ResultY[ring_id]=distance.value;	
	
	return *(ptr+4);
}



/*********************************************************************************************
** �������ƣ�Maxon�������
** ���������
** ���������
**********************************************************************************************/
void MaxonEnable(void)
{
   STM32_Send16(ID_MaxonConWord,MAXONENALBE);
}

void MaxonDisable(void)
{
   STM32_Send16(ID_MaxonConWord,MAXONDISABLE);
}

void MaxonQuickstop(void)
{
   STM32_Send16(ID_MaxonConWord,MAXONQUICKSTOP);
}

void MaxonSpeedMode(void)
{
   STM32_Send16(ID_MaxonModeSelect,MAXONSPEEDMODE);
}

void MaxonFaultReset(void)
{
   STM32_Send16(ID_MaxonModeSelect,0x0080);
}

void Maxon1SetSpeed(double speed)
{
   int32 tempspeed;
   if(-5000<=speed<=5000)
   {
      tempspeed=(int32)speed;
      STM32_Send32(ID_Maxon1Speed,tempspeed);
   }
}

void Maxon2SetSpeed(double speed)
{
   int32 tempspeed;
   if(-5000<=speed<=5000)
   {
      tempspeed=(int32)speed;
      STM32_Send32(ID_Maxon2Speed,tempspeed);
   }
}


/***********************************************************************************************
**                            End Of File
*************************************************************************************************/