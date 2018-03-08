/*
file:	nvram.c
data:	2006.12.21
discription:basic read and write for e2prom
reference:
created by winter_mao@163.com
*/
#include "oc_i2c_master_regs.h"
#include "oc_i2c_master.h"
#include "nvram.h"

char nvram_ReadBlock(int address, char *pBlock, int length)
{
	char ReadAddr[2];

	if( (length == 0)|| ((address >> 8) > NVRAM_MAX_PAGE) )
	{
		return (0);
	}

	ReadAddr[0] = (char)(address >> 8);
	ReadAddr[1] = (char)address;
	
	#ifdef NVRAM_32KBIT
	if(alt_i2c_master_write(NVRAM_CODE,ReadAddr,2,OC_I2C_MASTER_CR_STA_MSK)==0)
	{
		NVRAM_MSG("nvram_ReadBlock: write NVRAM DeviceAddr fail\n");
		return (0);
	}
	
	if(alt_i2c_master_read(NVRAM_CODE, pBlock, length, OC_I2C_MASTER_CR_STA_MSK | OC_I2C_MASTER_CR_STO_MSK) ==0 )
	{
		NVRAM_MSG("nvram_ReadBlock: read NVRAM data fail\n");
		return (0);
	}
	#else
	if(alt_i2c_master_write(NVRAM_CODE | (ReadAddr[0]<<1),ReadAddr[1],1,OC_I2C_MASTER_CR_STA_MSK)==0)
	{
		NVRAM_MSG("nvram_ReadBlock: write NVRAM DeviceAddr fail\n");
		return (0);
	}
	
	if(alt_i2c_master_read(NVRAM_CODE | (ReadAddr[0]<<1), pBlock, length, OC_I2C_MASTER_CR_STA_MSK | OC_I2C_MASTER_CR_STO_MSK) ==0 )
	{
		NVRAM_MSG("nvram_ReadBlock: read NVRAM data fail\n");
		return (0);
	}
	#endif
	return (-1);
}

char nvram_WriteBlock(int address, char *pBlock, int length)
{
	unsigned char count,i;
	char buff[NVRAM_PAGE_SIZE+2];
	
  if( (length == 0)|| ((address >> 8) > NVRAM_MAX_PAGE) )
	{
		return (0);
	}
	
  while( length )
  {
    count = NVRAM_PAGE_SIZE - ( address & (NVRAM_PAGE_SIZE - 1));
    if( count > length) count = length;

		#ifdef NVRAM_32KBIT
		buff[0] = (char)(address >> 8);
		buff[1] = (char)address;
		for (i=1; i <= count; i++) buff[i+1] = *pBlock++;
		
		if(alt_i2c_master_write(NVRAM_CODE,buff,count+2,OC_I2C_MASTER_CR_STA_MSK | OC_I2C_MASTER_CR_STO_MSK)==0)
		{
			NVRAM_MSG("nvram_WriteBlock: write NVRAM fail\n");
			return (0);
		}
		#else
		buff[0] = NVRAM_CODE | ((address >> 8) << 1);
		buff[1] = (char)address;
		for (i=1; i <= count; i++) buff[i+1] = *pBlock++;
		if(alt_i2c_master_write(buff[0],buff+1,count+1,OC_I2C_MASTER_CR_STA_MSK | OC_I2C_MASTER_CR_STO_MSK)==0)
		{
			NVRAM_MSG("nvram_WriteBlock: write NVRAM fail\n");
			return (0);
		}
		#endif
		
		nvram_WriteDelay(NVRAM_WRITE_DELAY);
    address += count;
    length -= count;
	}
	return (-1);
}

void nvram_WriteDelay(int num)
{
	int i;
	while(num--)
		for(i=0;i<60000;i++);
}


