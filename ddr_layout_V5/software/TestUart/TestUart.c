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

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "system.h"

int main()
{
  FILE *fp;
  int i=0;
  char ch;
  char buff[40];
  if((fp=fopen("/dev/uart_0","r+"))==NULL)
  {
	  printf("open device %s error!\n",UART_0_NAME);
	  return 0;
  }
  while(1)
  {
	  sprintf(buff,"this is test, i=%d\n",i);
	  printf("%s",buff);
	  fwrite(buff,strlen(buff),1,fp);
	  if(fread(&ch,1,1,fp)!=0)
	  {
		  printf("revice ch =%c\n",ch);
	  }
	  i++;
	  usleep(50000);
  }
  printf("Hello from Nios II!\n");

  return 0;
}
