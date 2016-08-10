
/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include <math.h>

#if DataBackEnable
/*********��������ص�����ΪDataBack_Xxx���������������ΪBackDataXxx��*********/

#define BackDataNum 15

static int BackDataCount = 0;
double BackData[3000][BackDataNum];

/*
 * ������: DataBack_Write
 * ��  ��: ������ת��Ϊ������λ��Ч���ֵ���������������ָ����ʽ��������520.1314������5201��-1
 * ��  ��: Ҫ���͵�����
 * ��  ��: ��
 * ��  ��: �ڡ��ⲿ����
 */
void DataBack_Write(double data)
{
	union u16_u8
	{
		int16_t value;
		uint8_t data[2];
	}temp;
	
	uint8_t data_pow = (uint8_t)log10(fabs(data)) - 3;
	temp.value = (int16_t)(data/pow(10.0,data_pow));	//ȡ��λ��Ч����
	
	Com_SendByte(2,temp.data[0]);
	Com_SendByte(2,temp.data[1]);
	Com_SendByte(2,data_pow);
}

/*
 * ������: DataBack_Send
 * ��  ��: ��������
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void DataBack_Send()
{
	int i,j;
	for(i=0;i<BackDataCount;i++)
		for(j=0;j<BackDataNum;j++)
		{
			DataBack_Write(BackData[i][j]);
			Delay_ms(10);
		}
}

/*
 * ������: DataBack_Init
 * ��  ��: ���ݻش���ʼ��
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void DataBack_Init()
{
	BackDataCount = 0;
}

/*
 * ������: DataBack_Save
 * ��  ��: ��������
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void DataBack_Save()
{
	if(BackDataCount <= 30000)
	{
		BackData[BackDataCount][0]  = 0;
		BackData[BackDataCount][1]  = 0;
		BackData[BackDataCount][2]  = 0;
		BackData[BackDataCount][3]  = 0;
		BackData[BackDataCount][4]  = 0;
		BackData[BackDataCount][5]  = 0;
		BackData[BackDataCount][6]  = 0;
		BackData[BackDataCount][7]  = 0;
		BackData[BackDataCount][8]  = 0;
		BackData[BackDataCount][9]  = 0;
		BackData[BackDataCount][10] = 0;
		BackData[BackDataCount][11] = 0;
		BackData[BackDataCount][12] = 0;
		BackData[BackDataCount][13] = 0;
		BackData[BackDataCount][14] = 0;
		
		BackDataCount++;		
	}
}

/*
 * ������: DataBack_GetCount
 * ��  ��: ����һ����¼�˶���������
 * ��  ��: ��
 * ��  ��: һ����¼�˶���������
 * ��  ��: �ⲿ����
 */
int DataBack_GetCount()
{
	return BackDataCount;
}

#endif

/**********************************END OF FILE*********************************/
