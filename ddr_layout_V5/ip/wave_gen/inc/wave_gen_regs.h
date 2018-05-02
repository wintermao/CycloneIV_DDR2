/******************************************************************************
//by mmh create 2018.4.28
******************************************************************************/

#ifndef __WAVE_GEN_REGS_H__
#define __WAVE_GEN_REGS_H__

#include <io.h>

#define WAVE_GEN_AMP_MAX_REG	              	0
#define IOADDR_WAVE_GEN_AMP_MAX(base)        	__IO_CALC_ADDRESS_NATIVE(base, WAVE_GEN_AMP_MAX_REG)
#define IORD_WAVE_GEN_AMP_MAX(base)           IORD(base, WAVE_GEN_AMP_MAX_REG) 
#define IOWR_WAVE_GEN_AMP_MAX(base, data)     IOWR(base, WAVE_GEN_AMP_MAX_REG, data)

#define WAVE_GEN_AMP_MIN_REG	              	1
#define IOADDR_WAVE_GEN_AMP_MIN(base)        	__IO_CALC_ADDRESS_NATIVE(base, WAVE_GEN_AMP_MIN_REG)
#define IORD_WAVE_GEN_AMP_MIN(base)           IORD(base, WAVE_GEN_AMP_MIN_REG) 
#define IOWR_WAVE_GEN_AMP_MIN(base, data)     IOWR(base, WAVE_GEN_AMP_MIN_REG, data)

#define WAVE_GEN_FREQ_REG	              			2
#define IOADDR_WAVE_GEN_FREQ(base)        		__IO_CALC_ADDRESS_NATIVE(base, WAVE_GEN_FREQ_REG)
#define IORD_WAVE_GEN_FREQ(base)           		IORD(base, WAVE_GEN_FREQ_REG) 
#define IOWR_WAVE_GEN_FREQ(base, data)     		IOWR(base, WAVE_GEN_FREQ_REG, data)

#define WAVE_GEN_SAMPLE_POINT_REG	            3
#define IOADDR_WAVE_GEN_SAMPLE_POINT(base)    __IO_CALC_ADDRESS_NATIVE(base, WAVE_GEN_SAMPLE_POINT_REG)
#define IORD_WAVE_GEN_SAMPLE_POINT(base)      IORD(base, WAVE_GEN_SAMPLE_POINT_REG) 
#define IOWR_WAVE_GEN_SAMPLE_POINT(base, data)    IOWR(base, WAVE_GEN_SAMPLE_POINT_REG, data)

#define WAVE_GEN_CONTROL_REG	              	4
#define IOADDR_WAVE_GEN_CONTROL(base)        	__IO_CALC_ADDRESS_NATIVE(base, WAVE_GEN_CONTROL_REG)
#define IORD_WAVE_GEN_CONTROL(base)           IORD(base, WAVE_GEN_CONTROL_REG) 
#define IOWR_WAVE_GEN_CONTROL(base, data)     IOWR(base, WAVE_GEN_CONTROL_REG, data)

#define WAVE_GEN_CONTROL_SAWTOOTH							0x0
#define WAVE_GEN_CONTROL_TRIANGLE							0x2
#define WAVE_GEN_CONTROL_SIN									0x4
#define WAVE_GEN_CONTROL_DAC									0x6

#define WAVE_GEN_DAC_REG	              			5
#define IOADDR_WAVE_GEN_DAC(base)        	__IO_CALC_ADDRESS_NATIVE(base, WAVE_GEN_DAC_REG)
#define IORD_WAVE_GEN_DAC(base)           		IORD(base, WAVE_GEN_DAC_REG) 
#define IOWR_WAVE_GEN_DAC(base, data)     		IOWR(base, WAVE_GEN_DAC_REG, data)

#endif /*__WAVE_GEN_REGS_H__ */
