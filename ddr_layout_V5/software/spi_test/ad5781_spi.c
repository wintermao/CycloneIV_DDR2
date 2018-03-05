/*
 * ad5781_spi.c
 *
 *  Created on: 2018-2-25
 *      Author: mmh
 */
#include "ad5781_spi.h"
#include "stdbool.h"

void ad5781_init(ad5781_dev *dev,alt_u32 base,alt_u32 slave)
{
	dev->base=base;
	dev->slave=slave;
	//ad5781_write_soft(dev,0);
	ad5781_write_control(dev,AD5781_CONTROL_RBUF_MSK);
}

alt_u32 ad5781_read_dac(ad5781_dev *dev)
{
	alt_u8 txbuff[3],rxbuff[3];
	alt_u32 result;
	txbuff[0]=AD5781_REGISTER_DAC>>16 | 0x80;
	alt_avalon_spi_command(dev->base,dev->slave,3,txbuff,0,rxbuff,0);
	alt_avalon_spi_command(dev->base,dev->slave,0,txbuff,3,rxbuff,0);
	result=rxbuff[0]<<16 | rxbuff[1]<<8 | rxbuff[2];
	result=result>>2 & 0x3ffff;
	return result;
}
alt_u32 ad5781_read_control(ad5781_dev *dev)
{
	alt_u8 txbuff[3],rxbuff[3];
	alt_u32 result;
	txbuff[0]=AD5781_REGISTER_CONTROL>>16 | 0x80;
	alt_avalon_spi_command(dev->base,dev->slave,3,txbuff,0,rxbuff,0);
	alt_avalon_spi_command(dev->base,dev->slave,0,txbuff,3,rxbuff,0);
	result=rxbuff[0]<<16 | rxbuff[1]<<8 | rxbuff[2];
	result=result & 0x3ff;
	return result;
}
alt_u32 ad5781_read_clear(ad5781_dev *dev)
{
	alt_u8 txbuff[3],rxbuff[3];
	alt_u32 result;
	txbuff[0]=AD5781_REGISTER_CLEAR>>16 | 0x80;
	alt_avalon_spi_command(dev->base,dev->slave,3,txbuff,0,rxbuff,0);
	alt_avalon_spi_command(dev->base,dev->slave,0,txbuff,3,rxbuff,0);
	result=rxbuff[0]<<16 | rxbuff[1]<<8 | rxbuff[2];
	result=result>>2 & 0x3ffff;
	return result;
}

void ad5781_write_dac(ad5781_dev *dev,alt_u32 data)
{
	alt_u8 txbuff[3],rxbuff[3];
	txbuff[0]=AD5781_REGISTER_DAC>>16 | data>>14;
	txbuff[1]=(data & 0x3fff)>>6;
	txbuff[2]=(data & 0x3f)<<2;
	alt_avalon_spi_command(dev->base,dev->slave,3,txbuff,0,rxbuff,0);
}
void ad5781_write_control(ad5781_dev *dev,alt_u32 data)
{
	alt_u8 txbuff[3],rxbuff[3];
	txbuff[0]=AD5781_REGISTER_CONTROL>>16;
	txbuff[1]=(data & 0xffff)>>8;
	txbuff[2]=data & 0xff;
	alt_avalon_spi_command(dev->base,dev->slave,3,txbuff,0,rxbuff,0);
}
void ad5781_write_clear(ad5781_dev *dev,alt_u32 data)
{
	alt_u8 txbuff[3],rxbuff[3];
	txbuff[0]=AD5781_REGISTER_CLEAR>>16 | data>>14;
	txbuff[1]=(data & 0x3fff)>>6;
	txbuff[2]=(data & 0x3f)<<2;
	alt_avalon_spi_command(dev->base,dev->slave,3,txbuff,0,rxbuff,0);
}
void ad5781_write_soft(ad5781_dev *dev,alt_u32 data)
{
	alt_u8 txbuff[3],rxbuff[3];
	txbuff[0]=AD5781_REGISTER_SOFT>>16;
	txbuff[2]=data & 0x7;	
	alt_avalon_spi_command(dev->base,dev->slave,3,txbuff,0,rxbuff,0);	
}
