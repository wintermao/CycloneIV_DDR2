# TCL File Generated by Component Editor 13.0
# Sat Apr 14 15:17:18 CST 2018
# DO NOT MODIFY


# 
# clk_gen "clk_gen" v2.0
# mmh 2018.04.14.15:17:18
# clock generate
# 

# 
# request TCL package from ACDS 13.0
# 
package require -exact qsys 13.0


# 
# module clk_gen
# 
set_module_property DESCRIPTION "clock generate"
set_module_property NAME clk_gen
set_module_property VERSION 2.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP System
set_module_property AUTHOR mmh
set_module_property DISPLAY_NAME clk_gen
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL clk_gen
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file clk_gen.v VERILOG PATH hdl/clk_gen.v TOP_LEVEL_FILE


# 
# parameters
# 
add_parameter clk_num INTEGER 4 ""
set_parameter_property clk_num DEFAULT_VALUE 4
set_parameter_property clk_num DISPLAY_NAME clk_num
set_parameter_property clk_num TYPE INTEGER
set_parameter_property clk_num UNITS None
set_parameter_property clk_num ALLOWED_RANGES -2147483648:2147483647
set_parameter_property clk_num DESCRIPTION ""
set_parameter_property clk_num HDL_PARAMETER true


# 
# display items
# 


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clk
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset_n reset_n Input 1


# 
# connection point s1
# 
add_interface s1 avalon end
set_interface_property s1 addressUnits WORDS
set_interface_property s1 associatedClock clk
set_interface_property s1 associatedReset reset
set_interface_property s1 bitsPerSymbol 8
set_interface_property s1 burstOnBurstBoundariesOnly false
set_interface_property s1 burstcountUnits WORDS
set_interface_property s1 explicitAddressSpan 0
set_interface_property s1 holdTime 0
set_interface_property s1 linewrapBursts false
set_interface_property s1 maximumPendingReadTransactions 0
set_interface_property s1 readLatency 0
set_interface_property s1 readWaitTime 1
set_interface_property s1 setupTime 0
set_interface_property s1 timingUnits Cycles
set_interface_property s1 writeWaitTime 0
set_interface_property s1 ENABLED true
set_interface_property s1 EXPORT_OF ""
set_interface_property s1 PORT_NAME_MAP ""
set_interface_property s1 SVD_ADDRESS_GROUP ""

add_interface_port s1 chipselect chipselect Input 1
add_interface_port s1 address address Input 5
add_interface_port s1 read read Input 1
add_interface_port s1 write write Input 1
add_interface_port s1 readdata readdata Output 32
add_interface_port s1 writedata writedata Input 32
set_interface_assignment s1 embeddedsw.configuration.isFlash 0
set_interface_assignment s1 embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment s1 embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment s1 embeddedsw.configuration.isPrintableDevice 0


# 
# connection point clk
# 
add_interface clk clock end
set_interface_property clk clockRate 54000000
set_interface_property clk ENABLED true
set_interface_property clk EXPORT_OF ""
set_interface_property clk PORT_NAME_MAP ""
set_interface_property clk SVD_ADDRESS_GROUP ""

add_interface_port clk clk clk Input 1


# 
# connection point clk_source
# 
add_interface clk_source clock end
set_interface_property clk_source clockRate 108000000
set_interface_property clk_source ENABLED true
set_interface_property clk_source EXPORT_OF ""
set_interface_property clk_source PORT_NAME_MAP ""
set_interface_property clk_source SVD_ADDRESS_GROUP ""

add_interface_port clk_source clk_source clk Input 1


# 
# connection point clk_out
# 
add_interface clk_out conduit end
set_interface_property clk_out associatedClock clk_source
set_interface_property clk_out associatedReset reset
set_interface_property clk_out ENABLED true
set_interface_property clk_out EXPORT_OF ""
set_interface_property clk_out PORT_NAME_MAP ""
set_interface_property clk_out SVD_ADDRESS_GROUP ""

add_interface_port clk_out clk_out export Output clk_num

