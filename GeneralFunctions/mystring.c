
/* Includes ------------------------------------------------------------------*/
#include "string.h"
#include "includes.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
char DataConvBuff[25] = {0};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
 * ������: Int2Str
 * ��  ��: ����ת��Ϊ�ַ���
 * ��  ��: -IntData ��������
 * ��  ��: �ַ���ָ��
 * ��  ��: �ⲿ����
 */
char *Int2Str(int IntData)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = DataConvBuff;

    if (!IntData)
    {
        *ptr++ = 0x30;     
        *ptr = 0;       
        return DataConvBuff;
    }
    
    if (IntData < 0)
    {
        *ptr++ = '-';  
        IntData *= -1;
    }
    
    for (i = 1000000000; i > 0; i /= 10)
    {
        d = IntData / i;
        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);     
            IntData -= (d * i);     
            flag = 1;
        }
    }
    *ptr = 0;

    return DataConvBuff;
}


/*
 * ������: Float2Str
 * ��  ��: ������ת��Ϊ�ַ���
 * ��  ��: -FloatData ������
 *         -PointNum Ҫ������С��λ��
 * ��  ��: �ַ���ָ��
 * ��  ��: �ⲿ����
 */
char *Float2Str(float FloatData, int PointNum)
{
	char *ptr = DataConvBuff;
    char *temp;
    
    if(FloatData<0 && FloatData>-1)
		*ptr++ = '-';
    
    /*���������ִ���*/
    temp = Int2Str((int)FloatData);
	strcpy(ptr, temp);
    ptr += strlen(temp);
	
    /*��С�����ִ���*/
    if(PointNum>0)
	{
		int i;
		*ptr++ = '.';
		if(FloatData<0)
            {FloatData = -FloatData;}
		FloatData=FloatData-(int)FloatData;
		for(i=0; i<PointNum; i++)
		{
			FloatData *=  10;
			*ptr++     =  ((int)FloatData+'0');
			FloatData  =  FloatData - (int)FloatData;
		}
		*ptr = '\0';
	}
    return DataConvBuff;
}

/*
 * ������: GetSimpFile
 * ��  ��: �õ�__FILE__���ļ�·�������һ���ļ�
 * ��  ��: 
 * ��  ��: �ַ���ָ��
 * ��  ��: �ⲿ����
 * ˵  ��: ���磺__FILE__ == "application\menuSys\MenuFunc.c",�򷵻ء�MenuFunc.c��
 */
char *GetSimpFile(char *str)
{
    char *ptr = str;
    
    /*ָ����ַ��������һ���ַ�*/
    ptr += strlen(str) - 1;
    for(; ptr-str>0; ptr--)
        {if(*ptr == '\\')    break;}
        
    return ++ptr;
}
