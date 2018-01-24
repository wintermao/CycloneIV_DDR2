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

#include "led_test.h"

#ifdef PIO_LED_NAME

/*
 * static void TestLEDs(void)
 *
 * This function tests LED functionality.
 * It exits when the user types a 'q'.
 */

static void TestLEDs(void) {
	static char ch;
	static char entry[4];
	static char led_msk[6]={PIO_LED0_MSK,PIO_LED1_MSK,PIO_LED2_MSK,PIO_LED3_MSK,PIO_LED4_MSK,PIO_LED5_MSK};
	int i,j;
	for(j=0;j<100;j++)
	for(i=0;i<6;i++){
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE, led_msk[i]);
		printf("j=%d led=0x%x\n",j,led_msk[i]);
		usleep(50000);
	}

}

#endif

int main() {
#ifdef PIO_LED_NAME
	TestLEDs();
#endif
	return (0);
}
