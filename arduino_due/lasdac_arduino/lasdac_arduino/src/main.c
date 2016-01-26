/*
Lasdac main prosjekt (for Arduino Due)

*/

#include "asf.h"
//#include <setup.c>

//states
#define STATE_IDLE 0
uint8_t state = STATE_IDLE;

//functions
void setup_spi(void);
void setup_dac(void);
void output_point(uint8_t *pointaddress);

//systick timer ISR
void SysTick_Handler(void)
{
	
}

int main (void)
{
	sysclk_init();
	board_init();
	setup_dac();
	setup_spi();
}

void output_point(uint8_t *pointaddress)
{
	//sends point data to the DACs. Argument is a pointer to an 8bit array with the following data in order:
	//8 MSB of x, 4 LSB of x + 4 MSB of y, 8 LSB of y, r, g, b, a
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, (pointaddress[0] << 4) + (pointaddress[1] >> 4) );
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, ((pointaddress[1] & 0xF) << 8) + pointaddress[2]);
	}
	//TODO: SPI for RGBA (GPIO for A?)
}

void setup_spi(void)
{
	//setup SPI for DAC084S085
	//TODO
	
}

void setup_dac(void)
{
	sysclk_enable_peripheral_clock(ID_DACC);
	dacc_reset(DACC);
	dacc_enable_channel(DACC, 0);
	dacc_enable_channel(DACC, 1);
	dacc_set_transfer_mode(DACC, 0);
}