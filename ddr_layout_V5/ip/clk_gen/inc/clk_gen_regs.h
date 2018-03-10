/******************************************************************************
//by mmh create 2018.3.4
******************************************************************************/

#ifndef __CLK_GEN_REGS_H__
#define __CLK_GEN_REGS_H__

#include <io.h>

#define CLK_GEN_AD1_REG                  0
#define CLK_GEN_AD2_REG                  1
#define CLK_GEN_DAC1_REG                 2
#define CLK_GEN_DAC2_REG                 3
#define CLK_GEN_DAC3_REG                 4
#define CLK_GEN_DAC4_REG                 5
#define CLK_GEN_LIGHT_REG                6

#define IORD_CLK_GEN_AD1(base)           IORD(base, CLK_GEN_AD1_REG) 
#define IOWR_CLK_GEN_AD1(base, data)     IOWR(base, CLK_GEN_AD1_REG, data)

#define IORD_CLK_GEN_AD2(base)           IORD(base, CLK_GEN_AD2_REG) 
#define IOWR_CLK_GEN_AD2(base, data)     IOWR(base, CLK_GEN_AD2_REG, data)

#define IORD_CLK_GEN_DAC1(base)          IORD(base, CLK_GEN_DAC1_REG) 
#define IOWR_CLK_GEN_DAC1(base, data)    IOWR(base, CLK_GEN_DAC1_REG, data)

#define IORD_CLK_GEN_DAC2(base)          IORD(base, CLK_GEN_DAC2_REG) 
#define IOWR_CLK_GEN_DAC2(base, data)    IOWR(base, CLK_GEN_DAC2_REG, data)

#define IORD_CLK_GEN_DAC3(base)          IORD(base, CLK_GEN_DAC3_REG) 
#define IOWR_CLK_GEN_DAC3(base, data)    IOWR(base, CLK_GEN_DAC3_REG, data)

#define IORD_CLK_GEN_DAC4(base)          IORD(base, CLK_GEN_DAC4_REG) 
#define IOWR_CLK_GEN_DAC4(base, data)    IOWR(base, CLK_GEN_DAC4_REG, data)

#define IORD_CLK_GEN_LIGHT(base)          IORD(base, CLK_GEN_LIGHT_REG) 
#define IOWR_CLK_GEN_LIGHT(base, data)    IOWR(base, CLK_GEN_LIGHT_REG, data)

#endif /*__CLK_GEN_REGS_H__ */
