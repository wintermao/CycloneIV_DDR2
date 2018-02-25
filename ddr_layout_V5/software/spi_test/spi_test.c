/*
 * "spi test" example.
 */

#include "spi_test.h"
#include "ad5142_spi.h"
#include "ad5781_spi.h"


volatile int edge_capture=0;
int triger=0;

/*********************************************
 * Button/Switch PIO Functions
 *********************************************/

/*******************************************************************
 * static void handle_button_interrupts( void* context, alt_u32 id)*
 *                                                                 *
 * Handle interrupts from the buttons.                             *
 * This interrupt event is triggered by a button/switch press.     *
 * This handler sets *context to the value read from the button    *
 * edge capture register.  The button edge capture register        *
 * is then cleared and normal program execution resumes.           *
 * The value stored in *context is used to control program flow    *
 * in the rest of this program's routines.                         *
 *                                                                 *
 * Provision is made here for systems that might have either the   *
 * legacy or enhanced interrupt API active, or for the Nios II IDE *
 * which does not support enhanced interrupts. For systems created *
 * using the Nios II softawre build tools, the enhanced API is     *
 * recommended for new designs.                                    *
 ******************************************************************/
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
static void handle_button_interrupts(void* context)
#else
static void handle_button_interrupts(void* context, alt_u32 id)
#endif
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

/* Initialize the button_pio. */

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
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
  alt_ic_isr_register(PIO_KEY_IRQ_INTERRUPT_CONTROLLER_ID, PIO_KEY_IRQ,
    handle_button_interrupts, edge_capture_ptr, 0x0);
#else
  alt_irq_register( PIO_KEY_IRQ, edge_capture_ptr,
    handle_button_interrupts);
#endif
}

/* Tear down the button_pio. */

static void disable_button_pio()
{
  /* Disable interrupts from the button_pio PIO component. */
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_KEY_BASE, 0x0);
  /* Un-register the IRQ handler by passing a null handler. */
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
  alt_ic_isr_register(PIO_KEY_IRQ_INTERRUPT_CONTROLLER_ID, PIO_KEY_IRQ,
    NULL, NULL, NULL);
#else
  alt_irq_register( PIO_KEY_IRQ, NULL, NULL );
#endif
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


void spi_rw_ad5142(ad5142_dev *dev)
{
	alt_u8 channel=1;
	alt_u8 result;
	int i;
	ad5142_write_rdac(dev,channel,0xa5);
	//ad5142_write_eeprom(dev,channel,0x79);
	result=ad5142_read_rdac(dev,channel);
	printf("rdac=%x\n",result);
	//result=ad5142_read_eeprom(dev,channel);
	//printf("eeprom=%x\n",result);
	while(1)
	for(i=0;i<255;i++)
	{
		ad5142_write_rdac(dev,channel,i);
		//result=ad5142_read_rdac(dev,channel);
		printf("i=%x rdac=%x\n",i,result);
		usleep(500000);
	}
}
void spi_rw_ad5781(ad5781_dev *dev)
{
	int i;
	alt_u32 result;

	while(1)
	for(i=0;i<0x3ffff;i++)
	{
		ad5781_write_dac(dev,i);
		result=ad5781_read_dac(dev);
		printf("i=%x dac=%x\n",i,result);
		usleep(500000);
	}
}

int main()
{
	ad5142_dev dev;
	ad5781_dev dev_5781;
	printf("Begin spi_test from Nios II!\n");
	/* Initialize the Buttons/Switches (SW0-SW3) */
	init_button_pio();
	ad5142_init(&dev,SPI_0_BASE,0);
	ad5142_protect(&dev,false);
	ad5781_init(&dev_5781,SPI_AD5781_BASE,0);
	while(1)
	{
		ButtonsHandle();

		if(triger!=0)
		{
			//spi_rw_ad5142(&dev);
			spi_rw_ad5781(&dev_5781);
			triger=0;
		}
	}
	disable_button_pio();
	return 0;
}
