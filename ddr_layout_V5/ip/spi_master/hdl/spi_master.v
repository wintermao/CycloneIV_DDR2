//------------------------------------------------
//   spi master
//   2018.1.11
//   create by mmh
//------------------------------------------------
  `timescale 10ns/1ns
  `define addr_rx 			3'h0
  `define addr_tx 			3'h1
  `define addr_status 	3'h2
  `define addr_control	3'h3
  `define addr_divide 	3'h4
  `define addr_chipsel 	3'h5
  module spi_master (
  									clk,
  									reset_n,
  									chipselect,
  									address,
  									read,
  									write,
  									readdata,
  									writedata,
  									miso,
  									mosi,
  									sclk,
  									ss
  									);
  									
//  parameter dataWidth;
  parameter numberOfSlaves=1;
  
	//avalon inteface
  input clk;               	// Host Processor clock
  input reset_n;						// reset
  input chipselect;         // Chip Select
  input [2:0] address;      // A2 - A0, lower bits of addressess bus
  input read;              	// read enables
  input write;							// write enables
  input [31:0] writedata;		// writedata
  output [31:0] readdata;		// readdata
  output interrupt;
  //spi inteface
  input miso;               // Master in slave out
  output mosi;              // Master out slave in
  output sclk;              // SPI clock
  output [numberOfSlaves:0] ss; 					// numberOfSlaves slave select lines
  
  reg [31:0] readdata;
  reg interrupt;
  reg [7:0] shift_register;       // Shift register
  reg [7:0] txdata;               // Transmit buffer
  reg [7:0] rxdata;               // Receive buffer
  reg [16:0] control;     				// Control Register COntrols things like ss, CPOL, CPHA, interupt
  reg [15:0] status;              // Status Register is a dummy register never used.
  reg [7:0] divide_num;         	// Clock divide counter
  reg [3:0] count;                // SPI woread length counter
  reg status_clear;								// status register update signal
  reg sclk;                       // SPI clock
  reg slave_chipselect;           // Slave chipselect flag
  reg mosi;                  			// Master out slave in
  reg spi_woread_send;            // Will send a new spi woread.
  reg [numberOfSlaves:0]ss_reg;
  reg [7:0] divide_pre;
  reg spi_clk_gen;
  reg status_toe,status_roe,status_tmt,status_trdy,status_rrdy,status_e;
  reg read_rx;
  wire CPOL = control[3];          
  wire CPHA = control[4];
  wire [numberOfSlaves:0]ss; 

	//initial default register
  initial 
  begin
      mosi = 0;
      control = 0;
      count = 0;
      slave_chipselect = 1;
      txdata = 0;
      rxdata = 0;
      divide_num = 0;
  end
  
  // Reading, writeiting SPI registers
  always @ (posedge clk or negedge reset_n) begin
  	if (!reset_n) begin
  		//register initial
      control <= 0;
      txdata <= 0;
      divide_pre <= 1;
      ss_reg <= 1;
  	end else begin
      if (chipselect & read) begin
        case (address) 
        	`addr_rx			: readdata <= {24'b0,rxdata};							//read receive register
          `addr_status 	: readdata <= {16'b0,status};							//read status register
          `addr_control	: readdata <= {16'b0,control};						//read control register
        endcase
      end else if(chipselect & write) begin
      	case (address) 
        	`addr_tx 			: txdata <= writedata[7:0];								//write tansmister register
          `addr_status 	: status <= writedata[15:0];							//write status register
          `addr_control	: control <= writedata[15:0];							//write control register
        	`addr_divide	: divide_pre <= writedata[7:0];						//write divede register
        	`addr_chipsel	:	ss_reg <= writedata[numberOfSlaves:0];	//write chip selelt register     
        endcase 	
      end
    end
  end

  // New Spi woread is intiated when transmit buffer is updated
  always @ (posedge clk or negedge reset_n) begin
  	if (!reset_n) begin
  		spi_woread_send <=0;
  	end else begin
      if (chipselect & write & (address == `addr_tx)) begin
          spi_woread_send <=1;																				//spi_woread_send=1 is start send
          if(count!=0) status_toe <= 1;						//set SPI_MASTER_STATUS_TOE_MSK status bit
          else status_toe <= 0;
          if(status_rrdy==1) status_roe <= 1;
          else 	status_roe <= 0;
      end else begin
          spi_woread_send <=0;
      end
    end
  end
  
  // generate status register clear signal
  always @ (posedge clk or negedge reset_n) begin
  	if (!reset_n) begin
  		status_clear <=0;
  	end else begin
      if (chipselect & write & (address == `addr_status)) begin
          status_clear <=1;																				//status_clear=1 is clear status register
      end else begin
          status_clear <=0;
      end
    end
  end
  
// generate read rxdata signal
  always @ (posedge clk or negedge reset_n) begin
  	if (!reset_n) begin
  		read_rx <=0;
  	end else begin
      if (chipselect & read & (address == `addr_rx)) begin
          read_rx <=1;																				//status_clear=1 is clear status register
      end else begin
          read_rx <=0;
      end
    end
  end
  
  // New SPI writeod starts when the transmit buffer is updated
  always @ (posedge clk or negedge reset_n) begin
  	if (!reset_n) begin
  		slave_chipselect <= 1;
  	end else begin
      if (spi_woread_send) begin
          slave_chipselect <= 0;																			//slave_chipselect=0 is spi chipselect active
      end else if ((count == 8) & ~(sclk ^ CPOL)) begin
          slave_chipselect <= 1;
      end 
    end   
  end
  
  // Clock Divider
  always @ (posedge clk or negedge reset_n) begin
  	if (!reset_n) begin
  		divide_num <= 0;
  	end else begin
      divide_num = divide_num + 1; 
      if( divide_num>= divide_pre) begin
      	divide_num = 0 ;  
      	spi_clk_gen = ~spi_clk_gen;
      end
    end
  end

  // Generating the SPI clock
  always @ (posedge spi_clk_gen) begin
      if (~slave_chipselect) begin			//slave_chipselect is low active
          sclk = ~sclk;
      end else if (~CPOL) begin
          sclk = 0; 										//CPOL=0,sclk=0
      end else begin
          sclk = 1;											//CPOL=1,sclk=1
      end
  end
  
  // Reading the miso line and shifting
  always @ (posedge (sclk ^ (CPHA ^ CPOL)) or posedge spi_woread_send) begin
      if (spi_woread_send) begin
          shift_register[7:0] = txdata;
      end else begin 
          shift_register = shift_register << 1;
          shift_register[0] = miso;
      end
  end
  
  // writeiting the mosi
  always @ (negedge (sclk ^ (CPHA ^ CPOL)) or posedge spi_woread_send) begin
      if (spi_woread_send) begin
          mosi = txdata[7];
      end else begin 
          mosi = shift_register[7];
      end
  end

  //status register SPI_MASTER_STATUS_TOE_MSK bit update
  always @ (posedge sclk or posedge slave_chipselect or posedge read_rx or negedge reset_n) begin
  	if (!reset_n) begin
  		status_tmt <= 1;
  		status_trdy <= 1;
  		status_rrdy <= 0;
  	end else if(slave_chipselect) begin
  		rxdata <= shift_register;         // updating read buffer
  		status_tmt <= 1;
  		status_trdy <= 1;
  		status_rrdy <= 1;
  	end else if (read_rx) begin
  		status_rrdy <= 0;
  	end else begin
  		status_tmt <= 0;
  		status_tryd <= 0;
  		status_rrdy <= 0;
  	end
  end
  
  // Counting SPI woread length
  always @ (posedge sclk or posedge slave_chipselector or negedge reset_n) begin
  	if (!reset_n) begin
  		count <= 0;
  	end else begin
      if (slave_chipselect) begin
          count <= 0;
      end else begin   
          count <= count + 1;
      end
    end
  end
  //generate interrupt signal
  always @ (posedge clk or negedge reset_n) begin
  	if (!reset_n) begin
  		interrupt <=0;
  	end else begin
      if((control & status & 16'hd8) && (control & 16'h100)) 
      	 interrupt <= 1;
      else interrupt <= 0;
      end
    end
  end
  
  // Slave Select output
  assign status_e = status_toe | status_roe;
  assign ss = slave_chipselect ? -1 : ~ss_reg; 
  assign status = {7'h0,status_e,status_rrdy,status_trdy,status_tmt,status_toe,status_roe,2'h0}; 
  endmodule
  
  //------------------------ END ----------------------