/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MYTYPEDEF_H
#define __MYTYPEDEF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

//��ṹ��
struct Point
{
	double x;
	double y;
};

//·����Ϣ�ṹ��
struct Path_Point
{
	struct Point position;	//λ��
	double speeddir;		//�ٶȷ���
	double selfdir;			//���巽��
	double speed;			//�ٶȴ�С
};

//��������Ϣ�ṹ��
struct Gyro_State
{
	double angle;			//�Ƕ�
	double convert1;		//��������תϵ��
	double convert2;		//�����Ƿ�תϵ��
};
//������Ϣ�ṹ��
struct Encoder_State
{
	double dis;				//����
	double convert1;		//��תϵ��
	double convert2;		//��תϵ��
	double r;				//������תʱ���̵���ת�뾶
	double radian;			//�����복������ϵY��������ļн�
};

//ȫ����λ��Ϣ�ṹ��
struct GPS_State
{
	struct Point position;	//
	double radian;			//����
};

//PID�ṹ��
struct PID
{
	double p;
	double i;
	double d;
	double mend;
	double ep1;
	double ep2;
};

//ÿ�����Ӷ�Ӧ��״̬
struct Mecanum_State
{
	int port;				//��Ӧ��PWM�˿�
	int arg;				//����ϵ��
};

//����ֵ
enum M_KeyNumTpye
{
    key1 = 1,
    key2,
    key3,
    key4,
    keyback,
    emergency,
    
    key5,
    key6,
    key7,
    key8,
    empty1,
    empty2,
    
    key9,
    key0,
    point,
    sign,
    keydelete,
    keyOK
};
#define pageup point
#define pagedown sign

typedef enum {
 		Type_Fp64 = 1 ,
 		Type_Int64,
 		Type_Fp32 ,
 		Type_Int32,
 		Type_Uint32,
 		Type_Int16,
 		Type_Uint16,
 		Type_Int8,
 		Type_Uint8,
 		Type_Gyro,
 		Type_Encoder,
 		Type_PID,
 		Type_Mecanum,
}SD_Value_Type;


typedef enum {
      TYPE_INT8	=  1,
      TYPE_UINT8	,
      TYPE_INT16	,
      TYPE_UINT16	,
      TYPE_INT32	,
      TYPE_UINT32	,
      TYPE_INT64	,
      TYPE_UINT64	,
      TYPE_FP32		,
      TYPE_FP64		,
//      TYPE_POINTFP32,
//      TYPE_POINTFP64,
}Value_Type;

//�б���ʾ�����
struct Input_ListValue
{
	void *value;
	Value_Type type;
	char *name;
};

#endif 

/**********************************END OF FILE*********************************/
