
#include <unistd.h>
#include <stdio.h>
#include "system.h"
#include "wave_gen.h"
#include "wave_gen_regs.h"

void set_freq(wave_gen_dev *dev,alt_u32 freq,alt_u16 sample_num)
{
	wave_gen_set_freq(dev,freq*sample_num);
}

int main()
{
	alt_u16 amp_min,amp_max,sample_num,dac;
	alt_u32 delay;
	alt_u32 freq;
	freq=10560000;
	amp_min=0;
	amp_max=0x3fff;
	sample_num=512;
	delay=2000000;
	dac=0;
	wave_gen_dev dev_wave_gen;
	wave_gen_init(&dev_wave_gen,WAVE_GEN_0_BASE,ALT_CPU_CPU_FREQ);
	wave_gen_set_amp(&dev_wave_gen,amp_min,amp_max);
	wave_gen_set_sample_num(&dev_wave_gen,sample_num);
	set_freq(&dev_wave_gen,60000,sample_num);
	//wave_gen_set_freq(&dev_wave_gen,freq);
	//wave_gen_set_mode(&dev_wave_gen,WAVE_GEN_CONTROL_TRIANGLE,1);

	printf("Hello from Nios II!\n");
	while(1)
	{
		wave_gen_set_mode(&dev_wave_gen,WAVE_GEN_CONTROL_SAWTOOTH,1);
		printf("set wave is sawtooth\n");
		usleep(delay);
		wave_gen_set_mode(&dev_wave_gen,WAVE_GEN_CONTROL_TRIANGLE,1);
		printf("set wave is triangle\n");
		usleep(delay);
		wave_gen_set_mode(&dev_wave_gen,WAVE_GEN_CONTROL_SIN,1);
		printf("set wave is sin\n");
		usleep(delay);
		wave_gen_set_mode(&dev_wave_gen,WAVE_GEN_CONTROL_DAC,1);
		dac=dac+0x1000;
		if(dac==0x4000) dac=0x3fff;
		else if(dac>0x4000) dac=0;
		wave_gen_set_dac(&dev_wave_gen,dac);
		printf("set wave is direct DAC =0x%x\n",dac);
		usleep(delay);
	}

  return 0;
}
