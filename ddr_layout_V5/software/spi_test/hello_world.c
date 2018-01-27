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
#include "system.h"
#include "altera_avalon_spi.h"
#include "altera_avalon_pio_regs.h"

int main()
{
	alt_u8 txbuff[2],rxbuff[2];
	int result;
	txbuff[0]=0x10;txbuff[1]=0x5a;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,0,rxbuff,0);
	printf("write 0x105a,returen 0x%x\n",result);

	txbuff[0]=0x30;txbuff[1]=0x01;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	printf("write 0x3001,returen 0x%x 0x%x 0x%x\n",result,rxbuff[0],rxbuff[1]);

	txbuff[0]=0x30;txbuff[1]=0x03;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	printf("write 0x3003,returen 0x%x 0x%x 0x%x\n",result,rxbuff[0],rxbuff[1]);

  printf("Hello from Nios II!\n");

  return 0;
}
