#include <stdio.h>
#include <iostream>
#include "libusb.h"

static struct libusb_device_handle *devh = NULL;
static unsigned long num_bytes = 0, num_xfer = 0;
#define EP_ISO_IN	0x06

static void LIBUSB_CALL cb_xfr(struct libusb_transfer *xfr)
{
	unsigned int i;

	if (xfr->status != LIBUSB_TRANSFER_COMPLETED) {
		fprintf(stderr, "transfer status %d\n", xfr->status);
		libusb_free_transfer(xfr);
		exit(3);
	}

	if (xfr->type == LIBUSB_TRANSFER_TYPE_ISOCHRONOUS) {
		for (i = 0; i < xfr->num_iso_packets; i++) {
			struct libusb_iso_packet_descriptor *pack = &xfr->iso_packet_desc[i];

			if (pack->status != LIBUSB_TRANSFER_COMPLETED) {
				fprintf(stderr, "Error: pack %u status %d\n", i, pack->status);
				exit(5);
			}

			printf("pack%u length:%u, actual_length:%u\n", i, pack->length, pack->actual_length);
		}
	}

	printf("length:%u, actual_length:%u\n", xfr->length, xfr->actual_length);
	for (i = 0; i < xfr->actual_length; i++) {
		printf("%02x", xfr->buffer[i]);
		if (i % 16)
			printf("\n");
		else if (i % 8)
			printf("  ");
		else
			printf(" ");
	}
	num_bytes += xfr->actual_length;
	num_xfer++;

	if (libusb_submit_transfer(xfr) < 0) {
		fprintf(stderr, "error re-submitting URB\n");
		exit(1);
	}
}


static void print_devs(libusb_device **devs)
{
	libusb_device *dev;
	int i = 0, j = 0;
	uint8_t path[8];

	while ((dev = devs[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		struct libusb_config_descriptor *config;

		int r = libusb_get_device_descriptor(dev, &desc);
		if (r < 0) {
			fprintf(stderr, "failed to get device descriptor");
			return;
		}

		printf("%04x:%04x (bus %d, device %d) speed %d ",
			desc.idVendor, desc.idProduct,
			libusb_get_bus_number(dev), libusb_get_device_address(dev),libusb_get_device_speed(dev));

		r = libusb_get_port_numbers(dev, path, sizeof(path));
		libusb_get_device_address(dev);

		r = libusb_get_config_descriptor(dev, 0, &config);

		if (r != 0) {
			fprintf(stderr, "failed to get config descriptor");
				//return;
		}
		else {
			printf("Max Power:%u mA\n, interfaces:%d ", config->MaxPower * 2, config->bNumInterfaces);
			
			const libusb_interface *inter;
			const libusb_interface_descriptor *interdesc;
			const libusb_endpoint_descriptor *epdesc;
			if (r != 0) {}
			else
				for (int j = 0; j < config->bNumInterfaces; j++) {
					inter = &config->interface[j];
					printf("altsettings: %d \n", inter->num_altsetting);

					for (int k = 0; k < (int)inter->num_altsetting; k++) {
						interdesc = &inter->altsetting[k];
						printf("interfacenr:%d ", interdesc->bInterfaceNumber);
						printf("nr of endpoints:%d \n ", interdesc->bNumEndpoints);
						for (int l = 0; l<(int)interdesc->bNumEndpoints; l++) {
							epdesc = &interdesc->endpoint[l];
							printf("Descriptor type:%04x ", epdesc->bDescriptorType);
							printf("EP adress:%04x \n", epdesc->bEndpointAddress);
							r = libusb_get_max_iso_packet_size(dev, epdesc->bEndpointAddress);
							printf("max is packet %d \n", r);
						}
					}
				}
			libusb_free_config_descriptor(config);
		}
		/*if (r > 0) {
			printf(" path: %d", path[0]);
			for (j = 1; j < r; j++)
				printf(".%d", path[j]);
		}*/
		printf("\n");
	}
}



int main(void)
{
	int rc;

		libusb_device **devs;
		int r;
		ssize_t cnt;

		r = libusb_init(NULL); //start a libusb session.
		if (r < 0) { printf("init error"); return r; }
		libusb_set_debug(NULL, 3); //Choose debug level

		cnt = libusb_get_device_list(NULL, &devs); //get a list of devices connected to host
		if (cnt < 0)
			return (int)cnt;

		print_devs(devs); //uses device list to print information about devices connected to host

		devh = libusb_open_device_with_vid_pid(NULL, 0x03eb, 0x2423); // opens atmel mcu on the arduino due board. 
		if (!devh) {
			fprintf(stderr, "Error finding USB device\n");
		}
		printf("device open, press any key\n");
		getchar();
		libusb_free_device_list(devs, 1); // removes all devices except the opened.




		r = libusb_claim_interface(devh, 0); // claims 0
		if (r < 0) {
			fprintf(stderr, "Error claiming interface: %s\n", libusb_error_name(r));
			getchar();
			return 1;
		}
		printf("inteface claimed\n");
		int actual;
		unsigned char *data = new unsigned char[1024];
		data[0] = 'a'; data[1] = 'b'; data[2] = 'c'; data[3] = 'd';
		data[777] = '8';

		unsigned char *data_read = new unsigned char[1024]; //pointer to store data from bulk transfer on inn endpoint.
		r = libusb_set_interface_alt_setting(devh, 0, 1); //bytter alternativ interface setting til ett med endpoint
		if (r < 0) {
			printf("failed to set alternate interface\n");
			return 1;
		}
		else printf("alternate interface set to 1\n");
		r = libusb_bulk_transfer(devh, (0x04), data, 1024, &actual, 0); //bulk transfer on out
		if (r == 0 && actual == 1024) printf("write_suksess!\n");
		else printf("write_error\n");

		r = libusb_bulk_transfer(devh, (0x83), data_read, 1024, &actual, 5); //bulk transfer on inn, should 
		if (r < 0)printf("read_error\n");
		printf("Data read: %c %c %c %c\n", data_read[0], data_read[1], data_read[2], data_read[3]);
		printf("read 777: %c\n", data_read[777]);
		
		//isochronous transfer attempt

		//static uint8_t buf[256];
		//static struct libusb_transfer *xfr;
		//int num_iso_pack = 1;
		//xfr = libusb_alloc_transfer(0);
		//libusb_fill_bulk_transfer(xfr, devh, 0x04, data, sizeof(data), cb_xfr, NULL, 0);
		//r = libusb_submit_transfer(xfr);
		//if (r < 0)printf("klarte ikke sende iso\n");
		//if (r == LIBUSB_ERROR_NOT_SUPPORTED)printf("Error not supported");
		//if (r == LIBUSB_ERROR_BUSY)printf("busy");
		//if (r == LIBUSB_ERROR_NO_DEVICE)printf("no device");

		//r = libusb_bulk_transfer(devh, (0x83), data_read, 4, &actual, 0); //bulk transfer on inn, should 
		//if (r < 0)printf("read_error\n");
		//printf("Data read: %c %c %c %c\n", data_read[0], data_read[1], data_read[2], data_read[3]);


		/*
		xfr = libusb_alloc_transfer(num_iso_pack);
		libusb_fill_iso_transfer(xfr, devh, 0x06, data, sizeof(data), num_iso_pack, cb_xfr,NULL, 0);
		r = libusb_submit_transfer(xfr);
		if (r < 0)printf("klarte ikke sende iso\n");
		if (r == LIBUSB_ERROR_NOT_SUPPORTED)printf("Error not supported");
		if (r == LIBUSB_ERROR_BUSY)printf("busy");
		if (r == LIBUSB_ERROR_NO_DEVICE)printf("no device");
		getchar();
        libusb_free_transfer(xfr);

		unsigned char *data_read2 = new unsigned char[64];
		for (int b = 0; b < 64; b++) {
			data_read2[b] = 't';
		}


		printf("\n");
		xfr = libusb_alloc_transfer(num_iso_pack);
		libusb_fill_iso_transfer(xfr, devh, 0x85 , data_read2, sizeof(data), num_iso_pack, cb_xfr, NULL,100);
		r= libusb_submit_transfer(xfr);
		if (r < 0)printf("klarte ikke lese iso\n");
		if (r == LIBUSB_ERROR_NOT_SUPPORTED)printf("Error not supported");
		if (r == LIBUSB_ERROR_BUSY)printf("busy");
		if (r == LIBUSB_ERROR_NO_DEVICE)printf("no device");

		libusb_free_transfer(xfr);*/

		printf("\n\n");
		r = libusb_release_interface(devh, 0);
		if (r < 0) {
			printf("interface release failed");
			return 1;
		}
		printf("interface released\n");
		
	libusb_close(devh);
	libusb_exit(NULL);
	printf("finished, press any key to exit...");
	getchar();
	return 0;
}