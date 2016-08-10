#include "all.h"

void TaskLcdDisplay(void *pdata)
{
	uint8 err; 
	uint8 *msg;
	static uint8 DisplayFlag=0; 
	pdata=pdata;
	
	if(DisplayFlag==0)//��ֻ�е�һ�����и�����ʱ�Ž��г�ʼ������
	{
		DisplayFlag=1;
		Display_Page=APPLICATION;
		
#if GyroFloatSetting
		LCD_Clear();
		LCD_SetXY(0,0);
		LCD_WriteString("Robot Team 13th");
		
	#if WalkGroundEnable
			LCD_SetXY(0,6);
			LCD_WriteString("Red Test");
	#else
			LCD_SetXY(0,6);
			LCD_WriteString("Red Contest");
	#endif
	
		if(rGSTATUS2 & 0x4)
		{
			
		}
		else
		{
			GYRO_CheckFloat();	//ֻ����������ʱ�ż����������Ư
			Sonic_Start=1;
		}
#endif

		if(rGSTATUS2 & 0x4)
		{
			DISPLAY_Message("Watch Dog Reset");
		}
		else if(rGSTATUS2 & 0x2)
		{
			DISPLAY_Message("wakeup reset");
		}

		Display_Page=StartPage;
		LCD_Clear();
		GPS_Clear();
	}
	
	for(;;)
	{
		
		switch(Display_Page)
		{
			case MENU://����˵���ʾ����
			case SUBMENU1:
			case SUBMENU2:
			case SUBMENU3:
			case SUBMENU4:
			case SUBMENU5:
			case SUBMENU6:
			case SUBMENU7:
			case SUBMENU8:
			case SHORTCUTMENU:
				DISPLAY_ShowMenu();
			break;
#if ShortcutSetting
			case SHORTCUTAPP://������ʾ������shortcut��Ķ̳���
				(*ShortcutMenu[*msg-1].entry)();//����ShortcutMenu����Ӧ�ĺ���
			break;
#endif
			default:
			break;
		}
		msg = OSMboxPend(MenuMbox,0,&err);		
		
	}
}