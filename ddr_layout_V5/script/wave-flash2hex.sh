#!/bin/sh
#

nios2-elf-objcopy -I srec -O ihex "D:/altera/project/CycloneIV_DDR2/ddr_layout_V5/flash/sin_epcs_flash.flash"  "D:/altera/project/CycloneIV_DDR2/ddr_layout_V5/flash/sin_epcs_flash.hex"
#
nios2-elf-objcopy -I srec -O ihex "D:/altera/project/CycloneIV_DDR2/ddr_layout_V5/flash/triangle_epcs_flash.flash"  "D:/altera/project/CycloneIV_DDR2/ddr_layout_V5/flash/triangle_epcs_flash.hex"
#
