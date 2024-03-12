############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project delilah-hw-filter
set_top filter
add_files delilah-hw-filter/filter.h
add_files delilah-hw-filter/filter.c
add_files -tb delilah-hw-filter/filter_test.c -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xczu17eg-ffvc1760-2-e} -tool vivado
create_clock -period 500MHz -name default
config_sdx -target none
config_export -format ip_catalog -rtl verilog -use_netlist none -vivado_optimization_level 2 -vivado_phys_opt place -vivado_report_level 0
config_interface -clock_enable=0 -expose_global=0 -m_axi_addr64 -m_axi_offset slave -register_io off -trim_dangling_port=0
set_clock_uncertainty 5%
#source "./delilah-hw-filter/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
