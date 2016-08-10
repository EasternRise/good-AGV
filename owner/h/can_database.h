#ifndef _CAN_DATABASE_H
#define _CAN_DATABASE_H
	#include "stm32f10x.h"
	
	#ifndef NULL
	#define NULL ((void *)0)
	#endif
	
	#define fp64 double
	#define fp32  float

	/*Data_Type*/
	#define READ_ONLY  0	//���ض�������д
	#define WRITE_ONLY 1	//����д�������
	
	
/*���������Ӧ��ID���б�*/
/*
IDλ��	[	(GS:GPS Slave  MS:Motor Slave)							]
NO.7	[			0--GS			|		1--Others				]
NO.6	[	0--MOSI		|	1--MISO	|	0--MS MOSI	|	1--Others	]
NO.5~0	[	ID numbers				|	ID numbers  &  Others		]
*/
	typedef enum
	{
		CAMERA_G_ID=0x01,
		CAMERA_L_ID =0x02,
		CAMERA_P_ID =0x03,
		ADC_ELE_ID=0x04,
		ADC_MOT_ID=0x05,
		
	}ID_NUMDEF;	
		
	/*���غ�GPSЭ����֮��������ʽ*/
  typedef enum
	{
		NO_COMMAND			= 0x00,
		//M_G_CMD_ID�µ�����
		GPS_READ			= 0x01,		//��ȡGPS��Ϣ����
		CHECK_FLOAT			= 0x02,		//֪ͨGPSЭ����У׼��������Ư����
		GYRO_INIT			= 0x03,		//֪ͨGPSЭ���ر궨����������
		ENC_L_INIT			= 0x04,		//֪ͨGPSЭ���ر궨��������תϵ������
		ENC_R_INIT			= 0x05,		//֪ͨGPSЭ���ر궨������ת�뾶����
		//G_M_CMD_ID�µ�����
		CF_NORMAL			= 0x06,
		CF_CHANGED			= 0x07,
		CF_ERROR			= 0x08
	}COM_TYPE;
	
	typedef struct
	{
		uint8_t  Data_type;
		ID_NUMDEF  Data_ID;
		uint8_t* Data_ptr;
		uint8_t  Data_length;
		
		//��can���߽ӵ����ݺ󣬵��õĺ���
		void (*MenuFunc)(void);			//��ں���		
		uint8_t  Channel;
		uint8_t  Fifo_num;			//�ڽ��շ�����ID���õ�fifo��
	}Can_Data;

	union fi64_to_u8     //fp64�����ݣ���int64_t������ת��u8�����ݽ���can���߷���
	{
		fp64	 f64_data;
		int64_t  i64_data;
		int32_t  i32_data[2];
		uint16_t u16_data[4];
		uint8_t  u8_data[8];
	};
	
	union f64_to_u8
	{
		float float_data[2];
		uint8_t u8_data[8];
	};
	union f32_to_u8
	{
		float float_data;
		uint8_t u8_data[4];
	};
	
	union f96_to_u8
	{
		float float_data[2];
		uint16_t u16_data[4];
		uint8_t u8_data[8];
	};
	
	extern uint8_t Can_Data_Num;
	extern Can_Data Can_Database[];
	extern uint8_t HASH_TABLE[256];
	
	extern uint8_t MOSI_CMD;
	extern uint8_t MISO_CMD;
    extern u16 CAMERA_DATA;
	
	extern	union fi64_to_u8 MISO_CAMER_OFFSET;
	extern	union fi64_to_u8 MISO_CAMER_ANGLE;
	
    extern union fi64_to_u8 MOSI_PWM;
	void Hash_Table_init(void);
	void Write_Database(ID_NUMDEF ID_NUM);
	
extern	union f64_to_u8 CAMERA_G_DATA;
extern  uint8_t CAMERA_L_DATA[2];
extern  union f96_to_u8 CAMERA_P_DATA;
	
extern  union f64_to_u8 ADC_ELE_DATA;
extern 	union f32_to_u8 ADC_MOT_DATA;



#endif
