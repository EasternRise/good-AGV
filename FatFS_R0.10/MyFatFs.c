/*--------------File Info-------------------------------------------------------
** ��   ��   ��:  MyFatFs.c
** ��        ��:  Ѧ����    ����
** ����޸�����:  2016.01.18
** ��        ��:  V1.0
** ��        ��:  FATFS���ù��ܲ��Ժ��� .
**------------------------------------------------------------------------------
*******************************************************************************/                                     
#include "MyFatFs.h"
#include "math.h"
 FIL fil;  
FATFS fs;
FRESULT fatfs_res;
UINT bw;
FRESULT filStatus;
/*******************************************************************************
* Function Name  : Test_f_mkdir
* Description    : ����Ŀ¼
* Input          : 
* Return         : res
*******************************************************************************/
FRESULT Test_f_mkdir(const TCHAR* path)//����һ����Ŀ¼,����Ŀ¼��·��Test_f_mkdir("/dir");ֻ��һ��һ���Ľ���Ŀ¼	
{

		
		fatfs_res=f_mkdir(path);//����һ����Ŀ¼

		return fatfs_res;
}
/*******************************************************************************
* Function Name  : Test_f_deldir
* Description    : ɾ��Ŀ¼
* Input          : 
* Return         : res
*******************************************************************************/
FRESULT Test_f_deldir(const TCHAR* path)//ɾ��һ��Ŀ¼,����Ŀ¼��·��;Ŀ¼��������ǿյĲ���ɾ��Test_f_deldir("/dir");	
{
   
		
		fatfs_res=f_unlink(path);//ɾ��һ��Ŀ¼

		return fatfs_res;
}
/*******************************************************************************
* Function Name  : Test_f_write
* Description    : д������
* Input          : 
* Return         : res
*******************************************************************************/

FRESULT Test_f_write(char *dat)
{	 
		f_printf(&fil,"%s",dat);
		return fatfs_res;

}

/*******************************************************************************
* Function Name  : write_double
* Description    : д��double��
* Input          :data:�����double��
* Return         : 
*******************************************************************************/

void write_double(double data)
{
	
//	f_lseek(&fil,fil.fsize);
	if(data<0&&data>-1)
	{

	f_printf(&fil, "%s", "   -0");
	}	else
	{		
  f_printf(&fil, "%5d", (int)data);
	}
	
	  f_printf(&fil, "%c", '.');
		if(data<0)
		data=-data;
		data=data-(int)data;
		data=data*10;
		f_printf(&fil, "%d", (int)data);
		data=data-(int)data;
  	data=data*10;
		f_printf(&fil, "%d", (int)data);
}

/*******************************************************************************
* Function Name  : f_mount_on
* Description    : ����ϵͳ
* Input          : 
* Return         :
*******************************************************************************/
void f_mount_on( void)
{
		f_mount(&fs,"0",1);
}
/*******************************************************************************
* Function Name  : f_mount_off
* Description    : ж��ϵͳ
* Input          : 
* Return         :
*******************************************************************************/
void f_mount_off(void )
{
		f_mount(NULL,"0",1);
}
/*******************************************************************************
* Function Name  : file_open
* Description    : ���ļ����������򴴽�
* Input          : 
* Return         :
*******************************************************************************/
void file_open(const TCHAR *path)
{
		filStatus=f_open(&fil,path,FA_OPEN_ALWAYS | FA_WRITE);
}
/*******************************************************************************
* Function Name  : file_close
* Description    : �ر��ļ�
* Input          : 
* Return         :
*******************************************************************************/
void file_close(void)
{
			f_close(&fil);
}
/*******************************************************************************
* Function Name  : SdTest
* Description    : ���Ժ���
* Input          : 
* Return         :
*******************************************************************************/
void SdTest(void)
{		int i=0;
		double temp=3.14159;
//		Pointfp64 point;
//		point.x=-0.567;
//		point.y=-1000.3432;
		f_mount_on();
		file_open("hello6.txt");
    	for (i=0;i<20;i++)
        {
            write_double(temp);
        }
		file_close();
		f_mount_off();
    
     while(1)
	{
		
		LCD_Clear();
		LCD_SetXY(0,0);
		LCD_WriteString("========SD========");
        
		
        switch(filStatus)
        {
            case FR_OK:
                LCD_SetXY(0,1);
                LCD_WriteString("FR_OK");
                break;
            default :
                LCD_SetXY(0,1);
                LCD_WriteString("ERROR");
                break;
                
        }
		refresh();	
        
		if(KeyReady==1)
		  {
			KeyReady=0;
			switch(KeyValue)
			{
				case keyback:
					return;
			}
		  }
		delay(LCD_DELAY);
	}
}
