
LIBRARY ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
--use ieee.std_logic_unsigned.all;
--use ieee.numeric_std.all;
ENTITY oc_i2c_master IS
  PORT (
    scl_pad_io : INOUT STD_LOGIC;
    sda_pad_io : INOUT STD_LOGIC;
    wb_ack_o : OUT STD_LOGIC;
    wb_adr_i : IN STD_LOGIC_VECTOR (2 DOWNTO 0);
    wb_clk_i : IN STD_LOGIC;
    wb_cyc_i : IN STD_LOGIC;
    wb_dat_i : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    wb_dat_o : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    wb_rst_i : IN STD_LOGIC;
    wb_stb_i : IN STD_LOGIC;
    wb_we_i  : IN STD_LOGIC;
    wb_inta_o : OUT STD_LOGIC
  );
END oc_i2c_master;

ARCHITECTURE behavior OF oc_i2c_master IS
    SIGNAL scl_pad_i : STD_LOGIC;
    SIGNAL scl_pad_o : STD_LOGIC;
    SIGNAL scl_padoen_o : STD_LOGIC;
    SIGNAL sda_pad_i : STD_LOGIC;
    SIGNAL sda_pad_o : STD_LOGIC;
    SIGNAL sda_padoen_o : STD_LOGIC;
    SIGNAL arst_i : STD_LOGIC;
	SIGNAL temp_wb_adr_i : unsigned(2 downto 0);


COMPONENT i2c_master_top
	PORT (
		-- wishbone signals
		wb_clk_i  : in  std_logic;		         	-- master clock input
		wb_rst_i  : in  std_logic;	         		-- synchronous active high reset
		arst_i    : in  std_logic;				-- asynchronous reset
		wb_adr_i  : in  unsigned(2 downto 0);	     	-- lower address bits
		wb_dat_i  : in  std_logic_vector(7 downto 0);	-- Databus input
		wb_dat_o  : out std_logic_vector(7 downto 0);	-- Databus output
		wb_we_i   : in  std_logic;	           		-- Write enable input
		wb_stb_i  : in  std_logic;                	-- Strobe signals / core select signal
		wb_cyc_i  : in  std_logic;	            	-- Valid bus cycle input
		wb_ack_o  : out std_logic;                 	-- Bus cycle acknowledge output
		wb_inta_o : out std_logic;                 	-- interrupt request output signal

		-- i2c lines
		scl_pad_i     : in  std_logic;                -- i2c clock line input
		scl_pad_o     : out std_logic;                -- i2c clock line output
		scl_padoen_o  : out std_logic;                -- i2c clock line output enable, active low
		sda_pad_i     : in  std_logic;                -- i2c data line input
		sda_pad_o     : out std_logic;                -- i2c data line output
		sda_padoen_o  : out std_logic                 -- i2c data line output enable, active low
	);
END COMPONENT;


BEGIN

temp_wb_adr_i <= unsigned(wb_adr_i);

i2c_top_inst : i2c_master_top
  port map(
		wb_clk_i  => wb_clk_i,  
		wb_rst_i  => wb_rst_i,  
		arst_i    => arst_i,    
		wb_adr_i  => temp_wb_adr_i,  
		wb_dat_i  => wb_dat_i(7 downto 0),  
		wb_dat_o  => wb_dat_o(7 downto 0),  
		wb_we_i   => wb_we_i,   
		wb_stb_i  => wb_stb_i,  
		wb_cyc_i  => wb_cyc_i,  
		wb_ack_o  => wb_ack_o,  
		wb_inta_o => wb_inta_o, 

		-- i2c lines
		scl_pad_i     => scl_pad_i,   
		scl_pad_o     => scl_pad_o,   
		scl_padoen_o  => scl_padoen_o,
		sda_pad_i     => sda_pad_i,   
		sda_pad_o     => sda_pad_o,   
		sda_padoen_o  => sda_padoen_o
  );

  arst_i <= '1';
  scl_pad_io  <= 'Z' WHEN ((scl_padoen_o) /= '0') ELSE  scl_pad_o;
  sda_pad_io  <= 'Z' WHEN ((sda_padoen_o) /= '0') ELSE  sda_pad_o;
  scl_pad_i <= scl_pad_io;
  sda_pad_i <= sda_pad_io;

END behavior;


