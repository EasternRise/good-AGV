/*
ÿ��һ��CAN�����豸
	1������Can_Data_Num����ֵ
	2��Ҫ��Can_Database�б������������Ϣ���ر�ע�ⲻҪ���
	3��void Hash_Table_init(void)�У�����¼��豸��Can_Database�б��е����
	4�����ID_NUMDEFö�ٶ����м�������ID�������������
*/

#include "all.h"

uint8_t Can_Data_Num=0;


//�¼�IDʱ����ID_NUMDEF�ж�����ӦID������


//��������ͷ�� һ��ADC��,��CANͨ��

//����ͷ ADC�嶼��ֻ�����ش�����
//IDΪ  CAMERA_G_ID CAMERA_L_ID CAMERA_P_ID ADC_ID
//����Ϊ CAMERA_G_ID��{float , float}
//����Ϊ CAMERA_L_ID��{uint8t , uint8t}
//����Ϊ CAMERA_P_ID��{float , float, float}
//����Ϊ ADC_ID			��{float , float}

union f64_to_u8 CAMERA_G_DATA;
uint8_t CAMERA_L_DATA[2];
union f96_to_u8 CAMERA_P_DATA;

union f64_to_u8 ADC_ELE_DATA;
union f32_to_u8 ADC_MOT_DATA;



Can_Data Can_Database[]=
{
	//Data_type		Data_ID				*Data_ptr					Data_length		*MenuFunc		Channel		Fifo_num
	//����&&GPSЭ����ͨ��ID*/
	//data_type �������������˵��
	//������ֻд ��ôЭ���ؾ���Ҫ�� ��ô��Ҫ�������Ĺ�����
	//********************************************************************/
	//�޸���ͯ��  ���Լ���˵ ��READ �ͼ�����չ������� ʱ��       2016/2/16
	//******************************************************************/
		{READ_ONLY,	CAMERA_G_ID,			(uint8_t *)(&CAMERA_G_DATA)				,8,			CAMERA_G_FUNC,			1,			CAN_Filter_FIFO0},
		{READ_ONLY,	CAMERA_L_ID,			(uint8_t *)(&CAMERA_L_DATA[0])		,2,			CAMERA_L_FUNC,			1,			CAN_Filter_FIFO1},
		{READ_ONLY,	CAMERA_P_ID,			(uint8_t *)(&CAMERA_P_DATA)				,8,		CAMERA_P_FUNC,			1,			CAN_Filter_FIFO1},
		{READ_ONLY,	ADC_ELE_ID,						(uint8_t *)(&ADC_ELE_DATA)						,8,			ADC_ELE_FUNC,						1,			CAN_Filter_FIFO0},
		{WRITE_ONLY,	ADC_MOT_ID,						(uint8_t *)(&ADC_MOT_DATA)						,4,			NULL,						1,			CAN_Filter_FIFO1},
	//{WRITE_ONLY,	M_G_CMD_ID,			(uint8_t *)(&MOSI_CMD)				,1,		M_G_CMD_FUNC,		1,			CAN_Filter_FIFO0},
	//{READ_ONLY,		G_M_CMD_ID,			(uint8_t *)(&MISO_CMD)				,1,		NULL,				1,			CAN_Filter_FIFO0},
};

//HASH_TABLE��ʼֵΪ255����ΪCan_Data_NumֵС��256�����豸������256��
uint8_t HASH_TABLE[256]={255};

void Hash_Table_init(void)
{
	int i;
	
	Can_Data_Num = sizeof(Can_Database) / sizeof(Can_Database[0]);
	for(i=0;i<256;i++)
	{
		HASH_TABLE[i] = 255;
	}
	for(i=0;i<Can_Data_Num;i++)
	{
		HASH_TABLE[Can_Database[i].Data_ID] = i;
	}
}
//��canд���� �ȳ�ʼ�� Data_ID�Ծ� candatabase������ 
//�����������  ����Ϊ Data_ID
//ǰ��Ϊʹ����hash_table
void Write_Database(ID_NUMDEF ID_NUM)
{
	uint8_t j;
	CanTxMsg TxMessage;
	/* Check the parameters */
	if((HASH_TABLE[ID_NUM] >= Can_Data_Num)||(Can_Database[HASH_TABLE[ID_NUM]].Data_type!=WRITE_ONLY))
	{
		LED4_on;
		return;
	}
	
	TxMessage.StdId=Can_Database[HASH_TABLE[ID_NUM]].Data_ID;
	TxMessage.ExtId=0;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.DLC=Can_Database[HASH_TABLE[ID_NUM]].Data_length;
	
	for(j=0;j<Can_Database[HASH_TABLE[ID_NUM]].Data_length;j++)
	{
		TxMessage.Data[j]=(*(Can_Database[HASH_TABLE[ID_NUM]].Data_ptr+j));
	}
	
	Can_SendData(&TxMessage);
	
}



