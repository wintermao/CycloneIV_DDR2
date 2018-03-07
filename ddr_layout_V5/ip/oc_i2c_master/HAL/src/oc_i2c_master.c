/*
file:	oc_i2c_master.c
data:	2006.12.21
discription:basic receiver and transmit for I2C
reference:	oc_i2c_master.c for www.opencores.org
created by winter_mao@163.com
*/
#include "oc_i2c_master_regs.h"
#include "system.h"
#include "io.h"
#include "oc_i2c_master.h"
#include "stdio.h"

void alt_i2c_master_init(void)
{
  IOWR_OC_I2C_MASTER_PRERLO(I2C_MASTER_ALTERA_BASE , MASTER_I2C_PRESCALE_SETTING & 0xFF);
  IOWR_OC_I2C_MASTER_PRERHI(I2C_MASTER_ALTERA_BASE , MASTER_I2C_PRESCALE_SETTING / 256);
  IOWR_OC_I2C_MASTER_CTR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CTR_EN_MSK);
  OC_I2C_MSG("alt_i2c_master_init over\n");
}

char alt_i2c_master_send(char address, char data)
{
  int timeout = I2C_TX_TIMEOUT;
  
  // send start and address
  IOWR_OC_I2C_MASTER_TXR(I2C_MASTER_ALTERA_BASE , address);
  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_STA_MSK | OC_I2C_MASTER_CR_WR_MSK);
  
  // wait for interrupt and ack
  while(!(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_IF_MSK))
  {
    if(!timeout--)
    {
      OC_I2C_MSG("alt_i2c_master_send: send DeviceAddress, transmit fail\n");
      return(0); // never got an interrupt - return error
    }
  }

  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_IACK_MSK);
  if(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_RXACK_MSK)
  {
    OC_I2C_MSG("alt_i2c_master_send: send DeviceAddress, but not slave ack\n");
    return(0); // no slave ack - return error
  }
  
  // ok, now send the data
  IOWR_OC_I2C_MASTER_TXR(I2C_MASTER_ALTERA_BASE , data);
  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_STO_MSK | OC_I2C_MASTER_CR_WR_MSK);
  
  // wait for interrupt and ack
  timeout = I2C_TX_TIMEOUT;
  while(!(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_IF_MSK))
  {
    if(!timeout--)
    {
      OC_I2C_MSG("alt_i2c_master_send: send data , transmit fail\n");
      return(0); // never got an interrupt - return error
    }
  }

  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_IACK_MSK);
  if(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_RXACK_MSK)
  {
    OC_I2C_MSG("alt_i2c_master_send: send data, but not slave ack\n");
    return(0); // no slave ack - return error
  }
  
  // everything went ok
  return(-1);
}

char alt_i2c_master_receive(char address)
{
  int timeout = I2C_TX_TIMEOUT;
  
  // send start and address
  IOWR_OC_I2C_MASTER_TXR(I2C_MASTER_ALTERA_BASE , address | 0x1);
  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_STA_MSK | OC_I2C_MASTER_CR_WR_MSK);
  
  // wait for interrupt and ack
  while(!(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_IF_MSK))
  {
    if(!timeout--)
    {
    	OC_I2C_MSG("alt_i2c_master_receive: send DeviceAddress, transmit fail\n");
      return(0); // never got an interrupt - return error
    }
  }

  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_IACK_MSK);
  if(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_RXACK_MSK)
  {
  	OC_I2C_MSG("alt_i2c_master_receive: send DeviceAddress, but not slave ack\n");
    return(0); // no slave ack - return error
  }
  
  // ok, now get the data
  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_STO_MSK | OC_I2C_MASTER_CR_RD_MSK | OC_I2C_MASTER_CR_ACK_MSK);
  
  // wait for interrupt and ack
  timeout = I2C_TX_TIMEOUT;
  
  while(!(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_IF_MSK))
  {
    if(!timeout--)
    {
    	OC_I2C_MSG("alt_i2c_master_receive: receive data , receive fail\n");
      return(0); // never got an interrupt - return error
    }
  }

  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_IACK_MSK);
  
  return(IORD_OC_I2C_MASTER_RXR(I2C_MASTER_ALTERA_BASE));
}

char alt_i2c_master_write(char address,char *data,char length,char control)
{
  int timeout = I2C_TX_TIMEOUT;
	char i; 
	
	if(control & OC_I2C_MASTER_CR_STA_MSK)		// send start and address
	{
	  IOWR_OC_I2C_MASTER_TXR(I2C_MASTER_ALTERA_BASE , address);
	  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_STA_MSK | OC_I2C_MASTER_CR_WR_MSK);
  
	  // wait for interrupt and ack
  	while(!(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_IF_MSK))
	  {
	    if(!timeout--)
	    {
	      OC_I2C_MSG("alt_i2c_master_write: send DeviceAddress, transmit fail\n");
	      return(0); // never got an interrupt - return error
	    }
	  }
	
	  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_IACK_MSK);
	  
  	if(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_RXACK_MSK)
	  {
	    OC_I2C_MSG("alt_i2c_master_write: send DeviceAddress, but not slave ack\n");
	    return(0); // no slave ack - return error
	  }
	}
 
  // ok, now send the data
  for(i=0;i<length;i++)
  {
	  IOWR_OC_I2C_MASTER_TXR(I2C_MASTER_ALTERA_BASE , *data);
	  if(i==(length-1) && (control & OC_I2C_MASTER_CR_STO_MSK))
	  	IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_STO_MSK | OC_I2C_MASTER_CR_WR_MSK);
	  else
	  	IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_WR_MSK);
	  data++;

	  // wait for interrupt and ack
	  timeout = I2C_TX_TIMEOUT;
	  
	  while(!(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_IF_MSK))
	  {
	    if(!timeout--)
	    {
	      OC_I2C_MSG("alt_i2c_master_write: send data %d, transmit fail\n",i);
	      return(0); // never got an interrupt - return error
	    }
	  }
	
	  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_IACK_MSK);
	  
	  if(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_RXACK_MSK)
	  {
	    OC_I2C_MSG("alt_i2c_master_write: send data %d, but not slave ack\n",i);
	    return(0); // no slave ack - return error
	  }
	}
  // everything went ok
  return(-1);
}

char alt_i2c_master_read(char address,char *data,char length,char control)
{
  int timeout = I2C_TX_TIMEOUT;
  char i;
  
  if(control & OC_I2C_MASTER_CR_STA_MSK)		// send start and address
	{
	  IOWR_OC_I2C_MASTER_TXR(I2C_MASTER_ALTERA_BASE , address | 0x1);
  	IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_STA_MSK | OC_I2C_MASTER_CR_WR_MSK);

	  // wait for interrupt and ack
	  while(!(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_IF_MSK))
	  {
	    if(!timeout--)
	    {
	      OC_I2C_MSG("alt_i2c_master_read: send DeviceAddress, transmit fail\n");
	      return(0); // never got an interrupt - return error
	    }
	  }
	
	  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_IACK_MSK);
	  if(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_RXACK_MSK)
	  {
	    OC_I2C_MSG("alt_i2c_master_read: send DeviceAddress, but not slave ack\n");
	    return(0); // no slave ack - return error
	  }
	}
	
  // ok, now receive the data
  for(i=0;i<length;i++)
  {
	  // ok, now get the data
	  if(i==(length-1) &&  (control & OC_I2C_MASTER_CR_STO_MSK))
	  	IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_STO_MSK | OC_I2C_MASTER_CR_RD_MSK | OC_I2C_MASTER_CR_ACK_MSK);
	  else
	  	IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_RD_MSK);
	  
	  // wait for interrupt and ack
	  timeout = I2C_TX_TIMEOUT;
	  
	  while(!(IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_IF_MSK))
	  {
	    if(!timeout--)
	    {
	    	OC_I2C_MSG("alt_i2c_master_read: receive data %d, receive fail\n",i);
	      return(0); // never got an interrupt - return error
	    }
	  }
	
	  IOWR_OC_I2C_MASTER_CR(I2C_MASTER_ALTERA_BASE , OC_I2C_MASTER_CR_IACK_MSK);
	  if((i!=(length-1)) && (IORD_OC_I2C_MASTER_SR(I2C_MASTER_ALTERA_BASE) & OC_I2C_MASTER_SR_RXACK_MSK))
	  {
	    OC_I2C_MSG("alt_i2c_master_read: receive data %d, but not slave ack\n",i);
	    return(0); // no slave ack - return error
	  }
	  
	  *data=IORD_OC_I2C_MASTER_RXR(I2C_MASTER_ALTERA_BASE);
	  data++;
	}
	return(-1);
}
