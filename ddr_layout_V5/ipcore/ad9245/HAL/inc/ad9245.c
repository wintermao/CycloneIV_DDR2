/*
 * ad9245.c
 *
 *  Created on: 2018-3-1
 *      Author: mmh
 */
#include "ad9245.h"
#include "stdbool.h"

void ad9245_init(ad5142_dev *dev,alt_u32 base)
{
	dev->base=base;
}

alt_u32 ad9245_read_ad(ad5142_dev *dev)
{
	alt_u32 result;
	result=IORD_AD9245_DATA(dev->base);
	return result;
}
