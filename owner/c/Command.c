#include "all.h"

#include "m_adc.h"
#include "obstacle.h"


//��λ�������� +  ��ά�����������λ����Ϣ��ʵ��״̬��ת��

//����ͷ1�����ݸ�ʽ 
//����ͷ2�����ݸ�ʽ  λ��uint8t(x,y) λ�����float(x,y) �Ƕ����(float) 

float  guide_dis_error=0;
float  guide_ang_error=0;

//�Ƕ����,λ�����
//�������ϵ�µ�
void CAMERA_G_FUNC(void){
	
	guide_ang_error=CAMERA_G_DATA.float_data[0]-90;
	guide_dis_error=CAMERA_G_DATA.float_data[1];
	
}

//X���, Y���

u8 pattern_find=0;
u8 slow_down=0;



void CAMERA_L_FUNC(void){
	pattern_find=1;
	
	now_pos.x=CAMERA_L_DATA[0];
	now_pos.y=CAMERA_L_DATA[1];	
	
	if(my_robot == on_road || my_robot == on_road_slow || my_robot == back_slow || my_robot == unloacted)
	{
		if(now_pos.x==0xff || now_pos.y == 0xff){
				slow_down=1;
		}
		else {
			if(my_robot == unloacted){
					obstacle_init();
					start_pos.x=now_pos.x;
					start_pos.y=now_pos.y;
					my_robot=see_point;
			}
			else if(my_robot == back_slow)
			{
				my_robot = see_point;
					start_pos.x=now_pos.x;
					start_pos.y=now_pos.y;
			}
			else if(now_pos.x != start_pos.x || now_pos.y != start_pos.y)//�����µĶ�λ��
			{	
					start_pos.x=now_pos.x;
					start_pos.y=now_pos.y;
					my_robot=see_point;
			}
		}
	}
}

//�Ƕ����,x���,y���
//��������ϵ�µ�

float locate_ang=0;
float locate_x_error=0;
float locate_y_error=0;

//ȫ������ϵ�µ�
int move_angle=0;

void CAMERA_P_FUNC(void){
	
	float row=0;
	float col=0;
	
	/*if (CAMERA_P_DATA.float_data[0]<0)
	{
		locate_ang=180+fabs(CAMERA_P_DATA.float_data[0]);
	}
	else
	{*/
  locate_ang =  CAMERA_P_DATA.float_data[0];
	
	row=CAMERA_P_DATA.u16_data[2];
	col=CAMERA_P_DATA.u16_data[3];
	
	locate_x_error=row-60;
	locate_y_error=col-80;
	
	
	
	if(my_robot == see_point)
	{
		if(fabs(locate_x_error) < 5 && fabs(locate_y_error )< 5)
		{
				//����״̬
				my_robot=adjust_pos;
			
				if(now_pos.x == target_pos.x && now_pos.y == target_pos.y)
						my_robot=arrive_target;
				
				else
				{
						//ȷ����������һ�׶���ȫ������ϵ��Ҫ����ô����̬�˶������ݶ�ά��õ�����ȫ������ϵ�µĽǶ������������˵�λ��
					
					if(p_status[ now_pos.x+now_pos.y*X_SIZE ] == all_dir || p_status[now_pos.x+now_pos.y*X_SIZE] == y_dir){
						if(y_direction==1)
						{
							move_angle=0;
							move_distance=delta_y-delta_slow;	
						}
						else
						{
							move_angle=180;
							move_distance=delta_y-delta_slow;	
						}
					}
					else if( p_status[now_pos.x+now_pos.y*X_SIZE] == x_dir ){
							move_angle=90*x_direction;
							move_distance=delta_x-delta_slow;
					}
					else if(p_status[now_pos.x+now_pos.y*X_SIZE] == zero_dir){
							;//�����˾�·��
					}
						
				}
				//������Ϣ,·���滮
		}
	}
	
	if(my_robot == adjust_pos )
	{
		//����Ѿ�ת��Ŀ��Ƕ�
		//����������ת���� on_board״̬
		if(fabs(locate_ang - move_angle) <1.5)
		{
			//my_robot=on_road;	
			my_robot=leave_point;	
			//������ʱ�����ڶ�ʱ���ж��иı�Ϊon road״̬
			//500ms����Ϊ�Ѿ��뿪
			leave_sec=450;
			TIM_Cmd(TIM6,ENABLE);
			slow_down=0;
		}
	}
}

//��ѹ
float max_vol=0;
float min_vol=0;
u8 low_ele=0;

void ADC_ELE_FUNC(void)
{
	
	max_vol=ADC_ELE_DATA.float_data[0];
	min_vol=ADC_ELE_DATA.float_data[1];
	if(max_vol<2.0)
		low_ele=0;
	else if(max_vol<v_thresh)
	{
		low_ele=1;
	
		//���Ŀ���Ϊ(0,0)
		target_pos.x=0;
		target_pos.y=0;
	}
}
	
