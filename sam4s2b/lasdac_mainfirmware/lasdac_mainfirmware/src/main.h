//lasdac: main.h

#ifndef MAIN_H_
#define MAIN_H_

#include "asf.h"

//macros
#define MAXSPEED 50000 //in pps
#define MINSPEED 1000 //in pps
#define MAXFRAMESIZE 2001 //in points

//global variables, reserve memory for buffers
uint16_t frameSize = 0;					//size of frame buffer in points
uint16_t framePos = 0;					//current position in frame in points
uint16_t newFrameSize = 0;				//incoming frame total size in points
bool newFrameReady = false;				//signals a new frame has been received and is ready to play when the current one ends
bool playing = false;					//signals a point should be output next systick
uint32_t outputSpeed = 20000;			//points per second rate
bool notRepeat = true;					//signals that current frame should be only be played once even if no new frame arrives before it ends
bool newNotRepeat = true;				//notRepeat value for pending frame

uint8_t frame1[MAXFRAMESIZE*8];					//frame buffer 1
uint8_t frame2[MAXFRAMESIZE*8];					//frame buffer 2
uint8_t frame3[MAXFRAMESIZE*8];					//frame buffer 3
uint8_t* frameAddress = &frame1[0];				//pointer to frame currently being played
uint8_t* newFrameAddress = &frame2[0];			//pointer to pending frame waiting to be played
uint8_t* usbBulkBufferAddress = &frame3[0];		//pointer to usb bulk transfer buffer
uint8_t usbInterruptBuffer[3];
uint8_t* usbInterruptBufferAddress = &usbInterruptBuffer[0];	//pointer to usb interrupt buffer

//functions
void speed_set(uint32_t rate);		//sets up the systick interrupt to match the playback rate (in pps)
void shutter_set(bool level);		//sets the shutter level
void statusled_set(bool level);		//sets the status LED level
void point_output(void);			//outputs current point (controlled by framePos and frameAddress variables)
void blank_and_center(void);		//blanks and centers output

//USB transfer interrupts
void usb_bulk_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep);
void usb_interrupt_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep);

#endif /* MAIN_H_ */