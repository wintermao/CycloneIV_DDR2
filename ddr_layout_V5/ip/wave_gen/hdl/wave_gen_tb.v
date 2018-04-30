//------------------------------------------------
//   wave generate testbench
//   2018.4.27
//   create by mmh
//------------------------------------------------

 `timescale 1ns/1ns
 `define delay 5
 `define delay_s 10
 
`define ADDR_AMP_MAX	3'h0
`define ADDR_AMP_MIN	3'h1
`define ADDR_FREQ_DIV	3'h2
`define ADDR_POINT		3'h3
`define ADDR_CONTROL	3'h4 
`define ADDR_DAC			3'h5

 module wave_gen_tb;

 	reg clk,reset_n,avs_s0_chipselect,avs_s0_read,avs_s0_write;
 	reg [31:0] avs_s0_writedata;
 	wire [31:0] avs_s0_readdata;
 	reg [2:0] avs_s0_address;
 	reg clk_source;
 	wire [13:0] dac;			
 			
 wave_gen tb(clk,reset_n,avs_s0_chipselect,avs_s0_write,avs_s0_read,avs_s0_writedata,avs_s0_readdata,avs_s0_address,clk_source,dac);
 
  defparam tb.AmpMax=14'h3fff;
	defparam tb.AmpMin=14'h0;
	defparam tb.FreqDiv=32'd20;
	defparam tb.SamplePonint=16'd256;
	
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
  input [2:0] addr;
  input [31:0] data;
  begin
  #`delay;
	avs_s0_address=addr;
	avs_s0_writedata=data;
	avs_s0_chipselect=1;
	avs_s0_write=1;
	#`delay;
	avs_s0_chipselect=0;
	avs_s0_write=0;
	end
endtask
   
 initial                         
   begin
     reset_n = 1;
     #`delay
     reset_n = 0;
     #`delay
     reset_n = 1;
     
     avalon_write(`ADDR_AMP_MAX,14'h3fff);
     avalon_write(`ADDR_AMP_MIN,14'h0); 
     avalon_write(`ADDR_FREQ_DIV,32'd3); 
     avalon_write(`ADDR_POINT,16'd256); 
     avalon_write(`ADDR_CONTROL,8'h1); 
     #30000
      avalon_write(`ADDR_CONTROL,8'h0);
     #1000
      avalon_write(`ADDR_CONTROL,8'h3);
     #50000
      avalon_write(`ADDR_CONTROL,8'h5);
     #50000
      avalon_write(`ADDR_AMP_MAX,14'h1fff);
     #50000
      avalon_write(`ADDR_AMP_MIN,14'h1000);
     #50000
      avalon_write(`ADDR_FREQ_DIV,32'h5);
     #50000
      avalon_write(`ADDR_CONTROL,8'h7);
      avalon_write(`ADDR_DAC,14'h3fff);
     #1000 
      avalon_write(`ADDR_DAC,14'h2fff); 
     #1000 
      avalon_write(`ADDR_DAC,14'h1fff);
     #1000 
      avalon_write(`ADDR_DAC,14'h0);            
      #1000 $stop;
     
   end

 endmodule

 /*************************************** END OF TB ***********************************************************************/