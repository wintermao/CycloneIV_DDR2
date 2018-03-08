/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include "alt_types.h"
#include "sys/alt_alarm.h"
#include "system.h"
#include "oc_i2c_master.h"
#include "nvram.h"


void Delay_1ms(int num)
{
  int start_time, finish_time;
  start_time = alt_nticks();
  while(1)
  {
    finish_time = alt_nticks();
    if((finish_time-start_time)>=num) break;
  }
}

int main()
{
  alt_u8 led = 0;
  alt_u8 buff[10]="ppkABC",buf1[10];

  printf("Hello from Nios II!\n");

  alt_i2c_master_init();
  nvram_WriteBlock(0,buff,6);
  printf("write NVRAM OVER\n");
  nvram_ReadBlock(0,buf1,6);
  buf1[6]='\0';
  printf("%s\n",buf1);

  return 0;
}
