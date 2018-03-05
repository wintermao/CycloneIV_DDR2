/*
 * spi_test.h
 *
 *  Created on: 2018-1-28
 *      Author: mmh
 */

#ifndef SPI_TEST_H_
#define SPI_TEST_H_

/* Includes */

#include "alt_types.h"
#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "altera_avalon_spi.h"
#include "sys/alt_irq.h"
#include "altera_avalon_pio_regs.h"

/* Button/Switch (SW0-SW3) Related Prototype */
#ifdef PIO_KEY_NAME
static void init_button_pio(void);
static void disable_button_pio(void);
static void ButtonsHandle( void );
#define PIO_KEY_SW0	0x02
#define PIO_KEY_SW1	0x01
#define PIO_KEY_SW2	0x04
#define PIO_KEY_SW3	0x08
#endif

#endif /* SPI_TEST_H_ */
