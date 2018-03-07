/*
 * SPI Test code. 
 * License. Do whatever you want with the code. Just remember my name :)
 * Author : Zubair Lutfullah Kakakhel. But most of this comes from scattered forum posts..
 * Email : EL12ZLK@LEEDS.AC.UK
 */
#include "alt_types.h"
#include "sys/alt_stdio.h"
#include "io.h"
#include "system.h"
#include "sys/alt_cache.h"

#include "altera_avalon_spi.h"
#include "altera_avalon_spi_regs.h"

#include "sys/alt_irq.h"

//This is the ISR that runs when the SPI Slave receives data
static void spi_rx_isr(void* isr_context){

	alt_printf("ISR :) %x \n" ,  IORD_ALTERA_AVALON_SPI_RXDATA(SPI_SLAVE_BASE));

        //This resets the IRQ flag. Otherwise the IRQ will continuously run.
	IOWR_ALTERA_AVALON_SPI_STATUS(SPI_SLAVE_BASE, 0x0);

}

int main()
{
  alt_printf("Hello from Nios II!\n");

  int return_code,ret;
  char spi_command_string_tx[10] = "$HELLOABC*";
  char spi_command_string_rx[10] = "$HELLOABC*";
 
  //This registers the Slave IRQ with NIOS
  ret = alt_ic_isr_register(SPI_SLAVE_IRQ_INTERRUPT_CONTROLLER_ID,SPI_SLAVE_IRQ,spi_rx_isr,(void *)spi_command_string_tx,0x0);
  alt_printf("IRQ register return %x \n", ret);

  //You need to enable the IRQ in the IP core control register as well.
  IOWR_ALTERA_AVALON_SPI_CONTROL(SPI_SLAVE_BASE,ALTERA_AVALON_SPI_CONTROL_SSO_MSK | ALTERA_AVALON_SPI_CONTROL_IRRDY_MSK);
  
  //Just calling the ISR to see if the function is OK.
  spi_rx_isr(NULL);

  return_code = alt_avalon_spi_command(SPI_MASTER_BASE,0 ,
                              1, spi_command_string_tx,
                              0, spi_command_string_rx,
                              0);

  return_code = alt_avalon_spi_command(SPI_MASTER_BASE,0 ,
                                1, &spi_command_string_tx[1],
                                0, spi_command_string_rx,
                                0);

  return_code = alt_avalon_spi_command(SPI_MASTER_BASE,0 ,
                                1, &spi_command_string_tx[2],
                                0, spi_command_string_rx,
                                0);

  return_code = alt_avalon_spi_command(SPI_MASTER_BASE,0 ,
                                1, &spi_command_string_tx[3],
                                0, spi_command_string_rx,
                                0);

  if(return_code < 0)
	  	 alt_printf("ERROR SPI TX RET = %x \n" , return_code);

  alt_printf("Transmit done. RET = %x spi_rx %x\n",return_code,spi_command_string_rx[0]);
  
  //RX is done via interrupts.
  alt_printf("Rx done \n");
  return 0;

}

