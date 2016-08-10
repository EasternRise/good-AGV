#include "all.h"

int Menu_Count=8;//�������Ҫ�����溯�����������
int SubMenu1_Count=8;	
int SubMenu2_Count=8;
int SubMenu3_Count=1;
int SubMenu4_Count=1;
int SubMenu5_Count=1;
int SubMenu6_Count=1;
int SubMenu7_Count=1;
int SubMenu8_Count=3;
int ShortcutMenu_Count=8;

struct Path Menu[]=//���溯�����д����ѭ��
{
	{PATH_System,	   "System",		FOLDER},
	{test,			   "Test",			FOLDER},
	{Error_Show,	   "Debug",			CONFIG},
	{Retry,	 		   "Restart",		CONFIG},
	{Ringtest,	 	   "Ringtest",		CONFIG},
	{RouteInfo,		   "FixInfo",		CONFIG},
	{Fix,		   	   "Fix",			CONFIG},
	{Owen,			   "owen",          FOLDER},
};

struct Path SubMenu1[]=//(�ο���System)�����˵��µĵ�1����������ΪFOLDERʱ�����Ӳ˵�����
{	
	{sys_Gyro,      	"Gyro",    		 	CONFIG},
	{sys_encoder,     	"Encoder",			CONFIG},
	{sys_gps,   		"GPS",		    	CONFIG}, 
	{sys_mecanum,       "Mecanum",       	CONFIG},
	{sys_SA_ST,			"SA ST",  	    	CONFIG},
	{sys_can,			"CAN_BUS",  	    CONFIG},
	{steertest,         "steertest",		CONFIG},
	{manualdata,	    "man_data",	    	CONFIG},
};

struct Path SubMenu2[]=//(�ο�: test)�����˵��µĵ�2����������ΪFOLDERʱ�����Ӳ˵�����
{
	{DataBackTest, "databack",		CONFIG},
	{PointPathtest,"Ppathtest",		CONFIG},
	{Shootest,	   "Shootest",		CONFIG},
	{Sonictest,	   "Sonictest",		CONFIG},
	{LidarInit,    "lidarInit",		CONFIG},
	{LidarTest,	   "Lidartest",		CONFIG},
	{LidarUse,	   "LidarUse",		CONFIG},
	{KeepTest,	   "KeepTest",		CONFIG}
};

struct Path SubMenu3[]=//(�ο�: red)�����˵��µĵ�3����������ΪFOLDERʱ�����Ӳ˵�����
{
	{PATH_System,	   "System",		FOLDER},
};

struct Path SubMenu4[]=//(�ο�: blue)�����˵��µĵ�4����������ΪFOLDERʱ�����Ӳ˵�����
{
	{PATH_System,	   "System",		FOLDER},

};

struct Path SubMenu5[]=//�����˵��µĵ�5����������ΪFOLDERʱ�����Ӳ˵�����
{
	{PATH_System,	   "System",		FOLDER},
};

struct Path SubMenu6[]=//�����˵��µĵ�6����������ΪFOLDERʱ�����Ӳ˵�����
{
	{PATH_System,	   "System",		FOLDER},
};

struct Path SubMenu7[]=//�����˵��µĵ�7����������ΪFOLDERʱ�����Ӳ˵�����
{
	{PATH_System,	   "System",		FOLDER},
};

struct Path SubMenu8[]=//(�ο���owen)�����˵��µĵ�8����������ΪFOLDERʱ�����Ӳ˵�����
{
	{owen_mecanum,	   "Mecanum",		CONFIG},
	{owen_maxon,	   "Maxon",		    CONFIG},
	{owen_route,	   "Route",		    CONFIG},
};

//warning:����shortcut�������û�����������ͬһ�����������У����鲻Ҫ�������޸����������õ���ȫ�ֱ�����������������ʹ�õĺ���
#if ShortcutSetting
struct Path ShortcutMenu[]=
{
	{SaveScreen,      	"SaveScreen",    		RED}, 
	{ShowScreen,     	"ShowScreen",			RED},
	{SC_SA_ST,			"SA ST",  	    		RED},
	{SC_Relay,  		"Relay",	    		RED},
	{SC_gps,     		"GPS",					RED},
	{SC_lightboard,   	"Lightboard",       	RED},
	{SC_SelfDef,   		"Self Def",       		RED},
	{SC_Manual,   		"Manual",       		RED},
};
#endif