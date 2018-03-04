/******************************************************************************
//by mmh create 2018.3.1
******************************************************************************/

#ifndef __AD9245_REGS_H__
#define __AD9245_REGS_H__

#include <io.h>

#define AD9245_REG                  0
#define IOADDR_AD9245_DATA(base)         __IO_CALC_ADDRESS_NATIVE(base, AD9245_REG)
#define IORD_AD9245_DATA(base)           IORD(base, AD9245_REG) 
#define IOWR_AD9245_DATA(base, data)     IOWR(base, AD9245_REG, data)

#endif /* __AD9245_REGS_H__ */
