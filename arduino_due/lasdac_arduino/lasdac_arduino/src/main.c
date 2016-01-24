/*
Lasdac main prosjekt (for Arduino Due)

*/

#include "asf.h"
//#include <setup.c>

void setup_spi(void);
void setup_dac(void);

//states
#define STATE_IDLE 0

uint8_t state = STATE_IDLE;

//systick timer ISR: freq controlled by main.timerFreq
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


void setup_spi(void)
{
	//setup SPI for DAC084S085
	//IKKE FERDIG
	
}

void setup_dac(void)
{
	sysclk_enable_peripheral_clock(ID_DACC);
	dacc_reset(DACC);
	dacc_enable_channel(DACC, 0);
	dacc_enable_channel(DACC, 1);
	dacc_set_transfer_mode(DACC, 0);
}
