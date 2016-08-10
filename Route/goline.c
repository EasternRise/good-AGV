
/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "math.h"

struct Point Sta_Point;
struct Point End_Point;
double Aim_Radian;
double Speed_Sta;
double Speed_Max;
double Line_Angle;
double S;
double Acc_Dis,Dec_Dis;
double Acc,Dec;
double Acc_Rate=0.3;
double Dec_Rate=0.3;

/*
 * ������: SetLine
 * ��  ��: ��ʼ����ֱ�߹���
 * ��  ��: -end_point  Ŀ��λ��
 *		   -aim_radian Ŀ��Ƕ�
 *		   -speed_sta  ��ʼ�ٶ�
 *		   -speed_max  ����ٶ�
 *		   -speed_end  �����ٶ�
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void SetLine(struct Point end_point,double aim_radian,double speed_sta,double speed_max,double speed_end)
{
	Sta_Point = GPS.position;		//��¼��ʼλ��
	End_Point = end_point;
	Aim_Radian = aim_radian;
	
	Speed_Sta = speed_sta;
	Speed_Max = speed_max;
	
	Line_Angle = GetLineAngle(Sta_Point,end_point);	//�����·���߶ε����
	
	S = GetLength(Sta_Point,end_point);				//�����·���߶εĳ���
	
	Acc_Dis = Acc_Rate*S;//���پ���ͼ��پ���
	Dec_Dis = Dec_Rate*S;
	
	Acc = (speed_max - speed_sta)/Acc_Dis;//���ٶ�����ٶȣ��������أ�
	Dec = (speed_end - speed_max)/Dec_Dis;
	
	PID_Clear();
}

void GoLine(void)
{
	struct Point pos;							//��������
	double phi;
	double speed=0;
	double speed_x,speed_y;						//������������ٶ�����ٶ�
	double speed_robot_x,speed_robot_y;			//ת��������������ķ��ٶ�
	
	double error_angle,error_dis;				//�Ƕ������������
	double Vout_A=0;							//PID������Ƕ����ֵ
	double Vout_D=0;							//PID������������ֵ
	double v_err_x,v_err_y;						//PID�����ٶȵķ���
	
	pos = GetFoot_P2L_PP(GPS.position,Sta_Point,End_Point);	//�õ���������
		
	//�����������긳�ٶ�
	if(GetLength(Sta_Point,pos) < Acc_Dis)
	{
		if(speed < Speed_Max)
			speed = Speed_Sta + Acc*GetLength(Sta_Point,pos);
		else
			speed = Speed_Max;
	}
	else if(GetLength(Sta_Point,pos) > (S-Dec_Dis))
	{
		speed = Speed_Max + Dec*(GetLength(Sta_Point,pos)-(S-Dec_Dis));
	}
	else
		speed = Speed_Max;
	
	//���ٶ���x,y�����ϵķ���
	speed_x = speed*cos(Line_Angle);
	speed_y = speed*sin(Line_Angle);
	
	//�Ƕ����;������
	error_angle = Aim_Radian-GPS.radian;
	error_dis   = ( GPS.position.x - Sta_Point.x ) * sin( Line_Angle ) 
				- ( GPS.position.y - Sta_Point.y ) * cos( Line_Angle );
	
	if(error_angle>pi)
		error_angle-=2*pi;
	if(error_angle<-pi)
		error_angle+=2*pi;
	
	//PID����(λ��ʽ)
	//if(GetLength(GPS.position,Sta_Point) >= Acc_Dis)
		Vout_A = 1000*AnglePID(error_angle,Pid_List[2]);
	Vout_D = DistancePID(error_dis,Pid_List[3]);
	
	//PID�����ٶȵķ���
	v_err_x = -Vout_D*sin(Line_Angle);
	v_err_y =  Vout_D*cos(Line_Angle);
	
	//���ϵ�������
	speed_x += v_err_x;
	speed_y += v_err_y;
	
	//������������ٶ�ת��Ϊ�����˾ֲ�������ٶ�
	phi = GPS.radian;
	speed_robot_x =  speed_x*cos(phi) + speed_y*sin(phi);
	speed_robot_y = -speed_x*sin(phi) + speed_y*cos(phi);
	
	//Ϊ���ָ��ٶ�
	Speed_X = speed_robot_x;
	Speed_Y = speed_robot_y;
	Speed_Rotation = Vout_A;
	
	//LCD��ʾ
	LCD_Clear();
	LCD_SetXY(0,0);
	LCD_WriteString("A:");
	LCD_WriteDouble(GPS.radian);
	
	LCD_SetXY(0,1);
	LCD_WriteString("X:");
	LCD_WriteDouble(GPS.position.x);
	
	LCD_SetXY(9,1);
	LCD_WriteString(" Y:");
	LCD_WriteDouble(GPS.position.y);
	
	LCD_SetXY(0,2);
	LCD_WriteString("error_angle:");
	LCD_WriteDouble(error_angle);
	
	LCD_SetXY(0,3);
	LCD_WriteString("error_dis:");
	LCD_WriteDouble(error_dis);
	
	LCD_SetXY(0,4);
	LCD_WriteString("Vout_A:");
	LCD_WriteDouble(Vout_A);
	
	LCD_SetXY(0,5);
	LCD_WriteString("Vout_D:");
	LCD_WriteDouble(Vout_D);
	
	LCD_SetXY(0,6);
	LCD_WriteDouble(speed_x);
	LCD_SetXY(10,6);
	LCD_WriteDouble(speed_y);
	
	LCD_SetXY(0,7);
	LCD_WriteDouble(Line_Angle);
}


/**********************************END OF FILE*********************************/
