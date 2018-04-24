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
