/*
 * ad5781_spi.h
 *
 *  Created on: 2018-2-25
 *      Author: mmh
 */

#ifndef __AD5781_SPI_H__
#define __AD5781_SPI_H__

#include "ad5781_regs.h"
#include "altera_avalon_spi.h"
#include "alt_types.h"
#include "stdbool.h"

typedef struct ad5781_dev_s
{
	alt_u32 base;
	alt_u32 slave;
}ad5781_dev;

void ad5781_init(ad5781_dev *dev,alt_u32 base,alt_u32 slave);
alt_u32 ad5781_read_dac(ad5781_dev *dev);
alt_u32 ad5781_read_control(ad5781_dev *dev);
alt_u32 ad5781_read_clear(ad5781_dev *dev);
void ad5781_write_dac(ad5781_dev *dev,alt_u32 data);
void ad5781_write_control(ad5781_dev *dev,alt_u32 data);
void ad5781_write_clear(ad5781_dev *dev,alt_u32 data);
void ad5781_write_soft(ad5781_dev *dev,alt_u32 data);

#endif /* __AD5781_SPI_H__ */
