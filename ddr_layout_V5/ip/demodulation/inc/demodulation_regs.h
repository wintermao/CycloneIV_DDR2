/******************************************************************************
//by mmh create 2018.4.30
******************************************************************************/

#ifndef __DEMODULATION_REGS_H__
#define __DEMODULATION_REGS_H__

#include <io.h>

#define DEMODULATION_SAMPLE1_START_REG	      				0
#define IOADDR_DEMODULATION_SAMPLE1_START(base) 			__IO_CALC_ADDRESS_NATIVE(base, DEMODULATION_SAMPLE1_START_REG)
#define IORD_DEMODULATION_SAMPLE1_START(base)         IORD(base, DEMODULATION_SAMPLE1_START_REG) 
#define IOWR_DEMODULATION_SAMPLE1_START(base, data)   IOWR(base, DEMODULATION_SAMPLE1_START_REG, data)

#define DEMODULATION_SAMPLE2_START_REG	      				1
#define IOADDR_DEMODULATION_SAMPLE2_START(base) 			__IO_CALC_ADDRESS_NATIVE(base, DEMODULATION_SAMPLE2_START_REG)
#define IORD_DEMODULATION_SAMPLE2_START(base)         IORD(base, DEMODULATION_SAMPLE2_START_REG) 
#define IOWR_DEMODULATION_SAMPLE2_START(base, data)   IOWR(base, DEMODULATION_SAMPLE2_START_REG, data)

#define DEMODULATION_SAMPLE1_NUM_REG	      					2
#define IOADDR_DEMODULATION_SAMPLE1_NUM(base) 				__IO_CALC_ADDRESS_NATIVE(base, DEMODULATION_SAMPLE1_NUM_REG)
#define IORD_DEMODULATION_SAMPLE1_NUM(base)         	IORD(base, DEMODULATION_SAMPLE1_NUM_REG) 
#define IOWR_DEMODULATION_SAMPLE1_NUM(base, data)   	IOWR(base, DEMODULATION_SAMPLE1_NUM_REG, data)

#define DEMODULATION_SAMPLE2_NUM_REG	      					3
#define IOADDR_DEMODULATION_SAMPLE2_NUM(base) 				__IO_CALC_ADDRESS_NATIVE(base, DEMODULATION_SAMPLE2_NUM_REG)
#define IORD_DEMODULATION_SAMPLE2_NUM(base)        		IORD(base, DEMODULATION_SAMPLE2_NUM_REG) 
#define IOWR_DEMODULATION_SAMPLE2_NUM(base, data)   	IOWR(base, DEMODULATION_SAMPLE2_NUM_REG, data)

#define DEMODULATION_AD_REG	      										4
#define IOADDR_DEMODULATION_AD(base) 									__IO_CALC_ADDRESS_NATIVE(base, DEMODULATION_AD_REG)
#define IORD_DEMODULATION_AD(base)        						IORD(base, DEMODULATION_AD_REG) 
#define IOWR_DEMODULATION_AD(base, data)   						IOWR(base, DEMODULATION_AD_REG, data)

#define DEMODULATION_FREQ_DIV_REG	      							5
#define IOADDR_DEMODULATION_FREQ_DIV(base) 						__IO_CALC_ADDRESS_NATIVE(base, DEMODULATION_FREQ_DIV_REG)
#define IORD_DEMODULATION_FREQ_DIV(base)        			IORD(base, DEMODULATION_FREQ_DIV_REG) 
#define IOWR_DEMODULATION_FREQ_DIV(base, data)   			IOWR(base, DEMODULATION_FREQ_DIV_REG, data)

#endif /*__DEMODULATION_REGS_H__ */
