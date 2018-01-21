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
	volatile alt_u8 led;
	static char ch;
	static char entry[4];
	int i,j;
	for(j=0;j<10;j++)
	for(i=0,led = 0x1;i<6;i++){
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE, led);
		printf("j=%d led=0x%x\n",j,led);
		led=led<<1;
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
