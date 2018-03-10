#ifndef __SPI_MASTER_H__
#define __SPI_MASTER_H__

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2003 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
******************************************************************************/
#include <stddef.h>

#include "alt_types.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Macros used by alt_sys_init
 */

#define SPI_MASTER_INSTANCE(name, device) extern int alt_no_storage
#define SPI_MASTER_INIT(name, device) while (0)

/*
 * Use this function to perform one SPI access on your target.  'base' should
 * be the base address of your SPI peripheral, while 'slave' indicates which
 * bit in the slave select register should be set.
 */
typedef struct spi_master_dev_s
{
	alt_u32 base;
}spi_master_dev;

void spi_master_init(spi_master_dev *dev,alt_u32 base,alt_8 slave,alt_u32 freq,alt_u8 cpol,alt_u8 cpha);
void spi_master_set_freq(spi_master_dev *dev,alt_u32 freq);
alt_u8 spi_master_get_freq(spi_master_dev *dev);
void spi_master_set_ss(spi_master_dev *dev,alt_u8 ss);
void spi_master_set_cpol_cpha(spi_master_dev *dev,alt_u8 cpol,alt_u8 cpha);
int spi_master_command(alt_u32 base, alt_u32 slave,
                           alt_u32 write_length, const alt_u8 * write_data,
                           alt_u32 read_length, alt_u8 * read_data,
                           alt_u32 flags);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SPI_MASTER_H__ */
