
#ifndef __OC_I2C_MASTER_REGS_H__
#define __OC_I2C_MASTER_REGS_H__

#include <io.h>

#define IOADDR_OC_I2C_MASTER_PRERLO(base)       __IO_CALC_ADDRESS_NATIVE(base, 0)
#define IORD_OC_I2C_MASTER_PRERLO(base)         IORD(base, 0)
#define IOWR_OC_I2C_MASTER_PRERLO(base, data)   IOWR(base, 0, data)

#define IOADDR_OC_I2C_MASTER_PRERHI(base)       __IO_CALC_ADDRESS_NATIVE(base, 1)
#define IORD_OC_I2C_MASTER_PRERHI(base)         IORD(base, 1)
#define IOWR_OC_I2C_MASTER_PRERHI(base, data)   IOWR(base, 1, data)

#define IOADDR_OC_I2C_MASTER_CTR(base)          __IO_CALC_ADDRESS_NATIVE(base, 2)
#define IORD_OC_I2C_MASTER_CTR(base)            IORD(base, 2)
#define IOWR_OC_I2C_MASTER_CTR(base, data)      IOWR(base, 2, data)

/* BITS 5:0 ARE RESERVED */
#define OC_I2C_MASTER_CTR_IEN_MSK               (0x40)
#define OC_I2C_MASTER_CTR_IEN_OFST              (6)
#define OC_I2C_MASTER_CTR_EN_MSK                (0x80)
#define OC_I2C_MASTER_CTR_EN_OFST               (7)

#define IOADDR_OC_I2C_MASTER_TXR(base)          __IO_CALC_ADDRESS_NATIVE(base, 3)
#define IOWR_OC_I2C_MASTER_TXR(base, data)      IOWR(base, 3, data)

#define OC_I2C_MASTER_TXR_RW_MSK                (0x1)
#define OC_I2C_MASTER_TXR_RW_OFST               (0)

#define IOADDR_OC_I2C_MASTER_RXR(base)          __IO_CALC_ADDRESS_NATIVE(base, 3)
#define IORD_OC_I2C_MASTER_RXR(base)            IORD(base, 3)

#define IOADDR_OC_I2C_MASTER_CR(base)           __IO_CALC_ADDRESS_NATIVE(base, 4)
#define IOWR_OC_I2C_MASTER_CR(base, data)       IOWR(base, 4, data)

#define OC_I2C_MASTER_CR_IACK_MSK               (0x1)
#define OC_I2C_MASTER_CR_IACK_OFST              (0)
/* BITS 1& 2 ARE RESERVED */
#define OC_I2C_MASTER_CR_ACK_MSK                (0x8)
#define OC_I2C_MASTER_CR_ACK_OFST               (3)
#define OC_I2C_MASTER_CR_WR_MSK                 (0x10)
#define OC_I2C_MASTER_CR_WR_OFST                (4)
#define OC_I2C_MASTER_CR_RD_MSK                 (0x20)
#define OC_I2C_MASTER_CR_RD_OFST                (5)
#define OC_I2C_MASTER_CR_STO_MSK                (0x40)
#define OC_I2C_MASTER_CR_STO_OFST               (6)
#define OC_I2C_MASTER_CR_STA_MSK                (0x80)
#define OC_I2C_MASTER_CR_STA_OFST               (7)

#define IOADDR_OC_I2C_MASTER_SR(base)           __IO_CALC_ADDRESS_NATIVE(base, 4)
#define IORD_OC_I2C_MASTER_SR(base)             IORD(base, 4)

#define OC_I2C_MASTER_SR_IF_MSK                 (0x1)
#define OC_I2C_MASTER_SR_IF_OFST                (0)
#define OC_I2C_MASTER_SR_TIP_MSK                (0x2)
#define OC_I2C_MASTER_SR_TIP_OFST               (1)
/* BITS 4:2 ARE RESERVED */
#define OC_I2C_MASTER_SR_AL_MSK                 (0x20)
#define OC_I2C_MASTER_SR_AL_OFST                (5)
#define OC_I2C_MASTER_SR_BUSY_MSK               (0x40)
#define OC_I2C_MASTER_SR_BUSY_OFST              (6)
#define OC_I2C_MASTER_SR_RXACK_MSK              (0x80)
#define OC_I2C_MASTER_SR_RXACK_OFS              (7)

#endif /* __OC_I2C_MASTER_REGS_H__ */
