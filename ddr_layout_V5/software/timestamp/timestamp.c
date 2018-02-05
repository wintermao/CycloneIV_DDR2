/*
 * timestamp.c
 *
 *  Created on: 2018-2-4
 *      Author: mmh
 */

#include "system.h"
#include "sys/alt_timestamp.h"          // Interval Timer核的驱动头文件
#include "alt_types.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
  alt_u32 t0,t1,dt;
  alt_u8 *ddr_byte1,*ddr_byte2;
  alt_u16 *ddr_word1,*ddr_word2;
  alt_u32 *ddr_dword1,*ddr_dword2;
  alt_u64 *ddr_ddword1,*ddr_ddword2;
  alt_u32 i,timestamp_freq;
  alt_u32 offset_source,offset_dest,base_source,base_dest,size_byte;

  //ddr test bank
  base_source=0;
  base_dest=0;
  offset_source=0x1000000;
  offset_dest=0x2000000;
  size_byte=0x100000;
/*
  //ddr test bank
  base_source=DDR2_BASE;
  base_dest=DDR2_BASE;
  offset_source=0x1000000;
  offset_dest=0x2000000;
  size_byte=0x100000;
*/
/*
  //onchipram test bank
  base_source=ONCHIP_RAM_BASE;
  base_dest=ONCHIP_RAM_BASE;
  offset_source=0;
  offset_dest=2048;
  size_byte=4096;
*/
  ddr_dword1=base_source+offset_source;
  for(i=0;i<size_byte/4;i++)		//generate data,size is 1M byte
  {
	  *ddr_dword1=i;
	  ddr_dword1++;
  }

  timestamp_freq=alt_timestamp_freq();
  printf("system freq= %ld Hz\n", timestamp_freq);
  printf("test data size=0x%x\n",size_byte);
  alt_timestamp_start();                // 开启时间戳服务

  ddr_byte1=base_source+offset_source;
  ddr_byte2=base_source+offset_dest;
  t0 = alt_timestamp();                 // 测量时间戳t0
  for(i=0;i<size_byte;i++)
  {
	  *ddr_byte2=*ddr_byte1;
	  ddr_byte1++;
	  ddr_byte2++;
  }
  t1 = alt_timestamp();                 // 测量时间戳1
  dt=t1-t0;
  printf("byte mode: t0=%ld t1=%ld dt=%ld time=%fs\n", t0,t1,dt,(double)dt/timestamp_freq);

  ddr_word1=base_source+offset_source;
  ddr_word2=base_source+offset_dest;
  t0 = alt_timestamp();                 // 测量时间戳t0
  for(i=0;i<size_byte/2;i++)
  {
	  *ddr_word2=*ddr_word1;
	  ddr_word1++;
	  ddr_word2++;
  }
  t1 = alt_timestamp();                 // 测量时间戳1
  dt=t1-t0;
  printf("word mode : t0=%ld t1=%ld dt=%ld time=%fs\n", t0,t1,dt,(double)dt/timestamp_freq);

  	ddr_dword1=base_source+offset_source;
	ddr_dword2=base_source+offset_dest;
	t0 = alt_timestamp();                 // 测量时间戳t0
	for(i=0;i<size_byte/4;i++)
	{
	  *ddr_dword2=*ddr_dword1;
	  ddr_dword1++;
	  ddr_dword2++;
	}
	t1 = alt_timestamp();                 // 测量时间戳1
	dt=t1-t0;
	printf("dword mode : t0=%ld t1=%ld dt=%ld time=%fs\n", t0,t1,dt,(double)dt/timestamp_freq);

    ddr_ddword1=base_source+offset_source;
	ddr_ddword2=base_source+offset_dest;
	t0 = alt_timestamp();                 // 测量时间戳t0
	for(i=0;i<size_byte/8;i++)
	{
	  *ddr_ddword2=*ddr_ddword1;
	  ddr_ddword1++;
	  ddr_ddword2++;
	}
	t1 = alt_timestamp();                 // 测量时间戳1
	dt=t1-t0;
	printf("ddword mode : t0=%ld t1=%ld dt=%ld time=%fs\n", t0,t1,dt,(double)dt/timestamp_freq);
  return 0;
}
