/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
// #include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
// #include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
#include "MMC_SD.h"		/* Example: Header file of existing MMC/SDC contorl module */

/* Definitions of physical drive number for each drive */
// #define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
// #define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
// #define USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	 if(pdrv)
    {
        return STA_NOINIT;  //��֧�ִ���0����
    }
		return 0;
// 	DSTATUS stat;
// 	int result;

// 	switch (pdrv) {
// 	case ATA :
// 		result = ATA_disk_status();

// 		// translate the reslut code here

// 		return stat;

// 	case MMC :
// 		result = MMC_disk_status();

// 		// translate the reslut code here

// 		return stat;

// 	case USB :
// 		result = USB_disk_status();

// 		// translate the reslut code here

// 		return stat;
// 	}
// 	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	
		u8 res;

    if(pdrv)
    {
        return STA_NOINIT;  //��֧�ִ���0�Ĳ���  0x01
    }

    res = SD_Initialize();//SD_Initialize() /
		if(res)//STM32 SPI��bug,��sd������ʧ�ܵ�ʱ�������ִ����������,���ܵ���SPI��д�쳣
			{
				SD_SPI_SpeedLow();
				SD_SPI_ReadWriteByte(0xff);//�ṩ�����8��ʱ��
				SD_SPI_SpeedHigh();
			}
    if(res == STA_NODISK)
    {
        return STA_NODISK; //0x02
    }
    else if(res != 0)
    {
        return STA_NOINIT;  //�������󣺳�ʼ��ʧ��
    }
    else
    {
        return 0;           //��ʼ���ɹ�
    }
// 	DSTATUS stat;
// 	int result;

// 	switch (pdrv) {
// 	case ATA :
// 		result = ATA_disk_initialize();

// 		// translate the reslut code here

// 		return stat;

// 	case MMC :
// 		result = MMC_disk_initialize();

// 		// translate the reslut code here

// 		return stat;

// 	case USB :
// 		result = USB_disk_initialize();

// 		// translate the reslut code here

// 		return stat;
// 	}
// 	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	u8 res=0;
		if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������		
		res=SD_ReadDisk(buff,sector,count);	 
		if(res)//STM32 SPI��bug,��sd������ʧ�ܵ�ʱ�������ִ����������,���ܵ���SPI��д�쳣
		{
			SD_SPI_SpeedLow();
			SD_SPI_ReadWriteByte(0xff);//�ṩ�����8��ʱ��
			SD_SPI_SpeedHigh();
		}
    	
    //������ֵ����SPI_SD_driver.c�ķ���ֵת��ff.c�ķ���ֵ
    if(res==0x00)return RES_OK;	 
    else return RES_ERROR;	// 	DRESULT res;
// 	int result;

// 	switch (pdrv) {
// 	case ATA :
// 		// translate the arguments here

// 		result = ATA_disk_read(buff, sector, count);

// 		// translate the reslut code here

// 		return res;

// 	case MMC :
// 		// translate the arguments here

// 		result = MMC_disk_read(buff, sector, count);

// 		// translate the reslut code here

// 		return res;

// 	case USB :
// 		// translate the arguments here

// 		result = USB_disk_read(buff, sector, count);

// 		// translate the reslut code here

// 		return res;
// 	}

// 	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	  u8 res=0;  
    if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������		 	 
		res=SD_WriteDisk((u8*)buff,sector,count);
    // ����ֵת��
    if(res == 0x00)return RES_OK;	 
    else return RES_ERROR;	
// 	DRESULT res;
// 	int result;

// 	switch (pdrv) {
// 	case ATA :
// 		// translate the arguments here

// 		result = ATA_disk_write(buff, sector, count);

// 		// translate the reslut code here

// 		return res;

// 	case MMC :
// 		// translate the arguments here

// 		result = MMC_disk_write(buff, sector, count);

// 		// translate the reslut code here

// 		return res;

// 	case USB :
// 		// translate the arguments here

// 		result = USB_disk_write(buff, sector, count);

// 		// translate the reslut code here

// 		return res;
// 	}

// 	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	 DRESULT res;
    if (pdrv)
    {    
        return RES_PARERR;  //��֧�ֵ����̲��������򷵻ز�������
    }
   
    switch(cmd)
	    {
		    case CTRL_SYNC:
				SD_CS=0;
		        if(SD_WaitReady()==0)res = RES_OK; 
		        else res = RES_ERROR;	  
				SD_CS=1;
		        break;	 
		    case GET_SECTOR_SIZE:
		        *(WORD*)buff = 512;
		        res = RES_OK;
		        break;	 
		    case GET_BLOCK_SIZE:
		        *(WORD*)buff = 8;
		        res = RES_OK;
		        break;	 
		    case GET_SECTOR_COUNT:
		        *(DWORD*)buff = SD_GetSectorCount();
		        res = RES_OK;
		        break;
		    default:
		        res = RES_PARERR;
		        break;
	    }

    return res;
// 	DRESULT res;
// 	int result;

// 	switch (pdrv) {
// 	case ATA :

// 		// Process of the command for the ATA drive

// 		return res;

// 	case MMC :

// 		// Process of the command for the MMC/SD card

// 		return res;

// 	case USB :

// 		// Process of the command the USB drive

// 		return res;
// 	}

// 	return RES_PARERR;
}
DWORD get_fattime (void)
{ /*
    struct tm t;
    DWORD date;
    t = Time_GetCalendarTime();
    t.tm_year -= 1980;		//��ݸ�Ϊ1980����
    t.tm_mon++;         	//0-11�¸�Ϊ1-12��
    t.tm_sec /= 2;      	//��������Ϊ0-29
    
    date = 0;
    date = (t.tm_year << 25)|(t.tm_mon<<21)|(t.tm_mday<<16)|\
            (t.tm_hour<<11)|(t.tm_min<<5)|(t.tm_sec);

    return date;*/
	return 0;
}

//�õ��ļ�Calendar��ʽ�Ľ�������,��DWORD get_fattime (void) ��任							
//struct tm
void get_Calendarfattime (DWORD date,DWORD time)
{  	/*
    struct tm t;
	DWORD time_t;

	t.tm_year=(date>>9)&0x007F;  //bit 9-15
	t.tm_mon=(date>>5)&0x000F;   //bit 5-8
	t.tm_mday=date&0x001F;       //bit 0-4

	t.tm_hour=(time>>11)&0x001F; //bit 11-15
	t.tm_min=(time>>5)&0x003F;   //bit  5-10
	t.tm_sec=(time&0x001F)<<1;   //bit  0-4

	t.tm_year+=1980;		     //��ݸ�Ϊ1980�����ļ�FAT��¼��ʽ
	t.tm_mon--;					 //FAT��¼��ʽ1-12,Calendar��Ӧ0-11

	//��������������ҪĿ����Ҫ�õ����ڶ�Ӧ�����������Ƚ����
    time_t=Time_ConvCalendarToUnix(t);
	t=Time_ConvUnixToCalendar(time_t);

    return t; */

}

#endif
