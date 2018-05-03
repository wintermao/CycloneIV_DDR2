/*
 * triangle_demodu.c
 *
 *  Created on: 2018-5-3
 *      Author: mmh
 */
#include "triangle_demodu_regs.h"
#include "triangle_demodu.h"
#include "stdbool.h"
void triangle_demodu_init(triangle_demodu_dev *dev,alt_u32 base,alt_u32 freq_in)
{
	dev->base=base;
	dev->freq_in=freq_in;
}
void triangle_demodu_set_amp(triangle_demodu_dev *dev,alt_u16 min,alt_u16 max)
{
	IOWR_TRIANGLE_DEMODU_AMP_MAX(dev->base,max);
	IOWR_TRIANGLE_DEMODU_AMP_MIN(dev->base,min);
	dev->max=max;
	dev->min=min;
}
void triangle_demodu_set_freq(triangle_demodu_dev *dev,alt_u32 freq,alt_u16 sample_num)
{
	float divide;
	divide=dev->freq_in/(freq*sample_num);
	IOWR_TRIANGLE_DEMODU_FREQ(dev->base,(int)divide);
	dev->freq=freq;
}
void triangle_demodu_set_sample_num(triangle_demodu_dev *dev,alt_u16 sample_num)
{
	IOWR_TRIANGLE_DEMODU_SAMPLE_POINT(dev->base,sample_num);
	dev->sample_num=sample_num;
}
void triangle_demodu_set_left(triangle_demodu_dev *dev,alt_u16 sample_start,alt_u16 sample_num)
{
	IOWR_TRIANGLE_DEMODU_SAMPLE1_START(dev->base,sample_start);
	IOWR_TRIANGLE_DEMODU_SAMPLE1_NUM(dev->base,sample_num);
	dev->start1=sample_start;
	dev->num1=sample_num;
}
void triangle_demodu_set_right(triangle_demodu_dev *dev,alt_u16 sample_start,alt_u16 sample_num)
{
	IOWR_TRIANGLE_DEMODU_SAMPLE2_START(dev->base,sample_start);
	IOWR_TRIANGLE_DEMODU_SAMPLE2_NUM(dev->base,sample_num);
	dev->start2=sample_start;
	dev->num2=sample_num;
}

