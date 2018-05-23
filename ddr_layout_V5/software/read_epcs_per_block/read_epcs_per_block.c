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
 #include "altera_avalon_epcs_flash_controller.h"
 #define test_size 65536
 //#define read_epcs

int cmp(unsigned char *buff,int size_buff,unsigned char *source,int size_source)
{
	unsigned char *p_buff,*p_source,a,b;
	int i,j;

	p_buff=buff;
	p_source=source;
	for(j=0;j<(size_buff-size_source);j++)
	{
		for(i=0;i<size_source;i++)
		{
			a=*(p_buff+i);
			b=*(p_source+i);
			if(a==b) continue;
			else
			{
				p_buff++;
				break;
			}
		}
		if(i==size_source) break;
	}
	if(j==(size_buff-size_source)) return -1;
	else return j;
}
void epcs()

{
 int i,j,locate;
 unsigned char  epcsbuf[test_size];
 //unsigned char source[6]={0x50,0x4b,0x03,0x04,0x0a,0x00};	//zipfile content
 //unsigned char source[6]={0x3e,0x00,0x17,0xa0,0xc1,0xd8}; //display block 2
 //unsigned char source[6]={0x3a,0x88,0x45,0x11,0x04,0xf4};	//elf content
 unsigned char source[6]={0x31,0x2f,0x12,0x12,0xf1,0x25};	//sof content
 int ret_code;
 alt_flash_fd*  my_epcs;//定义句柄
 int offset;
 my_epcs = alt_flash_open_dev(EPCS_FLASH_NAME);//打开FLASH器件，获取句柄
 if(my_epcs==NULL) printf("open %s failed!\n",EPCS_FLASH_NAME);

#ifdef read_epcs
 ret_code = alt_epcs_flash_get_info(my_epcs,(flash_region **) my_epcs->region_info,(int *)my_epcs->number_of_regions);//获取配置芯片信息
#else
 ret_code = alt_get_flash_info(my_epcs,(flash_region **) my_epcs->region_info,(int *)my_epcs->number_of_regions);
#endif

 if(ret_code!=0) printf("get epcs flash info error!\n");
 printf("the flash Regions=%d\n",my_epcs->number_of_regions);
 for(i=0;i<my_epcs->number_of_regions;i++)
 {
	 printf("Reginon[%d].offset=%d\n",i,my_epcs->region_info[i].offset);
	 printf("Reginon[%d].size=%d\n",i,my_epcs->region_info[i].region_size);
	 printf("Reginon[%d].numberOfBlock=%d\n",i,my_epcs->region_info[i].number_of_blocks);
	 printf("Reginon[%d].blockSize=%d\n",i,my_epcs->region_info[i].block_size);
 }
for(j=0;j<my_epcs->region_info[0].number_of_blocks;j++)
{
 offset=j * my_epcs->region_info[0].block_size; //calc offset
#ifdef read_epcs
 //ret_code = alt_epcs_flash_read(my_epcs, my_epcs->region_info[0].offset+offset, epcsbuf, test_size); //读test_size字节
 ret_code = alt_epcs_flash_read(my_epcs, offset, epcsbuf, test_size); //读test_size字节
#else
 //ret_code = alt_read_flash(my_epcs,my_epcs->region_info[0].offset+offset,epcsbuf, test_size);
 ret_code = alt_read_flash(my_epcs,offset,epcsbuf, test_size);
#endif

printf("j=%d ",j);
 printf("read epcs: ");
  for(i=0;i<32;i++)
  {
   printf("%02x ",epcsbuf[i]);
  }
  printf("\n");
  locate=cmp(epcsbuf,test_size,source,6);
  if(locate==-1) printf("find target empty!\n");
  else printf("find target ok!,lacate=0x%x\n",locate);
}
  /*
  printf("\nafter erase:\n");
  ret_code = alt_epcs_flash_erase_block(my_epcs,my_epcs->region_info->offset+offset);//擦除第8块
  ret_code = alt_epcs_flash_read(my_epcs, my_epcs->region_info->offset+offset, epcsbuf, test_size); //读test_size字节
  printf("read epcs: ");
	for(i=0;i<test_size;i++)
	{
	 printf("%02x ",epcsbuf[i]);
	}
  printf("\nwrite epcs:\n");
  for(i=0;i<test_size;i++)
   epcsbuf[i]=i;
 ret_code = alt_epcs_flash_write(my_epcs, my_epcs->region_info->offset+offset, epcsbuf, test_size); //写test_size字节
 ret_code = alt_epcs_flash_read(my_epcs, my_epcs->region_info->offset+offset, epcsbuf, test_size); //读test_size字节
 printf("read epcs: ");
	for(i=0;i<test_size;i++)
	{
	 printf("%02x ",epcsbuf[i]);
	}
  printf("\n");
  */
}

int main()
{
	epcs();
	return 0;
}
