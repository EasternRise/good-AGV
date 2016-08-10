#include "all.h"

void TaskPathSel (void *pdata)
{
	uint8  err;
	uint8  *msg;	
	pdata = pdata;
		
	for(;;)
	{
		msg = OSMboxPend(AppStartMbox,0,&err);//ָ��Menu_Selectindex
#if HaltSetting
		if(*msg==0xff)//����������������ʹ�ù����������������䷢���ݣ�����ֹͣ����ֹͣ����
			continue;//��ʱ�������Զ����У���Ӧ������龰�����ǵõ���key[1]�ĵ�ǰֵ��Ҳ���˳�����ֵ
#endif
		LCD_Clear();
		LCD_SetXY(0,0);
		switch(Display_Page)
		{   
			case MENU:
				Display_Page=APPLICATION;
				(*Menu[*msg-1].entry)();//����Menu����Ӧ�ĺ���
			break;
			case SUBMENU1:
				Display_Page=APPLICATION;
				(*SubMenu1[*msg-1].entry)();//����SubMenu1����Ӧ�ĺ���
			break;
			case SUBMENU2:
				Display_Page=APPLICATION;
				(*SubMenu2[*msg-1].entry)();//����SubMenu2����Ӧ�ĺ���
			break;
			case SUBMENU3:
				Display_Page=APPLICATION;
				(*SubMenu3[*msg-1].entry)();//����SubMenu3����Ӧ�ĺ���
			break;
			case SUBMENU4:
				Display_Page=APPLICATION;
				(*SubMenu4[*msg-1].entry)();//����SubMenu4����Ӧ�ĺ���
			break;
			case SUBMENU5:
				Display_Page=APPLICATION;
				(*SubMenu5[*msg-1].entry)();//����SubMenu5����Ӧ�ĺ���
			break;
			case SUBMENU6:
				Display_Page=APPLICATION;
				(*SubMenu6[*msg-1].entry)();//����SubMenu6����Ӧ�ĺ���
			break;
			case SUBMENU7:
				Display_Page=APPLICATION;
				(*SubMenu7[*msg-1].entry)();//����SubMenu7����Ӧ�ĺ���
			break;
			case SUBMENU8:
				Display_Page=APPLICATION;
				(*SubMenu8[*msg-1].entry)();//����SubMenu8����Ӧ�ĺ���
			break;
		}
	}
}