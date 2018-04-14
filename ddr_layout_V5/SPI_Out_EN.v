module SPI_Out_EN
(
 input wire SPI_SYNC,   
 input wire SPI_CLK,
 input wire nReset,
 input wire SPI_MOSI,
 input wire Clock_108M,
 
 output wire SPI_Out_EN,
 output wire SPI_Out_EN2
);
parameter SPI_Command_Len = 16;
parameter Output_Delay_Clock = 27;

reg [7:0]Clock_Number;      //16+8个固定时钟计数
reg [9:0]Clock_Number2; 
reg Out_enable;
reg Out_enable_Delay;
reg Write_Read_Flag;

//器件只支持正极性，上升沿。所以此处用下降沿计算
	  always@(posedge SPI_CLK or negedge SPI_SYNC or negedge nReset)    //主控器是正信号
	    begin 
		  if(!nReset)
		   begin
			 Clock_Number=0;
          Out_enable=1;
			 Write_Read_Flag=1;
			end
		  else if(!SPI_SYNC)
		   begin
			 Clock_Number=0;
          Out_enable=1;
			 Write_Read_Flag=1;
			end
		  else if(SPI_CLK)
		   begin
			 if(Clock_Number==0)Write_Read_Flag=SPI_MOSI;
		    if(Write_Read_Flag==0)       //0说明是写命令
            Out_enable=1;
		    else if(Write_Read_Flag==1)                          //1说明是读命令
		     begin
		      if(Clock_Number<SPI_Command_Len-1)       //最后一个clock跳变。需要延时一个clock
	          Out_enable=1;
            else
				 Out_enable=0;
	         Clock_Number=Clock_Number+1'h1;
		     end
			end
      end

//	output延时处理	
	 always@(posedge Clock_108M or negedge nReset)    //主控器是正信号
	  begin
	   if(!nReset)
		  begin
			Clock_Number2=0;
         Out_enable_Delay=1;
		  end
		else if(Out_enable)
		 begin
		  Out_enable_Delay=1;
	     Clock_Number2=0;
		 end
		else if(!Out_enable)	
		 begin
		  if(Clock_Number2<Output_Delay_Clock+1)
		   begin
			 Out_enable_Delay=1;
			 Clock_Number2=Clock_Number2+1'h1;
			end
		  else
		   Out_enable_Delay=0;	  
		 end
	  end

	assign SPI_Out_EN2=Out_enable_Delay;
   assign SPI_Out_EN=Out_enable | Out_enable_Delay;
	
endmodule