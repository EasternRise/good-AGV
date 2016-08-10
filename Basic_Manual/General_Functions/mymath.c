#include "all.h"

//�ĸ���ȡ���ֵ
fp64 Max_Four(fp64 a,fp64 b,fp64 c,fp64 d)
{
   fp64 maxdelta1,maxdelta2;
   
   maxdelta1=max(a,b);
   maxdelta2=max(c,d);
   
   return max(maxdelta1,maxdelta2);
} 

/********************************************************************************************************
** �������ƣ�Int32Abs
** �������ܣ�32λ��������ֵ����
** ��ڲ�����int32 Data
** ���ڲ���������ֵ
*********************************************************************************************************/
int16 Int16Abs(int16 Data)
{
	if(Data<0)
 		return -Data;
	else 
 		return Data;
}

int32 Int32Abs(int32 Data)
{
	if(Data<0)
 		return -Data;
	else 
 		return Data;
}
int64 Int64Abs(int64 Data)
{
	if(Data<0)
 		return -Data;
	else 
 		return Data;
}
/********************************************************************************************************
** �������ƣ�Fp32Abs
** �������ܣ�32λ����������ֵ����
** ��ڲ�����fp32 Data
** ���ڲ���������ֵ
*********************************************************************************************************/
fp32 Fp32Abs(fp32 Data)
{
	if(Data<0)
 		return -Data;
	else 
 		return Data;
}
/********************************************************************************************************
** �������ƣ�Fp64Abs
** �������ܣ�64λ����������ֵ����
** ��ڲ�����fp64 Data
** ���ڲ���������ֵ
*********************************************************************************************************/

fp64 Fp64Abs(fp64 Data)
{
	if(Data<0)
 		return -Data;
	else 
 		return Data;
}



//**********************************************************************************************************************
//�����ĸ��ֺ���
//**********************************************************************************************************************


//����������
fp64 Getlength(struct Pointfp64 a1, struct Pointfp64 a2)
{
   fp64 length;
   fp64 dx;
   fp64 dy;
   
   dx=a1.x-a2.x;
   dy=a1.y-a2.y;
   
   length=sqrt(dx*dx+dy*dy);
   
   return length;
}



//������������β����a1,a2������һ��������a2ָ��a1
struct Vector MakeVector1(struct Pointfp64 a1, struct Pointfp64 a2)
{
   struct Vector a;
   fp64 m;
   a.coordinate.x=a1.x-a2.x;
   a.coordinate.y=a1.y-a2.y;
   
   a.length=sqrt(a.coordinate.x*a.coordinate.x+a.coordinate.y*a.coordinate.y);
   
   if(a.length==0)
   {
      a.angle=0;
   }
   else
   { 
      m=a.coordinate.x/a.length;
   
      a.angle=acos(m);
   }
   
   if(a.coordinate.y<0)
   {
     a.angle=2*PI-a.angle;
   }
   
   return a;
}


//����������ָ�򣬲���һ����λ����
struct Vector MakeVector2(fp64 angle)
{
    struct Vector a;
    
    a.coordinate.x=cos(angle);
    a.coordinate.y=sin(angle);
 
    a.angle=angle;
    
    a.length=1;
    
    return a;
} 


//����һ��������ģ���ͷ��ǣ������������
 struct Vector MakeVector3(fp64 length,fp64 angle)
{  
    struct Vector a;
    
    a.angle=angle;
    
    a.length=length;
    
    a.coordinate.x=length*cos(angle);
    a.coordinate.y=length*sin(angle);
   
    return a;
}


//����һ�������������ʾ�������������
struct Vector MakeVector4(fp64 x,fp64 y)
{
    struct Vector a;
    fp64 m;
    a.coordinate.x=x;
    a.coordinate.y=y;
    
    
    a.length=sqrt(a.coordinate.x*a.coordinate.x+a.coordinate.y*a.coordinate.y);
    m=a.coordinate.x/a.length;
    a.angle=acos(m);
    
    if(a.coordinate.y<0)
    {
      a.angle=2*PI-a.angle;
    }
    return a;
}
    
    
    
//�����������ĵ��
fp64 DotProduct(struct Vector a1,struct Vector a2)
{
     return a1.coordinate.x*a2.coordinate.x+a1.coordinate.y*a2.coordinate.y;
}





//��һ��������һ���ض������ϵ�ͶӰ
fp64 Projection(struct Vector a1,fp64 angle)
{
     
    return DotProduct(a1,MakeVector2(angle));
}





//*********************************************************************************************************************************
//�����ֱ����һ�㵽ֱ�ߵĴ���
//*********************************************************************************************************************************
struct Pointfp64 GetFoot(fp64 a,fp64 b,fp64 c,struct Pointfp64 m)
{
   struct Pointfp64 n;
   
   if((a!=0)&&(b!=0))
   {
     n.x=((b*b*m.x)-a*c-a*b*m.y)/(a*a+b*b);
     
     n.y=((a*a*m.y)-b*c-a*b*m.x)/(a*a+b*b);
   }
   
   
   if(a==0)
   {
     n.x=m.x;
     n.y=-c/b;
   }
   
   
   
   if(b==0)
   {
     n.x=-c/a;
     n.y=m.y;
   }
   
   
   return n;
}



//**************************************************************************************************************************************
//�����ֱ�߹�ֱ��������һ��ķ�������������һ��ָ��ֱ�ߣ�ֱ�߷���Ϊax+by+c=0
//**************************************************************************************************************************************
struct Vector GetVector1 (fp64 a,fp64 b,fp64 c,struct Pointfp64 m)
{
  
  struct Vector n;
  
  if(a*m.x+b*m.y+c==0)
  {
    n.coordinate.x=0;
    n.coordinate.y=0;
    n.angle=0;
    n.length=0;
  }
  else
  {
    n=MakeVector1(GetFoot(a,b,c,m),m);
  }
  return n;
}





//*********************************************************************************************************************************************
//Բ��·���ĸ��ֺ���
//*********************************************************************************************************************************************


//��֪Բ�������Բ������������߷�����Բ

struct Circle GetCircle(struct Pointfp64 start_pos,fp64 start_direction,struct Pointfp64 aim_pos,fp64 aim_direction)
{
     
     struct Circle circle;

     struct Vector start_vector;
     struct Vector aim_vector;
     
     start_vector=MakeVector2(start_direction);
     aim_vector=MakeVector2(aim_direction);
     
     
     if((Fp64Abs(aim_direction-PI-start_direction)<0.001)|(Fp64Abs(aim_direction+PI-start_direction)<0.001))
     {     
        circle.center.x=(start_pos.x+aim_pos.x)/2;
        circle.center.y=(start_pos.y+aim_pos.y)/2;
     }
     else
     {
        circle.center.x=((start_vector.coordinate.x)*(aim_vector.coordinate.y)*(start_pos.x)-(start_vector.coordinate.y)*(aim_vector.coordinate.x)*(aim_pos.x)+(start_vector.coordinate.y)*(aim_vector.coordinate.y)*(start_pos.y-aim_pos.y))/(aim_vector.coordinate.y*start_vector.coordinate.x-start_vector.coordinate.y*aim_vector.coordinate.x);
         
        circle.center.y=((start_vector.coordinate.x)*(aim_vector.coordinate.x)*(start_pos.x-aim_pos.x)+(start_pos.y)*(start_vector.coordinate.y)*(aim_vector.coordinate.x)-(aim_pos.y)*(aim_vector.coordinate.y)*(start_vector.coordinate.x))/(start_vector.coordinate.y*aim_vector.coordinate.x-aim_vector.coordinate.y*start_vector.coordinate.x);
     }
     
     circle.r=sqrt((start_pos.x-circle.center.x)*(start_pos.x-circle.center.x)+(start_pos.y-circle.center.y)*(start_pos.y-circle.center.y));
     
     return circle;
}

//�����Բ�ϴ�a1��a2��ľ��룬��Ϊ˳ʱ�����ʱ���������,˳ʱ��1����ʱ��0
fp64 Circle_Length(struct Circle circle,struct Pointfp64 a1,struct Pointfp64 a2,uint8 turndir)
{

    struct Vector a1_vector;
    struct Vector a2_vector;
    fp64 delta_angle;
    
    a1_vector=MakeVector1(a1,circle.center);
    a2_vector=MakeVector1(a2,circle.center);
    
    if(a2_vector.angle<a1_vector.angle)
    {
      delta_angle=a2_vector.angle-a1_vector.angle+2*PI;
    }
    else
    {
      delta_angle=a2_vector.angle-a1_vector.angle;
    }
    
    if(turndir==0)
    {
      return delta_angle*circle.r;
    }
    else
    {
      return circle.r*(2*PI-delta_angle);
    }
}
//***********************************************************************************************************************************************************************


//�����ֱ����ȫ�������еķ�����yֵ����ķ��򣩷�ΧΪ��0��PI��
fp64 Linedirect (fp64 a,fp64 b,fp64 c)
{
   fp64 linedirect;
   
   if(b!=0)
   {
      linedirect=atan((-a)/b);
      if(linedirect<0)
      {
        linedirect=linedirect+PI;
      }
   }
   else
   {   
      linedirect=PI/2;
   }
   return linedirect;
}
     
fp64 MATH_GetLineAngle(struct Pointfp64 Startpoint, struct Pointfp64 Endpoint)
{	    
	fp64 AngleStartToEnd;
	
	if( Fp64Abs(Startpoint.x - Endpoint.x) <= 0.02)
    {
        if(Startpoint.y > Endpoint.y)
            AngleStartToEnd = -PI*0.5;
        else 
            AngleStartToEnd =  PI*0.5;
    }
    
    else
    {
        AngleStartToEnd = atan( (Endpoint.y -Startpoint.y) / (Endpoint.x - Startpoint.x) );
    }
    
    if ( (Startpoint.x > Endpoint.x) && (Startpoint.y <= Endpoint.y) )
        
        AngleStartToEnd = AngleStartToEnd + PI;
        
    if ( (Startpoint.x > Endpoint.x ) && (Startpoint.y > Endpoint.y) )
    
        AngleStartToEnd = AngleStartToEnd - PI;
            
    return AngleStartToEnd;
}

fp64  MATH_Distance( struct Pointfp64 StartPonit, struct Pointfp64 EndPoint ) 
{
   fp64 dist = sqrt(  ( StartPonit.x - EndPoint.x ) * ( StartPonit.x - EndPoint.x ) 
			         +( StartPonit.y - EndPoint.y ) * ( StartPonit.y - EndPoint.y ) );
   return dist ;
}

fp64 Max(fp64 a,fp64 b,fp64 c,fp64 d)

{
   fp64 maxdelta1,maxdelta2;
   
   maxdelta1=max(a,b);
   maxdelta2=max(c,d);
   
   return max(maxdelta1,maxdelta2);
}

/********************************************************************************************************
** �������ƣ�Round_Off
** �������ܣ�����ڲ�����������
** ��ڲ�����
** ���ڲ�����
*********************************************************************************************************/
int32 Round_Off(float a)
  {
  int32 b;
  b=(int32)a;
  if((a-b)>0.5)
    b=b+1;
  else 
    b=b;
  return b;
  }