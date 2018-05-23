/*
 * dma_test.c
 *
 *  Created on: 2018-5-21
 *      Author: mmh
 */


#include "system.h"
#include "sys/alt_timestamp.h"          // Interval Timer
#include "alt_types.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/alt_dma.h"
#include "clk_gen.h"
#include "clk_device.h"
#include "sys/alt_flash.h"
#include "sys/alt_flash_dev.h"
#include "altera_avalon_epcs_flash_controller.h"
#define data_size 0x49000
//#define read_epcs
static volatile int tx_done = 0;
alt_u32 *ddr_dword1,*ddr_dword2;
alt_u16 *ddr_u16;
alt_u32 offset_source,offset_dest,base_source,base_dest,size_byte;
alt_dma_txchan txchan;
extern int time_1s;
//callback funtion
static void done (void* handle)
{
    tx_done++;
    dma_init(txchan,ddr_dword1,ddr_dword2,size_byte);
}
void dma_init(alt_dma_txchan txchan,alt_u32 *s_addr,alt_u32 *d_addr,alt_u32 t_size)
{
	alt_dma_txchan_ioctl(txchan,  ALT_DMA_TX_ONLY_ON, d_addr);
	alt_dma_txchan_send(txchan, s_addr,	 t_size, done, NULL);
}

//form epcs read wave data,wave=0 is sin wave,wave=1 is triangle wave
int read_wave_data(alt_u8 wave,alt_u16 *buffer)
{
	int ret_code;
	alt_flash_fd*  my_epcs;
	int offset;
	int i;
	
 	my_epcs = alt_flash_open_dev(EPCS_FLASH_NAME);
 	if(my_epcs==NULL) printf("open %s failed!\n",EPCS_FLASH_NAME);
 	ret_code = alt_get_flash_info(my_epcs,(flash_region **) my_epcs->region_info,(int *)my_epcs->number_of_regions);
 	if(ret_code!=0) 
 		{
 			printf("get epcs flash info error!\n");
 			return -1;
 		}
 	printf("the flash Regions=%d\n",my_epcs->number_of_regions);
 	for(i=0;i<my_epcs->number_of_regions;i++)
 	{
	 	printf("Reginon[%d].offset=%d\n",i,my_epcs->region_info[i].offset);
	 	printf("Reginon[%d].size=%d\n",i,my_epcs->region_info[i].region_size);
	 	printf("Reginon[%d].numberOfBlock=%d\n",i,my_epcs->region_info[i].number_of_blocks);
	 	printf("Reginon[%d].blockSize=%d\n",i,my_epcs->region_info[i].block_size);
	}
	if(wave==0)	offset=(my_epcs->region_info[0].number_of_blocks-4) * my_epcs->region_info[0].block_size; //calc offset
	else offset=(my_epcs->region_info[0].number_of_blocks-2) * my_epcs->region_info[0].block_size; //calc offset
			
 	ret_code = alt_read_flash(my_epcs,offset,buffer, data_size);
	alt_flash_open_dev(EPCS_FLASH_NAME);
	return 0;
}

int main()
{
	clk_gen_dev dev_clk;
	alt_u32 t0,t1,dt;
  alt_u32 i,timestamp_freq;
  alt_u32 divide;
  int tx_done_last;
  int ret_code;
	
  tx_done_last=tx_done;
  divide=8;
  clk_gen_init(&dev_clk,CLK_GEN_BASE);
  clk_gen_write(&dev_clk,LIGHT,ALT_CPU_CPU_FREQ);
  clk_gen_write(&dev_clk,DAC1,divide);	//set DA freq to 1M

  //DDR2_BASE
  base_source=DDR2_BASE;
  base_dest=DAC2904_0_BASE;
  offset_source=0x2000000;
  offset_dest=0x000000;
  size_byte=data_size;

  ddr_dword1=base_source+offset_source;
  ddr_dword2=base_dest+offset_dest;
  
  ret_code=read_wave_data(1,ddr_dword1);
  if(ret_code!=0)
  	{
  		printf("read wave data fail!\n");
  		return -1;
  	}
  	
  timestamp_freq=alt_timestamp_freq();
  printf("time stamp system freq= %ld Hz\n", timestamp_freq);
  alt_timestamp_start();

	 //-----------------------------------------------------------
	 //open transmit channel
	 if ((txchan = alt_dma_txchan_open(DMA_0_NAME)) == NULL)
	 {
		 printf ("Failed to open transmit channel %s\n",DMA_0_NAME);
		 exit (1);
	 }
	 else
		 printf("open transmit channel.\n");

	//start send
	alt_dma_txchan_ioctl(txchan,  ALT_DMA_SET_MODE_32, NULL);
	alt_dma_txchan_ioctl(txchan,  ALT_DMA_TX_ONLY_ON, ddr_dword2);
	dma_init(txchan,ddr_dword1,ddr_dword2,size_byte);
	Timer_Initial();
	/*
	if (alt_dma_txchan_send(    txchan,
							 ddr_dword1,
							 size_byte,
							 done,
							  NULL) < 0)
	{
	  printf ("Failed to post transmit request.\n");
	  exit (1);
	}
	else
	{
	 t0 = alt_timestamp();
	 printf("start send.\n");
	}
	*/
     //-----------------------------------------------------------
	/*
     while (!tx_done);
     t1 = alt_timestamp();
     printf ("Transfer successful!\n");
     printf("divide freq=%d\n",divide);
     dt=t1-t0;
     printf("dma dword transmit: size=0x%x t0=%ld t1=%ld dt=%ld time=%fs\n", size_byte,t0,t1,dt,(double)dt/timestamp_freq);

     //-----------------------------------------------------------
     //关闭DMA接收信道

	while(1)
	{
		int i;
		if(tx_done=1)
		{
			tx_done=0;
			alt_dma_txchan_ioctl(txchan,  ALT_DMA_TX_ONLY_ON, ddr_dword2);
			alt_dma_txchan_send(    txchan,
										 ddr_dword1,
										 size_byte,
										 done,
										  NULL);
			i++;
			printf("dma transmit successful ,count=%5d\n",i);
		}
	}
	*/

	while(1)
	{
		if(time_1s==1)
		{
			time_1s=0;
			printf("transtims is %4d\n",tx_done-tx_done_last);
			tx_done_last=tx_done;
		}

	}
     alt_dma_txchan_close(txchan);


     return 0;

}
