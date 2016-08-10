#include "all.h"
#include "guide.h"

float guideDisError=0;
float guideAngError=0;

float Vout_0=0;
float Vout_1=0;

float Vout_X=0;
float Vout_Y=0;
float Vout_W=0;

//keep line
//����Ϊ���ص㵥λ�����ȣ�mm/s
void keep_line(float dis_err, float ang_err, float forward_speed)
{
	//camer1����λ�����ͽǶ����

	  
		Vout_X=0;
		Vout_Y=0;
		Vout_W=0;
			
		if(fabs(ang_err)<1.5/180.0*pi)
		{
			Vout_0 = Pid_Cal(ang_err,0);
		}
		else
		{
			Vout_0 = Pid_Cal(ang_err,1);
		}
		
		Vout_1 = Pid_Cal(dis_err,2);
	
	//����ֱ�߷���ǰ�����ٶ�
	//�ֽ⵽�ֲ�����ϵ�µ��ٶ� 
	Vout_X+=forward_speed*sin(ang_err);
	Vout_Y+=forward_speed*cos(ang_err);
	
	//У���Ƕ������ٶ� 
	Vout_X+=Vout_1;
	
	Vout_W=Vout_0;
		
	//���ٶ�
	SetSpeed(Vout_X,Vout_Y,Vout_W);
}

//keep point

void keep_point(float x_err, float y_err,float ang_err)
{
	//camer1����λ�����ͽǶ����
	
		Vout_X=0;
		Vout_Y=0;
		Vout_W=0;
			
	
		float dis=sqrt(x_err*x_err + y_err*y_err);
	
		if(fabs(ang_err)<3.5/180.0*pi)
		{
			Vout_0 = Pid_Cal(ang_err,3);
		}
		else
		{
			Vout_0 = Pid_Cal(ang_err,4);
		}
		if(Vout_0>1.4)
			Vout_0=1.4;
		if(Vout_0<-1.4)
			Vout_0=-1.4;
		
		
		Vout_1 = Pid_Cal(dis,5);
		Vout_W=Vout_0;
		
	Vout_X=Vout_1*x_err/dis;
	Vout_Y=Vout_1*y_err/dis;
		
	//���ٶ�
	SetSpeed(Vout_X,Vout_Y,Vout_W);
	
}

void change_pos(void)
{	
		static float tmp_ang=0;
		
		tmp_ang=move_angle-locate_ang;
	
		if(tmp_ang>pi || tmp_ang <-pi)
				SetSpeed(0,0,30);
		
		if(tmp_ang<pi || tmp_ang>-pi)
				SetSpeed(0,0,-30);
}

//����
point_pos start_pos={0};
point_pos target_pos={0};
point_pos now_pos={0};

//��ʼ��Ϊ������
//����������ܴ��ڶ�λ�㴦����������©�ж����µĿ�������ά��
enum robot_status my_robot=on_road;

//״̬������ͷ���������������ı�
//�˶����ݻ����˵�״̬Ҳѡ��ͬ���˶�ģʽ

//����ģʽ������Ľ����д���

//Ѳ��Ϊ����ͷ1
//��ά��Ϊ����ͷ2

//����ͷ1�ջ�ֱ�Ӵ�����λ�úͽǶ����
//����ͷ2���������ǵ�ǰ����������ϵ�µĽǶȺ�λ��

//�ǶȺ�λ�÷ֱ���ʲô���ĵ�λ��Ҫ����ȥ��ǰ�����




void move_car(float speed)
{
	float tmp_ang_err=0;
	
	switch(my_robot)
	{
			case on_road:
				//���Ϊ����ͷ������������
				if(slow_down == 1)
					keep_line(guide_dis_error,guide_ang_error/180*pi,150);
				else
					keep_line(guide_dis_error,guide_ang_error/180*pi,speed);
				break;
			case on_road_slow:
			case unloacted:
					keep_line(guide_dis_error,guide_ang_error/180*pi,150);
				break;
			case back_slow:
				keep_line(guide_dis_error,guide_ang_error/180*pi,-150);
				break;
			case see_point:
				keep_point(locate_x_error,locate_y_error,0);
				break;
			
			//�������״̬ʱһ����ȷ�������˵�Ŀ����̬
			//���ݵ�ǰ��̬���÷������������������˵���̬
			
			case adjust_pos:
				tmp_ang_err=(locate_ang-move_angle)/180*pi;
				if(tmp_ang_err>pi)
					tmp_ang_err-=2*pi;
				else if(tmp_ang_err<-pi)
					tmp_ang_err+=2*pi;
				keep_point(locate_x_error,locate_y_error,tmp_ang_err);
// 				change_pos();
				break;
				
				//�뿪����ǰ��
				case leave_point:
					SetSpeed(0,500,0);
					break;
				
				case arrive_target:
				
				SetSpeed(0,0,0);
				break;
			
			
		}
}

void stop_car(void)
{
	my_robot=arrive_target;
	
	SetSpeed(0,0,0);
	
	set_mecf(0);
	set_mecbr(0);
	set_mecbl(0);
	
}

