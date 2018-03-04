/*
 * dac2904.h
 *
 *  Created on: 2018-3-4
 *      Author: mmh
 */

#ifndef __DAC2904_H__
#define __DAC2904_H__

#include <stddef.h>

#include "alt_types.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Macros used by alt_sys_init
 */

#define DAC2904_INSTANCE(name, device) extern int alt_no_storage
#define DAC2904_INIT(name, device) while (0)

typedef struct dac2904_dev_s
{
	alt_u32 base;
}dac2904_dev;

void dac2904_init(dac2904_dev *dev,alt_u32 base);
void dac2904_write(dac2904_dev *dev,alt_u32 data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DAC2904_H__ */
