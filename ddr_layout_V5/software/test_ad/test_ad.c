#include "alt_types.h"
#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_pio_regs.h"
#include "dac2904.h"
#include "ad9245.h"
#include "clk_gen.h"

#define PIO_KEY_SW0	0x02
#define PIO_KEY_SW1	0x01
#define PIO_KEY_SW2	0x04
#define PIO_KEY_SW3	0x08

volatile int edge_capture=0;
int triger=0;

static void handle_button_interrupts(void* context, alt_u32 id)
{
  /* Cast context to edge_capture's type.
   * It is important to keep this volatile,
   * to avoid compiler optimization issues.
   */
  volatile int* edge_capture_ptr = (volatile int*) context;
  /* Store the value in the Button's edge capture register in *context. */
  *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_KEY_BASE);
  /* Reset the Button's edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_KEY_BASE, 0);

  /*
   * Read the PIO to delay ISR exit. This is done to prevent a spurious
   * interrupt in systems with high processor -> pio latency and fast
   * interrupts.
   */
  IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_KEY_BASE);
}

static void init_button_pio()
{
  /* Recast the edge_capture pointer to match the alt_irq_register() function
  * prototype. */
  void* edge_capture_ptr = (void*) &edge_capture;
  /* Enable all 4 button interrupts. */
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_KEY_BASE, 0xf);
  /* Reset the edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_KEY_BASE, 0x0);

  /*
   * Register the interrupt handler.
   * Provision is made here for systems that might have either the
   * legacy or enhanced interrupt API active, or for the Nios II IDE
   * which does not support enhanced interrupts. For systems created using
   * the Nios II softawre build tools, the enhanced API is recommended
   * for new designs.
   */

  alt_irq_register( PIO_KEY_IRQ, edge_capture_ptr,handle_button_interrupts);
}

static void disable_button_pio()
{
  /* Disable interrupts from the button_pio PIO component. */
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_KEY_BASE, 0x0);
  /* Un-register the IRQ handler by passing a null handler. */
  alt_irq_register( PIO_KEY_IRQ, NULL, NULL );

}

static void ButtonsHandle( void )
{

	if (0 != edge_capture)
	{
	  switch (edge_capture)
	  {
		case PIO_KEY_SW0:
			printf("\nButton 1 (SW0) Pressed. capture=0x%x\n",edge_capture);
			triger=1;
		  break;
		case PIO_KEY_SW1:
			printf("\nButton 2 (SW1) Pressed. capture=0x%x\n",edge_capture);
			triger=2;
		  break;
		case PIO_KEY_SW2:
			printf("\nButton 3 (SW2) Pressed. capture=0x%x\n",edge_capture);
			triger=3;
		  break;
		case PIO_KEY_SW3:
			printf("\nButton 4 (SW3) Pressed. capture=0x%x\n",edge_capture);
			triger=4;
		  break;
		default:
			printf("\nNo key. capture=0x%x\n",edge_capture);
			triger=0;
		  break;
	  }
	  edge_capture=0;
	}
}

int main()
{
	clk_gen_dev dev_clk;
	dac2904_dev dev_dac2904;
	ad9245_dev dev_ad9245;
	int i=0;
	printf("Begin spi_test from Nios II!\n");
	/* Initialize the Buttons/Switches (SW0-SW3) */
	init_button_pio();
	clk_gen_init(&dev_clk,CLK_GEN_BASE);
	clk_gen_write_light(&dev_clk,ALT_CPU_CPU_FREQ/4);
	dac2904_init(&dev_dac2904,DAC2904_1_BASE);
	clk_gen_write_dac1(&dev_dac2904,54);	//set DA freq to 1M
	ad9245_init(&dev_ad9245,AD9245_1_BASE);
	clk_gen_write_ad1(&dev_ad9245,54); 	//set samble freq to 1M
	while(1)
	{
		ButtonsHandle();
		if(triger != 0)
		{
			switch(triger)
			{
			case 1:
				dac2904_write(&dev_dac2904,i);
				i=(i+10)&0x3fff;
				break;
			case 2:
				dac2904_write(&dev_dac2904,i);
				i=(i-10)&0x3fff;
				break;
			case 3:
				dac2904_write(&dev_dac2904,i);
				i=(i+100)&0x3fff;
				break;
			case 4:
				dac2904_write(&dev_dac2904,i);
				i=(i-100)&0x3fff;
				break;
			default:
				break;
			}
			triger=0;
			printf("dac=0x0%4x , ad=0x%04x\n",i,ad9245_read_ad(&dev_ad9245));
		}
	}
	disable_button_pio();
	return 0;
}
