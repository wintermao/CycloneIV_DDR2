// wave_gen.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.
`timescale 1 ns / 1 ns


`define ADDR_AMP_MAX	3'h0
`define ADDR_AMP_MIN	3'h1
`define ADDR_FREQ_DIV	3'h2
`define ADDR_POINT		3'h3
`define ADDR_CONTROL	3'h4
`define ADDR_DAC			3'h5

module wave_gen (
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
		output wire [13:0] dac
	);
	parameter AmpMax=14'h3fff;
	parameter AmpMin=14'h0;
	parameter FreqDiv=32'd20;
	parameter SamplePonint=16'd256;
	
	reg [7:0] control;
	reg [13:0] dac_test;
	reg [31:0] freq_div;
	reg [13:0] amp_max;
	reg [13:0] amp_min;	
	reg [15:0] sample_num;
	reg [13:0] dac_reg;
	reg [13:0] step;
	reg [15:0] counter;
	reg [31:0] clk_count;
	reg clk_out;
	reg clk_out_ge2;
	reg [24:0] sin_step,sin_in;
	reg [31:0] cordic_in;
	wire [31:0] sin;
	reg [16:0] sin_out;
	reg [31:0] sin_out1;
	reg [31:0] sin_scale;
	
	always @(posedge clk or negedge reset_n)
	begin
		if (!reset_n)
		begin
			control <= 8'h1;
			amp_max <= AmpMax;
			amp_min <= AmpMin;
			freq_div <= FreqDiv;
			sample_num <= SamplePonint;
			dac_test <= 14'h0;
		end
		else
		begin
			if(avs_s0_chipselect & avs_s0_write)	begin
				case (avs_s0_address) 
        	`ADDR_AMP_MAX	: amp_max <= avs_s0_writedata[13:0];	
          `ADDR_AMP_MIN : amp_min <= avs_s0_writedata[13:0];	
          `ADDR_FREQ_DIV: freq_div <= avs_s0_writedata;
          `ADDR_POINT	: sample_num <= avs_s0_writedata[15:0];	
          `ADDR_CONTROL	: control <= avs_s0_writedata[7:0];
					`ADDR_DAC			: dac_test <= avs_s0_writedata[13:0];
        endcase
			end	if(avs_s0_chipselect & avs_s0_read) begin
				case (avs_s0_address) 
        	`ADDR_AMP_MAX	: avs_s0_readdata <= {18'h0,amp_max};	
          `ADDR_AMP_MIN : avs_s0_readdata <= {18'h0,amp_min};	
          `ADDR_FREQ_DIV: avs_s0_readdata <= freq_div;
          `ADDR_POINT	: avs_s0_readdata <= {16'h0,sample_num};	
          `ADDR_CONTROL	: avs_s0_readdata <= {24'h0,control};
					`ADDR_DAC			: avs_s0_readdata <= {18'h0,dac_test};
        endcase
			end
		end
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
			dac_reg <= 14'h0;
			counter <= 16'h0;
			step <= 14'h0;
			sin_in <= 25'h0;
			sin_step <= 25'h0;
		end	else begin
			counter <= counter +1'h1;
			if(control[2:1]==0) begin								//Sawtooth wave
				step <= (amp_max-amp_min)/sample_num;
				if(counter<sample_num) begin
					dac_reg <= dac_reg + step;
				end else begin
					counter <= 1'h0;
					dac_reg <= amp_min;
				end
			end else if(control[2:1]==1) begin											//Trigonometric wave 
				step <= ((amp_max-amp_min)/sample_num)<<1;
				if(counter<(sample_num>>1)) begin
					dac_reg <= dac_reg + step;
				end else if(counter<sample_num) begin
					dac_reg <= dac_reg - step;
				end else begin
					counter <= 1'h0;
					dac_reg <= amp_min;
				end
			end else if(control[2:1]==2) begin											//sin wave 
				sin_step <= 25'h1680000/sample_num;
				sin_in <= sin_in + sin_step;
				
				if(sin_in <= 25'h5a0000)
        	cordic_in <= sin_in;
    		else if(sin_in > 25'h5a0000 && sin_in <= 25'hb40000)
        	cordic_in = {2'b01,sin_in - 25'h5a0000};
    		else if(sin_in > 25'hb40000 && sin_in <= 25'h10e0000)
        	cordic_in = {2'b10,sin_in - 25'hb40000};
    		else if(sin_in > 25'h10e0000 && sin_in<=25'h1680000 )
        	cordic_in = {2'b11,sin_in - 25'h10e0000};
        else begin
        	sin_in <= 1'h0;
        	counter <= 1'h0 ;
        end
        
        sin_scale <=(( 18'h20000)<<8)/(amp_max-amp_min);
        sin_out <= (sin[16:0]+17'h10000);
        sin_out1 <= (sin_out<<8)/sin_scale;
        dac_reg <= amp_min+sin_out1[13:0];
			end else if(control[2:1]==3) begin
				dac_reg <= dac_test;
			end
		end
	end

Cordic_Test Cordic_dest(
    .CLK_50M                (clk_out),
    .RST_N                  (reset_n),
    .Phase                  (cordic_in),
    .Sin                    (sin),
    .Cos                    ( ),
    .Error                  ( )
);

assign dac = control[0]? dac_reg : 14'h0;	

endmodule
