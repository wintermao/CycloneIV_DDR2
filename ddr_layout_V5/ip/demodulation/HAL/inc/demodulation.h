/*
 * demodulation.h
 *
 *  Created on: 2018-5-2
 *      Author: mmh
 */

#ifndef _DEMODULATION_H__
#define _DEMODULATION_H__

#include <stddef.h>

#include "alt_types.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Macros used by alt_sys_init
 */

#define DEMODULATION_INSTANCE(name, device) extern int alt_no_storage
#define DEMODULATION_INIT(name, device) while (0)

typedef struct demodulation_dev_s
{
	alt_u32 base;
	alt_u32 freq_in;
}demodulation_dev;

void demodulation_init(demodulation_dev *dev,alt_u32 base,alt_u32 freq_in);
void demodulation_set_left(demodulation_dev *dev,alt_u16 sample1_start,alt_u16 sample1_num);
void demodulation_set_right(demodulation_dev *dev,alt_u16 sample2_start,alt_u16 sample2_num);
void demodulation_set_freq(demodulation_dev *dev,alt_u32 freq);
alt_u16 demodulation_get_ad(demodulation_dev *dev);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DEMODULATION_H__ */
