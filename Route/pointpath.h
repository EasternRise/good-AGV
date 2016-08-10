/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __POINTPATH_H
#define __POINTPATH_H

//ѡ����߻��ұ����� ֻ��ѡ��һ��
//������ֻ��һ��·������ ��ͬ�ĺ궨��ʱ�������ݲ�һ��
//��Ϊ�����ܵ��ǵ��󣬶��������ǶԳƵģ����ƹ�����ȫ���Ը���
//���������������ֻ��·�����鲻ͬ �����ڳ����в�Ҫ������������������


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "MyTypeDef.h"
/* Exported macro ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
extern int Point_NowNum;
extern int Point_StartNum;
extern int Point_EndNum;
extern int Point_NowNum_Back;
extern int Point_NowNum_Center;    

extern int	Route_Num;
extern int Route[];


/* Exported function prototype -----------------------------------------------*/
void SetPointPath(int sta_num,int end_num);
void GoPointPath(void);
void Go_Path(u8 RouteNum);
void dis_control(float error_dis,float error_angle);

extern const struct Path_Point PointRoute[];
extern	struct PID pid_adapt;

extern float k0;
extern float k1;
extern float k2;
extern float con_p;

extern float error_angle;
extern float error_dis;				
extern float fusion;
extern float angel;


extern float error_dis_back;	
extern float error_dis_center;
extern u16 camerError;
extern u8  lightError;


#endif 

/**********************************END OF FILE*********************************/
