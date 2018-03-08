/*
file:	nvram.h
data:	2006.12.21
discription:basic read and write for e2prom
reference:
created by winter_mao@163.com
*/
#ifndef NVRAM_H
#define NVRAM_H

#define NVRAM_DEBUG

#ifdef NVRAM_DEBUG
#define NVRAM_MSG		printf
#else
#define NVRAM_MSG
#endif

#define NVRAM_32KBIT

#ifdef NVRAM_32KBIT
	#define NVRAM_CODE				0xA0
	#define NVRAM_MAX_PAGE		0x0f
	#define NVRAM_PAGE_SIZE		32
	#define NVRAM_WRITE_DELAY 10
#else
	#define NVRAM_CODE				0xA0
	#define NVRAM_MaxPage			7
	#define NVRAM_PAGE_SIZE		16
	#define NVRAM_WRITE_DELAY 12
#endif

char nvram_ReadBlock(int address, char *pBlock, int length);
char nvram_WriteBlock(int address, char *pBlock, int length);
void nvram_WriteDelay(int num);
#endif
