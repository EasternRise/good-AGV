#include "all.h"
#include "obstacle.h"

//���������߼�
//ͨ���Ÿ����ı�����˵�״̬
//ͨ��move_car���Ƶ��̵���˶�
//ͨ���˵�������Ŀ�����趨
//�����ж����

u8 col_error=0;

int main(void)
{ 
    InitAll();
	
	
	col_error=0;
	//����
	low_ele=0;
	
	my_robot=unloacted;
	
	{
			LCD_Clear();
		  
	//		ShowMenuList();
			LCD_Welcom();		
	/*		while(1)
			{
					if (KeyReady==1)
					{ 
							KeyReady=0;
							KeyNumOperate(KeyValue);	
							
					}
					refresh();
					
					delay(10);
			}*/
	}
}
