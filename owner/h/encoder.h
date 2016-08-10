#ifndef _ENCODER_H
#define _ENCODER_H
#include "stm32f10x.h"

struct Encoder_Stat
{	
	int32_t Last;		//
	int32_t Total;		//����������
	double Convert;		//��תϵ��
	signed char dir;	//�ı�����ת�����������Ҫ�ķ�������1��������-1��
	double Distance;		//�����߹�λ��	
};

  extern struct Encoder_Stat Encoders[2];
  void Encoder_Update(void);
  void ENCODER_Clear(int index);
  void Encoder_Clear(int index);
  void Encoder_Init(void);
  void Encoder_InitXY(uint8_t i);
  void Encoder_InitR(void);
  void E_Init_Con(void);
#endif
