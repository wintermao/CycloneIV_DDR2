/*
 * ad5142_spi.h
 *
 *  Created on: 2018-2-3
 *      Author: mmh
 */

#ifndef AD5142_SPI_H_
#define AD5142_SPI_H_

#include "ad5142_reg.h"
#include "altera_avalon_spi.h"
#include "alt_types.h"
#include "stdbool.h"

typedef struct ad5142_dev_s
{
	alt_u32 base;
	alt_u32 slave;
}ad5142_dev;

void ad5142_init(ad5142_dev *dev,alt_u32 base,alt_u32 slave);
alt_u8 ad5142_read_rdac(ad5142_dev *dev,alt_u8 channel);
alt_u8 ad5142_read_eeprom(ad5142_dev *dev,alt_u8 channel);
void ad5142_write_rdac(ad5142_dev *dev,alt_u8 channel,alt_u8 data);
void ad5142_write_eeprom(ad5142_dev *dev,alt_u8 channel,alt_u8 data);
void ad5142_reset(ad5142_dev *dev);
void ad5142_protect(ad5142_dev *dev,bool state);
#endif /* AD5142_SPI_H_ */
