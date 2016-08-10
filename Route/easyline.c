
/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "math.h"


/*
 * ������: EasyLine
 * ��  ��: �򵥰���ֱ�߹���
 * ��  ��: -end_point  Ŀ��λ��
 *		   -aim_radian Ŀ��Ƕ�
 *		   -speed	   �����ٶ�(����ֵ������)
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void EasyLine(struct Point end_point,double aim_radian,double speed)
{
	struct Point sta_point = GPS.position;		//��¼��ʼλ��

	double phi;									//
	
	double speed_x,speed_y;						//������������ٶ�����ٶ�
	double speed_robot_x,speed_robot_y;			//ת��������������ķ��ٶ�
	
	double error_angle,error_dis;				//�Ƕ������������
	double Vout_A=0;							//PID������Ƕ����ֵ
	double Vout_D=0;							//PID������������ֵ
	double v_err_x,v_err_y;						//PID�����ٶȵķ���
	
	double lineangle = GetLineAngle(sta_point,end_point);	//�����·���߶ε����
	
	PID_Clear();
	
	//���ٶ���x,y�����ϵķ���
	speed_x = speed*cos(lineangle);
	speed_y = speed*sin(lineangle);
	
	//�Ƕ����;������
	error_angle = aim_radian-GPS.radian;
	error_dis   = ( GPS.position.x - sta_point.x ) * sin( lineangle ) 
				- ( GPS.position.y - sta_point.y ) * cos( lineangle );
	
	if(error_angle>pi)
		error_angle-=2*pi;
	if(error_angle<-pi)
		error_angle+=2*pi;
	
	//PID����(λ��ʽ)
	Vout_A = AnglePID(error_angle,Pid_List[2]);
	Vout_D = DistancePID(error_dis,Pid_List[3]);
	
	//PID�����ٶȵķ���
	v_err_x = -Vout_D*sin(lineangle);
	v_err_y =  Vout_D*cos(lineangle);
	
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
}


/**********************************END OF FILE*********************************/
