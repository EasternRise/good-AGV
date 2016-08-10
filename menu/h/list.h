/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MENULIST_H
#define __MENULIST_H

#include "TypeDef.h"

/* Private define ------------------------------------------------------------*/
#define M_NUM 8			//�˵��µ���Ŀ��������
#define M_COLM_NUM  20	//LCD�ɹ���ʾ������
#ifndef NULL
#define NULL ((void *)0)
#endif
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef void(*FuncPtrType)(void);

/* Exported variables --------------------------------------------------------*/
extern struct M_Type MainMenu[M_NUM];
extern struct M_Type *CurrentMenu;
/* Exported function prototype -----------------------------------------------*/

#endif 

/**********************************END OF FILE*********************************/

