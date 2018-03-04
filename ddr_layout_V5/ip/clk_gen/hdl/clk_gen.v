//create by mmh 2018.3.4

`define	AddrAD1			3'h00
`define	AddrAD2			3'h01
`define AddrDAC1		2'h02
`define AddrDAC2		3'h03
`define AddrDAC3		3'h04
`define	AddrDAC4		3'h05
`define	AddrLight		3'h06

module clk_gen					
(
	//clock output interface
	input  wire clk_source,				//clock sourece
	output reg ad1_clk,						//ad1 clock
	output reg ad2_clk,						//ad2 clock
	output reg dac1_clk,					//dac1 clock
	output reg dac2_clk,					//dac2 clock
	output reg dac3_clk,					//dac3 clock
	output reg dac4_clk,					//dac4 clock
	output reg light_clk,					//light clock
	
	//avalon interface
	input  wire clk,							//avalon clock
	input  wire reset_n,					//avalon reset_n
	input  wire chipselect,				//avalon chipselect
	input  wire [2:0] address,		//avalon address
	input  wire read,							//avalon read
	input  wire write,						//avalon write
	output reg  [31:0] readdata,	//avalon read data
	input  wire [31:0] writedata	//avalon write data
);
	reg	[31:0] ad1_pre,ad1_num;
	reg [31:0] ad2_pre,ad2_num;
	reg [31:0] dac1_pre,dac1_num;
	reg [31:0] dac2_pre,dac2_num;
	reg [31:0] dac3_pre,dac3_num;
	reg [31:0] dac4_pre,dac4_num;
	reg [31:0] light_pre,light_num;

	parameter OSC_CLOCK=108000000;

	always @(posedge clk or negedge reset_n)
	begin
		if (!reset_n)
		begin
			ad1_pre<=1;
			ad2_pre<=1;
			dac1_pre<=1;
			dac2_pre<=1;
			dac3_pre<=1;
			dac4_pre<=1;
			light_pre<=OSC_CLOCK/2;
		end
		else
		begin
			if(chipselect && write)		//avalon write 
			begin
				case(address)
					`AddrAD1:		ad1_pre <= writedata;
					`AddrAD2:		ad2_pre <= writedata;
					`AddrDAC1:	dac1_pre <= writedata;
					`AddrDAC2:	dac2_pre <= writedata;
					`AddrDAC3:	dac3_pre <= writedata;
					`AddrDAC4:	dac4_pre <= writedata;
					`AddrLight:	light_pre <= writedata;
				endcase
			end
			else if(chipselect && read)
			begin
				case(address)
					`AddrAD1:		readdata <= ad1_pre;
					`AddrAD2:		readdata <= ad2_pre;
					`AddrDAC1:	readdata <= dac1_pre;
					`AddrDAC2:	readdata <= dac2_pre;
					`AddrDAC3:	readdata <= dac3_pre;
					`AddrDAC4:	readdata <= dac4_pre;
					`AddrLight:	readdata <= light_pre;
				endcase
			end
		end
	end
	
	always @(posedge clk_source or negedge reset_n)
	begin
		if (!reset_n)
		begin
			ad1_num<=0;
			ad2_num<=0;
			dac1_num<=0;
			dac2_num<=0;
			dac3_num<=0;
			dac4_num<=0;
			light_num<=0;
			ad1_clk<=0;
			ad2_clk<=0;
			dac1_clk<=0;
			dac2_clk<=0;
			dac3_clk<=0;
			dac4_clk<=0;
			light_clk<=0;
		end
		else
		begin
			ad1_num<=ad1_num+1;
			ad2_num<=ad2_num+1;
			dac1_num<=dac1_num+1;
			dac2_num<=dac2_num+1;
			dac3_num<=dac3_num+1;
			dac4_num<=dac4_num+1;
			light_num<=light_num+1;
			
			if(ad1_num>=ad1_pre) 
			begin
				ad1_num<=0;
				ad1_clk <= ~ad1_clk;
			end 
			else 
			begin
				ad1_clk <= ad1_clk;
			end
			
			if(ad2_num>=ad2_pre) 
			begin
				ad2_num<=0;
				ad2_clk <= ~ad2_clk;
			end 
			else 
			begin
				ad2_clk <= ad2_clk;
			end
			
			if(dac1_num>=dac1_pre) 
			begin
				dac1_num<=0;
				dac1_clk <= ~dac1_clk;
			end 
			else 
			begin
				dac1_clk <= dac1_clk;
			end
			
			if(dac2_num>=dac2_pre) 
			begin
				dac2_num<=0;
				dac2_clk <= ~dac2_clk;
			end 
			else 
			begin
				dac2_clk <= dac2_clk;
			end
			
			if(dac3_num>=dac3_pre) 
			begin
				dac3_num<=0;
				dac3_clk <= ~dac3_clk;
			end 
			else 
			begin
				dac3_clk <= dac3_clk;
			end
			
			if(dac4_num>=dac4_pre) 
			begin
				dac4_num<=0;
				dac4_clk <= ~dac4_clk;
			end 
			else 
			begin
				dac4_clk <= dac4_clk;
			end
			
			if(light_num>=light_pre) 
			begin
				light_num<=0;
				light_clk <= ~light_clk;
			end 
			else 
			begin
				light_clk <= light_clk;
			end
		end
	end
endmodule
