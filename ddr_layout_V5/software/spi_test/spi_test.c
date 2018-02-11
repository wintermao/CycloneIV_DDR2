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

#include "spi_test.h"
#include "ad5142_spi.h"


volatile int edge_capture=0;
int triger=0;

#ifdef PIO_KEY_NAME

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

#endif

#ifdef SPI_0_NAME
static void rw_spi(void)
{
	alt_u8 txbuff[2],rxbuff[2];
	int result;
	static alt_u8 i=0;

	//txbuff[0]=0x10;txbuff[1]=0x5a;
	//result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,0,rxbuff,0);
	//printf("write 0x%02x%02x,return %d\n",txbuff[0],txbuff[1],result);

	//txbuff[0]=0x20;txbuff[1]=0x5a;
	//result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,0,rxbuff,0);
	//printf("write 0x%02x%02x,return %d\n",txbuff[0],txbuff[1],result);
/*
	txbuff[0]=0x10;txbuff[1]=i;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,0,rxbuff,0);
	printf("write 0x%02x%02x,return %d, ",txbuff[0],txbuff[1],result);
	txbuff[0]=0x30;txbuff[1]=0x03;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	printf("read 0x%02x%02x,return %d 0x%02x%02x\n",txbuff[0],txbuff[1],result,rxbuff[0],rxbuff[1]);
	i++;
	*/
	txbuff[0]=0x10;txbuff[1]=i;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	//result=alt_avalon_spi_command(SPI_0_BASE,0,1,txbuff+1,0,rxbuff,0);
	//printf("s write 0x%02x%02x,return %d, ",txbuff[0],txbuff[1],result);
	//printf("s read 0x%02x%02x,return %d 0x%02x%02x\n",txbuff[0],txbuff[1],result,rxbuff[0],rxbuff[1]);
	txbuff[0]=0x30;txbuff[1]=0x03;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	txbuff[0]=0x30;txbuff[1]=0x02;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	txbuff[0]=0x30;txbuff[1]=0x01;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	txbuff[0]=0x30;txbuff[1]=0x00;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	//result=alt_avalon_spi_command(SPI_0_BASE,0,0,txbuff,2,rxbuff,0);
	//result=alt_avalon_spi_command(SPI_0_BASE,0,1,txbuff+1,2,rxbuff,0);
	printf("read 0x%02x%02x,return %d 0x%02x%02x\n",txbuff[0],txbuff[1],result,rxbuff[0],rxbuff[1]);
	i++;
/*
	txbuff[0]=0x33;txbuff[1]=0x00;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	printf("write 0x%02x%02x,return %d 0x%02x%02x\n",txbuff[0],txbuff[1],result,rxbuff[0],rxbuff[1]);


	txbuff[0]=0x30;txbuff[1]=0x01;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	printf("write 0x%02x%02x,return %d 0x%02x%02x\n",txbuff[0],txbuff[1],result,rxbuff[0],rxbuff[1]);

	txbuff[0]=0x30;txbuff[1]=0x02;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	printf("write 0x%02x%02x,return %d 0x%02x%02x\n",txbuff[0],txbuff[1],result,rxbuff[0],rxbuff[1]);


	txbuff[0]=0x30;txbuff[1]=0x03;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	printf("write 0x%02x%02x,return %d 0x%02x%02x\n",txbuff[0],txbuff[1],result,rxbuff[0],rxbuff[1]);

	txbuff[0]=0x30;txbuff[1]=0x04;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	printf("write 0x%02x%02x,return %d 0x%02x%02x\n",txbuff[0],txbuff[1],result,rxbuff[0],rxbuff[1]);
*/
}
static void rw_spi_2(void)
{
	alt_u8 txbuff[2],rxbuff[2];
	int result;
	static alt_u8 i=0;

	txbuff[0]=0x11;txbuff[1]=i;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,0,rxbuff,0);
	txbuff[0]=0x31;txbuff[1]=0x03;
	result=alt_avalon_spi_command(SPI_0_BASE,0,2,txbuff,2,rxbuff,0);
	printf("read 0x%02x%02x,return %d 0x%02x%02x\n",txbuff[0],txbuff[1],result,rxbuff[0],rxbuff[1]);
	i++;
}
#endif

void spi_new(ad5152_dev *dev)
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

int main()
{
	ad5152_dev dev;
	printf("Begin spi_test from Nios II!\n");
#ifdef PIO_KEY_NAME
	/* Initialize the Buttons/Switches (SW0-SW3) */
	init_button_pio();
#endif
	ad5142_init(&dev,SPI_0_BASE,0);
	ad5142_protect(&dev,false);
	while(1)
	{
#ifdef PIO_KEY_NAME
		ButtonsHandle();

#endif
		if(triger!=0)
		{
#ifdef SPI_0_NAME
			//rw_spi();
			spi_new(&dev);
			//rw_spi_2();
#endif
			triger=0;
		}
	}
	disable_button_pio();
  return 0;
}
