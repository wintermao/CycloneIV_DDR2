// triangle_demodu.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.

`timescale 1 ns / 1 ns
`include "triangle_define.v"

module triangle_demodu (
		//avalon interface
		input  wire clk,                // clock.clk
		input  wire reset_n,            // reset.reset
		input  wire avs_s0_chipselect,	//			.chipselect
		input  wire avs_s0_write,       //      .write
		input  wire avs_s0_read,				//			.read
		input  wire [31:0] avs_s0_writedata,  //      .writedata
		output reg  [31:0] avs_s0_readdata,		//			.readdata
		input  wire [3:0] avs_s0_address,
		//dac interface
		input wire	clk_source,						//source clock
		input wire  [13:0] ad,
		output wire clk_sample,
		output wire [13:0] dac_modu,
		output wire [13:0] dac_demodu
	);
	parameter AmpMax=14'h3fff;
	parameter AmpMin=14'h0;
	parameter FreqDiv=32'd20;
	parameter SamplePonint=16'd256;
	parameter Sample1Start=16'd32;
	parameter Sample2Start=16'd128;
	parameter Sample1Num=16'd32;
	parameter Sample2Num=16'd32;
		
	reg [31:0] freq_div;
	reg [13:0] amp_max;
	reg [13:0] amp_min;	
	reg [15:0] sample_num;
	reg [15:0] sample_1_start;
	reg [15:0] sample_2_start;
	reg [15:0] sample_1_num;
	reg [15:0] sample_2_num;
	
	reg [13:0] dac_reg;
	reg [13:0] step;
	reg [15:0] counter_modu;
	reg [15:0] counter_demodu;
	reg [31:0] clk_count;
	reg clk_out;
	reg [31:0] sum_left,sum_right;
	reg [13:0] ave_left,ave_right;
	reg direction,direction_last;
	
	always @(posedge clk or negedge reset_n)
	begin
		if (!reset_n)
		begin
			amp_max <= AmpMax;
			amp_min <= AmpMin;
			freq_div <= FreqDiv;
			sample_num <= SamplePonint;
			sample_1_start <= Sample1Start;
			sample_2_start <= Sample2Start;
			sample_1_num <= Sample1Num;
			sample_2_num <= Sample2Num;
		end
		else
		begin
			if(avs_s0_chipselect & avs_s0_write)	begin
				case (avs_s0_address) 
        	`ADDR_AMP_MAX	: amp_max <= avs_s0_writedata[13:0];	
          `ADDR_AMP_MIN : amp_min <= avs_s0_writedata[13:0];	
          `ADDR_FREQ_DIV: freq_div <= avs_s0_writedata;
          `ADDR_POINT	: sample_num <= avs_s0_writedata[15:0];	
        	`ADDR_SAMPLE1_START	: sample_1_start <= avs_s0_writedata[15:0];	
          `ADDR_SAMPLE2_START : sample_2_start <= avs_s0_writedata[15:0];	
          `ADDR_SAMPLE1_NUM: sample_1_num <= avs_s0_writedata[15:0];	
          `ADDR_SAMPLE2_NUM	: sample_2_num <= avs_s0_writedata[15:0];	          
        endcase
			end	if(avs_s0_chipselect & avs_s0_read) begin
				case (avs_s0_address) 
        	`ADDR_AMP_MAX	: avs_s0_readdata <= {18'h0,amp_max};	
          `ADDR_AMP_MIN : avs_s0_readdata <= {18'h0,amp_min};	
          `ADDR_FREQ_DIV: avs_s0_readdata <= freq_div;
          `ADDR_POINT	: avs_s0_readdata <= {16'h0,sample_num};	
        	`ADDR_SAMPLE1_START	: avs_s0_readdata <= {16'h0,sample_1_start};	
          `ADDR_SAMPLE2_START : avs_s0_readdata <= {16'h0,sample_2_start};	
          `ADDR_SAMPLE1_NUM: avs_s0_readdata <=  {16'h0,sample_1_num};	
          `ADDR_SAMPLE2_NUM	: avs_s0_readdata <= {16'h0,sample_2_num};	
        endcase
			end
		end
	end
	
	always @(posedge clk_source or negedge reset_n)
	begin
		if (!reset_n) begin
			clk_count <= 0;
			clk_out <= 0;
		end	else begin
			if(clk_count>=(freq_div-1)) begin
				clk_count<=0;
				clk_out <= 0;
			end else if(clk_count==(freq_div>>1)) begin
				clk_count<=clk_count+1;
				clk_out <= 1;
			end else begin 
				clk_count<=clk_count+1;
				clk_out <= clk_out;
			end
		end
	end
	
	assign clk_sample = (freq_div==1)? clk_source : clk_out;
		
	always @(posedge clk_sample or negedge reset_n)
	begin
		if (!reset_n)	begin
			dac_reg <= 14'h0;
			counter_modu <= 16'h0;
			step <= 14'h0;
		end	else begin
			counter_modu <= counter_modu +1'h1;
			step <= ((amp_max-amp_min)/sample_num)<<1;
			if(counter_modu<(sample_num>>1)) begin
				dac_reg <= dac_reg + step;
				direction <= 1'h1;
			end else if(counter_modu<sample_num-1) begin
				dac_reg <= dac_reg - step;
				direction <= 1'h0;
			end else begin
				counter_modu <= 1'h0;
				dac_reg <= amp_min;
				direction <= 1'h0;
			end
		end
	end
	
	assign dac_modu = dac_reg;

	always @(posedge clk_sample)
	begin
		direction_last <= direction;
	end
	
	always @(posedge clk_sample or negedge reset_n)
	begin
		if (!reset_n)	begin
			counter_demodu <= 16'h0;
			sum_left <= 32'h0;
			sum_right <= 32'h0;
		end	else begin
			if(direction_last==0 && direction==1) begin
				counter_demodu <= 16'h0;
				sum_left <= 32'h0;
				sum_right <= 32'h0;
			end else begin
				counter_demodu <= counter_demodu +1'h1;
			end
			if(counter_demodu>=sample_1_start && counter_demodu<(sample_1_start+sample_1_num)) begin
				sum_left <= sum_left + ad;
			end else if(counter_demodu>=sample_2_start && counter_demodu<(sample_2_start+sample_2_num)) begin
				sum_right <= sum_right + ad;
			end else begin
				ave_left <= sum_left/sample_1_num;
				ave_right <= sum_right/sample_2_num;
			end
		end
	end

	assign dac_demodu = ave_left - ave_right + 14'h2000;	

endmodule
