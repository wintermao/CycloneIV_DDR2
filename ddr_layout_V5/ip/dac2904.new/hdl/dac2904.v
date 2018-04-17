// dac2904.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.

`timescale 1 ns / 1 ns
module dac2904 (
		input  wire        clk,                // clock.clk
		input  wire        reset_n,            // reset.reset
		input  wire 			 avs_s0_chipselect,	 //			 .chipselect
		input  wire        avs_s0_write,       //      .write
		input  wire [31:0] avs_s0_writedata,   //      .writedata
		output reg         avs_s0_waitrequest, //      .waitrequest
		input wire				sample_clock,				 //sample clock
		output reg [13:0] dac_data						 //dac transfer data
	);

	always @(posedge clk or negedge reset_n)
	begin
		if (!reset_n)
		begin
			dac_data <= 14'h0;
		end
		else
		begin
			if(avs_s0_chipselect && avs_s0_write)	begin
				dac_data <= avs_s0_writedata[13:0];
			end	else begin
				dac_data <= dac_data;
			end
		end
	end
	
	reg sample_clk_last;
	always@(posedge clk)
	begin
		if(!reset_n) 	sample_clk_last <= 1'b0;
		else 	sample_clk_last <= sample_clock;
	end	
	
	always @(posedge clk or negedge reset_n)
	begin
		if (!reset_n) avs_s0_waitrequest <= 1'b0;
		else
		begin
			if( (sample_clk_last == 1'b0 )&( sample_clock == 1'b1) ) avs_s0_waitrequest <= 1'b0;
			else avs_s0_waitrequest <= 1'b1;
		end
	end

endmodule
