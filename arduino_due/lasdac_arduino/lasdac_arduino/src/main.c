/*
Lasdac main prosjekt (for Arduino Due)

*/

#include "asf.h"
#include <math.h>
//#include <setup.c>

//macros
#define MAXSPEED 50000
#define MINSPEED 1000

//states
typedef enum {STATE_IDLE, STATE_OUTPUT, STATE_TEST} state_type;
state_type state = STATE_IDLE;

//functions
void spi_init(void);
void dac_init(void);
void speed_set(uint32_t speed);
void point_output(uint8_t *pointAddress);
void blank_and_center(void);

//global variables
uint8_t *outputAddress = NULL; //current memory location for outputting point
uint32_t outputSize = 0; //size of frame output buffer
uint32_t outputSpeed = 30000; //points per second
uint8_t testPoint[7] = {0xFF, 0xF0, 0x00, 0b10101010, 0b10101010, 0b10101010, 0b10101010};
uint16_t dac_val = 0;

//systick timer ISR
void SysTick_Handler(void)
{
	switch (state)
	{
		case STATE_IDLE: //do nothing
			break;
		case STATE_OUTPUT: //output current point
			//TODO: Check pointer/size etc if ok
			point_output(outputAddress);
			outputAddress += 7;
			break;
		case STATE_TEST:
			point_output(&testPoint[0]);
			break;
		default: //unexpected
			state = STATE_IDLE;
			break;
	}
}

int main (void)
{
	sysclk_init();
	board_init();
	dac_init();
	spi_init();
	
	state = STATE_IDLE;
	speed_set(outputSpeed);
	blank_and_center();
	
	state = STATE_TEST;
}

void point_output(uint8_t *pointAddress)
{
	//sends point data to the DACs. Argument is a pointer to an 8bit array with the following data in order:
	//8 MSB of x, 4 LSB of x + 4 MSB of y, 8 LSB of y, r, g, b, (user?)
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, (pointAddress[0] << 4) + (pointAddress[1] >> 4) ); //X
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, ((pointAddress[1] & 0xF) << 8) + pointAddress[2]); //Y
	}
	spi_write(SPI0, (pointAddress[3] << 4) + (0b0001 << 12), 0, 0); //R
	spi_write(SPI0, (pointAddress[4] << 4) + (0b0101 << 12), 0, 0); //G
	spi_write(SPI0, (pointAddress[5] << 4) + (0b1001 << 12), 0, 0); //B
	spi_write(SPI0, (pointAddress[6] << 4) + (0b1101 << 12), 0, 0); //user ?
}

void blank_and_center(void)
{
	//outputs a blanked and centered point
	uint8_t neutralPoint[7] = {0x80, 0x08, 0x00, 0, 0, 0, 0};
	point_output(&neutralPoint[0]);
}

void speed_set(uint32_t speed)
{
	//set the output speed in points per second
	if (speed > MAXSPEED)
		speed = MAXSPEED;
	else if (speed < MINSPEED)
		speed = MINSPEED;
	outputSpeed = speed;
	SysTick_Config( ceil(sysclk_get_cpu_hz() / speed) );
}

void spi_init(void)
{
	//setup SPI for DAC084S085
	gpio_configure_pin(SPI0_MISO_GPIO, SPI0_MISO_FLAGS);
	gpio_configure_pin(SPI0_MOSI_GPIO, SPI0_MOSI_FLAGS);
	gpio_configure_pin(SPI0_SPCK_GPIO, SPI0_SPCK_FLAGS);
	gpio_configure_pin(SPI0_NPCS0_GPIO, SPI0_NPCS0_FLAGS);
	spi_enable_clock(SPI0);
	spi_disable(SPI0);
	spi_reset(SPI0);
	spi_set_master_mode(SPI0);
	spi_set_fixed_peripheral_select(SPI0);
	spi_disable_mode_fault_detect(SPI0);
	spi_configure_cs_behavior(SPI0, 0, SPI_CS_RISE_FORCED);
	spi_set_delay_between_chip_select(SPI0, 6);
	spi_set_peripheral_chip_select_value(SPI0, spi_get_pcs(0));
	spi_set_clock_polarity(SPI0, 0, 0);
	spi_set_clock_phase(SPI0, 0, 0);
	spi_set_bits_per_transfer(SPI0, 0, SPI_CSR_BITS_16_BIT);
	spi_set_baudrate_div(SPI0, 0, ceil(sysclk_get_cpu_hz() / 30000000)); //default for dac: 30000000
	spi_set_transfer_delay(SPI0, 0, 0, 0);
	spi_enable(SPI0);
}

void dac_init(void)
{
	//setup sam internal DAC controller
	sysclk_enable_peripheral_clock(ID_DACC);
	dacc_reset(DACC);
	dacc_enable_channel(DACC, 0);
	dacc_enable_channel(DACC, 1);
	dacc_set_transfer_mode(DACC, 0);
}