
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "alt_types.h"
#define	BUF_SIZE (50)

void print_file_contents(FILE* fp);

/******************************************************************
*  Function: main
*
*  Purpose: Opens the files file1.txt and file2.txt, then calls
*           print_file_contents to print them to stdout.
*
******************************************************************/
alt_u16 hex2bin(char *st)
{
	alt_u16 data;
	if(*st>='A') data=(*st-'A'+10)<<12;
	else data=(*st-'0')<<12;
	if(*(st+1)>='A') data=data+((*(st+1)-'A'+10)<<8);
	else data=data+((*(st+1)-'0')<<8);
	if(*(st+2)>='A') data=data+((*(st+2)-'A'+10)<<4);
	else data=data+((*(st+2)-'0')<<4);
	if(*(st+3)>='A') data=data+(*(st+3)-'A'+10);
	else data=data+(*(st+3)-'0');
	return data;
}
int	main(void)
{
	FILE	*in_fp,*out_fp;

	char in_file1[]="/mnt/host/triangle.txt";
	char in_file2[]="/mnt/host/sin.txt";
	char out_file1[]="/mnt/host/triangle.bin";
	char out_file2[]="/mnt/host/sin.bin";
	alt_u16 data;
	char st[20];
	int i;

	in_fp	=	fopen	(in_file1, "r");
	if (in_fp ==	NULL)
	{
		printf ("Cannot	open %s .\n",in_file1);
		exit (1);
	}
	out_fp	=	fopen	(out_file1, "wb");
	if (out_fp ==	NULL)
	{
		printf ("Cannot	open %s .\n",out_file1);
		exit (1);
	}
	i=0;
	while(!feof(in_fp))
	{
		fscanf(in_fp,"%s",st);
		data=hex2bin(st);
		fwrite(&data,2,1,out_fp);
		printf("i=%d st=%s data=0x%x\n",i++,st,data);
	}
	printf("create %s files successfully.\n",out_file1);
	fclose (in_fp);
	fclose (out_fp);

	in_fp	=	fopen	(in_file2, "r");
	if (in_fp ==	NULL)
	{
		printf ("Cannot	open %s .\n",in_file2);
		exit (1);
	}
	out_fp	=	fopen	(out_file2, "wb");
	if (out_fp ==	NULL)
	{
		printf ("Cannot	open %s .\n",out_file2);
		exit (1);
	}
	while(!feof(in_fp))
	{
		fscanf(in_fp,"%s",st);
		data=hex2bin(st);
		fwrite(&data,2,1,out_fp);
		//printf("i=%d st=%s data=0x%x\n",i++,st,data);
	}
	printf("create %s files successfully.\n",out_file2);
	fclose (in_fp);
	fclose (out_fp);

	return 0;
}

