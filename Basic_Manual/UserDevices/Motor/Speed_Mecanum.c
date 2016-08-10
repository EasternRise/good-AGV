#include "all.h"
#ifndef WheelSelectSetting
////////////////////////��ȫ����////////////////////////////////////////////////////////////////////////


 fp32  Speed_F =0;                      //�洢ǰ�����ֵ��ٶ�ֵ
 
 fp32  Speed_FR=0;                      //�洢ǰ���ֵ��ٶ�ֵ
 
 fp32  Speed_BL=0;                     //�洢�������ֵ��ٶ�ֵ
 
 fp32  Speed_BR=0;                     //�洢�������ֵ��ٶ�ֵ
 
 fp64   MaxAcc=50.0;                  //�洢�����ٶ�ֵ
	

////////////////////////////////����ǰ��ֱ������У��ϵ��////////////////////////////////////////////////////


fp64  Motor_FL_Argument_Ford = 1.0;

fp64  Motor_FR_Argument_Ford = 1.0;

fp64  Motor_BL_Argument_Ford = 1.0;

fp64  Motor_BR_Argument_Ford = 1.0;


////////////////////////////////���Ӻ���ֱ������У��ϵ��////////////////////////////////////////////////////


fp64  Motor_FL_Argument_Back = 1.0;

fp64  Motor_FR_Argument_Back = 1.0;

fp64  Motor_BL_Argument_Back = 1.0;

fp64  Motor_BR_Argument_Back = 1.0;


////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Speed_Motor(fp64 speed_FL,fp64 speed_FR,fp64 speed_BL,fp64 speed_BR)
{


 	fp64  speed_fl_delta;                   //�洢ǰ���ֵ��ٶ�ֵ��������
 	fp64  speed_fr_delta;                   //�洢ǰ���ֵ��ٶ�ֵ��������
 	fp64  speed_bl_delta;                   //�洢�����ֵ��ٶ�ֵ��������
 	fp64  speed_br_delta;                   //�洢�����ֵ��ٶ�ֵ��������
 
 	fp64  speed_delta_max;                  //�洢�ٶȱ仯�����ֵ
 	fp64  Max_Acc=MaxAcc;             		//�洢�����ٶ�ֵ
 
 	fp64  PWM_Max;							//�洢�ĸ�PWMֵ������һ��
 
 	static fp64     Speed_FL_Now = 0;      	//�洢ǰ���ֱ��ε�Ŀ���ٶ�
 	static fp64     Speed_FR_Now = 0;      	//�洢ǰ���ֱ��ε�Ŀ���ٶ�
 	static fp64     Speed_BL_Now = 0;       //�洢�����ֱ��ε�Ŀ���ٶ�
 	static fp64     Speed_BR_Now = 0;       //�洢�����ֱ��ε�Ŀ���ٶ�
 
 	static fp64     Speed_FL_Last = 0;    	//�洢ǰ�����ϴε�Ŀ���ٶ�
 	static fp64     Speed_FR_Last = 0;    	//�洢ǰ�����ϴε�Ŀ���ٶ�
 	static fp64     Speed_BL_Last = 0;      //�洢�������ϴε�Ŀ���ٶ�
 	static fp64     Speed_BR_Last = 0;      //�洢�������ϴε�Ŀ���ٶ�
 
 	static fp64 	PWM_FL = 0.5;			//�洢ǰ���ֵ�ռ�ձ�
 	static fp64 	PWM_FR = 0.5;			//�洢ǰ���ֵ�ռ�ձ�
 	static fp64		PWM_BL = 0.5;			//�洢�����ֵ�ռ�ձ�
 	static fp64		PWM_BR = 0.5;			//�洢�����ֵ�ռ�ձ�
 
 
 /***************************************�������ٶȽ�������*****************************************/
 /****************************************************************************************************/
 
 
	Speed_FL_Now = speed_FL;
	Speed_FR_Now = speed_FR;
   	Speed_BL_Now = speed_BL;
    Speed_BR_Now = speed_BR;
 
 
 	speed_fl_delta = Speed_FL_Now-Speed_FL_Last;
 	speed_fr_delta = Speed_FR_Now-Speed_FR_Last;
 	speed_bl_delta = Speed_BL_Now-Speed_BL_Last;
 	speed_br_delta = Speed_BR_Now-Speed_BR_Last;
 
 
 	speed_delta_max=Max(Fp64Abs(speed_fl_delta),Fp64Abs(speed_fr_delta),Fp64Abs(speed_bl_delta),Fp64Abs(speed_br_delta));


    if((speed_delta_max >= Max_Acc) && (Acc_Limit_enable==1))
    {
     	Speed_FL_Last += Max_Acc*(speed_fl_delta/speed_delta_max);
     	Speed_FR_Last += Max_Acc*(speed_fr_delta/speed_delta_max);
        Speed_BL_Last += Max_Acc*(speed_bl_delta/speed_delta_max);
        Speed_BR_Last += Max_Acc*(speed_br_delta/speed_delta_max);
    }
  	else if((speed_delta_max <= -Max_Acc) && (Acc_Limit_enable==1))
   	{
     	Speed_FL_Last -= Max_Acc*(speed_fl_delta/speed_delta_max);
     	Speed_FR_Last -= Max_Acc*(speed_fr_delta/speed_delta_max);
        Speed_BL_Last -= Max_Acc*(speed_bl_delta/speed_delta_max);
        Speed_BR_Last -= Max_Acc*(speed_br_delta/speed_delta_max);
 	}
	else
 	{
		Speed_FL_Last = Speed_FL_Now;
		Speed_FR_Last = Speed_FR_Now;
       	Speed_BL_Last = Speed_BL_Now;
       	Speed_BR_Last = Speed_BR_Now;
    }
                                 

 /*****************************************ת��ת��Ϊռ�ձ�*******************************************/
 /****************************************************************************************************/
 
	speed_FL = Speed_FL_Last * MotorF_Argument;
	speed_FR = Speed_FR_Last * MotorFR_Argument;
  	speed_BL = Speed_BL_Last * MotorBL_Argument;
 	speed_BR = Speed_BR_Last * MotorBR_Argument;
 	
  	 	
 	if(speed_FL<(-2374.5/28) || speed_FL>(2404.5/28))
 		PWM_FL = (0.006269*14*speed_FL+49.93)/100;
 	else
 	{
 		if(speed_FL>0)
 			PWM_FL = (0.006186*14*speed_FL+50)/100;
 		else
 			PWM_FL = (0.006235*14*speed_FL+49.76)/100;
 	}
 		//PWM_FL = (0.006235*14*speed_FL+49.98)/100;
 	if(speed_FR<(-2374.5/28) || speed_FR>(2404.5/28))
 		PWM_FR = (0.006269*14*speed_FR+49.93)/100;
 	else
 	{
 		if(speed_FR>0)
 			PWM_FR = (0.006186*14*speed_FR+50)/100;
 		else
 			PWM_FR = (0.006235*14*speed_FR+49.76)/100;
 	}
 		//PWM_FR = (0.006235*14*speed_FR+49.98)/100;
  	if(speed_BL<(-2374.5/28) || speed_BL>(2404.5/28))
 		PWM_BL = (0.006269*14*speed_BL+49.93)/100;
 	else
 	{
 		if(speed_BL>0)
 			PWM_BL = (0.006186*14*speed_BL+50)/100;
 		else
 			PWM_BL = (0.006235*14*speed_BL+49.76)/100;
 	}
 		//PWM_BL = (0.006235*14*speed_BL+49.98)/100;
 	if(speed_BR<(-2374.5/28) || speed_BR>(2404.5/28))
 		PWM_BR = (0.006269*14*speed_BR+49.93)/100;
 	else
 	{
 		if(speed_BR>0)
 			PWM_BR = (0.006186*14*speed_BR+50)/100;
 		else
 			PWM_BR = (0.006235*14*speed_BR+49.76)/100;
 	}
 		//PWM_BR = (0.006235*14*speed_BR+49.98)/100;
 	
 /****************************************���ٶȽ�����������******************************************/
 /****************************************************************************************************/

	if(speed_FL<=0)
		PWM_FL=PWM_FL*Motor_FL_Argument_Back;
	else
		PWM_FL=PWM_FL*Motor_FL_Argument_Ford;

	if(speed_FR<=0)
		PWM_FR=PWM_FR*Motor_FR_Argument_Back;
	else
		PWM_FR=PWM_FR*Motor_FR_Argument_Ford;
		
	if(speed_BL<=0)
		PWM_BL=PWM_BL*Motor_BL_Argument_Back;
	else
		PWM_BL=PWM_BL*Motor_BL_Argument_Ford;

	if(speed_BR<=0)
		PWM_BR=PWM_BR*Motor_BR_Argument_Back;
	else
		PWM_BR=PWM_BR*Motor_BR_Argument_Ford;


	PWM_Max=Max(Fp64Abs(PWM_FL-0.5),Fp64Abs(PWM_BL-0.5),Fp64Abs(PWM_BR-0.5),Fp64Abs(PWM_FR-0.5));
	
	if(PWM_Max>=0.48)
	{
		PWM_FL = 0.48*(PWM_FL-0.5) / PWM_Max + 0.5; 
		PWM_FR = 0.48*(PWM_FR-0.5) / PWM_Max + 0.5; 
		PWM_BL = 0.48*(PWM_BL-0.5) / PWM_Max + 0.5;
		PWM_BR = 0.48*(PWM_BR-0.5) / PWM_Max + 0.5;		
	}
        
 	SetPWM( Motor_F, PWM_FL);
 	SetPWM( Motor_FR, PWM_FR);
 	SetPWM( Motor_BL, PWM_BL);
 	SetPWM( Motor_BR, PWM_BR);
	
}   
#endif