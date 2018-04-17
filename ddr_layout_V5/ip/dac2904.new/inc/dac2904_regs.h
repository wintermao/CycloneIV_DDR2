/******************************************************************************
//by mmh create 2018.3.4
******************************************************************************/

#ifndef __DAC2904_REGS_H__
#define __DAC2904_REGS_H__

#include <io.h>

#define DAC2904_REG                  0
#define IOADDR_DAC2904_DATA(base)         __IO_CALC_ADDRESS_NATIVE(base, DAC2904_REG)
#define IORD_DAC2904_DATA(base)           IORD(base, DAC2904_REG) 
#define IOWR_DAC2904_DATA(base, data)     IOWR(base, DAC2904_REG, data)

#endif /* __DAC2904_REGS_H__ */
