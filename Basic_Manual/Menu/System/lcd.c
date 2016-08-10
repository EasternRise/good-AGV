#include "all.h"

uint8 LCD_Table[LCD_LEN];
uint8 LCD_Index=0;

#if LCDBufferSetting
uint8 LCDTable[20][8];		//�洢��ǰҺ������ʾ����
uint8 LCDTableSave[20][8];	//�洢����shortcutʱ�û�������ʾ����
uint8 LCDIndex=0;			//�洢��ǰLCD����ֵ
uint8 LCDIndexSave;			//�洢����shortcutʱ�û���������ֵ
#endif

#if HaltSetting
uint8 HaltFlag=0;			//��ͣ��־λ��1��ͣ��0����
uint8 HaltBuffer[5]="    ";	//���½���ʾhaltʱ���洢��Ӧ��ʾ��LCD�ַ�
#endif

void LCD_PushByte(uint8 data)		//����һ���ַ�
{
#if HaltSetting
	uint8 StringHalt[5]="halt";
	if(HaltFlag==1 && LCDIndex>75 && LCDIndex<80)
	{
		if(data>=0x20 && data<=0x7e)
		{
			UART1_TxBuffer[UART1_TxBufferTop++]=StringHalt[LCDIndex-76];
			HaltBuffer[LCDIndex-76]=data;
			LCDIndex++;
			if(LCDIndex==LCD_LEN)
				LCDIndex=0;
			return;
		}
	}
#endif
	LCD_Table[LCD_Index]=data;
	if(LCD_Index==LCD_LEN-1)
		LCD_Index=0;
	else
		LCD_Index++;
	//UART1_TxBuffer[UART1_TxBufferTop++]=data;
#if LCDBufferSetting
	if(data>=0x20 && data<=0x7e)	//�����������ַ�
	{
		LCDTable[LCDIndex%20][LCDIndex/20]=data;
		LCDIndex++;
		if(LCDIndex==LCD_LEN)
			LCDIndex=0;
	}
#endif
	//UNMASKSubIrq(BIT_SUB_TXD1);
}

void LCD_PushString(char *data)		//����һ���ַ���
{
	while(*data)
	{
		LCD_PushByte(*data++);
	}
}

void LCD_Printf(const char *fmt,...)
{
    va_list ap;
    char string[LCD_LEN];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    va_end(ap);
	LCD_PushString(string);

}
void UART0_Printf(const char *fmt,...)
{
    va_list ap;
    char string[LCD_LEN];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    va_end(ap);
	UART0_SendString(string);

}
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

#if LCDBufferSetting

void LCD_Save()//�洢LCDҳ��
{
	int i,j;
	for(i=0;i<8;i++)
		for(j=0;j<20;j++)
			LCDTableSave[j][i]=LCDTable[j][i];//����ǰLCD��ʾ���ݴ���
	LCDIndexSave=LCDIndex;//����ǰLCD��������
#if HaltSetting
	if(HaltFlag==1)//��ͣ״̬ʱ�����������½ǵı�־"halt"�����Ǵ��뱾Ӧ��ʾ��ֵ
	{
		LCDTableSave[16][3]=HaltBuffer[0];
		LCDTableSave[17][3]=HaltBuffer[1];
		LCDTableSave[18][3]=HaltBuffer[2];
		LCDTableSave[19][3]=HaltBuffer[3];
	}
#endif
}

void LCD_Load()//���ش洢��LCDҳ��
{
	int i,j;
	LCD_Clear();
	for(i=0;i<8;i++)
		for(j=0;j<20;j++)
		{
			LCD_WriteChar(LCDTableSave[j][i]);//д�洢��LCDҳ������
		}
	LCD_SetXY(LCDIndexSave%20,LCDIndex/20);//���¶�λ��ǰLCD����λ��
	//LCDIndex=LCDIndexSave;
}

#endif

void LCD_Clear()//����ʱ��ͬʱ�������(0,0)
{
	//LCD_WriteChar(12);//������������ʱΪ��LCD_PushByte()�������Լ�¼LCD����
	LCD_WriteStringXY("                                                                                ",0,0); 
	LCD_WriteStringXY("                                                                                ",0,4); 

	LCD_SetXY(0,0);
}



