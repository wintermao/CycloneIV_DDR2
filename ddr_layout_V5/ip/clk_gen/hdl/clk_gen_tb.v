//------------------------------------------------
//   spi master testbench
//   2018.3.14
//   create by mmh
//------------------------------------------------

 `timescale 1ns/1ns
 `define delay 5
 
 module clk_gen_tb;
 parameter clk_num=4;
 	reg clk_source,clk,reset_n,chipselect,read,write;
 	reg [31:0] writedata;
 	reg [4:0] address;
 	wire	[clk_num-1:0] clk_out;
 	wire [31:0] readdata;					
 clk_gen tb(clk_source,clk_out,clk,reset_n,chipselect,address,read,write,readdata,writedata);
  defparam tb.clk_num=clk_num;
	// Generates serial clock of time period 10
 initial                         
   begin
     clk_source = 0;
     forever #`delay clk_source = !clk_source;
   end
 initial                         
   begin
     clk=0;
     forever #`delay clk = !clk;
   end
task  avalon_write;
  input [4:0] addr;
  input [31:0] data;
  begin
  #`delay;
	address=addr;
	writedata=data;
	chipselect=1;
	write=1;
	#`delay;
	chipselect=0;
	write=0;
	end
endtask
   
 initial                         
   begin
     reset_n = 1;
     #`delay
     reset_n = 0;
     #`delay
     reset_n = 1;
     
     avalon_write(5'h0,32'h2);
     avalon_write(5'h1,32'h3); 
     avalon_write(5'h2,32'h4); 
     avalon_write(5'h3,32'h5); 
     
   end


 endmodule

 /*************************************** END OF TB ***********************************************************************/