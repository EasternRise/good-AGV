
/* Includes ------------------------------------------------------------------*/
#include "all.h"

u8 PID_flag=1;

struct PID Pid_List[]=
{
		{1.5,0,0.05},    //��Ƕ�PID
		{0.65,0,0.1},    //С�Ƕ�PID		
		{0.65,0,0.07},    //��λ��PID
		

		{1.8,0,0.05},    //��Ƕ�PID
		{0.85,0,0.1},    //С�Ƕ�PID
		{1.10,0,0.7},    //��λ��PID
};

/*
 * ������: PID_Clear
 * ��  ��: ��PID�洢�����ֵ���
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void PID_Clear(void)
{
	int i;
	
	for(i=0;i<2;i++)                                 //�޸�
	{
		Pid_List[i].mend=0;
		Pid_List[i].ep1=0;
		Pid_List[i].ep2=0;
	}
}

/*
 * ������: PID
 * ��  ��: λ��ʽPID����������������ʽ�ĵ���
 * ��  ��: -Error �����
 *		   -pid pid����
 * ��  ��: �������
 * ��  ��: �ⲿ����
 */

float Pid_Cal(double Error,int pid_num)
{
    static	double A=0;
    static	double B=0;
    static	double C=0;
    static	double delta=0;
	
	A = (Pid_List[pid_num].p+Pid_List[pid_num].i+Pid_List[pid_num].d);
	B = -(Pid_List[pid_num].p+2*Pid_List[pid_num].d);
	C = Pid_List[pid_num].d;
	
	delta = A*Error + B*Pid_List[pid_num].ep1 + C*Pid_List[pid_num].ep2;
	Pid_List[pid_num].mend += delta;
	
	Pid_List[pid_num].ep2 = Pid_List[pid_num].ep1;
	Pid_List[pid_num].ep1 = Error;
	
	return Pid_List[pid_num].mend;
}



/**********************************END OF FILE*********************************/
