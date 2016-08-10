#include "all.h"

//·������ѡ�� 
uint8 RouteForm=RouteFree;

//·��������ɵı�־,1��ʾδ��ɣ�0��ʾ�����
uint8 RouteFinish;

//////////////////////////////////////////////
//ѡ�����·�����õĵ��󣨵���
uint8  SetPointList;

//��ǰ���õ����е������������
uint16 Point_Num;
       
//��ǰ��Ӧ�������õ����е��±꣨����
uint16 Point_NowNum;

//����ʱ��Ӧ�ĵ����±�
uint16 Point_EndNum;
    
//ÿ����Ѱ�ο���ķ�Χ������
uint16 Count_Step=9;
 
struct  Pointfp64 StartPoint;
struct  Pointfp64 AimPoint;
fp64    Start_angle;
fp64    Aim_Angle;
fp64    s_now;
struct  Pointfp64 now_pos;
fp64    Line_Angle;
fp64    s_NowAim;

fp64    Start_Speed;
fp64    Top_Speed;
fp64    End_Speed;
fp64   	Up_Ratio;
fp64   	Down_Ratio;
fp64  	Amend_a1 ;					// ������ٶ�
fp64 	Amend_a2 ;					// ������ٶ�

/////////////////////////////////////////////


//
void SetLine( int16 speed_now, int16 speed_top, int16 speed_end, fp32 AP, fp32 DP, struct Pointfp64 aim_pos, fp64 Macc , fp64 radian)
{
	LCD_SetXY(0,1);
	LCD_WriteString("setting1");
	RouteForm=RouteLine;	
    RouteFinish=1;
	StartPoint=Gps_List[0].position;
	//Line_Angle = 0.0;
	s_now      = Gps_List[0].distance;					
	now_pos    = Gps_List[0].position;
	Line_Angle = MATH_GetLineAngle(now_pos,aim_pos);
	s_NowAim   = MATH_Distance(now_pos,aim_pos);				// ��¼����һ��ʼ�Ķ�λ��Ϣ
   	MaxAcc=Macc;
   	AimPoint=aim_pos;
   	Start_angle=Gps_List[0].angle;
   	Aim_Angle=radian;
   	Start_Speed=speed_now;
   	Top_Speed=speed_top;
   	End_Speed=speed_end;
   	Up_Ratio=AP;
   	Down_Ratio=DP;
   	Amend_a1 = ( speed_top - speed_now )/( AP * s_NowAim );					// ������ٶ�
   	Amend_a2 = ( speed_end - speed_top )/( DP * s_NowAim );					// ������ٶ�
  	LCD_SetXY(0,2);
	LCD_WriteString("setting2");
   	PID_Clear();			//��������·���������
}



void GoLine(void)
{
	fp64 			motor;				// ���ֱ�׼�ٶ�
	fp64 			amend_motor;		// ���ӻ���ٵ��ٶ���
	fp64 			error_angle = 0.0;	// �Ƕ����
	fp64 			error_dis = 0.0;	// λ�����
	//fp64           	v_err_x;
	//fp64            v_err_y;	
	fp64			k;					//line��б��
	//fp64  			speed_x;
	//fp64 			speed_y;
	fp64            phi;
	struct Pointfp64 pos;
	
	//�������۵�����						
		k =tan(Line_Angle);

	    if(Fp64Abs(AimPoint.x - StartPoint.x)>=0.02)
	    {
		    pos.x=(k*Gps_List[0].position.y+Gps_List[0].position.x+k*k*StartPoint.x-k*StartPoint.y)/(1+k*k);
		    pos.y=k*(pos.x-StartPoint.x)+StartPoint.y;
	    }
	    else
	    {
		    pos.x=StartPoint.x;
		    pos.y=Gps_List[0].position.y;
	    }	    
	    
	// ���ٽ׶�    
	    if( MATH_Distance(StartPoint,pos)  < (Up_Ratio * s_NowAim) )						
	    {
	    	if (motor<Top_Speed)
	    	{
	    	   amend_motor = Amend_a1 * MATH_Distance(StartPoint,pos);
	 
    		   motor = Start_Speed + amend_motor;
    		}
    		else
    		{
    		   motor =Top_Speed;
    		} 
    	}
    	
    // ���ٽ׶�	
    	else if( MATH_Distance(StartPoint,pos) > (s_NowAim - s_NowAim * Down_Ratio) )			
    	{
    		amend_motor = Amend_a2 * ( MATH_Distance(StartPoint,pos)-(s_NowAim - s_NowAim * Down_Ratio) );
		
    		motor =Top_Speed + amend_motor;
    		
    	}
   
    	/*else if( MATH_Distance(StartPoint,pos) > (s_NowAim - 800) )			// ���ٽ׶�
    	{
    		if (motor>End_Speed)
    		{
    		   motor=0x3100;
    		}
    	}*/
    	
    	
    // ���ٽ׶�	
    	else																
    	{
    	    motor = Top_Speed;
    	}  
    	

    	     	 	
    //�Ƕ����	
        error_angle = Gps_List[0].radian-Aim_Angle;
        
    //λ�����
        error_dis =   ( Gps_List[0].position.x - StartPoint.x ) * sin( Line_Angle ) 
				    - ( Gps_List[0].position.y - StartPoint.y ) * cos( Line_Angle );
				    
  	
	// ������ٶ�
       // speed_x=motor*cos(Line_Angle);
       // speed_y=motor*sin(Line_Angle);
        
	 
	 if( MATH_Distance(StartPoint,pos)  >= (Up_Ratio * s_NowAim) )
	 {
    	Vout[0]=1000*AnglePID(error_angle,Pid_List[7].PROP,Pid_List[7].Ti,Pid_List[7].Td);

	 } 	
	  	Vout[1]=DistancePID(error_dis,Pid_List[8].PROP,Pid_List[8].Ti,Pid_List[8].Td);
     
		if(Vout[0]>300)
    		 Vout[0]=300;
   		if(Vout[0]<-300)
    		 Vout[0]=-300;
  
  
  // Vout[0]=0;
       
        
        //v_err_x=-Vout[1]*sin(Line_Angle);
        //v_err_y=Vout[1]*cos(Line_Angle);
        
        phi=Gps_List[0].radian;
	
    Speed_F =55.3859*Vout[0];//1812.747826*(speed_x+v_err_x)*(cos(phi)-sin(phi)) + 1812.747826*(speed_y+v_err_y)*(cos(phi)+sin(phi)) + 7478.744943*(Vout[0]);

    Speed_FR=55.3859*Vout[0];//-1812.747826*(speed_x+v_err_x)*(cos(phi)+sin(phi)) + 1812.747826*(speed_y+v_err_y)*(cos(phi)-sin(phi)) - 7478.744943*(Vout[0]);

    Speed_BL=0.09095*(motor+Vout[1])-2.8648*Vout[0];//-1812.747826*(speed_x+v_err_x)*(cos(phi)+sin(phi)) + 1812.747826*(speed_y+v_err_y)*(cos(phi)-sin(phi)) + 7478.744943*(Vout[0]);

    Speed_BR=0.09095*(motor+Vout[1])+2.8648*Vout[0];// 1812.747826*(speed_x+v_err_x)*(cos(phi)-sin(phi)) + 1812.747826*(speed_y+v_err_y)*(cos(phi)+sin(phi)) - 7478.744943*(Vout[0]);



		Data[12]=error_angle;
		Data[13]=error_dis;
		
		
		SaveMovingData();
		
		
		
		LCD_SetXY(0,0);
		LCD_WriteString("A_FL:");
		LCD_WriteNum(error_convert[1]);
		//LCD_WriteString("   ");

		LCD_SetXY(0,1);
		LCD_WriteString("A_FR:");
		LCD_WriteNum(error_convert[3]);
		//LCD_WriteString("    ");
	
		LCD_SetXY(0,2);
		LCD_WriteString("A_BL:");
		LCD_WriteNum(error_convert[5]);
		//LCD_WriteString("    ");	

		LCD_SetXY(0,3);
		LCD_WriteString("A_BR:");
		LCD_WriteNum(error_convert[7]);
		//LCD_WriteString("    ");	

		LCD_SetXY(0,4);
		LCD_WriteString("Vout[0]:");
		LCD_WriteNum(7478.744943*Vout[0]/14000);
        LCD_WriteString("    ");	

        
        LCD_SetXY(0,5);
		LCD_WriteString("Vout[1]:");
		LCD_WriteNum(1812.747826*Vout[1]*sin(Line_Angle)/14000);
		LCD_WriteString("   ");	
		
		LCD_SetXY(0,6);
		LCD_WriteString("A:");
		LCD_WriteNum(Gps_List[0].angle);
		//LCD_WriteString("    ");
		
		LCD_SetXY(0,7);
		LCD_WriteString("X:");
		LCD_WriteNum(Gps_List[0].position.x);
		//LCD_WriteString("  ");	
		
		LCD_SetXY(10,7);
		LCD_WriteString("Y:");
		LCD_WriteNum(Gps_List[0].position.y);
		//LCD_WriteString(" ");
       } 


void GoLineTest(void)
{
	int err;
	struct Pointfp64 aimpos1={1000,0};
	//struct Pointfp64 aimpos2={2000,2000};
	//struct Pointfp64 aimpos3={4000,4000};
	struct Value Values[]=
     {   
        {(void*)&Pid_List[8].PROP,	TYPE_FP64,	"DP"}, 
        {(void*)&Pid_List[8].Ti,	TYPE_FP64,	"DI"}, 
        {(void*)&Pid_List[8].Td,	TYPE_FP64,	"DD"},
        {(void*)&Pid_List[7].PROP,	TYPE_FP64,	"AP"}, 
        {(void*)&Pid_List[7].Ti,	TYPE_FP64,	"AI"}, 
        {(void*)&Pid_List[7].Td,	TYPE_FP64,	"AD"},

      };
	DISPLAY_ValuesManager(Values,6,PID_NANDPAGE);
	
	
	LCD_Clear();
	GPS_Clear();
	PID_Clear();
	
	OSMboxPost(RouteMbox,&err);
	RouteForm=RouteStop;
	
	/******************************Route[1]******************************************************************/
	PID_flag=0;
	SetLine(50,500,40,0.2,0.2,aimpos1,100,0);
	
	while(RouteFinish) 
	 {
	 
	 	
		if(Gps_List[0].position.x>=aimpos1.x)
	 	{
	 		RouteFinish=0;
	 		RouteForm=RouteStop;
	 		LCD_SetXY(0,2);
			LCD_WriteString("route1 done");	
		}
		OSTimeDly(1);
	 }
	/*PressAnyKey();
	SetLine(40,1000,40,0.2,0.2,aimpos2,100,10);
	
	while(RouteFinish) 
	 {
		if(Gps_List[0].position.x>=aimpos2.x)
	 	{
	 		RouteFinish=0;
	 		RouteForm=RouteStop;
	 		LCD_SetXY(0,2);
			LCD_WriteString("route2 done");	
		}
		OSTimeDly(1);
	 }
	PressAnyKey();
	SetLine(40,1000,40,0.2,0.2,aimpos3,100,10);
	
	while(RouteFinish) 
	 {
		if(Gps_List[0].position.x>=aimpos3.x)
	 	{
	 		RouteFinish=0;
	 		RouteForm=RouteStop;
	 		LCD_SetXY(0,2);
			LCD_WriteString("route3 done");	
		}
		OSTimeDly(1);
	 }
	PressAnyKey();
	
*/
}


