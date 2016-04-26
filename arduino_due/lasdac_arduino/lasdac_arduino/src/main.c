/*
Lasdac main prosjekt (for Arduino Due)

Required Atmel Software Framework modules:
	DACC - Digital-to-Analog Converter
	Generic Board Support (ATSAM3X8E)
	GPIO
	IOPORT
	PIO
	SPI - Serial Perihperal Interface
	USB Device Vendor Class

*/

#include "asf.h"
#include <string.h>
#include <math.h>

//macros
#define MAXSPEED 50000 //in pps
#define MINSPEED 1000 //in pps
#define MAXFRAMESIZE 2501 //in points
#define BUFFERSIZE 20008
#define PIN_SHUTTER IOPORT_CREATE_PIN(PIOC,12)
#define PIN_STATUSLED IOPORT_CREATE_PIN(PIOB,27)
#define PIN_ERRORLED IOPORT_CREATE_PIN(PIOC,14)

//functions
void spi_init(void);
void dac_init(void);
void iopins_init(void);
void speed_set(uint32_t speed);
void shutter_set(bool level);
void statusled_set(bool level);
void errorled_set(bool level);
void point_output();
void blank_and_center(void);
void start(void);
void stop(void);
void usb_bulk_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep);


typedef struct{
	uint16_t X;
	uint16_t Y;
	uint8_t  R;
	uint8_t  G;
	uint8_t  B;
	uint8_t  I;
}Point;

typedef struct{
	uint8_t  command;
	uint16_t data;
}ControlPacket;

//global variables, reserve memory for buffers
uint16_t frameSize = 0;					//size of frame buffer in points
uint16_t framePos = 0;					//current position in frame in points
uint16_t newFrameSize = 0;				//incoming frame total size in points
bool newFrameReady = false;				//signals a new frame has been received and is ready to play when the current one ends
bool playing = false;					//signals a point should be output next systick
uint32_t outputSpeed = 20000;			//points per second

Point frame1[MAXFRAMESIZE];		//frame buffer 1
Point frame2[MAXFRAMESIZE];		//frame buffer 2
Point frame3[MAXFRAMESIZE];		//frame buffer 3
Point* frameAddress = &frame1[0];			//pointer to frame currently being played
Point* newFrameAddress = &frame2[0];		//pointer to pending frame waiting to be played
Point* usbBulkBufferAddress = &frame3[0];	//pointer to usb bulk transfer buffer
uint8_t usbInterruptBuffer[4];
ControlPacket* usbInterruptBufferAddress = &usbInterruptBuffer[0];	//pointer to usb interrupt buffer

void SysTick_Handler(void) //systick timer ISR
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
				cpu_irq_enter_critical();
					Point* previousFrameAddress = frameAddress;
					frameAddress = newFrameAddress;
					newFrameAddress = previousFrameAddress;
					newFrameReady = false;
					framePos = 0;
					frameSize = newFrameSize;
				cpu_irq_leave_critical();
				point_output();
				framePos++;
				speed_set(outputSpeed);
			}
			else
			{
				//loop frame
				framePos = 0;
				point_output();
				framePos++;
			}
		}
		else
		{
			//output current point
			point_output();
			framePos++;
		}
	}
	else
		statusled_set(LOW);
}

void usb_bulk_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep)
{
	UNUSED(ep);
	if ( (!newFrameReady) && (status == UDD_EP_TRANSFER_OK) )
	{
		uint16_t numOfPoints = (uint16_t)((length)/8 + 0.5) - 1; //rounding in case of decimal errors
		
		//reading control struct (last point transfered)
		uint8_t flags = usbBulkBufferAddress[numOfPoints].R;
		outputSpeed = usbBulkBufferAddress[numOfPoints].X;
		
		cpu_irq_enter_critical();
			if ( (!playing) || (flags & 1) )
			{
				Point* previousFrameAddress = frameAddress;
				frameAddress = usbBulkBufferAddress;
				usbBulkBufferAddress = previousFrameAddress;
				framePos = 0;
				frameSize = numOfPoints;
				newFrameReady = false;
				playing = true;
				speed_set(outputSpeed);
			} 
			else
			{
				Point* previousNewFrameAddress = newFrameAddress;
				newFrameAddress = usbBulkBufferAddress;
				usbBulkBufferAddress = previousNewFrameAddress;	
				newFrameSize = numOfPoints;
				newFrameReady = true;
			}
		cpu_irq_leave_critical();
	}
	
	
	udi_vendor_bulk_out_run((uint8_t*)usbBulkBufferAddress, BUFFERSIZE, usb_bulk_out_callback);
}

void usb_control_placeholder(void)
{
	uint8_t data[4];
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

int callback_vendor_enable(void)
{
	start();
	udi_vendor_bulk_out_run((uint8_t*)usbBulkBufferAddress, BUFFERSIZE, usb_bulk_out_callback);
	return 1;
}

void callback_vendor_disable(void)
{
	stop();
}

int main (void) //entry function
{
	sysclk_init();
	board_init();
	dac_init();
	spi_init();
	iopins_init();
	irq_initialize_vectors();
	cpu_irq_enable();
	udc_start();
	
	shutter_set(HIGH);
	statusled_set(LOW);
	errorled_set(LOW);
	blank_and_center();
	
	//testing
	/*memcpy(&frame1[0], &testFrame[0], 2331);
	frameAddress = &frame1[0];
	frameSize = 2331;
	playing = true;
	speed_set(50000);*/
}

void point_output() //sends point data to the DACs, data is point number "framePos" in buffer "frameAddress".
{	
	Point currentPoint = frameAddress[framePos];
	
	spi_write(SPI0, (currentPoint.G << 4) + (0b0001 << 12), 0, 0); //G
	spi_write(SPI0, (currentPoint.B << 4) + (0b0101 << 12), 0, 0); //B
	spi_write(SPI0, (currentPoint.I << 4) + (0b1001 << 12), 0, 0); //I
	spi_write(SPI0, (currentPoint.R << 4) + (0b1101 << 12), 0, 0); //R
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, currentPoint.X ); //X
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, currentPoint.Y ); //Y
	}
}

void blank_and_center(void) //outputs a blanked and centered point
{
	Point currentPoint = {0x800, 0x800, 0,0,0,0};
	
	spi_write(SPI0, (currentPoint.G << 4) + (0b0001 << 12), 0, 0); //G
	spi_write(SPI0, (currentPoint.B << 4) + (0b0101 << 12), 0, 0); //B
	spi_write(SPI0, (currentPoint.I << 4) + (0b1001 << 12), 0, 0); //I
	spi_write(SPI0, (currentPoint.R << 4) + (0b1101 << 12), 0, 0); //R
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, currentPoint.X ); //X
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, currentPoint.Y ); //Y
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

void shutter_set(bool level) //set the shutter signal off or on
{
	ioport_set_pin_level(PIN_SHUTTER, level);
}

void statusled_set(bool level) //set the statusled on or off
{
	ioport_set_pin_level(PIN_STATUSLED, level);
}

void errorled_set(bool level) //set the error led on or off
{
	ioport_set_pin_level(PIN_ERRORLED, level);
}

void iopins_init(void) //setup io pins config
{
	ioport_set_pin_mode(PIN_SHUTTER, IOPORT_DIR_OUTPUT);
	ioport_set_pin_mode(PIN_STATUSLED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_mode(PIN_ERRORLED, IOPORT_DIR_OUTPUT);
}

void spi_init(void) //setup SPI for DAC084S085
{
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
	spi_set_baudrate_div(SPI0, 0, (sysclk_get_cpu_hz() / 20000000) + 1 ); //default for dac: 30000000
	spi_set_transfer_delay(SPI0, 0, 0, 0);
	spi_enable(SPI0);
}

void dac_init(void) //setup sam internal DAC controller
{
	sysclk_enable_peripheral_clock(ID_DACC);
	dacc_reset(DACC);
	dacc_enable_channel(DACC, 0);
	dacc_enable_channel(DACC, 1);
	dacc_set_transfer_mode(DACC, 0);
}

void start(void) //starts and initialized the DAC, must be called before output
{	
	statusled_set(HIGH);
}

void stop(void) //shuts down the DAC, must be started again before output
{
	playing = false;
	blank_and_center();
	statusled_set(LOW);
}