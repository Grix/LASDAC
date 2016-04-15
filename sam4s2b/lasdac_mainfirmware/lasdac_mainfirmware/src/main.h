/*
 * main.h
 *
 * Created: 2016-04-01 15:52:26
 *  Author: gitle
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "asf.h"

//macros
#define MAXSPEED 50000				//in pps
#define MINSPEED 1000				//in pps
#define MAXFRAMESIZE 3333			//in points
#define USB_DATAPACKETSIZE 64		//in bytes 
#define USB_CONTROLPACKETSIZE 64	//in bytes 

//global variables, reserve memory for buffers
uint32_t frameSize = 0;					//size of frame buffer in bytes
uint32_t framePos = 0;					//current position in frame in byte number
uint16_t newFrameSize = 0;				//incoming frame total size in points
uint16_t newFramePos = 0;				//incoming frame position
bool newFrameReady = false;				//signals a new frame has been received and is ready to play when the current one ends
bool playing = false;					//signals a point should be output next systick
bool syncedStart = true;				//start new frame after current ends (true) or immediately after new frame received (false)
uint32_t lastErrorCode = 0;				//holds code of last error
uint32_t outputSpeed = 20000;			//points per second
uint8_t frame1[MAXFRAMESIZE * 7];		//frame buffer 1
uint8_t frame2[MAXFRAMESIZE * 7];		//frame buffer 2
uint8_t *frameAddress = &frame1[0];		//start of current frame buffer
uint8_t *newFrameAddress = &frame2[0];	//incoming frame buffer address

uint8_t testPoint[7] = {0xFF, 0xFf, 0xff, 0xff, 0xff, 0xff, 0xff};
uint8_t testFrame[2331] = {0,0,0,0,0,0,0,0,192,12,1,1,1,1,1,144,25,2,2,2,2,2,80,37,2,2,2,2,3,16,49,3,3,3,3,3,224,62,4,4,4,4,4,160,74,5,5,5,5,5,96,86,5,5,5,5,6,48,99,6,6,6,6,6,240,111,7,7,7,7,7,176,123,8,8,8,8,8,128,136,8,8,8,8,9,64,148,9,9,9,9,10,0,160,10,10,10,10,10,208,173,11,11,11,11,11,144,185,12,12,12,12,12,80,197,12,12,12,12,13,32,210,13,13,13,13,13,224,222,14,14,14,14,14,160,234,15,15,15,15,15,112,247,15,15,15,15,16,49,3,16,16,16,16,16,241,15,17,17,17,17,17,193,28,18,18,18,18,18,129,40,18,18,18,18,19,65,52,19,19,19,19,20,17,65,20,20,20,20,20,209,77,21,21,21,21,21,145,89,22,22,22,22,22,97,102,22,22,22,22,23,33,114,23,23,23,23,23,225,126,24,24,24,24,24,177,139,25,25,25,25,25,113,151,25,25,25,25,26,49,163,26,26,26,26,27,1,176,27,27,27,27,27,193,188,28,28,28,28,28,129,200,28,28,28,28,29,81,213,29,29,29,29,30,17,225,30,30,30,30,30,209,237,31,31,31,31,31,161,250,31,31,31,31,32,98,6,32,32,32,32,33,34,18,33,33,33,33,33,242,31,34,34,34,34,34,178,43,35,35,35,35,35,114,55,35,35,35,35,36,66,68,36,36,36,36,37,2,80,37,37,37,37,37,194,92,38,38,38,38,38,146,105,38,38,38,38,39,82,117,39,39,39,39,40,18,129,40,40,40,40,40,226,142,41,41,41,41,41,162,154,41,41,41,41,42,98,166,42,42,42,42,43,50,179,43,43,43,43,43,242,191,44,44,44,44,44,178,203,45,45,45,45,45,130,216,45,45,45,45,46,66,228,46,46,46,46,47,2,240,47,47,47,47,47,210,253,48,48,48,48,48,147,9,48,48,48,48,49,83,21,49,49,49,49,50,35,34,50,50,50,50,50,227,46,51,51,51,51,51,163,58,51,51,51,51,52,115,71,52,52,52,52,53,51,83,53,53,53,53,53,243,95,54,54,54,54,54,195,108,55,55,55,55,55,131,120,55,55,55,55,56,67,132,56,56,56,56,57,19,145,57,57,57,57,57,211,157,58,58,58,58,58,147,169,58,58,58,58,59,99,182,59,59,59,59,60,35,194,60,60,60,60,60,227,206,61,61,61,61,61,179,219,61,61,61,61,62,115,231,62,62,62,62,63,51,243,63,63,63,63,64,4,0,64,64,64,64,64,196,12,65,65,65,65,65,132,24,65,65,65,65,66,84,37,66,66,66,66,67,20,49,67,67,67,67,67,212,61,68,68,68,68,68,164,74,68,68,68,68,69,100,86,69,69,69,69,70,36,98,70,70,70,70,70,244,111,71,71,71,71,71,180,123,71,71,71,71,72,116,135,72,72,72,72,73,68,148,73,73,73,73,74,4,160,74,74,74,74,74,196,172,75,75,75,75,75,148,185,75,75,75,75,76,84,197,76,76,76,76,77,20,209,77,77,77,77,77,228,222,78,78,78,78,78,164,234,78,78,78,78,79,100,246,79,79,79,79,80,53,3,80,80,80,80,80,245,15,81,81,81,81,81,181,27,81,81,81,81,82,133,40,82,82,82,82,83,69,52,83,83,83,83,84,5,64,84,84,84,84,84,213,77,84,84,84,84,85,149,89,85,85,85,85,86,85,101,86,86,86,86,87,37,114,87,87,87,87,87,229,126,88,88,88,88,88,165,138,88,88,88,88,89,117,151,89,89,89,89,90,53,163,90,90,90,90,90,245,175,91,91,91,91,91,197,188,91,91,91,91,92,133,200,92,92,92,92,93,69,212,93,93,93,93,94,21,225,94,94,94,94,94,213,237,94,94,94,94,95,149,249,95,95,95,95,96,102,6,96,96,96,96,97,38,18,97,97,97,97,97,230,30,98,98,98,98,98,182,43,98,98,98,98,99,118,55,99,99,99,99,100,54,67,100,100,100,100,101,6,80,101,101,101,101,101,198,92,101,101,101,101,102,134,104,102,102,102,102,103,86,117,103,103,103,103,104,22,129,104,104,104,104,104,214,141,104,104,104,104,105,166,154,105,105,105,105,106,102,166,106,106,106,106,107,38,178,107,107,107,107,107,246,191,108,108,108,108,108,182,203,108,108,108,108,109,118,215,109,109,109,109,110,70,228,110,110,110,110,111,6,240,111,111,111,111,111,198,252,111,111,111,111,112,151,9,112,112,112,112,113,87,21,113,113,113,113,114,23,33,114,114,114,114,114,231,46,114,114,114,114,115,167,58,115,115,115,115,116,103,70,116,116,116,116,117,55,83,117,117,117,117,117,247,95,118,118,118,118,118,183,107,118,118,118,118,119,135,120,119,119,119,119,120,71,132,120,120,120,120,121,7,144,121,121,121,121,121,215,157,121,121,121,121,122,151,169,122,122,122,122,123,87,181,123,123,123,123,124,39,194,124,124,124,124,124,231,206,124,124,124,124,125,167,218,125,125,125,125,126,119,231,126,126,126,126,127,55,243,127,127,127,127,128,8,0,128,128,128,128,128,200,12,128,128,128,128,129,136,24,129,129,129,129,130,88,37,130,130,130,130,131,24,49,131,131,131,131,131,216,61,131,131,131,131,132,168,74,132,132,132,132,133,104,86,133,133,133,133,134,40,98,134,134,134,134,134,248,111,134,134,134,134,135,184,123,135,135,135,135,136,120,135,136,136,136,136,137,72,148,137,137,137,137,138,8,160,137,137,137,137,138,200,172,138,138,138,138,139,152,185,139,139,139,139,140,88,197,140,140,140,140,141,24,209,141,141,141,141,141,232,222,141,141,141,141,142,168,234,142,142,142,142,143,104,246,143,143,143,143,144,57,3,144,144,144,144,144,249,15,144,144,144,144,145,185,27,145,145,145,145,146,137,40,146,146,146,146,147,73,52,147,147,147,147,148,9,64,147,147,147,147,148,217,77,148,148,148,148,149,153,89,149,149,149,149,150,89,101,150,150,150,150,151,41,114,151,151,151,151,151,233,126,151,151,151,151,152,169,138,152,152,152,152,153,121,151,153,153,153,153,154,57,163,154,154,154,154,154,249,175,154,154,154,154,155,201,188,155,155,155,155,156,137,200,156,156,156,156,157,73,212,157,157,157,157,158,25,225,157,157,157,157,158,217,237,158,158,158,158,159,153,249,159,159,159,159,160,106,6,160,160,160,160,161,42,18,161,161,161,161,161,234,30,161,161,161,161,162,186,43,162,162,162,162,163,122,55,163,163,163,163,164,58,67,164,164,164,164,165,10,80,164,164,164,164,165,202,92,165,165,165,165,166,138,104,166,166,166,166,167,90,117,167,167,167,167,168,26,129,167,167,167,167,168,218,141,168,168,168,168,169,170,154,169,169,169,169,170,106,166,170,170,170,170,171,42,178,171,171,171,171,171,250,191,171,171,171,171,172,186,203,172,172,172,172,173,122,215,173,173,173,173,174,74,228,174,174,174,174,175,10,240,174,174,174,174,175,202,252,175,175,175,175,176,155,9,176,176,176,176,177,91,21,177,177,177,177,178,27,33,177,177,177,177,178,235,46,178,178,178,178,179,171,58,179,179,179,179,180,107,70,180,180,180,180,181,59,83,180,180,180,180,181,251,95,181,181,181,181,182,187,107,182,182,182,182,183,139,120,183,183,183,183,184,75,132,184,184,184,184,185,11,144,184,184,184,184,185,219,157,185,185,185,185,186,155,169,186,186,186,186,187,91,181,187,187,187,187,188,43,194,187,187,187,187,188,235,206,188,188,188,188,189,171,218,189,189,189,189,190,123,231,190,190,190,190,191,59,243,190,190,190,190,191,251,255,191,191,191,191,192,204,12,192,192,192,192,193,140,24,193,193,193,193,194,76,36,194,194,194,194,195,28,49,194,194,194,194,195,220,61,195,195,195,195,196,156,73,196,196,196,196,197,108,86,197,197,197,197,198,44,98,197,197,197,197,198,236,110,198,198,198,198,199,188,123,199,199,199,199,200,124,135,200,200,200,200,201,60,147,200,200,200,200,202,12,160,201,201,201,201,202,204,172,202,202,202,202,203,140,184,203,203,203,203,204,92,197,204,204,204,204,205,28,209,204,204,204,204,205,220,221,205,205,205,205,206,172,234,206,206,206,206,207,108,246,207,207,207,207,208,45,2,207,207,207,207,208,253,15,208,208,208,208,209,189,27,209,209,209,209,210,125,39,210,210,210,210,211,77,52,210,210,210,210,212,13,64,211,211,211,211,212,205,76,212,212,212,212,213,157,89,213,213,213,213,214,93,101,214,214,214,214,215,29,113,214,214,214,214,215,237,126,215,215,215,215,216,173,138,216,216,216,216,217,109,150,217,217,217,217,218,61,163,217,217,217,217,218,253,175,218,218,218,218,219,189,187,219,219,219,219,220,141,200,220,220,220,220,221,77,212,220,220,220,220,222,13,224,221,221,221,221,222,221,237,222,222,222,222,223,157,249,223,223,223,223,224,94,5,224,224,224,224,225,46,18,224,224,224,224,225,238,30,225,225,225,225,226,174,42,226,226,226,226,227,126,55,227,227,227,227,228,62,67,227,227,227,227,228,254,79,228,228,228,228,229,206,92,229,229,229,229,230,142,104,230,230,230,230,231,78,116,230,230,230,230,232,30,129,231,231,231,231,232,222,141,232,232,232,232,233,158,153,233,233,233,233,234,110,166,233,233,233,233,235,46,178,234,234,234,234,235,238,190,235,235,235,235,236,190,203,236,236,236,236,237,126,215,237,237,237,237,238,62,227,237,237,237,237,239,14,240,238,238,238,238,239,206,252,239,239,239,239,240,143,8,240,240,240,240,241,95,21,240,240,240,240,242,31,33,241,241,241,241,242,223,45,242,242,242,242,243,175,58,243,243,243,243,244,111,70,243,243,243,243,245,47,82,244,244,244,244,245,255,95,245,245,245,245,246,191,107,246,246,246,246,247,127,119,247,247,247,247,248,79,132,247,247,247,247,249,15,144,248,248,248,248,249,207,156,249,249,249,249,250,159,169,250,250,250,250,251,95,181,250,250,250,250,252,31,193,251,251,251,251,252,239,206,252,252,252,252,253,175,218,253,253,253,253,254,111,230,253,253,253,253,255,63,243,254,254,254,254,255,255,255,255,255,255,255};

uint8_t usbIsoBuffer[USB_DATAPACKETSIZE];			//buffer for usb iso transfer
uint8_t *usbIsoBufferAddress = &usbIsoBuffer[0];	//pointer to usb iso buffer
uint8_t usbControlBuffer[USB_CONTROLPACKETSIZE];		//buffer for usb iso transfer
uint8_t *usbControlBufferAddress = &usbControlBuffer[0];	//pointer to usb iso buffer

//functions
void usb_iso_received(udd_ep_status_t, iram_size_t, udd_ep_id_t);		//called when received an usb iso packet
void usb_control_received(void);	//called when received an usb control/setup packet
void speed_set(uint32_t speed);		//sets the playback speed in points per second
void shutter_set(bool onoff);		//sets the shutter level
void statusled_set(bool onoff);		//sets the status led level
void point_output(uint8_t *pointAddress);	//outputs point to DACs
void blank_and_center(void);		//outputs default blanked point to DACs	
void start(void);				
void stop(void);


#endif /* MAIN_H_ */