module dac2904					
(
	//dac2904 interface
	output reg [13:0] dac_data,		//dac transfer data
	
	//avalon interface
	input  wire clk,							//avalon clock
	input  wire reset_n,					//avalon reset_n
	input  wire chipselect,				//avalon chipselect
	input  wire write,						//avalon write
	input  wire [31:0] writedata	//avalon write data
);

	always @(posedge clk or negedge reset_n)
	begin
		if (!reset_n)
		begin
			//system init
		end
		else
		begin
			if(chipselect && write)		//avalon write 
			begin
				dac_data <= writedata[13:0];
			end
			else
			begin
				dac_data <= dac_data;
			end
		end
	end

endmodule
