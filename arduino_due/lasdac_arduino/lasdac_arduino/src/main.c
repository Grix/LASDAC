/*
Lasdac main prosjekt (for Arduino Due)

*/

#include "asf.h"
//#include <setup.c>

//states
#define STATE_IDLE 0
uint8_t state = STATE_IDLE;

//structs
typedef struct
{
	uint16_t x;
	uint16_t y;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} point;

//functions
void setup_spi(void);
void setup_dac(void);
void output_point(point);

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

void output_point(point point_arg)
{
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, (uint32_t)point_arg.x);
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, (uint32_t)point_arg.y);
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