#include "all.h"

#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)

int32_t Int32Abs(int32_t Data)
{
	if(Data<0)
		return -Data;
	else 
		return Data;
}
int64_t Int64Abs(int64_t Data)
{
	if(Data<0)
		return -Data;
	else 
		return Data;
}

float F_Abs(float Data)
{
	if(Data<0)
		return -Data;
	else 
		return Data;
}

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
float GetLength(Pointfp64 a,Pointfp64  b)
{
	float length;
	float dx,dy;
	dx = ((float)a.x-(float)b.x)*((float)a.x-(float)b.x);
	dy = ((float)a.y-(float)b.y)*((float)a.y-(float)b.y);
	length = sqrt(dx+dy);
	return length;
}

/*
 * ������: GetDis_P2L
 * ��  ��: ��㵽ֱ�ߵľ���(��֪һ��ʽ: ax+by+c=0)
 * ��  ��: -p ��
 *		   -a -b -c ֱ�߷��̵�ϵ��
 * ��  ��: �㵽ֱ�ߵľ���
 * ��  ��: �ⲿ����
 */
float GetDis_P2L(Pointfp64  p,float a,float b,float c)
{
	return (a*p.x+b*p.y+c)/(sqrt(a*a+b*b));
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
float GetDis_P2L_PK( Pointfp64 p, Pointfp64 p0,double k)
{
	float a,b,c;
	a=k;
	b=-1;
	c=-k*p0.x+p0.y;
	
	return GetDis_P2L(p,a,b,c);
}

int circle_circle_intersection(double x0, double y0, double r0,
                               double x1, double y1, double r1,
                               double *xi, double *yi,
                               double *xi_prime, double *yi_prime)
{
  double a, dx, dy, d, h, rx, ry;
  double x2, y2;

  /* dx and dy are the vertical and horizontal distances between
   * the circle centers.
   */
  dx = x1 - x0;
  dy = y1 - y0;

  /* Determine the straight-line distance between the centers. */
  //d = sqrt((dy*dy) + (dx*dx));
  d = hypot(dx,dy); // Suggested by Keith Briggs

  /* Check for solvability. */
  if (d > (r0 + r1))
  {
    /* no solution. circles do not intersect. */
    return 0;
  }
  if (d < fabs(r0 - r1))
  {
    /* no solution. one circle is contained in the other */
    return 0;
  }

  /* 'point 2' is the point where the line through the circle
   * intersection points crosses the line between the circle
   * centers.
   */

  /* Determine the distance from point 0 to point 2. */
  a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

  /* Determine the coordinates of point 2. */
  x2 = x0 + (dx * a/d);
  y2 = y0 + (dy * a/d);

  /* Determine the distance from point 2 to either of the
   * intersection points.
   */
  h = sqrt((r0*r0) - (a*a));

  /* Now determine the offsets of the intersection points from
   * point 2.
   */
  rx = -dy * (h/d);
  ry = dx * (h/d);

  /* Determine the absolute intersection points. */
  *xi = x2 + rx;
  *xi_prime = x2 - rx;
  *yi = y2 + ry;
  *yi_prime = y2 - ry;

  return 1;
}

