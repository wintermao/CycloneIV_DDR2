//------------------------------------------------
//   dac2904 testbench
//   2018.4.16
//   create by mmh
//------------------------------------------------

 `timescale 1ns/1ns
 `define delay 5
 `define sample_delay 20
 `define write_delay 30
 
 
 module dac2904_tb;

 	reg sample_clk,clk,reset_n,chipselect,write;
 	wire waitrequest;
 	wire [13:0] dac_data;
 	reg [31:0] writedata;
				
 dac2904 tb(clk,reset_n,chipselect,write,writedata,waitrequest,sample_clk,dac_data);

	// Generates avalon clock of time period 10
 initial                         
   begin
     clk = 0;
     forever #`delay clk = !clk;
   end

 initial                         
   begin
     sample_clk=0;
     forever #`sample_delay sample_clk = !sample_clk;
   end
task  avalon_write;
  input [31:0] data;
  begin
  #`delay;
	writedata=data;
	chipselect=1;
	write=1;
	#`delay;
	chipselect=0;
	write=0;
	#`write_delay;
	end
endtask
   
 initial                         
   begin
     reset_n = 1;
     #`delay
     reset_n = 0;
     #`delay
     reset_n = 1;
     
     avalon_write(32'h2);
     avalon_write(32'h3); 
     avalon_write(32'h4); 
     avalon_write(32'h5); 
     
   end


 endmodule

 /*************************************** END OF TB ***********************************************************************/