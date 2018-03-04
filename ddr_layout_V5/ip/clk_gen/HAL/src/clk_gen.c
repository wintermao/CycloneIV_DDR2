/*
 * clk_gen.c
 *
 *  Created on: 2018-3-2
 *      Author: mmh
 */
#include "clk_gen_regs.h"
#include "clk_gen.h"
#include "stdbool.h"

void clk_gen_init(clk_gen_dev *dev,alt_u32 base)
{
	dev->base=base;
}

alt_u32 clk_gen_read_ad1(clk_gen_dev *dev)
{
	alt_u32 result;
	result= IORD_CLK_GEN_AD1(dev->base);
	return result;
}
alt_u32 clk_gen_read_ad2(clk_gen_dev *dev)
{
	alt_u32 result;
	result= IORD_CLK_GEN_AD2(dev->base);
	return result;
}
alt_u32 clk_gen_read_dac1(clk_gen_dev *dev)
{
	alt_u32 result;
	result= IORD_CLK_GEN_DAC1(dev->base);
	return result;
}
alt_u32 clk_gen_read_dac2(clk_gen_dev *dev)
{
	alt_u32 result;
	result= IORD_CLK_GEN_DAC2(dev->base);
	return result;
}
alt_u32 clk_gen_read_dac3(clk_gen_dev *dev)
{
	alt_u32 result;
	result= IORD_CLK_GEN_DAC3(dev->base);
	return result;
}
alt_u32 clk_gen_read_dac4(clk_gen_dev *dev)
{
	alt_u32 result;
	result= IORD_CLK_GEN_DAC4(dev->base);
	return result;
}
alt_u32 clk_gen_read_light(clk_gen_dev *dev)
{
	alt_u32 result;
	result= IORD_CLK_GEN_LIGHT(dev->base);
	return result;
}
void clk_gen_write_ad1(clk_gen_dev *dev,alt_u32 data)
{
	IOWR_CLK_GEN_AD1(dev->base,data);
}
void clk_gen_write_ad2(clk_gen_dev *dev,alt_u32 data)
{
	IOWR_CLK_GEN_AD2(dev->base,data);
}
void clk_gen_write_dac1(clk_gen_dev *dev,alt_u32 data)
{
	IOWR_CLK_GEN_DAC1(dev->base,data);
}
void clk_gen_write_dac2(clk_gen_dev *dev,alt_u32 data)
{
	IOWR_CLK_GEN_DAC2(dev->base,data);
}
void clk_gen_write_dac3(clk_gen_dev *dev,alt_u32 data)
{
	IOWR_CLK_GEN_DAC3(dev->base,data);
}
void clk_gen_write_dac4(clk_gen_dev *dev,alt_u32 data)
{
	IOWR_CLK_GEN_DAC4(dev->base,data);
}
void clk_gen_write_light(clk_gen_dev *dev,alt_u32 data)
{
	IOWR_CLK_GEN_LIGHT(dev->base,data);
}
