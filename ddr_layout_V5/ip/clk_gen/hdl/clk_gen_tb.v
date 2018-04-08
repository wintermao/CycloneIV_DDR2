//------------------------------------------------
//   spi master testbench
//   2018.3.14
//   create by mmh
//------------------------------------------------

 `timescale 1ns/1ns
 `define delay 5
 
 module clk_gen_tb;
 localparam clk_num=4;
 	reg clk_source,clk,reset_n,chipselectread,write;
 	reg [31:0] writedata;
 	reg [3:0] address;
 	wire	[clk_num-1:0] clk_out;
 	wire [31:0] readdata;					
 clk_gen tb(clk_source,clk_out,clk,reset_n,chipselect,address,read,write,readdata,writedata);

	// Generates serial clock of time period 10
 initial                         
   begin
     clk_source = 0;
     forever #`delay clk_source = !clk_source;
   end
   
 initial                         
   begin
     reset_n = 1;
     #`delay
     reset_n = 0;
     #`delay
     reset_n = 1;
     
   end


 endmodule

 /*************************************** END OF TB ***********************************************************************/