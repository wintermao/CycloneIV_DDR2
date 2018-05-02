#
# demodulation_sw.tcl
#

# Create a new driver
create_driver demodulation_driver

# Associate it with some hardware known as "demodulation"
set_sw_property hw_class_name demodulation

# The version of this driver
set_sw_property version 13.0

# This driver may be incompatible with versions of hardware less
# than specified below. Updates to hardware and device drivers
# rendering the driver incompatible with older versions of
# hardware are noted with this property assignment.
set_sw_property min_compatible_hw_version 1.0

# Initialize the driver in alt_sys_init()
set_sw_property auto_initialize true

# Location in generated BSP that above sources will be copied into
set_sw_property bsp_subdirectory drivers

#
# Source file listings...
#

# C/C++ source files
add_sw_property c_source HAL/src/demodulation.c

# Include files
add_sw_property include_source HAL/inc/demodulation.h
add_sw_property include_source inc/demodulation_regs.h

# This driver supports HAL & UCOSII BSP (OS) types
add_sw_property supported_bsp_type HAL
add_sw_property supported_bsp_type UCOSII

# End of file
