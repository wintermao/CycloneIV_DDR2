/*
 * ad9245.h
 *
 *  Created on: 2018-3-1
 *      Author: mmh
 */

#ifndef __AD9245_H__
#define __AD9245_H__

#include <stddef.h>

#include "alt_types.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Macros used by alt_sys_init
 */

#define AD9245_INSTANCE(name, device) extern int alt_no_storage
#define AD9245_INIT(name, device) while (0)

typedef struct ad9245_dev_s
{
	alt_u32 base;
}ad9245_dev;

void ad9245_init(ad9245_dev *dev,alt_u32 base);
alt_u32 ad9245_read_ad(ad9245_dev *dev);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AD9245_H__ */
