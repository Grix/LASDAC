/*
Lasdac main prosjekt (for SAM4S2B board)

Required Atmel Software Framework modules:
	DACC - Digital-to-Analog Converter
	Generic Board Support (ATSAM3X8E)
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
		if (framePos > (frameSize - 7))
		{
			//frame finished
			if (newFrameReady)
			{
				//load new frame, switch buffers
				if (frameAddress == &frame1[0])
				{
					frameAddress = &frame2[0];
					newFrameAddress = &frame1[0];
				}
				else
				{
					frameAddress = &frame1[0];
					newFrameAddress = &frame2[0];
				}
				newFramePos = 0;
				newFrameReady = false;
				speed_set(outputSpeed);
				framePos = 0;
				point_output(frameAddress + framePos);
				framePos += 7;
			}
			else
			{
				//loop frame
				framePos = 0;
				point_output(frameAddress + framePos);
				framePos += 7;
			}
		}
		else
		{
			//output current point
			point_output(frameAddress + framePos);
			framePos += 7;
		}
	}
	else
		statusled_set(LOW);
}

void usb_iso_received()
{
	//	Byte 0-3: First packet control bits (0xAAAAAAAA)
	//	Byte 4-5: Scanning speed in pps (big endian)
	//	Byte 6-7: Size of frame in points (big endian)
	//	Byte 8-X: Point data
	//		Each point: 8 MSB of x, 4 LSB of x + 4 MSB of y, 8 LSB of y, r, g, b, i (7 bytes total)
	//	Byte X-4: Last packet control bits (0xBBBBBBBB)
	
	uint8_t* data = usbIsoBufferAddress;
	bool processPacket = false;
	bool lastPacket = false;
	uint8_t intraFramePos = 0;
	
	if (!newFrameReady)
	{
		//if control bits indicate first packet in frame
		if (	(data[0] == 0xAA) &&
		(data[1] == 0xAA) &&
		(data[2] == 0xAA) &&
		(data[3] == 0xAA) )
		{
			outputSpeed = ( (data[4] << 8) + data[5] );
			newFrameSize = ( ((data[6] << 8) + data[7]) * 7 + 4);
			
			if ((outputSpeed > MAXSPEED) || (outputSpeed < MINSPEED))
			{
				//error: wrong speed
			}
			else if (newFrameSize > MAXFRAMESIZE)
			{
				//error: wrong size
			}
			else
			{
				intraFramePos = 8;
				newFramePos = 0;
				processPacket = true;
			}
		}
		else if (newFramePos != 0)
		{
			processPacket = true;
		}
	}
	
	if (processPacket)
	{
		uint16_t bytesToCopy = USB_DATAPACKETSIZE - intraFramePos;
		
		//if last packet in frame expected
		if ( (newFrameSize - newFramePos) <= bytesToCopy )
		{
			//adjust copy size and position
			bytesToCopy = newFrameSize - newFramePos;
			lastPacket = true;
		}
		
		//TODO copy data, below works?
		memcpy(&newFrameAddress[newFramePos], &data[intraFramePos], bytesToCopy);
		newFramePos += bytesToCopy;
		
		//if last packet in frame expected
		if (lastPacket)
		{
			//if control bytes indicates last packet in frame
			uint8_t* frameEnd = newFrameAddress+newFrameSize;
			
			if (	( *(frameEnd-0) == 0xBB) &&
			( *(frameEnd-1) == 0xBB) &&
			( *(frameEnd-2) == 0xBB) &&
			( *(frameEnd-3) == 0xBB) )
			{
				//frame successfully received
				newFrameReady = true;
				if (!playing)
				{
					playing = true;
					speed_set(outputSpeed);
				}
				
			}
			else
			{
				//faulty frame, discard
				newFramePos = 0;
			}
		}
	}
	
	//udi_vendor_iso_out_run(usbIsoBufferAddress, USB_DATAPACKETSIZE, usb_iso_received);
	udi_vendor_bulk_out_run(usbIsoBufferAddress, USB_DATAPACKETSIZE, usb_iso_received);
}

void usb_control_received(void)
{
	uint8_t *data = usbControlBufferAddress;
	//	Byte 0: Command
	//	Byte 1-3: Data (big endian)
	
	if (data[0] == 0x01)		//STOP
	{
		playing = false;
		statusled_set(LOW);
	}
	else if (data[0] == 0x02)	//SHUTTER
	{
		
		if (data[3] == 0)
		shutter_set(LOW);
		else
		shutter_set(HIGH);
	}
	else if (data[0] == 0x03)	//STATUS_REQUEST
	{
		//TODO
	}
	else if (data[0] == 0x04)	//CLOSE
	{
		//TODO
	}
}

int main (void) //entry function
{
	board_init();
	
	shutter_set(HIGH);
	statusled_set(LOW);
	blank_and_center();
	
	//testing
	/*memcpy(&frame1[0], &testFrame[0], 2331);
	frameAddress = &frame1[0];
	frameSize = 2331;
	playing = true;
	speed_set(50000);*/
}

void point_output(uint8_t *pointAddress) //sends point data to the DACs.
{
	//Argument is a pointer to an 8bit array with the following data in order:
	//8 MSB of x, 4 LSB of x + 4 MSB of y, 8 LSB of y, r, g, b, i
	
	spi_write(SPI, (pointAddress[3] << 4) + (0b0000 << 12), 0, 0); //R
	spi_write(SPI, (pointAddress[4] << 4) + (0b0100 << 12), 0, 0); //G
	spi_write(SPI, (pointAddress[5] << 4) + (0b1000 << 12), 0, 0); //B
	spi_write(SPI, (pointAddress[6] << 4) + (0b1101 << 12), 0, 0); //I , update outputs of all color channels
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, (pointAddress[0] << 4) + (pointAddress[1] >> 4) ); //X
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, ((pointAddress[1] & 0xF) << 8) + pointAddress[2]); //Y
	}
}

void blank_and_center(void) //outputs a blanked and centered point
{
	uint8_t neutralPoint[7] = {0x80, 0x08, 0x00, 0, 0, 0, 0};
	point_output(&neutralPoint[0]);
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

void shutter_set(bool onoff) //set the shutter signal off or on
{
	ioport_set_pin_level(PIN_SHUTTER, onoff);
}

void statusled_set(bool onoff) //set the statusled on or off
{
	ioport_set_pin_level(PIN_STATUSLED, onoff);
}

void start(void) //starts and initialized the DAC, must be called before output
{	
	//udi_vendor_iso_out_run(usbIsoBufferAddress, USB_DATAPACKETSIZE, usb_iso_received);
	udi_vendor_bulk_out_run(usbIsoBufferAddress, USB_DATAPACKETSIZE, usb_iso_received);
	statusled_set(HIGH);
}

void stop(void) //shuts down the DAC, must be started again before output
{
	playing = false;
	blank_and_center();
	statusled_set(LOW);
}

int callback_vendor_enable(void)
{
	start();
	return 1;
}

void callback_vendor_disable(void)
{
	stop();
}