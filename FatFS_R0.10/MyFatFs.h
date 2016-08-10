#ifndef __MYFATFS_H
#define __MYFATFS_H
#include <stm32f10x.h>
#include "all.h"
#include "MyTypeDef.h"
extern FIL fil;  
extern FATFS fs;
extern FRESULT fatfs_res;
extern UINT bw;
FRESULT Test_f_mkdir(const TCHAR* path);//����һ����Ŀ¼,����Ŀ¼��·��Test_f_mkdir("/dir");ֻ��һ��һ���Ľ���Ŀ¼	
FRESULT Test_f_deldir(const TCHAR* path);//ɾ��һ��Ŀ¼,����Ŀ¼��·��
FRESULT Test_f_write(char *dat);//д���ַ�
void write_double(double data);//д��double��
void write_float(float data);
void f_mount_off(void );
void f_mount_on( void);
void file_open(const TCHAR *path);
void file_close(void);
void SdTest(void);
#endif
