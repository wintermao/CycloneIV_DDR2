# TCL File Generated by Component Editor 13.0
# Mon Apr 30 22:38:48 CST 2018
# DO NOT MODIFY


# 
# demodulation "demodulation" v1.0
# mmh 2018.04.30.22:38:48
# demodulation
# 

# 
# request TCL package from ACDS 13.0
# 
package require -exact qsys 13.0


# 
# module demodulation
# 
set_module_property DESCRIPTION demodulation
set_module_property NAME demodulation
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP System
set_module_property AUTHOR mmh
set_module_property DISPLAY_NAME demodulation
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL demodulation
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file demodulation.v VERILOG PATH hdl/demodulation.v TOP_LEVEL_FILE


# 
# parameters
# 
add_parameter Sample1Start STD_LOGIC_VECTOR 32
set_parameter_property Sample1Start DEFAULT_VALUE 32
set_parameter_property Sample1Start DISPLAY_NAME Sample1Start
set_parameter_property Sample1Start TYPE STD_LOGIC_VECTOR
set_parameter_property Sample1Start UNITS None
set_parameter_property Sample1Start ALLOWED_RANGES 0:262143
set_parameter_property Sample1Start HDL_PARAMETER true
add_parameter Sample2Start STD_LOGIC_VECTOR 128
set_parameter_property Sample2Start DEFAULT_VALUE 128
set_parameter_property Sample2Start DISPLAY_NAME Sample2Start
set_parameter_property Sample2Start TYPE STD_LOGIC_VECTOR
set_parameter_property Sample2Start UNITS None
set_parameter_property Sample2Start ALLOWED_RANGES 0:262143
set_parameter_property Sample2Start HDL_PARAMETER true
add_parameter Sample1Num STD_LOGIC_VECTOR 32
set_parameter_property Sample1Num DEFAULT_VALUE 32
set_parameter_property Sample1Num DISPLAY_NAME Sample1Num
set_parameter_property Sample1Num TYPE STD_LOGIC_VECTOR
set_parameter_property Sample1Num UNITS None
set_parameter_property Sample1Num ALLOWED_RANGES 0:262143
set_parameter_property Sample1Num HDL_PARAMETER true
add_parameter Sample2Num STD_LOGIC_VECTOR 32
set_parameter_property Sample2Num DEFAULT_VALUE 32
set_parameter_property Sample2Num DISPLAY_NAME Sample2Num
set_parameter_property Sample2Num TYPE STD_LOGIC_VECTOR
set_parameter_property Sample2Num UNITS None
set_parameter_property Sample2Num ALLOWED_RANGES 0:262143
set_parameter_property Sample2Num HDL_PARAMETER true
add_parameter FreqDiv STD_LOGIC_VECTOR 1
set_parameter_property FreqDiv DEFAULT_VALUE 1
set_parameter_property FreqDiv DISPLAY_NAME FreqDiv
set_parameter_property FreqDiv TYPE STD_LOGIC_VECTOR
set_parameter_property FreqDiv UNITS None
set_parameter_property FreqDiv ALLOWED_RANGES 0:17179869183
set_parameter_property FreqDiv HDL_PARAMETER true


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

add_interface_port clock clk clk Input 1


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

add_interface_port reset reset_n reset_n Input 1


# 
# connection point s0
# 
add_interface s0 avalon end
set_interface_property s0 addressUnits WORDS
set_interface_property s0 associatedClock clock
set_interface_property s0 associatedReset reset
set_interface_property s0 bitsPerSymbol 8
set_interface_property s0 burstOnBurstBoundariesOnly false
set_interface_property s0 burstcountUnits WORDS
set_interface_property s0 explicitAddressSpan 0
set_interface_property s0 holdTime 0
set_interface_property s0 linewrapBursts false
set_interface_property s0 maximumPendingReadTransactions 0
set_interface_property s0 readLatency 0
set_interface_property s0 readWaitTime 1
set_interface_property s0 setupTime 0
set_interface_property s0 timingUnits Cycles
set_interface_property s0 writeWaitTime 0
set_interface_property s0 ENABLED true
set_interface_property s0 EXPORT_OF ""
set_interface_property s0 PORT_NAME_MAP ""
set_interface_property s0 SVD_ADDRESS_GROUP ""

add_interface_port s0 avs_s0_chipselect chipselect Input 1
add_interface_port s0 avs_s0_write write Input 1
add_interface_port s0 avs_s0_read read Input 1
add_interface_port s0 avs_s0_writedata writedata Input 32
add_interface_port s0 avs_s0_readdata readdata Output 32
add_interface_port s0 avs_s0_address address Input 3
set_interface_assignment s0 embeddedsw.configuration.isFlash 0
set_interface_assignment s0 embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment s0 embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment s0 embeddedsw.configuration.isPrintableDevice 0


# 
# connection point clk_source
# 
add_interface clk_source clock end
set_interface_property clk_source clockRate 0
set_interface_property clk_source ENABLED true
set_interface_property clk_source EXPORT_OF ""
set_interface_property clk_source PORT_NAME_MAP ""
set_interface_property clk_source SVD_ADDRESS_GROUP ""

add_interface_port clk_source clk_source clk Input 1


# 
# connection point ad_da
# 
add_interface ad_da conduit end
set_interface_property ad_da associatedClock clock
set_interface_property ad_da associatedReset reset
set_interface_property ad_da ENABLED true
set_interface_property ad_da EXPORT_OF ""
set_interface_property ad_da PORT_NAME_MAP ""
set_interface_property ad_da SVD_ADDRESS_GROUP ""

add_interface_port ad_da dac export Output 14
add_interface_port ad_da ad export Input 14
add_interface_port ad_da modulation_wave export Input 1

