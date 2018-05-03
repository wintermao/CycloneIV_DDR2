
#include <unistd.h>
#include <stdio.h>
#include "system.h"
#include "wave_gen.h"
#include "wave_gen_regs.h"
#include "triangle_demodu.h"
#include "clk_gen.h"
#include "clk_device.h"

int main()
{
	alt_u16 left_start,left_num,right_start,right_num;
	alt_u32 freq;
	triangle_demodu_dev dev_triangle_demodu0;
	triangle_demodu_dev dev_triangle_demodu1;
	wave_gen_dev dev_wave_gen;
	clk_gen_dev dev_clk;

	freq=60000;
	left_start=32;
	left_num=128;
	right_start=128+32;
	right_num=128;

	//set light freq to 1 Hz
	clk_gen_write(&dev_clk,LIGHT,ALT_CPU_CPU_FREQ);

	//generate sawtooth wave,freq is 1 Hz
	wave_gen_init(&dev_wave_gen,WAVE_GEN_0_BASE,ALT_CPU_CPU_FREQ);
	wave_gen_set_amp(&dev_wave_gen,0,0x3fff);
	wave_gen_set_sample_num(&dev_wave_gen,1024);
	wave_gen_set_freq(&dev_wave_gen,1024);
	wave_gen_set_mode(&dev_wave_gen,WAVE_GEN_CONTROL_SAWTOOTH,1);

	triangle_demodu_init(&dev_triangle_demodu0,TRIANGLE_DEMODU_0_BASE,ALT_CPU_CPU_FREQ);
	triangle_demodu_set_amp(&dev_triangle_demodu0,0,12888);
	triangle_demodu_set_sample_num(&dev_triangle_demodu0,256);
	triangle_demodu_set_freq(&dev_triangle_demodu0,freq,256);
	triangle_demodu_set_left(&dev_triangle_demodu0,left_start,left_num);
	triangle_demodu_set_right(&dev_triangle_demodu0,right_start,right_num);

	triangle_demodu_init(&dev_triangle_demodu1,TRIANGLE_DEMODU_1_BASE,ALT_CPU_CPU_FREQ);
	triangle_demodu_set_amp(&dev_triangle_demodu1,0,12888);
	triangle_demodu_set_sample_num(&dev_triangle_demodu1,256);
	triangle_demodu_set_freq(&dev_triangle_demodu1,freq,250);
	triangle_demodu_set_left(&dev_triangle_demodu1,left_start,left_num);
	triangle_demodu_set_right(&dev_triangle_demodu1,right_start,right_num);

	printf("Hello from Nios II!\n");
	while(1)
	{

	}

  return 0;
}
