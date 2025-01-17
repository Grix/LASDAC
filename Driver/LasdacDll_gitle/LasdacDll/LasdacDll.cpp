// LasdacDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "libusb.h"
#include "LasdacDll.h"

using namespace std;
static struct libusb_device_handle *devh = NULL;
#define ep_bulk_out	0x02

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
int send_frame(uint8_t flags, uint16_t speed, uint16_t nr_points, uint8_t * punkter) {

	static int count = 0;
	int actual_transfer = 0;
	int r_value = 0;
	uint8_t speedmsb = ((speed >> 8) & 0xff);
	uint8_t speedlsb = (speed & 0x00ff);
	uint8_t nr_pointmsb = ((nr_points >> 8) & 0xff);
	uint8_t nr_pointlsb = (nr_points & 0x00ff);

	punkter[(nr_points * 8)] = speedlsb;
	punkter[((nr_points * 8)) + 1] = speedmsb;
	punkter[((nr_points * 8)) + 2] = nr_pointlsb;
	punkter[((nr_points * 8)) + 3] = nr_pointmsb;
	punkter[((nr_points * 8)) + 4] = flags;



	r_value = libusb_bulk_transfer(devh, ep_bulk_out, punkter, ((nr_points * 8) + 5), &actual_transfer, 0);
	if (r_value == 0 && actual_transfer == ((nr_points * 8) + 5))
	{
		return 0;
	}



	else return -1;
}

int open_device() {
	int r = 0;
	r = libusb_init(NULL);
	if (r < 0) {
		return -1;
	}
	devh = libusb_open_device_with_vid_pid(NULL, 0x03eb, 0x2423);
	if (!devh) {
		return -2;
	}
	r = libusb_claim_interface(devh, 0);
	if (r < 0) {
		return -3;
	}
	r = libusb_set_interface_alt_setting(devh, 0, 1);
	if (r < 0) {
		return -4;
	}
	return 0;
}
int close_device() {
	libusb_close(devh);
	libusb_exit(NULL);
	return 0;
}