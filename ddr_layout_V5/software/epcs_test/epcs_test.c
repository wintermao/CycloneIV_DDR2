/*
 * epcs_test.c
 *
 *  Created on: 2018-2-4
 *      Author: mmh
 */

 #include "system.h"
 #include <stdio.h>
 #include "alt_types.h"
 #include "sys/alt_flash.h"
 #include "sys/alt_flash_dev.h"
 unsigned char  epcsbuf[32];

int ret_code;

alt_flash_fd*  my_epcs;//定义句柄

void epcs()

{
 int i;

my_epcs = alt_flash_open_dev("/dev/epcs_flash_controller_0");//打开FLASH器件，获取句柄

ret_code = alt_epcs_flash_get_info (my_epcs, my_epcs->region_info,my_epcs->number_of_regions);//获取配置芯片信息
printf("ret_code=%d",ret_code);
 if(my_epcs) //信息获取成功
 {
  //example application, read general data from epcs address 0x70000
  ret_code = alt_epcs_flash_erase_block(my_epcs,my_epcs->region_info->offset+0x70000);//擦除第8块
 ret_code = alt_epcs_flash_read(my_epcs, my_epcs->region_info->offset+0x70000, epcsbuf, 40); //读32字节
 printf("offset=%d\n",my_epcs->region_info[0].offset);
  printf("size=%d\n",my_epcs->region_info[0].region_size);
  printf("numberOfBlock=%d\n",my_epcs->region_info[0].number_of_blocks);
  printf("blockSize=%d\n",my_epcs->region_info[0].block_size);
  printf("after erase:\n");
  for(i=0;i<40;i++)
  {
   printf("%x ",epcsbuf[i]);
  }
  printf("\nafter write:\n");
  for(i=0;i<32;i++)
   epcsbuf[i]=i+0x22;
  ret_code = alt_epcs_flash_write(my_epcs, my_epcs->region_info->offset+0x70000, epcsbuf, 32); //写32字节
 ret_code = alt_epcs_flash_read(my_epcs, my_epcs->region_info->offset+0x70000, epcsbuf, 40); //读32字节
 for(i=0;i<40;i++)
  {
   printf("%x ",epcsbuf[i]);
  }
  printf("\n");
  }
 }
int main()
{
	epcs();
}
