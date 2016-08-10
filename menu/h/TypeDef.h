
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MENUTYPEDEF_H
#define __MENUTYPEDEF_H

/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototype -----------------------------------------------*/


//����ڵ�
struct M_NodeType
{
	struct M_Type *prev;//ǰ���˵�
	struct M_Type *next;//�󼶲˵�
};
//�˵�������
enum M_AttribType
{
	M_Empty = 0x00,		//��
	M_UFunc = 0x01,		//�û�����
	M_SMenu = 0x02,		//�˵�
};
//�˵���
struct M_Type
{
	char *Name;						//����
	enum M_AttribType  M_Attrib;	//����
	void (*MenuFunc)(void);			//��ں���
    struct M_NodeType Mnode;		//�ڵ�
};

#endif
/**********************************END OF FILE*********************************/

