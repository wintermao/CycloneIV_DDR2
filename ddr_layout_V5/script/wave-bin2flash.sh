#!/bin/sh
#
# This file was automatically generated.
#
# It can be overwritten by nios2-flash-programmer-generate or nios2-flash-programmer-gui.
#

#
# Converting Binary File: D:\altera\project\CycloneIV_DDR2\ddr_layout_V5\software\file_trans\sin.bin to: "..\flash/sin_epcs_flash.flash"
#

bin2flash --input="D:/altera/project/CycloneIV_DDR2/ddr_layout_V5/software/file_trans/sin.bin" --output="D:/altera/project/CycloneIV_DDR2/ddr_layout_V5/flash/sin_epcs_flash.flash" --location=0xf00000 --verbose 
bin2flash --input="D:/altera/project/CycloneIV_DDR2/ddr_layout_V5/software/file_trans/triangle.bin" --output="D:/altera/project/CycloneIV_DDR2/ddr_layout_V5/flash/triangle_epcs_flash.flash" --location=0xf80000 --verbose 
#
# Programming File: "..\flash/sin_epcs_flash.flash" To Device: epcs_flash
#
#nios2-flash-programmer "../flash/sin_epcs_flash.flash" --base=0x1003000 --epcs --sidp=0x258 --id=0x0 --timestamp=1525339533 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --verbose 

