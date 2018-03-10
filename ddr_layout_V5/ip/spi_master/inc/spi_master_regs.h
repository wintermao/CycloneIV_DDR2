/*
 * SPI_Master_regs.h
 *
 *  Created on: 2018-2-10
 *      Author: mmh
 */

#ifndef __SPI_MASTER_REGS_H__
#define __SPI_MASTER_REGS_H__

#include <io.h>

#define SPI_MASTER_RXDATA_REG                 0
#define IOADDR_SPI_MASTER_RXDATA(base)        __IO_CALC_ADDRESS_NATIVE(base, SPI_MASTER_RXDATA_REG)
#define IORD_SPI_MASTER_RXDATA(base)          IORD(base, SPI_MASTER_RXDATA_REG) 
#define IOWR_SPI_MASTER_RXDATA(base, data)    IOWR(base, SPI_MASTER_RXDATA_REG, data)

#define SPI_MASTER_TXDATA_REG                  1
#define IOADDR_SPI_MASTER_TXDATA(base)         __IO_CALC_ADDRESS_NATIVE(base, SPI_MASTER_TXDATA_REG)
#define IORD_SPI_MASTER_TXDATA(base)           IORD(base, SPI_MASTER_TXDATA_REG) 
#define IOWR_SPI_MASTER_TXDATA(base, data)     IOWR(base, SPI_MASTER_TXDATA_REG, data)

#define SPI_MASTER_STATUS_REG                  2
#define IOADDR_SPI_MASTER_STATUS(base)         __IO_CALC_ADDRESS_NATIVE(base, SPI_MASTER_STATUS_REG)
#define IORD_SPI_MASTER_STATUS(base)           IORD(base, SPI_MASTER_STATUS_REG) 
#define IOWR_SPI_MASTER_STATUS(base, data)     IOWR(base, SPI_MASTER_STATUS_REG, data)

#define SPI_MASTER_STATUS_ROE_MSK              (0x8)
#define SPI_MASTER_STATUS_ROE_OFST             (3)
#define SPI_MASTER_STATUS_TOE_MSK              (0x10)
#define SPI_MASTER_STATUS_TOE_OFST             (4)
#define SPI_MASTER_STATUS_TMT_MSK              (0x20)
#define SPI_MASTER_STATUS_TMT_OFST             (5)
#define SPI_MASTER_STATUS_TRDY_MSK             (0x40)
#define SPI_MASTER_STATUS_TRDY_OFST            (6)
#define SPI_MASTER_STATUS_RRDY_MSK             (0x80)
#define SPI_MASTER_STATUS_RRDY_OFST            (7)
#define SPI_MASTER_STATUS_E_MSK                (0x100)
#define SPI_MASTER_STATUS_E_OFST               (8)

#define SPI_MASTER_CONTROL_REG                  3
#define IOADDR_SPI_MASTER_CONTROL(base)         __IO_CALC_ADDRESS_NATIVE(base, SPI_MASTER_CONTROL_REG)
#define IORD_SPI_MASTER_CONTROL(base)           IORD(base, SPI_MASTER_CONTROL_REG) 
#define IOWR_SPI_MASTER_CONTROL(base, data)     IOWR(base, SPI_MASTER_CONTROL_REG, data)

#define SPI_MASTER_CONTROL_CPOL_MSK            (0x1)
#define SPI_MASTER_CONTROL_CPOL_OFST           (0)
#define SPI_MASTER_CONTROL_CPHA_MSK            (0x2)
#define SPI_MASTER_CONTROL_CPHA_OFST           (1)
#define SPI_MASTER_CONTROL_IROE_MSK            (0x8)
#define SPI_MASTER_CONTROL_IROE_OFST           (3)
#define SPI_MASTER_CONTROL_ITOE_MSK            (0x10)
#define SPI_MASTER_CONTROL_ITOE_OFST           (4)
#define SPI_MASTER_CONTROL_ITRDY_MSK           (0x40)
#define SPI_MASTER_CONTROL_ITRDY_OFS           (6)
#define SPI_MASTER_CONTROL_IRRDY_MSK           (0x80)
#define SPI_MASTER_CONTROL_IRRDY_OFS           (7)
#define SPI_MASTER_CONTROL_IE_MSK              (0x100)
#define SPI_MASTER_CONTROL_IE_OFST             (8)
#define SPI_MASTER_CONTROL_SSO_MSK             (0x400)
#define SPI_MASTER_CONTROL_SSO_OFST            (10)

#define SPI_MASTER_DIVIDE_REG                  4
#define IOADDR_SPI_MASTER_DIVIDE(base)         __IO_CALC_ADDRESS_NATIVE(base, SPI_MASTER_DIVIDE_REG)
#define IORD_SPI_MASTER_DIVIDE(base)           IORD(base, SPI_MASTER_DIVIDE_REG) 
#define IOWR_SPI_MASTER_DIVIDE(base, data)     IOWR(base, SPI_MASTER_DIVIDE_REG, data)

#define SPI_MASTER_SLAVE_SEL_REG               5
#define IOADDR_SPI_MASTER_SLAVE_SEL(base)      __IO_CALC_ADDRESS_NATIVE(base, SPI_MASTER_SLAVE_SEL_REG)
#define IORD_SPI_MASTER_SLAVE_SEL(base)        IORD(base, SPI_MASTER_SLAVE_SEL_REG) 
#define IOWR_SPI_MASTER_SLAVE_SEL(base, data)  IOWR(base, SPI_MASTER_SLAVE_SEL_REG, data)

#endif /* __SPI_MASTER_REGS_H__ */
