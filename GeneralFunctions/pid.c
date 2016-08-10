
/* Includes ------------------------------------------------------------------*/
#include "includes.h"

u8 PID_flag=1;

struct PID Pid_List[]=
{
	{0,1000000,0},	//0  ��Բ�Ƕ�PID
	{0,1000000,0},	//1  ��Բ����PID
	
	{0.8,1000000,0},	//2  ֱ�߽Ƕ�PID
	{9,1000000,8},	    //3  ֱ�߾���PID
	
	{-0.5,10000,1},	    //4  Keep�Ƕ�PID
	{6,1000000,0},		//5  Keep����PID
	
	{1.1,1000000,3},//6  �ܵ�Ƕ�PID
	{8,1000000,0},	//7  �ܵ����PID  
	
	{0,1000000,0},	//8  �ư�Ƕ�PID
	{0,1000000,0},  //9  �ư����PID
	{0,1000000,0},  //10  
	{0,1000000,0},  //11 
	
	{60,10000,3},  //12  ����ͷ��Բ��λ����PID   
	{-120,10000,3},	//13  ����ͷ��Բ��λ�Ƕ�PID
	
	{10,1000,0},	//14  ��������ͷǰ����PID
	{1.5,600,0},	//15  ��������ͷ����PID
	{20,10000,0},		//16  ��������ͷzPID

	{35,500,0},//17  ��������ͷ�Ƕ�PID
	
	{-6,10000,1},  	//18  ����������ͷxPID
	{-50,10000,1},	//19  ����������ͷyPID
	{-0.5,10000,1},	//20  ����������ͷ�Ƕ�PID
	
	{-20,3000,0},	//21  ����ǰ������ͷ����PID
	{20,5000,0},	//22  �����Ա�����ͷ����PID
	
	{10,100000,0.1},  //23  ��ǧ����������ͷǰ����PID
	{-0.5,100000,0.1},  //24  ��ǧ����������ͷ����PID
	{20,100000,0.1}, //25  ��ǧ����������ͷzPID
	
	{-20,10000,3},  //26  ����ͷ��Բ��λ����PID    by��ZhangHui 4.15 
	{0.5,5000,3},	//27  ����ͷ��Բ��λ�Ƕ�PID		by��ZhangHui 4.15 						
};
																								
static double A_ErrorPast1=0;
static double A_ErrorPast2=0;
static double A_Mend=0;
static double D_ErrorPast1=0;
static double D_ErrorPast2=0;
static double D_Mend=0;

fp64 Cam_X_EP1 = 0.0;
fp64 Cam_X_EP2 = 0.0;
fp64 Cam_Y_EP1 = 0.0;
fp64 Cam_Y_EP2 = 0.0;
fp64 Cam_Z_EP1 = 0.0;
fp64 Cam_Z_EP2 = 0.0;
fp64 Cam_A_EP1 = 0.0;
fp64 Cam_A_EP2 = 0.0;
fp64 WT_D1_EP1  = 0.0;
fp64 WT_D1_EP2  = 0.0;
fp64 WT_D2_EP1  = 0.0;
fp64 WT_D2_EP2  = 0.0;


fp64 Cam_X_AmendV = 0;
fp64 Cam_Y_AmendV = 0;
fp64 Cam_Z_AmendV = 0; 
fp64 Cam_A_AmendV = 0;
fp64 WT_D1_AmendV  = 0;
fp64 WT_D2_AmendV  = 0;




fp64 Vout[5]={0.0};


/*
 * ������: PID_Clear
 * ��  ��: ��PID�洢�����ֵ���
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void PID_Clear()
{
	int i;
	
	for(i=0;i<28;i++)
	{
		Pid_List[i].mend=0;
		Pid_List[i].ep1=0;
		Pid_List[i].ep2=0;
	}
	
	A_ErrorPast1 = 0.0;
	A_ErrorPast2 = 0.0;
	A_Mend = 0.0;
	D_ErrorPast1 = 0.0;
	D_ErrorPast2 = 0.0;
	D_Mend = 0.0;
	
	Cam_X_EP1 = 0.0;
	Cam_X_EP2 = 0.0;
	Cam_Y_EP1 = 0.0;
	Cam_Y_EP2 = 0.0;
	Cam_Z_EP1 = 0.0;
	Cam_Z_EP2 = 0.0;
	Cam_A_EP1 = 0.0;
	Cam_A_EP2 = 0.0;
	WT_D1_EP1  = 0.0;
	WT_D1_EP2  = 0.0;
	WT_D2_EP1  = 0.0;
	WT_D2_EP2  = 0.0;


	Cam_X_AmendV = 0.0;
	Cam_Y_AmendV = 0.0;
	Cam_Z_AmendV = 0.0;
	Cam_A_AmendV = 0.0;
	WT_D1_AmendV  = 0.0;
	WT_D2_AmendV  = 0.0;
	
	for(i=0;i<5;i++)
	   Vout[i]=0;
}

/*
 * ������: PID
 * ��  ��: λ��ʽPID����������������ʽ�ĵ���
 * ��  ��: -Error �����
 *		   -pid pid����
 * ��  ��: �������
 * ��  ��: �ⲿ����
 */
double PID(double Error,struct PID pid)
{
	double A=0;
	double B=0;
	double C=0;
	double delta=0;
	
	A = (pid.p*(1+1/pid.i+pid.d));
	B = -pid.p*(1+2*pid.d);
	C = pid.p*pid.d;
	
	delta = A*Error + B*pid.ep1 + C*pid.ep2;
	pid.mend += delta;
	
	pid.ep2 = pid.ep1;
	pid.ep1 = Error;
	
	return pid.mend;
}


/*
 * ������: AnglePID
 * ��  ��: λ��ʽ�Ƕ�PID����������������ʽ�ĵ���
 * ��  ��: -Error �����
 *		   -pid pid����
 * ��  ��: ���ٶ�
 * ��  ��: �ⲿ����
 */
double AnglePID(double Error,struct PID pid)
{
	double A=0;
	double B=0;
	double C=0;
	double delta=0;

	
	A = (pid.p*(1+1/pid.i+pid.d));
	B = -pid.p*(1+2*pid.d);
	C = pid.p*pid.d;
	
	delta = A*Error + B*A_ErrorPast1 + C*A_ErrorPast2;
	A_Mend += delta;
	
	A_ErrorPast2=A_ErrorPast1;
	A_ErrorPast1=Error;
	
	return A_Mend;
}

/*
 * ������: DistancePID
 * ��  ��: λ��ʽ����PID����������������ʽ�ĵ���
 * ��  ��: -Error �����
 *		   -pid pid����
 * ��  ��: �ٶ�
 * ��  ��: �ⲿ����
 */
double DistancePID(double Error,struct PID pid)
{
	double A=0;
	double B=0;
	double C=0;
	double delta=0;
	
	A = (pid.p*(1+1/pid.i+pid.d));
	B = -pid.p*(1+2*pid.d);
	C = pid.p*pid.d;
	
	delta = A*Error + B*D_ErrorPast1 + C*D_ErrorPast2;
	D_Mend+=delta;
	
	D_ErrorPast2=D_ErrorPast1;
	D_ErrorPast1=Error;
	
	return D_Mend;
}

fp64 Cam_X_PID(s16 error_dis,struct PID pid)
{
	fp64  Cam_a0 = 0.0;
	fp64  Cam_a1 = 0.0;
	fp64  Cam_a2 = 0.0;
	fp64  Cam_Vd=0.0;
	u8    Iflag=0;

	if(error_dis<20)//���ַ���
		Iflag=1;

	Cam_a0 = ( pid.p * ( 1 + 1 / pid.i*Iflag + pid.d ));     
	Cam_a1 = ( -pid.p * (1 + 2 * pid.d));         
	Cam_a2 = ( pid.p * pid.d );    	
	Cam_Vd = Cam_a0 *error_dis + Cam_a1 *Cam_X_EP1 + Cam_a2 *Cam_X_EP2; 
	Cam_X_AmendV = Cam_X_AmendV + Cam_Vd;
	Cam_X_EP2 = Cam_X_EP1;
	Cam_X_EP1 = error_dis;

	return Cam_X_AmendV;
}

fp64 Cam_Y_PID(s16 error_dis,struct PID pid)
{
	fp64  Cam_a0 = 0.0;
	fp64  Cam_a1 = 0.0;
	fp64  Cam_a2 = 0.0;
	fp64  Cam_Vd=0.0;   
	u8    Iflag=0;

	if(error_dis<20)//���ַ���
		Iflag=1;	

	Cam_a0 = ( pid.p * ( 1 + 1 / pid.i*Iflag + pid.d ));     
	Cam_a1 = ( -pid.p * (1 + 2 * pid.d));         
	Cam_a2 = ( pid.p * pid.d );    	
	Cam_Vd = Cam_a0 *error_dis + Cam_a1 *Cam_Y_EP1 + Cam_a2 *Cam_Y_EP2; 
	Cam_Y_AmendV = Cam_Y_AmendV + Cam_Vd;
	Cam_Y_EP2 = Cam_Y_EP1;
	Cam_Y_EP1 = error_dis;

	return Cam_Y_AmendV;
}

fp64 Cam_Z_PID(s16 error_dis,struct PID pid)
{
	fp64  Cam_a0 = 0.0;
	fp64  Cam_a1 = 0.0;
	fp64  Cam_a2 = 0.0;
	fp64  Cam_Vd=0.0;
	u8    Iflag=0;

	if(error_dis<50)//���ַ���
		Iflag=1;

	Cam_a0 = ( pid.p * ( 1 + 1 / pid.i*Iflag + pid.d ));     
	Cam_a1 = ( -pid.p * (1 + 2 * pid.d));         
	Cam_a2 = ( pid.p * pid.d );   	
	Cam_Vd = Cam_a0 *error_dis + Cam_a1 *Cam_Z_EP1 + Cam_a2 *Cam_Z_EP2; 
	Cam_Z_AmendV = Cam_Z_AmendV + Cam_Vd;
	Cam_Z_EP2 = Cam_Z_EP1;
	Cam_Z_EP1 = error_dis;

	return Cam_Z_AmendV;
}

fp64 Cam_A_PID(double error_angle,struct PID pid)
{
	fp64  Cam_a0 = 0.0;
	fp64  Cam_a1 = 0.0;
	fp64  Cam_a2 = 0.0;
	fp64  Cam_Vd = 0.0;    


	Cam_a0 = ( pid.p * ( 1 + 1 / pid.i + pid.d ));     
	Cam_a1 = ( -pid.p * (1 + 2 * pid.d));         
	Cam_a2 = ( pid.p * pid.d );   	
	Cam_Vd = Cam_a0 *error_angle + Cam_a1 *Cam_A_EP1 + Cam_a2 *Cam_A_EP2; 
	Cam_A_AmendV = Cam_A_AmendV + Cam_Vd;
	Cam_A_EP2 = Cam_A_EP1;
	Cam_A_EP1 = error_angle;

	return Cam_A_AmendV;
}


fp64 WT_D1_PID(double error_dis,struct PID pid)
{
	fp64  WT_a0 = 0.0;
	fp64  WT_a1 = 0.0;
	fp64  WT_a2 = 0.0;
	fp64  WT_Vd = 0.0;    


	WT_a0 = ( pid.p * ( 1 + 1 / pid.i + pid.d ));     
	WT_a1 = ( -pid.p * (1 + 2 * pid.d));         
	WT_a2 = ( pid.p * pid.d );

	WT_Vd = WT_a0 *error_dis + WT_a1 *WT_D1_EP1 + WT_a2 *WT_D1_EP2; 
	WT_D1_AmendV = WT_D1_AmendV + WT_Vd;
	WT_D1_EP2 = WT_D1_EP1;
	WT_D1_EP1 = error_dis;

	return WT_D1_AmendV;
}

fp64 WT_D2_PID(double error_dis,struct PID pid)
{
	fp64  WT_a0 = 0.0;
	fp64  WT_a1 = 0.0;
	fp64  WT_a2 = 0.0;
	fp64  WT_Vd = 0.0;


	WT_a0 = ( pid.p * ( 1 + 1 / pid.i + pid.d ));
	WT_a1 = ( -pid.p * (1 + 2 * pid.d));
	WT_a2 = ( pid.p * pid.d );

	WT_Vd = WT_a0 *error_dis + WT_a1 *WT_D2_EP1 + WT_a2 *WT_D2_EP2;
	WT_D2_AmendV = WT_D2_AmendV + WT_Vd;
	WT_D2_EP2 = WT_D2_EP1;
	WT_D2_EP1 = error_dis;

	return WT_D2_AmendV;
}

/**********************************END OF FILE*********************************/
