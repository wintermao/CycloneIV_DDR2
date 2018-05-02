/*
 * wave_gen.c
 *
 *  Created on: 2018-5-2
 *      Author: mmh
 */
#include "wave_gen_regs.h"
#include "wave_gen.h"
#include "stdbool.h"
void wave_gen_init(wave_gen_dev *dev,alt_u32 base,alt_u32 freq_in)
{
	dev->base=base;
	dev->freq_in=freq_in;
}
void wave_gen_set_amp(wave_gen_dev *dev,alt_u16 min,alt_u16 max)
{
	IOWR_WAVE_GEN_AMP_MAX(dev->base,max);
	IOWR_WAVE_GEN_AMP_MIN(dev->base,min);
}
void wave_gen_set_freq(wave_gen_dev *dev,alt_u32 freq)
{
	float divide;
	divide=dev->freq_in/freq;
	IOWR_WAVE_GEN_FREQ(dev->base,(int)divide);
}
void wave_gen_set_sample_num(wave_gen_dev *dev,alt_u16 sample_num)
{
	IOWR_WAVE_GEN_SAMPLE_POINT(dev->base,sample_num);
}
void wave_gen_set_mode(wave_gen_dev *dev,alt_u8 mode,alt_u8 out_en)
{
	IOWR_WAVE_GEN_CONTROL(dev->base,(mode & 0xfe)| (out_en& 1));
}
void wave_gen_set_dac(wave_gen_dev *dev,alt_u16 dac)
{
	IOWR_WAVE_GEN_DAC(dev->base,dac);
}

