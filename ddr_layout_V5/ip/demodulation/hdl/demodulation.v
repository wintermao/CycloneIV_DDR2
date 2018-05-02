// demodulation.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.
`timescale 1 ns / 1 ns


`define ADDR_SAMPLE1_START	3'h0
`define ADDR_SAMPLE2_START	3'h1
`define ADDR_SAMPLE1_NUM		3'h2
`define ADDR_SAMPLE2_NUM		3'h3
`define ADDR_AD							3'h4
`define ADDR_FREQ_DIV				3'h5

module demodulation (
		//avalon interface
		input  wire clk,                // clock.clk
		input  wire reset_n,            // reset.reset
		input  wire avs_s0_chipselect,	//			.chipselect
		input  wire avs_s0_write,       //      .write
		input  wire avs_s0_read,				//			.read
		input  wire [31:0] avs_s0_writedata,  //      .writedata
		output reg  [31:0] avs_s0_readdata,		//			.readdata
		input  wire [2:0] avs_s0_address,
		//dac interface
		input wire	clk_source,						//source clock
		input wire  modulation_wave,
		input wire  [13:0] ad,
		output wire [13:0] dac
	);
	parameter Sample1Start=16'd32;
	parameter Sample2Start=16'd128;
	parameter Sample1Num=16'd32;
	parameter Sample2Num=16'd32;
	parameter FreqDiv=32'h1;
	
	reg [15:0] sample_1_start;
	reg [15:0] sample_2_start;
	reg [15:0] sample_1_num;
	reg [15:0] sample_2_num;
	//reg [13:0] dac_reg;
	reg [15:0] counter;
	reg [31:0] clk_count;
	wire clk_out;
	reg clk_out_ge2;
	reg modulation_wave_last;
	reg [31:0] freq_div;
	reg [31:0] sum_left,sum_right;
	reg [13:0] ave_left,ave_right;
	
	always @(posedge clk or negedge reset_n)
	begin
		if (!reset_n)
		begin
			sample_1_start <= Sample1Start;
			sample_2_start <= Sample2Start;
			sample_1_num <= Sample1Num;
			sample_2_num <= Sample2Num;
			freq_div <= FreqDiv;
		end
		else
		begin
			if(avs_s0_chipselect & avs_s0_write)	begin
				case (avs_s0_address) 
        	`ADDR_SAMPLE1_START	: sample_1_start <= avs_s0_writedata[15:0];	
          `ADDR_SAMPLE2_START : sample_2_start <= avs_s0_writedata[15:0];	
          `ADDR_SAMPLE1_NUM: sample_1_num <= avs_s0_writedata[15:0];	
          `ADDR_SAMPLE2_NUM	: sample_2_num <= avs_s0_writedata[15:0];	
          `ADDR_FREQ_DIV:			freq_div <= avs_s0_writedata;
        endcase
			end	if(avs_s0_chipselect & avs_s0_read) begin
				case (avs_s0_address) 
        	`ADDR_SAMPLE1_START	: avs_s0_readdata <= {16'h0,sample_1_start};	
          `ADDR_SAMPLE2_START : avs_s0_readdata <= {16'h0,sample_2_start};	
          `ADDR_SAMPLE1_NUM: avs_s0_readdata <=  {16'h0,sample_1_num};	
          `ADDR_SAMPLE2_NUM	: avs_s0_readdata <= {16'h0,sample_2_num};	
					`ADDR_AD			: avs_s0_readdata <= {18'h0,ad};
					`ADDR_FREQ_DIV:	avs_s0_readdata <= freq_div;
        endcase
			end
		end
	end
	
	always @(posedge clk_source)
	begin
		modulation_wave_last <= modulation_wave;
	end
	
	always @(posedge clk_source or negedge reset_n)
	begin
		if (!reset_n) begin
			clk_count <= 0;
			clk_out_ge2 <= 0;
		end	else begin
			if(clk_count>=(freq_div-1)) begin
				clk_count<=0;
				clk_out_ge2 <= 0;
			end else if(clk_count==(freq_div>>1)) begin
				clk_count<=clk_count+1;
				clk_out_ge2 <= 1;
			end else begin 
				clk_count<=clk_count+1;
				clk_out_ge2 <= clk_out_ge2;
			end
		end
	end
	
	assign clk_out = (freq_div==1)? clk_source : clk_out_ge2;
		
	always @(posedge clk_out or negedge reset_n)
	begin
		if (!reset_n)	begin
			counter <= 16'h0;
			sum_left <= 32'h0;
			sum_right <= 32'h0;
		end	else begin
			if(modulation_wave_last==0 && modulation_wave==1) begin
				counter <= 16'h0;
				sum_left <= 32'h0;
				sum_right <= 32'h0;
			end else begin
				counter <= counter +1'h1;
			end
			if(counter>=sample_1_start && counter<(sample_1_start+sample_1_num)) begin
				sum_left <= sum_left + ad;
			end else if(counter>=sample_2_start && counter<(sample_2_start+sample_2_num)) begin
				sum_right <= sum_right + ad;
			end else begin
				ave_left <= sum_left/sample_1_num;
				ave_right <= sum_right/sample_2_num;
			end

		end
	end

	assign dac = ave_left - ave_right + 14'h2000;	

endmodule
