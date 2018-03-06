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

#include "alt_types.h"

#include "spi_master_regs.h"
#include "spi_master.h"

/* This is a very simple routine which performs one SPI master transaction.
 * It would be possible to implement a more efficient version using interrupts
 * and sleeping threads but this is probably not worthwhile initially.
 */
void spi_master_init(alt_u32 base,alt_32 slave,alt_u8 freq,alt_u8 cpol,alt_u8 cpha)
{
	alt_u8 control;
	control=(slave<<5);
	if(cpol==0) control &= 0xf7;
	else control |= 0x4;
	if(cpha==0) control &= 0xef;
	else control |= 0x10;
	control +=(freq & 0x7);
	IOWR_SPI_MASTER_CONTROL(base,control);
}
		
int spi_master_command(alt_u32 base, 
                           alt_u32 write_length, const alt_u8 * write_data,
                           alt_u32 read_length, alt_u8 * read_data,)
{
  const alt_u8 * write_end = write_data + write_length;
  alt_u8 * read_end = read_data + read_length;

  alt_u32 write_zeros = read_length;
  alt_u32 read_ignore = write_length;
  alt_u32 status;

  /* Keep clocking until all the data has been processed. */
  for ( ; ; )
  {
    
    do
    {
      status = IORD_SPI_MASTER_STATUS(base);
    }
    while ((status & SPI_MASTER_STATUS_E_MSK) != 0 );

    if (write_data < write_end)
      IOWR_SPI_MASTER_TXDATA(base, *write_data++);
    else if (write_zeros > 0)
    {
      write_zeros--;
      IOWR_SPI_MASTER_TXDATA(base, 0);
    }


    alt_u32 rxdata = IORD_SPI_MASTER_RXDATA(base);

    if (read_ignore > 0)
      read_ignore--;
    else
      *read_data++ = (alt_u8)rxdata;

    if (read_ignore == 0 && read_data == read_end)
      break;

    
  }

  /* Wait until the interface has finished transmitting */
  do
  {
    status = IORD_SPI_MASTER_STATUS(base);
  }
  while ((status & SPI_MASTER_STATUS_E_MSK) != 0);

  return read_length;
}

