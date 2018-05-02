/*
 * demodulation.c
 *
 *  Created on: 2018-5-2
 *      Author: mmh
 */
#include "demodulation_regs.h"
#include "demodulation.h"
#include "stdbool.h"

void demodulation_init(demodulation_dev *dev,alt_u32 base,alt_u32 freq_in)
{
	dev->base=base;
	dev->freq_in=freq_in;	
}
void demodulation_set_left(demodulation_dev *dev,alt_u16 sample1_start,alt_u16 sample1_num)
{
	IOWR_DEMODULATION_SAMPLE1_START(dev->base,sample1_start);
	IOWR_DEMODULATION_SAMPLE1_NUM(dev->base,sample1_num);
}
void demodulation_set_right(demodulation_dev *dev,alt_u16 sample2_start,alt_u16 sample2_num)
{
	IOWR_DEMODULATION_SAMPLE2_START(dev->base,sample2_start);
	IOWR_DEMODULATION_SAMPLE2_NUM(dev->base,sample2_num);
}
void demodulation_set_freq(demodulation_dev *dev,alt_u32 freq)
{
	float divide;
	divide=dev->freq_in/freq;
	IOWR_DEMODULATION_FREQ_DIV(dev->base,(int)divide);
}
alt_u16 demodulation_get_ad(demodulation_dev *dev)
{
	alt_u16 result;
	result=IORD_DEMODULATION_AD(dev->base);
	return result;
}
