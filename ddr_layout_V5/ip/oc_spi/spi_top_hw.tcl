# TCL File Generated by Component Editor 13.0
# Tue Mar 06 22:59:39 CST 2018
# DO NOT MODIFY


# 
# oc_spi "SPI Opencore" v11.1
# GIrving 2018.03.06.22:59:39
# Standard configurable SPI - Opencores
# 

# 
# request TCL package from ACDS 13.0
# 
package require -exact qsys 13.0


# 
# module oc_spi
# 
set_module_property DESCRIPTION "Standard configurable SPI - Opencores"
set_module_property NAME oc_spi
set_module_property VERSION 11.1
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP "Interface Protocols/Serial"
set_module_property AUTHOR GIrving
set_module_property DISPLAY_NAME "SPI Opencore"
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false


# 
# file sets
# 
add_fileset quartus_synth QUARTUS_SYNTH "" "Quartus Synthesis"
set_fileset_property quartus_synth TOP_LEVEL spi_top
set_fileset_property quartus_synth ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file spi_clgen.v VERILOG PATH hdl/spi_clgen.v
add_fileset_file spi_defines.v VERILOG PATH hdl/spi_defines.v
add_fileset_file spi_shift.v VERILOG PATH hdl/spi_shift.v
add_fileset_file spi_top.v VERILOG PATH hdl/spi_top.v TOP_LEVEL_FILE
add_fileset_file timescale.v VERILOG PATH hdl/timescale.v

add_fileset sim_verilog SIM_VERILOG "" "Verilog Simulation"
set_fileset_property sim_verilog TOP_LEVEL spi_top
set_fileset_property sim_verilog ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file spi_clgen.v VERILOG PATH hdl/spi_clgen.v
add_fileset_file spi_defines.v VERILOG PATH hdl/spi_defines.v
add_fileset_file spi_shift.v VERILOG PATH hdl/spi_shift.v
add_fileset_file spi_top.v VERILOG PATH hdl/spi_top.v
add_fileset_file timescale.v VERILOG PATH hdl/timescale.v


# 
# parameters
# 
add_parameter Tp INTEGER 1
set_parameter_property Tp DEFAULT_VALUE 1
set_parameter_property Tp DISPLAY_NAME Tp
set_parameter_property Tp TYPE INTEGER
set_parameter_property Tp UNITS None
set_parameter_property Tp ALLOWED_RANGES -2147483648:2147483647
set_parameter_property Tp HDL_PARAMETER true


# 
# display items
# 


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock wb_clk_i clk Input 1


# 
# connection point avalon_slave
# 
add_interface avalon_slave avalon end
set_interface_property avalon_slave addressUnits WORDS
set_interface_property avalon_slave associatedClock clock
set_interface_property avalon_slave associatedReset reset
set_interface_property avalon_slave bitsPerSymbol 8
set_interface_property avalon_slave burstOnBurstBoundariesOnly false
set_interface_property avalon_slave burstcountUnits WORDS
set_interface_property avalon_slave explicitAddressSpan 0
set_interface_property avalon_slave holdTime 0
set_interface_property avalon_slave linewrapBursts false
set_interface_property avalon_slave maximumPendingReadTransactions 0
set_interface_property avalon_slave readLatency 0
set_interface_property avalon_slave readWaitTime 1
set_interface_property avalon_slave setupTime 0
set_interface_property avalon_slave timingUnits Cycles
set_interface_property avalon_slave writeWaitTime 0
set_interface_property avalon_slave ENABLED true
set_interface_property avalon_slave EXPORT_OF ""
set_interface_property avalon_slave PORT_NAME_MAP ""
set_interface_property avalon_slave SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave wb_dat_i writedata Input 32
add_interface_port avalon_slave wb_dat_o readdata Output 32
add_interface_port avalon_slave wb_sel_i writebyteenable Input 4
add_interface_port avalon_slave wb_we_i read_n Input 1
add_interface_port avalon_slave wb_stb_i chipselect Input 1
add_interface_port avalon_slave wb_ack_o waitrequest_n Output 1
add_interface_port avalon_slave wb_adr_i address Input 5
set_interface_assignment avalon_slave embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave embeddedsw.configuration.isPrintableDevice 0


# 
# connection point conduit_export
# 
add_interface conduit_export conduit end
set_interface_property conduit_export associatedClock ""
set_interface_property conduit_export associatedReset ""
set_interface_property conduit_export ENABLED true
set_interface_property conduit_export EXPORT_OF ""
set_interface_property conduit_export PORT_NAME_MAP ""
set_interface_property conduit_export SVD_ADDRESS_GROUP ""

add_interface_port conduit_export wb_err_o export Output 1
add_interface_port conduit_export ss_pad_o export Output 8
add_interface_port conduit_export sclk_pad_o export Output 1
add_interface_port conduit_export mosi_pad_o export Output 1
add_interface_port conduit_export miso_pad_i export Input 1


# 
# connection point interrupt
# 
add_interface interrupt interrupt end
set_interface_property interrupt associatedAddressablePoint avalon_slave
set_interface_property interrupt associatedClock clock
set_interface_property interrupt associatedReset reset
set_interface_property interrupt ENABLED true
set_interface_property interrupt EXPORT_OF ""
set_interface_property interrupt PORT_NAME_MAP ""
set_interface_property interrupt SVD_ADDRESS_GROUP ""

add_interface_port interrupt wb_int_o irq Output 1


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset wb_rst_i reset Input 1

