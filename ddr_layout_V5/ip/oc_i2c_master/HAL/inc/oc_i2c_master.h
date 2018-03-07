/*
file:	oc_i2c_master.h
data:	2006.12.21
discription:basic receiver and transmit for I2C
reference:	oc_i2c_master.c for www.opencores.org
created by winter_mao@163.com
*/

#ifndef OC_I2C_MASTER_H
#define OC_I2C_MASTER_H

#define OC_I2C_DEBUG

#ifdef OC_I2C_DEBUG
#define OC_I2C_MSG										printf
#else
#define OC_I2C_MSG
#endif

#define MASTER_I2C_CLOCK_FREQ         (100000)
#define MASTER_I2C_PRESCALE_SETTING   ((ALT_CPU_FREQ/(5 * MASTER_I2C_CLOCK_FREQ))-1)
#define I2C_TX_TIMEOUT                (0x100000)

#ifndef I2C_MASTER_ALTERA_BASE
#define I2C_MASTER_ALTERA_BASE OC_I2C_MASTER_0_BASE
#endif

void alt_i2c_master_init(void);
char alt_i2c_master_send(char address, char data);
char alt_i2c_master_receive(char address);
char alt_i2c_master_write(char address,char *data,char length,char control);
char alt_i2c_master_read(char address,char *data,char length,char control);

#include "sys/alt_dev.h"

typedef struct
{
  alt_dev        dev;
  int            base;
} oc_i2c_master_dev;

#define OC_I2C_MASTER_INSTANCE(name, device)   \
  static oc_i2c_master_dev device =               \
    {                                               \
      {                                             \
        ALT_LLIST_ENTRY,                            \
        name##_NAME,                                \
        NULL, /* open */                            \
        NULL, /* close */                           \
        NULL,                       \
        NULL,                      \
        NULL, /* lseek */                           \
        NULL, /* fstat */                           \
        NULL, /* ioctl */                           \
      },                                            \
      name##_BASE                                   \
    }

#define OC_I2C_MASTER_INIT(name, device) alt_dev_reg (&device.dev)

#endif	/*OC_I2C_MASTER_H*/
