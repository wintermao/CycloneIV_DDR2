/*
 * clk_gen.h
 *
 *  Created on: 2018-3-4
 *      Author: mmh
 */

#ifndef __CLK_GEN_H__
#define __CLK_GEN_H__

#include <stddef.h>

#include "alt_types.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Macros used by alt_sys_init
 */

#define CLK_GEN_INSTANCE(name, device) extern int alt_no_storage
#define CLK_GEN_INIT(name, device) while (0)

typedef struct clk_gen_dev_s
{
	alt_u32 base;
}clk_gen_dev;

void clk_gen_init(clk_gen_dev *dev,alt_u32 base);
alt_u32 clk_gen_read_ad1(clk_gen_dev *dev);
alt_u32 clk_gen_read_ad2(clk_gen_dev *dev);
alt_u32 clk_gen_read_dac1(clk_gen_dev *dev);
alt_u32 clk_gen_read_dac2(clk_gen_dev *dev);
alt_u32 clk_gen_read_dac3(clk_gen_dev *dev);
alt_u32 clk_gen_read_dac4(clk_gen_dev *dev);
alt_u32 clk_gen_read_light(clk_gen_dev *dev);
void clk_gen_write_ad1(clk_gen_dev *dev,alt_u32 data);
void clk_gen_write_ad2(clk_gen_dev *dev,alt_u32 data);
void clk_gen_write_dac1(clk_gen_dev *dev,alt_u32 data);
void clk_gen_write_dac2(clk_gen_dev *dev,alt_u32 data);
void clk_gen_write_dac3(clk_gen_dev *dev,alt_u32 data);
void clk_gen_write_dac4(clk_gen_dev *dev,alt_u32 data);
void clk_gen_write_light(clk_gen_dev *dev,alt_u32 data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CLK_GEN_H__ */
