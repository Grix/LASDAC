// gitle_usbtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "libusb.h"

static struct libusb_device_handle *devh = NULL;

struct Point
{
	UINT16 X;
	UINT16 Y;
	UINT8  R;
	UINT8  G;
	UINT8  B;
	UINT8  I;
};

Point frameOn[2] = {
	{ 0xffff, 0xffff, 0xff, 0xff, 0xff, 0xff },
	{ 20000, 0, 0, 0, 0, 0 }
};
Point frameOff[2] = {
	{ 0, 0, 0, 0, 0, 0 },
	{ 20000, 0, 0, 0, 0, 0 }
};

int _tmain(int argc, _TCHAR* argv[])
{
	int r; //various return codes

	r = libusb_init(NULL); //start a libusb session.
	if (r < 0) 
	{ 
		printf("init error"); 
		getchar();
		return r; 
	}
	libusb_set_debug(NULL, 3); //Choose debug level

	devh = libusb_open_device_with_vid_pid(NULL, 0x03eb, 0x2423); // opens atmel mcu on the arduino due board. 
	if (!devh) 
	{
		printf("Error finding USB device\n");
		getchar();
		return 0;
	}

	printf("device open, press any key\n");
	getchar();

	r = libusb_claim_interface(devh, 0); // claims 0
	if (r < 0) 
	{
		printf("Error claiming interface: %s\n", libusb_error_name(r));
		getchar();
		return r;
	}

	r = libusb_set_interface_alt_setting(devh, 0, 1); //bytter alternativ interface setting til ett med endpoint
	if (r < 0) 
	{
		printf("failed to set alternate interface\n");
		printf("%s\n", libusb_error_name(r));
		return r;
	}

	while (1)
	{
		uint8_t buffer_in[16];
		/*uint8_t buffer[16];
		buffer[15880] = 100;*/
		int actual_length = 0;
		char q;

		r = libusb_bulk_transfer(devh, 0x06, (uint8_t*)&frameOn[0], 16, &actual_length, 32); //out
		if ((r != 0) && (actual_length != 16))
		{
			printf("error sending\n");
			printf("%s\n", libusb_error_name(r));
			getchar();
			return r;
		}

		//r = libusb_bulk_transfer(devh, 0x85, &buffer_in[0], 16, &actual_length, 32); //in
		//if ((r != 0) && (actual_length != 16))
		//{
		//	printf("error receiving\n");
		//	printf("%s\n", libusb_error_name(r));
		//	getchar();
		//	return r;
		//}

		//printf("Received: %d \n\n", buffer_in[15880]);
		printf("On");
		q = getchar();
		if (q == 'q')
			break;

		r = libusb_bulk_transfer(devh, 0x06, (uint8_t*)&frameOff[0], 16, &actual_length, 32); //out
		if ((r != 0) && (actual_length != 16))
		{
			printf("error sending\n");
			printf("%s\n", libusb_error_name(r));
			getchar();
			return r;
		}

		printf("Off");
		q = getchar();
		if (q == 'q')
			break;

	}


	return 1;
}

