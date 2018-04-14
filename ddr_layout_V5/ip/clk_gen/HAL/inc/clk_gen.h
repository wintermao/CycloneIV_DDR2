/*
 * clk_gen.h
 *
 *  Created on: 2018-4-14
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
alt_u32 clk_gen_read(clk_gen_dev *dev,alt_u8 addr);
void clk_gen_write_ad1(clk_gen_dev *dev,alt_u8 addr,alt_u32 data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CLK_GEN_H__ */
