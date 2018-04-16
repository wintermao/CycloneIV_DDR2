/*
 * dac2904.c
 *
 *  Created on: 2018-3-2
 *      Author: mmh
 */
#include "dac2904_regs.h"
#include "dac2904.h"
#include "stdbool.h"

void dac2904_init(dac2904_dev *dev,alt_u32 base)
{
	dev->base=base;
}

void dac2904_write(dac2904_dev *dev,alt_u32 data)
{
	IOWR_DAC2904_DATA(dev->base,data);
}
