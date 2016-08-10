
/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include <math.h>

/*
 * ������: MaxFour
 * ��  ��: ���ĸ����е����ֵ
 * ��  ��: -a -b -c -d �ĸ�����
 * ��  ��: �ĸ����е����ֵ
 * ��  ��: �ⲿ����
 */
double MaxFour(double a,double b,double c,double d)
{
	double maxtemp1,maxtemp2;
	maxtemp1=Max(a,b);
	maxtemp2=Max(c,d);
	return Max(maxtemp1,maxtemp2);
}
 
/*
 * ������: GetLength
 * ��  ��: ��������֮��ľ���
 * ��  ��: -a -b ������
 * ��  ��: ������֮��ľ���
 * ��  ��: �ⲿ����
 */
double GetLength(struct Point a,struct Point b)
{
	double length;
	double dx,dy;
	dx = (a.x-b.x)*(a.x-b.x);
	dy = (a.y-b.y)*(a.y-b.y);
	length = sqrt(dx+dy);
	return length;
}

/*
 * ������: GetLineSlope
 * ��  ��: �����������ߵ�б��
 * ��  ��: -a -b ������
 * ��  ��: ���������ߵ�б��
 * ��  ��: �ⲿ����
 */
double GetLineSlope(struct Point a,struct Point b)
{
	double slope;
	if(Abs(a.x-b.x) <= 0.02)
		slope=pi/2;
	else
		slope = (b.y-a.y)/(b.x-a.x);
	
	return slope;
}

/*
 * ������: GetLineAngle
 * ��  ��: ��������֮�����ߵ����(����)
 * ��  ��: -sta ��ʼ��
 *		   -end ������
 * ��  ��: ���������ߵ����(����-PI~PI)
 * ��  ��: �ⲿ����
 */
double GetLineAngle(struct Point sta,struct Point end)
{
	double radian;
	if(Abs(sta.x-end.x) <= 0.02)
	{
		if(sta.y>end.y) radian=-pi/2;
		else radian=pi/2;
	}
	else
	{
		radian = atan((end.y-sta.y)/(end.x-sta.x));
		
		//atanֵ��Ϊ���ĺ͵�һ���ޣ�����Ҫͨ���жϷ�������������޵Ĳ���
		if(sta.x>end.x && sta.y<end.y) radian+=pi;
		else if(sta.x>end.x && sta.y>end.y) radian-=pi;
	}
	
	return radian;
}

/****************************���ֵ㵽ֱ�߷��������******************************/

/*
 * ������: GetDis_P2L
 * ��  ��: ��㵽ֱ�ߵľ���(��֪һ��ʽ: ax+by+c=0)
 * ��  ��: -p ��
 *		   -a -b -c ֱ�߷��̵�ϵ��
 * ��  ��: �㵽ֱ�ߵľ���
 * ��  ��: �ⲿ����
 */
double GetDis_P2L(struct Point p,double a,double b,double c)
{
	return Abs(a*p.x+b*p.y+c)/(sqrt(a*a+b*b));
}

/*
 * ������: GetDis_P2L_PP
 * ��  ��: ��㵽ֱ�ߵľ���(��֪����ʽ: (y-y1)(x2-x1)=(y2-y1)(x-x1))
 * ��  ��: -p  ��
 *		   -p1 -p2 ֱ��������
 * ��  ��: �㵽ֱ�ߵľ���
 * ��  ��: �ⲿ����
 */
double GetDis_P2L_PP(struct Point p,struct Point p1,struct Point p2)
{
	double a,b,c;
	a=p2.y-p1.y;
	b=p1.x-p2.x;
	c=p2.x*p1.y-p1.x*p2.y;
	
	return GetDis_P2L(p,a,b,c);
}

/*
 * ������: GetDis_P2L_PK
 * ��  ��: ��㵽ֱ�ߵľ���(��֪��бʽ: y-y0=k(x-x0))
 * ��  ��: -p  ��
 *		   -p0 ֱ����һ��
		   -k  ֱ�߷��̵�б��
 * ��  ��: �㵽ֱ�ߵľ���
 * ��  ��: �ⲿ����
 */
double GetDis_P2L_PK(struct Point p,struct Point p0,double k)
{
	double a,b,c;
	a=k;
	b=-1;
	c=-k*p0.x+p0.y;
	
	return GetDis_P2L(p,a,b,c);
}

/****************************���ֵ㵽ֱ�߷�������******************************/

/*
 * ������: GetFoot_P2L
 * ��  ��: ��㵽ֱ�ߵĴ���(��֪һ��ʽ: ax+by+c=0)
 * ��  ��: -p ��
 *		   -a -b -c ֱ�߷��̵�ϵ��
 * ��  ��: ����
 * ��  ��: �ⲿ����
 */
struct Point GetFoot_P2L(struct Point p,double a,double b,double c)
{
	struct Point foot;
	foot.x=(b*b*p.x-a*b*p.y-a*c)/(a*a+b*b);
	foot.y=(a*a*p.y-a*b*p.x-b*c)/(a*a+b*b);
	
	return foot;
}

/*
 * ������: GetFoot_P2L_PP
 * ��  ��: ��㵽ֱ�ߵĴ���(��֪����ʽ: (y-y1)(x2-x1)=(y2-y1)(x-x1))
 * ��  ��: -p  ��
 *		   -p1 -p2 ֱ��������
 * ��  ��: ����
 * ��  ��: �ⲿ����
 */
struct Point GetFoot_P2L_PP(struct Point p,struct Point p1,struct Point p2)
{
	struct Point foot;
	double a,b,c;
	a=p2.y-p1.y;
	b=p1.x-p2.x;
	c=p2.x*p1.y-p1.x*p2.y;
	
	foot = GetFoot_P2L(p,a,b,c);
	return foot;
}

/*
 * ������: GetFoot_P2L_PK
 * ��  ��: ��㵽ֱ�ߵĴ���(��֪��бʽ: y-y0=k(x-x0))
 * ��  ��: -p  ��
 *		   -p0 ֱ����һ��
		   -k  ֱ�߷��̵�б��
 * ��  ��: ����
 * ��  ��: �ⲿ����
 */
struct Point GetFoot_P2L_PK(struct Point p,struct Point p0,double k)
{
	struct Point foot;
	double a,b,c;
	a=k;
	b=-1;
	c=-k*p0.x+p0.y;
	
	foot = GetFoot_P2L(p,a,b,c);
	return foot;
}

/**********************************END OF FILE*********************************/

