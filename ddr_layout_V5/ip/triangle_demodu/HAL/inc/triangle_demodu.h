/*
 * wave_gen.h
 *
 *  Created on: 2018-5-3
 *      Author: mmh
 */

#ifndef __TRIANGLE_DEMODU_H__
#define __TRIANGLE_DEMODU_H__

#include <stddef.h>

#include "alt_types.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Macros used by alt_sys_init
 */

#define TRIANGLE_DEMODU_INSTANCE(name, device) extern int alt_no_storage
#define TRIANGLE_DEMODU_INIT(name, device) while (0)

typedef struct triangle_demodu_dev_s
{
	alt_u32 base;
	alt_u32 freq_in;
	alt_u16 max;
	alt_u16 min;
	alt_u32 freq;
	alt_u16 sample_num;
	alt_u16 start1;
	alt_u16 num1;
	alt_u16 start2;
	alt_u16 num2;
}triangle_demodu_dev;

void triangle_demodu_init(triangle_demodu_dev *dev,alt_u32 base,alt_u32 freq_in);
void triangle_demodu_set_amp(triangle_demodu_dev *dev,alt_u16 min,alt_u16 max);
void triangle_demodu_set_freq(triangle_demodu_dev *dev,alt_u32 freq,alt_u16 sample_num);
void triangle_demodu_set_sample_num(triangle_demodu_dev *dev,alt_u16 sample_num);
void triangle_demodu_set_left(triangle_demodu_dev *dev,alt_u16 sample1_start,alt_u16 sample1_num);
void triangle_demodu_set_right(triangle_demodu_dev *dev,alt_u16 sample2_start,alt_u16 sample2_num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TRIANGLE_DEMODU_H__ */
