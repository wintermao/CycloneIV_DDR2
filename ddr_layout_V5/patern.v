module data_generator( in_clk, out_data,data_clk);  
   input in_clk;
   output [27:0]out_data;
   output data_clk;
	
 assign out_data= 28'b1; 
 assign data_clk=in_clk;
 
 endmodule
  
  