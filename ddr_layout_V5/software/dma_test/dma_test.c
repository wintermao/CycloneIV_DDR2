/*
 * dma_test.c
 *
 *  Created on: 2018-2-4
 *      Author: mmh
 */


#include "system.h"
#include "sys/alt_timestamp.h"          // Interval Timer
#include "alt_types.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/alt_dma.h"

#define CHAR_LENGTH    1024

static volatile int tx_done = 0;
volatile static alt_u8 chr[CHAR_LENGTH];
//callback funtion
static void done (void* handle)
{
    tx_done++;
}

int main()
{
  alt_u32 t0,t1,dt;
  alt_u32 i,timestamp_freq;
  alt_u32 *ddr_dword1,*ddr_dword2;
  alt_u32 offset_source,offset_dest,base_source,base_dest,size_byte;
  //创建DMA信道
  alt_dma_txchan txchan;
  alt_dma_rxchan rxchan;
  //DDR2_BASE
  base_source=DDR2_BASE;
  base_dest=DDR2_BASE;
  offset_source=0x1000000;
  offset_dest=0x2000000;
  size_byte=0x100000;

  ddr_dword1=base_source+offset_source;
  ddr_dword2=base_dest+offset_dest;
	for(i=0;i<size_byte/4;i++)		//generate data,size is 1M byte
	{
	  *ddr_dword1=i;
	  ddr_dword1++;
	}
  timestamp_freq=alt_timestamp_freq();
  printf("system freq= %ld Hz\n", timestamp_freq);
  alt_timestamp_start();

	 //-----------------------------------------------------------
	 //打开发送通道
	 if ((txchan = alt_dma_txchan_open("/dev/dma_0")) == NULL)
	 {
		 printf ("Failed to open transmit channel /dev/dma_0\n");
		 exit (1);
	 }
	 else
		 printf("打开发送通道.\n");
	 //打开接收通道
	if ((rxchan = alt_dma_rxchan_open("/dev/dma_0")) == NULL)
	{
	  printf ("Failed to open receive channel /dev/dma_0\n");
	  exit (1);
	}
	else
	  printf("打开接收通道.\n");
	//start send
     ddr_dword1=base_source+offset_source;
     if (alt_dma_txchan_send(    txchan,
    		 	 	 	 	 	 ddr_dword1,
    		 	 	 	 	 	 size_byte,
                                 NULL,
                                 NULL) < 0)
     {
         printf ("Failed to post transmit request.\n");
         exit (1);
     }
     else
     {
    	 //t0 = alt_timestamp();
    	 printf("开始发送.\n");
     }
     //start receive
     ddr_dword2=base_dest+offset_dest;
     if (alt_dma_rxchan_prepare( rxchan,
    		 	 	 	 	 	 ddr_dword2,
    		 	 	 	 	 	 size_byte,
    		 	 	 	 	 	 done,
                                 NULL) < 0)
     {
         printf ("Failed to post receive request.\n");
         exit (1);
     }
     else
     {
    	 t0 = alt_timestamp();
    	 printf("开始接收.\n");
     }
     //-----------------------------------------------------------
     /* 等待发送结束 */
     while (!tx_done);
     t1 = alt_timestamp();
     printf ("Transfer successful!\n");
     dt=t1-t0;
     printf("dma dword transmit: t0=%ld t1=%ld dt=%ld time=%fs\n", t0,t1,dt,(double)dt/timestamp_freq);
     //-----------------------------------------------------------
     //关闭DMA接收信道
     alt_dma_txchan_close(txchan);


     return 0;

}
