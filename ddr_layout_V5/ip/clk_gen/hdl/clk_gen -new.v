//create by mmh 2018.3.22


module clk_gen					
(clk_source,clk_out,clk,reset_n,chipselect,address,read,write,readdata,writedata);
	parameter clk_num=4;
	//clock output interface
	input  wire clk_source;						//clock sourece
	output reg [clk_num-1:0] clk_out;	//clock output
	
	//avalon interface
	input  wire clk;							//avalon clock
	input  wire reset_n;					//avalon reset_n
	input  wire chipselect;				//avalon chipselect
	input  wire [3:0] address;		//avalon address
	input  wire read;							//avalon read
	input  wire write;						//avalon write
	output reg  [31:0] readdata;	//avalon read data
	input  wire [31:0] writedata;	//avalon write data

	
	reg	[31:0] clk_pre[0:clk_num-1];	//predivide
	reg [31:0] clk_count[0:clk_num-1];	//counter
	integer i;

	always @(posedge clk or negedge reset_n)
	begin
		if (!reset_n)
		begin
			for(i=0;i<clk_num;i=i+1) clk_pre[i]<=2+i;
		end
		else
		begin
			if(chipselect && write)		//avalon write 
			begin
				if(address<clk_num) clk_pre[address]<=writedata;
			end
			else if(chipselect && read)
			begin
				if(address<clk_num) readdata<=clk_pre[address];
			end
		end
	end
	
	always @(posedge clk_source or negedge reset_n)
	begin
		if (!reset_n)
		begin
			for(i=0;i<clk_num;i=i+1) clk_count[i]<=0;
		end
		else
		begin
			for(i=0;i<clk_num;i=i+1) begin
				if(clk_count[i]==clk_pre[i]-1) clk_count[i]<=0;
				else clk_count[i]<=clk_count[i]+1;
				if(clk_count[i]==clk_pre[i]-1) clk_out[i] <= ~clk_out[i];
				else if(clk_count[i]==clk_pre[i]>>1) clk_out[i] <= ~clk_out[i];
				else clk_out[i] <= clk_out[i];
			end
		end
	end
endmodule
