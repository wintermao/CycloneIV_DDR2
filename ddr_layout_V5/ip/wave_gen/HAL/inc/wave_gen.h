/*
 * wave_gen.h
 *
 *  Created on: 2018-5-2
 *      Author: mmh
 */

#ifndef __WAVE_GEN_H__
#define __WAVE_GEN_H__

#include <stddef.h>

#include "alt_types.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Macros used by alt_sys_init
 */

#define WAVE_GEN_INSTANCE(name, device) extern int alt_no_storage
#define WAVE_GEN_INIT(name, device) while (0)

typedef struct wave_gen_dev_s
{
	alt_u32 base;
	alt_u32 freq_in;
}wave_gen_dev;

void wave_gen_init(wave_gen_dev *dev,alt_u32 base,alt_u32 freq_in);
void wave_gen_set_amp(wave_gen_dev *dev,alt_u16 min,alt_u16 max);
void wave_gen_set_freq(wave_gen_dev *dev,alt_u32 freq);
void wave_gen_set_sample_num(wave_gen_dev *dev,alt_u16 sample_num);
void wave_gen_set_mode(wave_gen_dev *dev,alt_u8 sample_num,alt_u8 out_en);
void wave_gen_set_dac(wave_gen_dev *dev,alt_u16 dac);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WAVE_GEN_H__ */
