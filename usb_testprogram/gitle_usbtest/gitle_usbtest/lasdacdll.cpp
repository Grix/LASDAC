// LasdacDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "libusb.h"
#include "stdio.h"

using namespace std;
static struct libusb_device_handle *devh = NULL;
#define ep_bulk_out	0x06
#define DLLEXPORT extern "C" __declspec(dllexport)


typedef struct
{
	UINT16 X;
	UINT16 Y;
	UINT8  R;
	UINT8  G;
	UINT8  B;
	UINT8  I;
}Point;
/*
namespace LasdacFuncs
{

void MyLasdacFuncs::open_device() {
libusb_init(NULL);
devh = libusb_open_device_with_vid_pid(NULL, 0x03eb, 0x2423);
}
void MyLasdacFuncs::close_device() {
libusb_close(devh);
libusb_exit(NULL);
}


void MyLasdacFuncs::send_frame(uint8_t flags, uint16_t speed, uint16_t nr_points, Point * punkter){

static int count = 0;
int actual_transfer = 0;
int r_value = 0;
uint8_t speed_8msb = 0;
uint8_t speed_8lsb = 0;
Point* punkt_buffer = new Point[nr_points + 1];

if (count < nr_points) {
punkt_buffer[count] = *punkter;
count++;
}
else
punkt_buffer[count + 1] = { speed,0,0,0,flags,0 };
r_value = libusb_bulk_transfer(devh, ep_bulk_out, (uint8_t*)(punkt_buffer), sizeof(punkt_buffer), &actual_transfer, 0);
if (r_value == 0 && actual_transfer == sizeof((uint8_t*)(punkt_buffer)))
{
delete[] punkt_buffer;
count = 0;
}
return;
}



void MyLasdacFuncs::print_test() {
printf("test");
getchar();
return;
}

}*/


DLLEXPORT int send_frame(uint8_t flags, uint16_t speed, uint16_t nr_points, Point* punkter) {

	static int count = 0;
	int actual_transfer = 0;
	int r_value = 0;

	punkter[nr_points] = { speed, nr_points, flags, 0, 0, 0 };

	r_value = libusb_bulk_transfer(devh, ep_bulk_out, (uint8_t*)(punkter), sizeof(punkter), &actual_transfer, 32);
	if (r_value == 0 && actual_transfer == sizeof((uint8_t*)(punkter)))
	{
		return 0;
	}
	else return -1;
}


DLLEXPORT int open_device() {
	int r = 0;
	r = libusb_init(NULL);
	if (r < 0) { return -1; }
	devh = libusb_open_device_with_vid_pid(NULL, 0x03eb, 0x2423);
	if (!devh) {
		return -1;
	}
	r = libusb_claim_interface(devh, 0);
	if (r < 0) {

		return -1;
	}
	r = libusb_set_interface_alt_setting(devh, 0, 1);
	if (r < 0) {

		return -1;
	}
	return 0;
}


DLLEXPORT int close_device() {
	libusb_close(devh);
	libusb_exit(NULL);
	return 0;
}


DLLEXPORT void print_test2() {
	printf("test");
	getchar();
	return;
}

