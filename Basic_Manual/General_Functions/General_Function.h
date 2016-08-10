#ifndef GENERAL_FUNCTION_H
#define GENERAL_FUNCTION_H

extern fp32   ArgForTurn;
#define ETOC 380
//�ṹ�嶨�岿��

//��ṹ��
struct  Pointfp64
{
	fp64  x;
	fp64  y;
};
struct  Pointfp32
{
	fp32  x;
	fp32  y;
};
//�����ṹ��
struct Vector
{
    struct Pointfp32 coordinate ;
    fp64 angle;                    //�û����Ʊ�ʾ
    fp64 length;
};

//Բ�ṹ��
struct Circle
{
    struct Pointfp64 center;
    fp64 r;
};


//·����Ϣ��ṹ��
struct Path_Point
{
    struct Pointfp64 position;
    fp64 lineangle;
    fp64 radius;
    fp64 speed_point;
}; 



//·�����ٽṹ��
struct Path_Acc
{
	int16 startnum;
    int16 endnum;
    fp64 startspeed;
    fp64 aimspeed;
}; 


//ȫ����λ��Ϣ�ṹ��
struct  Gps_State
{   
	
	struct Pointfp64  	position;	  	//��ǰ����	
	fp64				distancestep1; 	//����1����ǰ������
	fp64				distancestep2;  //����2����ǰ������
	fp64				distance;		//������ǰ������ 
	fp64			    distance1;		//����1ǰ������
	fp64				distance2;		//����2ǰ������
	fp64              	anglestep;	  	//������ת�Ƕ� 
	fp64  				angle;        	//��ǰ�Ƕ� 		
	fp64				radian;			//��ǰ����
	fp64				speed;			//��ǰ�Ƕ�
	fp64				acceleration;	//��ǰ���ٶ�
	fp64				rotationspeed;	//��ǰ��ת�ٶ�
	fp64				rotationacc;	//��ǰ��ת���ٶ�
};

//·���ṹ��
struct Path
{
	void (*entry)();//·����ں���
	char *name;//·������
	int  type;	//·������
};


struct Value
{
	void * enter;
	int type;
	char * name;
};

extern fp64 error_convert[];
//mymath.c
#define PI					3.14159265359

extern fp64 Max_Four(fp64 a,fp64 b,fp64 c,fp64 d);
extern fp64 MATH_Distance( struct Pointfp64 StartPonit, struct Pointfp64 EndPoint ) ;
extern fp64 MATH_GetLineAngle(struct Pointfp64 Startpoint, struct Pointfp64 Endpoint);
//����16λ�з������ľ���ֵ
extern int16 Int16Abs(int16 Data);

//����32λ�з������ľ���ֵ
extern int32 Int32Abs(int32 Data);

extern int64 Int64Abs(int64 Data);

//����32λ�������ľ���ֵ
extern fp32 Fp32Abs(fp32 Data);

//����64λ�������ľ���ֵ
extern fp64 Fp64Abs(fp64 Data);


extern fp64 Getlength(struct Pointfp64 a1, struct Pointfp64 a2);

extern struct Vector MakeVector1(struct Pointfp64 a1, struct Pointfp64 a2);

extern struct  Vector MakeVector2(fp64 angle);

extern struct Vector MakeVector3(fp64 length,fp64 angle);

extern struct Vector MakeVector4(fp64 x,fp64 y);

extern fp64 DotProduct(struct Vector a1,struct Vector a2);

extern fp64 Projection(struct Vector a1,fp64 angle);

extern struct Pointfp64 GetFoot(fp64 a,fp64 b,fp64 c,struct Pointfp64 m);

extern struct Vector GetVector1 (fp64 a,fp64 b,fp64 c,struct Pointfp64 m);

extern struct Circle GetCircle(struct Pointfp64 start_pos,fp64 start_direction,struct Pointfp64 aim_pos,fp64 aim_direction);

extern fp64 Circle_Length(struct Circle circle,struct Pointfp64 a1,struct Pointfp64 a2,uint8 turndir);

extern fp64 Linedirect (fp64 a,fp64 b,fp64 c);

extern fp64 Max(fp64 a,fp64 b,fp64 c,fp64 d);

extern int32 Round_Off(float a);

//gps.c
extern struct Gps_State Gps_List[];

extern fp64 Gps_Speed;

extern int PRE_Count1;

extern int PRE_Count2;

extern int PRE_Count3;

extern void GPS_Init(struct Pointfp64 position,fp64 angle);

extern void GpsUpdate(void);

extern void Expection_FLS( void );

extern void GPS_Clear(void);

extern void GPSModulation(fp64 d);

extern fp64 sina,sinb,cosa,cosb,sinab,angle_a,angle_b;

extern fp64 Ac1,Ac2;


//gyro.c
extern struct Pointfp64 Start_RotatePosition;

//pid.c

struct PID
{
	fp64 PROP;
	fp64 Ti;
	fp64 Td;
};
#define Front 1
#define Back  0

extern struct Value Pid_Values[];

extern fp64 A_EP1;

extern fp64 A_EP2;

extern fp64 D_EP1;

extern fp64 D_EP2;

extern fp64 A_AmendV;
extern fp64 AmendV;
extern fp64 D_AmendV;

extern uint8 PID_ListLength;

extern struct PID Pid_List[];

extern uint8 PID_Clear(void);

extern void PID_NandInit(void);

extern void PID_NandSave(void);

extern fp64 AnglePID(fp64 AngleError,fp64 A_prop,fp64 A_ti,fp64 A_td);

extern fp64 DistancePID(fp64 DistanceError,fp64 D_prop,fp64 D_ti,fp64 D_td);

extern void PIDMecanum(uint8 dir,fp64 AngleError,fp64 A_prop,fp64 A_ti,fp64 A_td,fp64 DistanceError,fp64 D_prop,fp64 D_ti,fp64 D_td);

extern fp64 Vout[2];


#endif