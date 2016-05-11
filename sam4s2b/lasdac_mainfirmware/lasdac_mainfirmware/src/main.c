/*
Lasdac main prosjekt (for SAM4S2B board)

Required Atmel Software Framework modules:
	DACC - Digital-to-Analog Converter
	Generic Board Support (ATSAM4S2B)
	GPIO
	IOPORT
	PIO
	SPI - Serial Peripheral Interface
	USB Device Vendor Class
*/

#include "main.h"
#include <string.h>

void SysTick_Handler(void) //systick timer ISR, called for each point
{
	if (playing)
	{
		statusled_set(HIGH);
		if (framePos >= frameSize)
		{
			//frame finished
			if (newFrameReady)
			{
				//load new frame, switch buffers
				uint8_t* previousFrameAddress = frameAddress;
				frameAddress = newFrameAddress;
				newFrameAddress = previousFrameAddress;
				newFrameReady = false;
				framePos = 0;
				frameSize = newFrameSize;
				notRepeat = newNotRepeat;
				point_output();
				framePos += 8;
				speed_set(outputSpeed);
			}
			else
			{
				if (!notRepeat)
				{
					//loop frame
					framePos = 0;
					point_output();
					framePos += 8;
				}
				else
				{
					framePos = 0;
					playing = false;
					blank_and_center();
					statusled_set(LOW);
				}
				
			}
		}
		else
		{
			//output current point
			point_output();
			framePos += 8;
		}
	}
	else
	statusled_set(LOW);
}

void usb_bulk_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep)
{
	UNUSED(ep);
	
	//multi-byte values are little endian
	//0-n:	frame data, point is 16bit X, 16bit Y, 8bit R, 8bit G, 8bit B, 8bit I
	//n:	output rate 16bit
	//n+2:	frame size in points 16bit
	//n+4:	flags
	
	if ( (!newFrameReady) && (status == UDD_EP_TRANSFER_OK) && (length <= MAXFRAMESIZE * 8 + 5) ) //if received ok and buffer is not full
	{
		uint16_t numOfPointBytes = length - 5; //from length of received data
		uint16_t numOfPointBytes2 = ((usbBulkBufferAddress[numOfPointBytes + 3] << 8) + usbBulkBufferAddress[numOfPointBytes + 2]) * 8; //from control bytes
		
		if (numOfPointBytes == numOfPointBytes2) //sanity check, skip frame if conflicting frame size information
		{
			uint8_t flags = usbBulkBufferAddress[numOfPointBytes + 4];
			newNotRepeat = (flags & (1 << 1));
			outputSpeed = (usbBulkBufferAddress[numOfPointBytes + 1] << 8) + usbBulkBufferAddress[numOfPointBytes + 0];
			
			cpu_irq_enter_critical();
				if ( (!playing) || (flags & (1 << 0)) ) //if frame is to start playing immediately
				{
					uint8_t* previousFrameAddress = frameAddress;
					frameAddress = usbBulkBufferAddress;
					usbBulkBufferAddress = previousFrameAddress;
					framePos = 0;
					frameSize = numOfPointBytes;
					newFrameReady = false;
					playing = true;
					notRepeat = newNotRepeat;
					speed_set(outputSpeed);
				} 
				else
				{
					uint8_t* previousNewFrameAddress = newFrameAddress;
					newFrameAddress = usbBulkBufferAddress;
					usbBulkBufferAddress = previousNewFrameAddress;	
					newFrameSize = numOfPointBytes;
					newFrameReady = true;
				}
			cpu_irq_leave_critical();
		}
	}
	
	udi_vendor_bulk_out_run((uint8_t*)usbBulkBufferAddress, MAXFRAMESIZE * 8 + 5, usb_bulk_out_callback);
}

void usb_interrupt_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep)
{
	//	Byte 0: Command
	//	Byte 1-2: Data (little endian)
	
	UNUSED(ep);
	if ( (status == UDD_EP_TRANSFER_OK) && (length == 3) )
	{
			
		if (usbInterruptBufferAddress[0] == 0x01)			//STOP
		{
			playing = false;
			framePos = 0;
			statusled_set(LOW);
			blank_and_center();
		}
		else if (usbInterruptBufferAddress[0] == 0x02)	//SHUTTER
		{
			shutter_set(usbInterruptBufferAddress[1]);
		}
		else if (usbInterruptBufferAddress[0] == 0x03)	//STATUS_REQUEST
		{
			//TODO
		}
	}
	
	udi_vendor_interrupt_out_run((uint8_t*)usbInterruptBufferAddress, 3, usb_interrupt_out_callback);
}

int main (void) //entry function
{
	board_init();
	
	shutter_set(HIGH);
	statusled_set(LOW);
	blank_and_center();
}

void point_output(void) //sends point data to the DACs, data is point number "framePos" in buffer "frameAddress".
{
	uint8_t* currentPoint = frameAddress + framePos;
	
	spi_write(SPI, (currentPoint[5] << 4) + (0b0001 << 12), 0, 0); //G
	spi_write(SPI, (currentPoint[6] << 4) + (0b0101 << 12), 0, 0); //B
	spi_write(SPI, (currentPoint[7] << 4) + (0b1001 << 12), 0, 0); //I
	spi_write(SPI, (currentPoint[4] << 4) + (0b1101 << 12), 0, 0); //R
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, (currentPoint[1] << 8) + currentPoint[0] ); //X
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, (currentPoint[3] << 8) + currentPoint[2] ); //Y
	}
}

void blank_and_center(void) //outputs a blanked and centered point
{
	uint8_t blankedPoint[8] = {0x00, 0x80, 0x00, 0x80, 0,0,0,0};
	uint8_t* currentPoint = &blankedPoint[0];
	
	spi_write(SPI, (currentPoint[5] << 4) + (0b0001 << 12), 0, 0); //G
	spi_write(SPI, (currentPoint[6] << 4) + (0b0101 << 12), 0, 0); //B
	spi_write(SPI, (currentPoint[7] << 4) + (0b1001 << 12), 0, 0); //I
	spi_write(SPI, (currentPoint[4] << 4) + (0b1101 << 12), 0, 0); //R
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, (currentPoint[0] << 8) + currentPoint[1] ); //X
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, (currentPoint[2] << 8) + currentPoint[3] ); //Y
	}
}

void speed_set(uint32_t speed) //set the output speed in points per second
{
	if (speed > MAXSPEED)
	speed = MAXSPEED;
	else if (speed < MINSPEED)
	speed = MINSPEED;
	outputSpeed = speed;
	SysTick_Config( (sysclk_get_cpu_hz() / speed) + 1);
}

int callback_vendor_enable(void)
{
	udi_vendor_bulk_out_run((uint8_t*)usbBulkBufferAddress, MAXFRAMESIZE * 8 + 5, usb_bulk_out_callback);
	udi_vendor_interrupt_out_run((uint8_t*)usbInterruptBufferAddress, 3, usb_interrupt_out_callback);
	return 1;
}

void callback_vendor_disable(void)
{
	playing = false;
	framePos = 0;
	blank_and_center();
	statusled_set(LOW);
}

void shutter_set(bool level)
{
	ioport_set_pin_level(PIN_SHUTTER, level);
}

void statusled_set(bool level)
{
	ioport_set_pin_level(PIN_STATUSLED, level);
}