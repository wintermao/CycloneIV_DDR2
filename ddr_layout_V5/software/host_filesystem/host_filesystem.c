/**************************************************************************
 * Copyright (c) 2004 Altera Corporation, San Jose, California, USA.      *
 * All rights reserved. All use of this software and documentation is     *
 * subject to the License Agreement located at the end of this file below.*
 *************************************************************************/
/**************************************************************************
 *
 *
 * Description
 ***************
 * A simple example that demonstrates the use of the GDB Host file
 * system.
 *
 *
 * Requirements
 ****************
 * This is a "Hosted" application. According to the ANSI C standard, hosted
 * applications can rely on numerous system-services (including properly-
 * initialized device drivers and, in this case, STDOUT).
 *
 * When this program is compiled, code is added before main(), so that all
 * devices are properly-initialized and all system-services (e.g. the <stdio>
 * library) are ready-to-use. In this hosted environment, all standard C
 * programs will run.
 *
 * A hosted application (like this example) does not need to concern itself
 * with initializing devices. As long as it only calls C Standard Library
 * functions, a hosted application can run "as if on a workstation."
 *
 * An application runs in a hosted environment if it declares the function
 * main(), which this application does.
 *
 * This software example requires a STDOUT component such as a UART or
 * JTAG UART.  Therefore it can run on the following hardware examples:
 *
 * Nios Development Board, Stratix II Edition:
 * -  Standard
 * -  Full Featured
 *
 * DSP Development Board, Stratix II Edition:
 * -  Standard
 * -  Full Featured
 *
 * Nios Development Board, Cyclone II Edition:
 * -  Standard
 * -  Full Featured
 * -  Low Cost
 *
 * Nios Development Board, Stratix Edition:
 * -  Standard
 * -  Full Featured
 * 
 * Nios Development Board, Stratix Professional Edition:
 * -  Standard
 * -  Full Featured
 * 
 * Nios Development Board, Cyclone Edition:
 * -  Standard
 * -  Full Featured
 * -  Low Cost
 *
 * Peripherals Exercised by SW
 *******************************
 * The example's purpose is to demonstrate the use of the GDB host file system. 
 * To build & run the application, perform the following steps:
 *
 *
 * === I.  BUILD PROJECT ===
 * 1. After creating a new "Host File System" software example project
 *    targeting a Nios II "standard" or "full_featured" hardware example
 *    design, you may build it by choosing "Build All" from the Nios II IDE
 *    "Project" menu.
 *
 * 2. Wait for the build process to complete. During the software build, the
 *    files necessary to run this example are generated.
 *
 * === II. RUN PROGRAM === *
 * 1. Right-click the software project and select "Debug As -> Nios II Hardware"
 *    Note: For the Host file system part of the design to work, you must use
 *          Debug As -> Nios II Hardware, not Run As -> Nios II Hardware. This is
 *          due to the fact that the Host file system feature relies upon a
 *          GDB server running, which only occurs in "Debug As" mode.
 *
 * 
 * Software Files
 ******************
 * host_filesystem.c - Main C file that contains all code in this example.
 *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE (50)

int	main(void)
{
  FILE*	fp_ascii =  NULL;
  FILE* fp_bin =  NULL;
  char buffer[BUF_SIZE];
  int read_size, i;
  
  /*
   * Read ASCII file from host and print its contents
   */ 
  fp_ascii  = fopen ("/mnt/host/hostfs_read_ascii.txt", "r");
	if (fp_ascii ==	NULL)
	{
		printf ("Cannot	open file hostfs_read_ascii.txt.\n");
		exit (1);
	}
  fgets(buffer, sizeof(buffer), fp_ascii);
  printf("%s", buffer);
  fclose (fp_ascii);
  
  /*
   * Read binary file from host and print its contents
   */ 
  fp_bin  = fopen ("/mnt/host/hostfs_read_binary.bin", "r");
	if (fp_bin ==	NULL)
	{
		printf ("Cannot	open file hostfs_read_binary.bin.\n");
		exit (1);
	}
  read_size = fread (buffer, 1, BUF_SIZE, fp_bin);
  for(i = 0; i < read_size; i++)
  {
    printf("%X ", buffer[i]);
  }
  fclose (fp_bin);

  /*
   * Write a string to an ASCII file on the host
   */ 
  fp_ascii  = fopen ("/mnt/host/hostfs_write_ascii.txt", "w");
	if (fp_ascii ==	NULL)
	{
		printf ("Cannot	open file hostfs_write_ascii.txt.\n");
		exit (1);
	}
  strcpy(buffer, "Hello from the target!");
  fputs(buffer, fp_ascii);
  fclose (fp_ascii);
  
  /*
   * Write values 0-9 to a binary file on the host
   */ 
  fp_bin  = fopen ("/mnt/host/hostfs_write_binary.bin", "w");
	if (fp_bin ==	NULL)
	{
		printf ("Cannot	open file hostfs_write_binary.bin.\n");
		exit (1);
	}
  for(i = 0; i < 10; i++) {
    buffer[i] = i;
  }
  fwrite(buffer, 1, 10, fp_bin); 
  fclose (fp_bin);

	printf("\n\nRead and wrote all files successfully.  Check your project\n");
	printf("directory for the files written by the host filesystem,\n");
	printf(" - hostfs_write_ascii.txt\n - hostfs_write_binary.bin\n");

	return 0;
}


/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
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
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/
