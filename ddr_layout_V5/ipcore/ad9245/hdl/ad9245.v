module ad9245					
(
	//ad9245 interface
	input wire ad_clk_source,			//ad clock source
	output  wire ad_clk,					//ad sample clock
	input  wire [13:0] ad_data,		//ad sample data
	
	//AVALON interface
	input  wire clk,							//AVALON clock
	input  wire reset_n,					//AVALON reset_n
	input  wire chipselect,				//AVALON chipselect
	input  wire read,							//AVALON read
	output reg [31:0] readdata		//AVALON read data
);

	always @(posedge clk or negedge reset_n)
	begin
		if (!reset_n)
		begin
			//system init
		end
		else
		begin
			if(chipselect && read)		//AVALON read 
			begin
				readdata <= {18'h0,ad_data};
			end
		end
	end
	assign ad_clk=ad_clk_source;
endmodule
