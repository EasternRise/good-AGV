#include "All.h"
#if ManualSetting

uint8 Route_Num=0;
uint8 ManualData[11];//ǰ���ֽڴ����ݣ���ʮ�ֽ��жϳ�������
uint8 FBonly_flag=0;
uint8 SA2_en=1;
//�ֱ���ֵ�ٶȣ���Speed_F���ϵõ����ٶȣ���ɺ�Ҫ���ԭFaulHaber_speed_FL
fp32 Manual_speed_FL=0;			//�ֶ���ǰ���ٶ�
fp32 Manual_speed_FR=0;			//�ֶ���ǰ���ٶ�
fp32 Manual_speed_BL=0;			//�ֶ�������ٶ�
fp32 Manual_speed_BR=0;			//�ֶ��Һ����ٶ�
 
void TaskManual(void *pdata)
{
	//uint8 auto_flag=0;
	int16 Speed_UP_DOWN;					//�洢�ֱ������ٶ�ֵ
	int16 Speed_LEFT_RIGHT;
	int16 Speed_TURN;
	
	fp64  Speed_UD;							//�洢ת�����ٶ�ֵ
	fp64  Speed_LR;
	fp64  Speed_T;
	
	uint8 temp;								//����ж�ManualData[10]
	fp32 mutiple=1.0;
	//static uint8 flag=0;
	
	fp32 Rotation[6]={0};//����6�������λ����Ϣ
	
	OSTimeDly(100);
	MaxonDisable();
	OSTimeDly(10);
	MaxonEnable();
	OSTimeDly(10);
	MaxonSpeedMode();
	
	for(;;)
	{
		temp=ManualData[10];
		FPGA_ReadManual(ManualData);
		if(ManualData[10]!=temp)			//�ֱ���������
		{
			time_flag=0;
			//ҡ�˶������ٶ�
			Speed_UP_DOWN=((uint16)ManualData[2]<<8)+(uint16)ManualData[1];
			
			if(Speed_UP_DOWN>=0x3000)
    		 	Speed_UD = (fp64)(Speed_UP_DOWN-0x3000)/1.5;
			else
				Speed_UD = (fp64)(Speed_UP_DOWN-0x3000)/1.5;
						
			Speed_LEFT_RIGHT=((uint16)ManualData[4]<<8)+(uint16)ManualData[3];
		
			if(Speed_LEFT_RIGHT>=0x3000)
				Speed_LR = -(fp64)(Speed_LEFT_RIGHT-0x3000)/1.5;
			else
				Speed_LR = -(fp64)(Speed_LEFT_RIGHT-0x3000)/1.5;
						
			Speed_TURN=((uint16)ManualData[6]<<8)+(uint16)ManualData[5];
		
		 	if(Speed_TURN>=0x3000)
    		   	Speed_T = (fp64)(Speed_TURN-0x3000)/8.0;
    		else
    		   	Speed_T = (fp64)(Speed_TURN-0x3000)/8.0;
    		
    		if(FBonly_flag==1)
    		{
    			Speed_LR=0;
    			Speed_T =0;
    		}
    		//�����ٶȷֽ�
			Manual_speed_FL=(5.53859*Speed_LR)*mutiple;
			Manual_speed_FR=(5.53859*Speed_LR)*mutiple;
			Manual_speed_BL=(0.09095*Speed_UD-0.28648*Speed_LR)*mutiple;
			Manual_speed_BR=(0.09095*Speed_UD+0.28648*Speed_LR)*mutiple;
			
			if(Button8_On)
			{
				Manual_speed_FL=Manual_speed_FL/10;
				Manual_speed_FR=Manual_speed_FR/10;
				Manual_speed_BL=Manual_speed_BL/10;
				Manual_speed_BR=Manual_speed_BR/10;
			}
			
    		Speed_Motor((Speed_F+Manual_speed_FL), (Speed_FR+Manual_speed_FR), (Speed_BL+Manual_speed_BL),(Speed_BR+Manual_speed_BR));	
		  	
		  	error_convert[0] = Manual_speed_FL/14000;
		  	error_convert[1] = Speed_F/14000;
		  	error_convert[2] = Manual_speed_FR/14000;
		  	error_convert[3] = Speed_FR/14000;
		  	error_convert[4] = Manual_speed_BL/14000;
		  	error_convert[5] = Speed_BL/14000;
		  	error_convert[6] = Manual_speed_BR/14000;
		  	error_convert[7] = Speed_BR/14000;
		  	
		  	
		  	//�ϲ㶯��

		  	
		  	//����1֮�⣬�����������Ƶ�ŷ�

		  	if(Button2_Up && Button7_Off)
			{
				Relay_Clear(24);
			}
			
			if(Button2_Down && Button7_Off)
			{
				Relay_Set(24);
			}

			if(Button3_Up && Button7_Off)
			{
				Relay_Set(23);
			}
			
			if(Button3_Down && Button7_Off)
			{
				Relay_Clear(23);
			}

			if(Button4_Up && Button7_Off)
			{
				Relay_Clear(22);
				Relay_Set(21);
			}
			
			if(Button4_Down && Button7_Off)
			{
				Relay_Clear(21);
				Relay_Set(22);
			}

			if(Button5_Up && Button7_Off)
			{
				Relay_Clear(19);
				Relay_Set(20);				
			}
			
			if(Button5_Down && Button7_Off)
			{
			    Relay_Clear(20);
				Relay_Set(19);
;
			}
			
			

			
			
			//7��Ϊ�ڶ����ܼ�������1����ϼ������ϲ���
			
			if(Button1_Up && Button7_On)
			{
			    Rotation[0]+=0.05;
				arm_motor(ID_MOTOR1 , Rotation[0]);
			}
			
			if(Button1_Down && Button7_On)
			{
			    Rotation[0]-=0.05;
				arm_motor(ID_MOTOR1 , Rotation[0]);
			}
			
			if(Button2_Up && Button7_On)
			{
			    Rotation[1]+=0.05;
				arm_motor(ID_MOTOR2 , Rotation[1]);
			}
			
			if(Button2_Down && Button7_On)
			{
			    Rotation[1]-=0.05;
				arm_motor(ID_MOTOR2 , Rotation[1]);
			}		
			
			if(Button3_Up && Button7_On)
			{
			    Rotation[2]=1;
				arm_motor(ID_MOTOR3 , Rotation[2]);
			}
			
			if(Button3_Down && Button7_On)
			{
			    Rotation[2]=-1;
				arm_motor(ID_MOTOR3 , Rotation[2]);
			}
	        
	       /* if(Button3_Off)
			{
			    Rotation[2]=0;
				arm_motor(ID_MOTOR3 , Rotation[2]);
			}*/


			if(Button6_Left && Button7_On)
			{
			    Rotation[5]-=0.05;
				arm_motor(ID_MOTOR6 , Rotation[5]);
			}
			
			if(Button6_Right && Button7_On)
			{
			    Rotation[5]+=0.05;
				arm_motor(ID_MOTOR6 , Rotation[5]);
			}	
				
			/*
			//�Զ���������
			if(Button6_Off)
				auto_flag=0;
			if((auto_flag==0) && Button8_On && Button6_Right)
			{
				auto_flag=1;
				if (Route_Num<=7)
				{
					Route_Num++;
					OSMboxPost(AutoMbox,&Route_Num);
					OSMboxPost(ArmMbox,&Route_Num);
				}
			
			}*/
			
		}
		else			//�ֱ����߻��������쳣
		{
		    if(time_flag>200)//time_flag��ʱ����м����������ʱ�����һ��ֵ�����������
						 	 //��Ҫ������ֹ�ֱ�����arm�ֿ�ʱ�����ܡ����߷ֿ�ʱ��1s���Զ�ͣ��
		    {
                  Speed_F=0;
                  Speed_FR=0;
                  Speed_BL=0;
                  Speed_BR=0;
                  
			      Acc_Limit_enable=0;
			      Speed_Motor(0,0,0,0);
			      Acc_Limit_enable=1;
			      
			      OSTaskDel(RoutePrio);	
			      OSTaskCreate (TaskRoute ,  (void *)0,  &TaskRouteStk[TaskStkLengh -1],RoutePrio);
		    }       
		 }
		 
		 OSTimeDly(1);
	}
}			

#endif			
		
		
		
		
		
		
		