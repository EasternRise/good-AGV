#ifndef _GPS_H
#define _GPS_H
  #include "stm32f10x.h"
  #include "MyTypeDef.h"

#define GPS_STATCOUNT	2


// #define CARWIDTH 246.5 
// #define CARLENGTH 301

#define CARWIDTH 202 
#define CARLENGTH 300

typedef struct 
{   
	Pointfp64  	                position;	  	    //��ǰ����	
    double  	        		angle;        	    //��ǰ�Ƕ� 		
	double				        radian;			    //��ǰ����

	double			            distance1;	  	    //����1ǰ������
	double			        	distance2;		    //����2ǰ������
    double                      GyroAngle;          //�������ǵõ��ĽǶ�
    
    double				        distancestep1; 	    //����1����ǰ������
	double				        distancestep2;      //����2����ǰ������
	
	float				        speed;			    //��ǰ�ٶ�
	float				        acceleration;	    //��ǰ���ٶ�
}Gps_State;

extern	Pointfp64  	position_forward;//ǰ������
extern	Pointfp64  	position_center;//ǰ������

extern Gps_State Gps_List[GPS_STATCOUNT];
extern Pointfp64 Gps_assume;//��������ͷ���߼����У��ʱ�����õı���

void GPS_Update(void);
void GPS_Clear(void);
void GPS_Init(Pointfp64 position,double radian);



 
#endif
