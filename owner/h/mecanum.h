/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MECANUM_H
#define __MECANUM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported macro ------------------------------------------------------------*/

#define SPEED_STOP Speed_X = Speed_Y = Speed_Rotation = 0

/* Exported variables --------------------------------------------------------*/

extern float Speed_X;
extern float Speed_Y;
extern float Speed_Rotation;

extern struct Mecanum_State Mec_F;		//���ֵ�״̬����
extern struct Mecanum_State Mec_FR;
extern struct Mecanum_State Mec_BL;
extern struct Mecanum_State Mec_BR;
extern float Max_Acc;
extern float real_speed_x;
extern float real_speed_y;
extern float real_speed_rot;

/* Exported function prototype -----------------------------------------------*/
void SetSpeed(float speed_x,float speed_y,float speed_rotation);
void Mecanum_test(struct Mecanum_State *mec);

extern float wheel_i_R[3][3];


extern float f_speed;
extern	float bl_speed;
extern	float br_speed;
	
#endif 

/**********************************END OF FILE*********************************/
