
/* Includes ------------------------------------------------------------------*/
#include "all.h"


/* Private typedef -----------------------------------------------------------*/
//typedef void(* func)(void);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
 * ������: ShowMenuList
 * ��  ��: �˵���ʾ
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
 
void ShowMenuList(void)
{
    int i=0,j=0;
    struct M_Type *M_TypePtr;
    char *str;
	
		LCD_Clear();
	
    for (i=0; i<2; i++)//������ʾ��ÿ��4��
        for(j=0;j<M_NUM/2;j++)
        {
            M_TypePtr = CurrentMenu + (i*(M_NUM/2) + j);
            str = M_TypePtr->Name;
						LCD_SetXY(i*10,j);
            LCD_WriteString(str);
        }
}

/*
 * ������: KeyNumOperate
 * ��  ��: ������Ӧ
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void KeyNumOperate(u8 Key_Value)
{		
    switch (Key_Value)
    {          

        case key1:
			GoKeyNum(1);
            break;
        case key2:
			GoKeyNum(2);
            break;
        case key3:
			GoKeyNum(3);
            break;
        case key4:
			GoKeyNum(4);
            break;
        case 5:
            if(CurrentMenu != MainMenu)
                CurrentMenu = CurrentMenu->Mnode.prev;
            break;
        case key5:
			GoKeyNum(5);
            break;
        case key6:
			GoKeyNum(6);
            break;
        case key7:
			GoKeyNum(7);
            break;
        case key8:
			GoKeyNum(8);
            break;
        case key9:
			GoKeyNum(9);
            break;
        default:
            break;
    }
	ShowMenuList();
}

/*
 * ������: GoKeyNum
 * ��  ��: ������Ӧ������
 * ��  ��: -KeyNum ����ļ�ֵ
 * ��  ��: ��
 * ��  ��: �ڲ�����
 */
void GoKeyNum(int KeyNum)
{
		
    struct M_Type *MenuTemp;
    MenuTemp = CurrentMenu + KeyNum -1;
    
    if(MenuTemp->M_Attrib == M_SMenu)//������Ӳ˵��������ǲ˵�����ʾ���Ӳ˵��б�
        CurrentMenu = MenuTemp->Mnode.next;
    else if(MenuTemp->M_Attrib == M_UFunc)//�������û���������ִ�к���
			MenuTemp->MenuFunc(); 
    else if(MenuTemp->M_Attrib == M_Empty) {;}//�����ǿգ���ִ��һ������

}

/********************************    END OF FILE    ***************************/

