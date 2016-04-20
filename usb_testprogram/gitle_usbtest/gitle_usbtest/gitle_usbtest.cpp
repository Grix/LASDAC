// gitle_usbtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "libusb.h"

static struct libusb_device_handle *devh = NULL;

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
	


	return 1;
}

