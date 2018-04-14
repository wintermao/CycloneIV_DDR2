/*
 * clk_gen.c
 *
 *  Created on: 2018-4-14
 *      Author: mmh
 */
#include "clk_gen_regs.h"
#include "clk_gen.h"
#include "stdbool.h"

void clk_gen_init(clk_gen_dev *dev,alt_u32 base)
{
	dev->base=base;
}

alt_u32 clk_gen_read(clk_gen_dev *dev,alt_u8 addr)
{
	alt_u32 result;
	result= IORD_CLK_GEN(dev->base,addr);
	return result;
}

void clk_gen_write_ad1(clk_gen_dev *dev,alt_u8 addr,alt_u32 data)
{
	IOWR_CLK_GEN(dev->base,addr,data);
}
