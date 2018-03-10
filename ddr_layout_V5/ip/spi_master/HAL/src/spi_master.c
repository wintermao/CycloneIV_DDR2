#include "spi_master_regs.h"
#include "spi_master.h"
#include "system.h"

void spi_master_set_freq(spi_master_dev *dev,alt_u32 freq)
{
	alt_u8 divide;
	divide=ALT_CPU_FREQ/freq/2/4;
	IOWR_SPI_MASTER_DIVIDE(dev->base,divide);
}
alt_u8 spi_master_get_freq(spi_master_dev *dev)
{
	alt_u8 result;
	result=IORD_SPI_MASTER_DIVIDE(dev->base);
	return result;
}
void spi_master_set_ss(spi_master_dev *dev,alt_u8 ss)
{
	alt_u16 control_word;
	control_word=IORD_SPI_MASTER_CONTROL(dev->base);
	if(ss==0) control_word=control_word & (~SPI_MASTER_CONTROL_SSO_MSK);
	else control_word=control_word | SPI_MASTER_CONTROL_SSO_MSK;
	IOWR_SPI_MASTER_CONTROL(dev->base,control_word);
}
void spi_master_set_cpol_cpha(spi_master_dev *dev,alt_u8 cpol,alt_u8 cpha)
{
	alt_u16 control_word;
	control_word=IORD_SPI_MASTER_CONTROL(dev->base);
	if(cpol==0) control_word=control_word & (~SPI_MASTER_CONTROL_CPOL_MSK);
	else control_word=control_word | SPI_MASTER_CONTROL_CPOL_MSK;
	if(cpha==0) control_word=control_word & (~SPI_MASTER_CONTROL_CPHA_MSK);
	else control_word=control_word | SPI_MASTER_CONTROL_CPHA_MSK;
	IOWR_SPI_MASTER_CONTROL(dev->base,control_word);
}	
void spi_master_init(spi_master_dev *dev,alt_u32 base,alt_8 slave,alt_u32 freq,alt_u8 cpol,alt_u8 cpha)
{
	dev->base=base;
	IOWR_SPI_MASTER_SLAVE_SEL(dev->base,slave);
	spi_master_set_cpol_cpha(dev,cpol,cpha);
	spi_master_set_freq(dev,freq);
	spi_master_set_ss(dev,1);
}
int spi_master_command(alt_u32 base,  alt_u32 slave,
                           alt_u32 write_length, const alt_u8 * write_data,
                           alt_u32 read_length, alt_u8 * read_data, alt_u32 flags)
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

