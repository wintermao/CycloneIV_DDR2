module led_flash( in_clk,reset_n,flash);  
   input in_clk;
   input reset_n;
   output flash;
   
   reg flash;
   reg [23:0]counter_temp;

parameter OSC_CLOCK=27000000;
initial
begin
flash=0;
counter_temp=0;
end
always @(posedge in_clk or negedge reset_n)
begin
	if (reset_n == 0)
    begin
    	counter_temp<=0;
			flash<=0;
    end
  else
    begin
    	counter_temp=counter_temp+1;
    	if(counter_temp>=(OSC_CLOCK/2))
    	begin
    		counter_temp=0;
    		flash=~flash;
    	end
  	end
 end
endmodule