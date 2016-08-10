#include "all.h"
#include "stdarg.h"

//�洢��ǰҺ������ʾ����
uint8_t LCD_Table[LCD_LEN];
uint8_t LCD_Index=0;




void LCD_PushByte(uint8_t data)		//����һ���ַ�
{
	LCD_Table[LCD_Index]=data;
	if(LCD_Index >= (LCD_LEN-1))
		LCD_Index=0;
	else
		LCD_Index++;
}

void LCD_PushString(char *data)		//����һ���ַ���
{
	while(*data)
	{
		LCD_PushByte(*data++);
	}
}

// void LCD_Printf(const char *fmt,...)
// {
//     va_list ap;
//     char string[LCD_LEN];

//     va_start(ap,fmt);
//     vsprintf(string,fmt,ap);
//     va_end(ap);
// 	LCD_PushString(string);

// }
// void UART0_Printf(const char *fmt,...)
// {
//     va_list ap;
//     char string[LCD_LEN];

//     va_start(ap,fmt);
//     vsprintf(string,fmt,ap);
//     va_end(ap);
// 	UART0_SendString(string);

// }

void LCD_SetXY(int x,int y)
{
	LCD_Index=x+y*20;
}

void LCD_WriteChar(char data)
{
	LCD_PushByte(data);
}

void LCD_WriteString(char *data)
{
	LCD_PushString(data);
}

void LCD_WriteInt(int data)//д�������ӵ�λ���λд
{
	char answer[100];
	int index=98;
	int pose=0;//�����ű�־��
	if(data<0)
	{
		pose=1;
		data=-data;
	}
	answer[99]='\0';//���λ�洢������־
	while(data>9)//�洢����λ
	{
		answer[index--]=data%10+'0';
		data=data/10;
	}
	answer[index]=data+'0';
	if(pose)//�洢������
	{
		answer[--index]='-';
	}
	LCD_PushString(answer+index);//д��������
}

void LCD_WriteDouble(double data,int m)//дdouble������mΪС�����λ�����Ӹ�λ���λд
{
	if(data<0&&data>-1)
		LCD_WriteChar('-');//д����
	LCD_WriteInt((int)data);//д��������
	if(m>0)
	{
		int i;
		LCD_WriteChar('.');//дС����
		if(data<0)
			data=-data;
		data=data-(int)data;
		for(i=0;i<m;i++)//дС������
		{
			data=data*10;
			LCD_WriteChar((int)data+'0');
			data=data-(int)data;
		}
		
	}
	
}


void LCD_WriteNum(double data)//дdouble������С�������6λ���Ӹ�λ���λд
{
	char str[5];
	int flag=0,i;
	if(data<0)
	{
		LCD_WriteChar('-');//д����
		data=-data;
	}
	LCD_WriteInt((int)data);//д��������
	data=data-(int)data;
	for(i=0;i<5;i++)//��С�����ֱ�����һ���ַ�����
	{
		data=data*10;
		str[i]=(int)data+'0';
		if(str[i]!='0')
		{
			flag=i+1;
		}
		data=data-(int)data;
		
	}
	if(flag!=0)
		LCD_WriteChar('.');//дС����
	for(i=0;i<flag;i++)
	{
		LCD_WriteChar(str[i]);//дС������
	}	
	for(i=flag;i<6;i++)
	{
		LCD_WriteChar(' ');//С����󲻹�6λ�򲹿ո�
	}
}

void LCD_WriteCharXY(char data,int x,int y)
{
	LCD_SetXY(x,y);
	LCD_PushByte(data);
}

void LCD_WriteStringXY(char *data,int x,int y)
{
	LCD_SetXY(x,y);
	LCD_PushString(data);
}

void LCD_WriteIntXY(int data,int x,int y)
{
	LCD_SetXY(x,y);
	LCD_WriteInt(data);
}

void LCD_WriteDoubleXY(double data,int m,int x,int y)
{
	LCD_SetXY(x,y);
	LCD_WriteDouble(data, m);
}

void LCD_WriteNumXY(double data,int x,int y)
{
	LCD_SetXY(x,y);
	LCD_WriteNum(data);
}

void LCD_Clear(void)//����ʱ��ͬʱ�������(0,0)
{
	//LCD_WriteChar(12);//������������ʱΪ��LCD_PushByte()�������Լ�¼LCD����
	LCD_WriteStringXY("                                                                                ",0,0); 
	LCD_WriteStringXY("                                                                                ",0,4); 

	LCD_SetXY(0,0);
}

void LCD_Clear_Line(u8 C_line)
{
	LCD_WriteStringXY("                    ",0,C_line); 
}

void LCD_Clear_Forward(u8 L_count)
{
	char i=0;
	for(i=0;i<L_count;i++)
	{
		LCD_Clear_Line(i);
	}
}


/*********************************************
*	*	uart����Է�������
********************************************/

void WriteChar(char data)
{
	UART3_SendByte(data);
}

void WriteString(char *data)		//����һ���ַ���
{
	while(*data)
	{
		WriteChar(*data++);
	}
}

void WriteInt(int data)//д�������ӵ�λ���λд
{
	char answer[100];
	int index=98;
	int pose=0;//�����ű�־��
	if(data<0)
	{
		pose=1;
		data=-data;
	}
	answer[99]='\0';//���λ�洢������־
	while(data>9)//�洢����λ
	{
		answer[index--]=data%10+'0';
		data=data/10;
	}
	answer[index]=data+'0';
	if(pose)//�洢������
	{
		answer[--index]='-';
	}
	WriteString(answer+index);//д��������
}

void WriteDouble(double data,int m)//дdouble������mΪС�����λ�����Ӹ�λ���λд
{
    //��дWriteDouble���� ��ʹ���β�m
// 	if(data<0&&data>-1)
// 		WriteChar('-');//д����
// 		WriteInt((int)data);//д��������
// 	if(m>0)
// 	{
// 		int i;
// 		WriteChar('.');//дС����
// 		if(data<0)
// 			data=-data;
// 		data=data-(int)data;
// 		for(i=0;i<m;i++)//дС������
// 		{
// 			data=data*10;
// 			WriteChar((int)data+'0');
// 			data=data-(int)data;
// 		}
// 		
// 	}
    	unsigned char* pdata;
		unsigned char i = 0;
        float w_data;
        w_data=(float)data;
        pdata = (unsigned char *)&w_data;
        for(i = 0;i < 4;i ++)
		{
			USART_SendData(USART3, * (pdata + i));
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);    
		}
	
}

//4��20�й�80��Ԫ��ÿ10����ԪΪһ��ˢ��
//Һ����д20�У�8��;��0�п�ʼ����0�п�ʼ

void refresh(void)
{
    {
    RefreshDma();
    }
}

void refresh_slow(void)
{
    static	char send_flag=0;
    
    if(send_flag%10==0)
    {
        RefreshDma(); 
    }
    send_flag++;
}
void RefreshDma(void)
{
    
    static	int m=0;
    
    UART3_SendByte(0xff);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);    
    UART3_SendByte(30*(m/2)+(m%2)*10);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);    

    DMA_Cmd(DMA1_Channel2, DISABLE );  //??USART1 TX DMA1 ??????   
    DMA1_Channel2->CMAR = (uint32_t)&LCD_Table[10*m];
 	DMA_SetCurrDataCounter(DMA1_Channel2,10);//DMA???DMA?????
 	DMA_Cmd(DMA1_Channel2, ENABLE);  //??USART1 TX DMA1 ?????? 
    
    if(m>=15)
        m= 0;
    else
        m++;
}






