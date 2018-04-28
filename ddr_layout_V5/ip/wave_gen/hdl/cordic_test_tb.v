`timescale 1 ps/ 1 ps

module Cordic_Test_tb;

// Inputs
reg                         CLK_50M;
reg                         RST_N;
reg             [24:0]      cnt;
reg             [24:0]      cnt_n;
reg             [31:0]      Phase;
reg             [31:0]      Phase_n;
wire            [31:0]      Sin;
wire            [31:0]      Cos;
wire            [31:0]      Error;
reg							[24:0]			step;

// Instantiate the Unit Under Test (UUT)
Cordic_Test                 uut 
(
    .CLK_50M                (CLK_50M    ),
    .RST_N                  (RST_N      ),
    .Phase                  (Phase      ),
    .Sin                    (Sin        ),
    .Cos                    (Cos        ),
    .Error                  (Error      )
);

initial
begin
    #0 CLK_50M = 1'b0;
    #10000 RST_N = 1'b0;
    #10000 RST_N = 1'b1;
    #10000000 $stop;
end 

always #10000 
begin
    CLK_50M = ~CLK_50M;
end

always @ (posedge CLK_50M or negedge RST_N)
begin
    if(!RST_N) begin
        cnt <= 1'b0;
        step <= 25'h10000;
    end else
        cnt <= cnt_n;
end

always @ (*)
begin
    if(cnt >= 25'h1680000)
        cnt_n = 1'b0;
    else
        cnt_n = cnt + step;
end

//生成相位0-359度,Phase[26:25]为相位的象限,Phase[24:16]为相位整数值，Phase[15:0]为相位小数值
always @ (posedge CLK_50M or negedge RST_N)
begin
    if(!RST_N)
        Phase <= 1'b0;
    else
        Phase <= Phase_n;
end

always @ (*)
begin
    if(cnt <= 25'h5a0000)
        Phase_n = cnt;
    else if(cnt > 25'h5a0000 && cnt <= 25'hb40000)
        Phase_n = {2'b01,cnt - 25'h5a0000};
    else if(cnt > 25'hb40000 && cnt <= 25'h10e0000)
        Phase_n = {2'b10,cnt - 25'hb40000};
    else if(cnt > 25'h10e0000)
        Phase_n = {2'b11,cnt - 25'h10e0000};
end

endmodule