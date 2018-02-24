/*
 * ad5142_spi.c
 *
 *  Created on: 2018-2-3
 *      Author: mmh
 */
#include "ad5142_spi.h"
#include "stdbool.h"

void ad5142_init(ad5152_dev *dev,alt_u32 base,alt_u32 slave)
{
	dev->base=base;
	dev->slave=slave;
}

alt_u8 ad5142_read_rdac(ad5152_dev *dev,alt_u8 channel)
{
	alt_u8 txbuff[2],rxbuff[2];
	txbuff[0]=AD5142_COMMAND_READ | (AD5142_RDAC_ADDRESS_MSK & channel);
	txbuff[1]=AD5142_REGISTER_RDAC;
	alt_avalon_spi_command(dev->base,dev->slave,2,txbuff,0,rxbuff,0);
	alt_avalon_spi_command(dev->base,dev->slave,0,txbuff,2,rxbuff,0);
	return rxbuff[1];
}
alt_u8 ad5142_read_eeprom(ad5152_dev *dev,alt_u8 channel)
{
	alt_u8 txbuff[2],rxbuff[2];
	txbuff[0]=AD5142_COMMAND_READ | (AD5142_RDAC_ADDRESS_MSK & channel);
	txbuff[1]=AD5142_REGISTER_EEPROM;
	alt_avalon_spi_command(dev->base,dev->slave,2,txbuff,0,rxbuff,0);
	alt_avalon_spi_command(dev->base,dev->slave,0,txbuff,2,rxbuff,0);
	return rxbuff[1];
}
void ad5142_write_rdac(ad5152_dev *dev,alt_u8 channel,alt_u8 data)
{
	alt_u8 txbuff[2],rxbuff[2];
	txbuff[0]=AD5142_COMMAND_SERIAL_TO_RDAC | (AD5142_RDAC_ADDRESS_MSK & channel);
	txbuff[1]=data;
	alt_avalon_spi_command(dev->base,dev->slave,2,txbuff,0,rxbuff,0);
}
void ad5142_write_eeprom(ad5152_dev *dev,alt_u8 channel,alt_u8 data)
{
	alt_u8 txbuff[2],rxbuff[2];
	txbuff[0]=AD5142_COMMAND_SERIAL_TO_EEPROM | (AD5142_RDAC_ADDRESS_MSK & channel);
	txbuff[1]=data;
	alt_avalon_spi_command(dev->base,dev->slave,2,txbuff,0,rxbuff,0);
}
void ad5142_reset(ad5152_dev *dev)
{
	alt_u8 txbuff[2],rxbuff[2];
	txbuff[0]=AD5142_COMMAND_RESET;
	alt_avalon_spi_command(dev->base,dev->slave,2,txbuff,0,rxbuff,0);
}
void ad5142_protect(ad5152_dev *dev,bool state)
{
	alt_u8 txbuff[2],rxbuff[2];
	txbuff[0]=AD5142_COMMAND_SERIAL_TO_CONTROL;
	if(state==true) txbuff[1]=AD5142_CONTROL_RDAC_PROTECT | AD5142_CONTROL_EEPROM_PROTECT;
	else  txbuff[1]=AD5142_CONTROL_RDAC_NORMAL | AD5142_CONTROL_EEPROM_NORMAL;
	alt_avalon_spi_command(dev->base,dev->slave,2,txbuff,0,rxbuff,0);
}
