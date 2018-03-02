/*
 * ad9245.h
 *
 *  Created on: 2018-3-1
 *      Author: mmh
 */

#ifndef AD9245_H_
#define AD9245_H_

#include "ad5142_reg.h"
#include "altera_avalon_spi.h"
#include "alt_types.h"
#include "stdbool.h"

typedef struct ad9245_dev_s
{
	alt_u32 base;
}ad9245_dev;

void ad9245_init(ad5142_dev *dev,alt_u32 base);
alt_u32 ad9245_read_ad(ad9245_dev *dev);

#endif /* AD9245_H_ */
