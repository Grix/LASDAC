/*
Lasdac main prosjekt (for Arduino Due)

*/

#include "asf.h"
#include <math.h>
#include <string.h>
//#include <setup.c>

//macros
#define MAXSPEED 50000 //in pps
#define MINSPEED 1000 //in pps
#define MAXFRAMESIZE 3333 //in points
#define PIN_SHUTTER IOPORT_CREATE_PIN(PIOC,12)
#define PIN_STATUSLED IOPORT_CREATE_PIN(PIOC,13)
#define PIN_ERRORLED IOPORT_CREATE_PIN(PIOC,14)

//functions
void spi_init(void);
void dac_init(void);
void iopins_init(void);
void speed_set(uint32_t speed);
void shutter_set(bool onoff);
void statusled_set(bool onoff);
void errorled_set(bool onoff);
void point_output(uint8_t *pointAddress);
void blank_and_center(void);
void start(void);
void stop(void);

//global variables, reserve memory for buffers
uint32_t frameSize = 0; //size of frame buffer in bytes
uint32_t framePos = 0; //current position in frame in byte number
uint16_t newFrameSize = 0; //incoming frame total size in points
uint16_t newFramePos = 0; //incoming frame position
bool newFrameReady = false; //signals a new frame has been received and is ready to play when the current one ends
bool playing = false; //signals a point should be output next systick
uint32_t outputSpeed = 20000; //points per second
uint8_t frame1[MAXFRAMESIZE * 7]; //frame buffer 1
uint8_t frame2[MAXFRAMESIZE * 7]; //frame buffer 2
uint8_t *frameAddress = &frame1[0]; //start of current frame buffer
uint8_t *newFrameAddress = &frame2[0]; //incoming frame buffer address
uint8_t testPoint[7] = {0xFF, 0xF0, 0x00, 0b10101010, 0b10101010, 0b10101010, 0b10101010};
uint8_t testFrame[4662] = {130,8,32,0,0,0,0,134,40,98,0,0,0,0,138,88,165,0,0,0,0,142,120,231,0,0,0,0,146,153,41,0,0,0,0,150,201,108,0,0,0,0,154,233,174,0,0,0,0,159,9,240,0,0,0,0,163,42,50,0,0,0,0,167,90,117,0,0,0,0,171,122,183,0,0,0,0,175,154,249,0,0,0,0,179,187,59,0,0,0,0,183,235,126,0,0,0,0,188,11,192,0,0,0,0,192,44,2,0,0,0,0,196,92,69,0,0,0,0,200,124,135,0,0,0,0,204,156,201,0,0,0,0,208,189,11,0,0,0,0,212,237,78,0,0,0,0,217,13,144,0,0,0,0,221,45,210,0,0,0,0,225,94,21,0,0,0,0,229,126,87,0,0,0,0,233,158,153,0,0,0,0,237,190,219,0,0,0,0,241,239,30,0,0,0,0,246,15,96,0,0,0,0,250,47,162,0,0,0,0,254,79,228,0,0,0,0,254,255,239,0,0,0,0,254,255,239,255,255,255,255,254,255,239,255,255,255,255,254,255,239,255,255,255,255,254,255,239,255,255,255,255,253,15,239,255,255,255,255,251,15,239,255,255,255,255,249,15,239,255,255,255,255,248,255,239,255,255,255,255,246,15,239,255,255,255,255,243,31,239,255,255,255,255,242,239,239,255,255,255,255,239,255,239,255,255,255,255,237,15,239,255,255,255,255,236,223,239,255,255,255,255,233,239,239,255,255,255,255,230,255,239,255,255,255,255,230,207,239,255,255,255,255,227,223,239,255,255,255,255,224,239,239,255,255,255,255,224,191,239,255,255,255,255,221,207,239,255,255,255,255,218,239,239,255,255,255,255,218,191,239,255,255,255,255,215,207,239,255,255,255,255,212,223,239,255,255,255,255,212,175,239,255,255,255,255,209,191,239,255,255,255,255,206,207,239,255,255,255,255,206,159,239,255,255,255,255,203,175,239,255,255,255,255,200,191,239,255,255,255,255,200,143,239,255,255,255,255,197,159,239,255,255,255,255,194,175,239,255,255,255,255,194,143,239,255,255,255,255,191,159,239,255,255,255,255,188,175,239,255,255,255,255,188,127,239,255,255,255,255,185,143,239,255,255,255,255,182,159,239,255,255,255,255,182,111,239,255,255,255,255,179,127,239,255,255,255,255,176,143,239,255,255,255,255,176,95,239,255,255,255,255,173,111,239,255,255,255,255,170,127,239,255,255,255,255,170,79,239,255,255,255,255,167,95,239,255,255,255,255,164,111,239,255,255,255,255,164,79,239,255,255,255,255,161,95,239,255,255,255,255,158,111,239,255,255,255,255,158,63,239,255,255,255,255,156,63,239,255,255,255,255,154,79,239,255,255,255,255,152,79,239,255,255,255,255,152,47,239,255,255,255,255,149,63,239,255,255,255,255,146,79,239,255,255,255,255,146,31,239,255,255,255,255,143,47,239,255,255,255,255,140,63,239,255,255,255,255,140,31,239,255,255,255,255,137,47,239,255,255,255,255,134,63,239,255,255,255,255,134,15,239,255,255,255,255,131,31,239,255,255,255,255,128,47,239,255,255,255,255,127,255,239,255,255,255,255,125,15,239,255,255,255,255,122,31,239,255,255,255,255,121,239,239,255,255,255,255,118,255,239,255,255,255,255,116,15,239,255,255,255,255,115,223,239,255,255,255,255,112,239,239,255,255,255,255,109,255,239,255,255,255,255,109,223,239,255,255,255,255,106,239,239,255,255,255,255,103,255,239,255,255,255,255,103,207,239,255,255,255,255,100,223,239,255,255,255,255,97,239,239,255,255,255,255,97,191,239,255,255,255,255,94,207,239,255,255,255,255,91,223,239,255,255,255,255,91,175,239,255,255,255,255,88,191,239,255,255,255,255,85,207,239,255,255,255,255,85,175,239,255,255,255,255,82,191,239,255,255,255,255,79,207,239,255,255,255,255,79,159,239,255,255,255,255,76,175,239,255,255,255,255,73,191,239,255,255,255,255,73,143,239,255,255,255,255,70,159,239,255,255,255,255,67,175,239,255,255,255,255,67,127,239,255,255,255,255,64,143,239,255,255,255,255,61,159,239,255,255,255,255,61,111,239,255,255,255,255,58,127,239,255,255,255,255,55,143,239,255,255,255,255,55,111,239,255,255,255,255,53,111,239,255,255,255,255,51,111,239,255,255,255,255,49,127,239,255,255,255,255,49,95,239,255,255,255,255,46,111,239,255,255,255,255,43,127,239,255,255,255,255,43,79,239,255,255,255,255,40,95,239,255,255,255,255,37,111,239,255,255,255,255,37,63,239,255,255,255,255,34,79,239,255,255,255,255,31,95,239,255,255,255,255,31,63,239,255,255,255,255,28,79,239,255,255,255,255,25,95,239,255,255,255,255,25,47,239,255,255,255,255,22,63,239,255,255,255,255,19,79,239,255,255,255,255,19,31,239,255,255,255,255,16,47,239,255,255,255,255,13,63,239,255,255,255,255,13,15,239,255,255,255,255,10,31,239,255,255,255,255,7,47,239,255,255,255,255,6,255,239,255,255,255,255,4,15,239,255,255,255,255,1,31,239,255,255,255,255,0,255,239,255,255,255,255,0,255,239,0,0,0,0,0,255,239,0,0,0,0,0,255,239,0,0,0,0,0,255,239,0,0,0,0,3,223,239,0,0,0,0,9,191,239,0,0,0,0,15,159,239,0,0,0,0,21,127,239,0,0,0,0,27,79,239,0,0,0,0,33,47,239,0,0,0,0,39,15,239,0,0,0,0,44,239,239,0,0,0,0,50,191,239,0,0,0,0,56,159,239,0,0,0,0,62,127,239,0,0,0,0,68,79,239,0,0,0,0,74,47,239,0,0,0,0,80,15,239,0,0,0,0,85,239,239,0,0,0,0,91,191,239,0,0,0,0,97,159,239,0,0,0,0,103,127,239,0,0,0,0,109,95,239,0,0,0,0,115,47,239,0,0,0,0,121,15,239,0,0,0,0,126,239,239,0,0,0,0,132,207,239,0,0,0,0,138,159,239,0,0,0,0,144,127,239,0,0,0,0,150,95,239,0,0,0,0,156,47,239,0,0,0,0,162,15,239,0,0,0,0,167,239,239,0,0,0,0,173,207,239,0,0,0,0,179,159,239,0,0,0,0,185,127,239,0,0,0,0,191,95,239,0,0,0,0,197,63,239,0,0,0,0,203,15,239,0,0,0,0,208,239,239,0,0,0,0,214,207,239,0,0,0,0,220,159,239,0,0,0,0,226,127,239,0,0,0,0,232,95,239,0,0,0,0,238,63,239,0,0,0,0,244,15,239,0,0,0,0,249,239,239,0,0,0,0,254,255,239,0,0,0,0,254,255,239,255,0,0,255,254,255,239,255,0,0,255,254,255,239,255,0,0,255,254,255,239,255,0,0,255,254,255,192,255,0,0,255,254,255,145,255,0,0,255,254,255,143,255,0,0,255,254,255,96,255,0,0,255,254,255,49,255,0,0,255,254,255,46,255,0,0,255,254,254,255,255,0,0,255,254,254,208,255,0,0,255,254,254,205,255,0,0,255,254,254,158,255,0,0,255,254,254,111,255,0,0,255,254,254,108,255,0,0,255,254,254,61,255,0,0,255,254,254,14,255,0,0,255,254,254,11,255,0,0,255,254,253,220,255,0,0,255,254,253,174,255,0,0,255,254,253,171,255,0,0,255,254,253,124,255,0,0,255,254,253,77,255,0,0,255,254,253,74,255,0,0,255,254,253,27,255,0,0,255,254,252,236,255,0,0,255,254,252,233,255,0,0,255,254,252,202,255,0,0,255,254,252,170,255,0,0,255,254,252,138,255,0,0,255,254,252,136,255,0,0,255,254,252,89,255,0,0,255,254,252,42,255,0,0,255,254,252,40,255,0,0,255,254,251,249,255,0,0,255,254,251,202,255,0,0,255,254,251,199,255,0,0,255,254,251,152,255,0,0,255,254,251,105,255,0,0,255,254,251,102,255,0,0,255,254,251,55,255,0,0,255,254,251,8,255,0,0,255,254,251,5,255,0,0,255,254,250,214,255,0,0,255,254,250,167,255,0,0,255,254,250,164,255,0,0,255,254,250,117,255,0,0,255,254,250,70,255,0,0,255,254,250,68,255,0,0,255,254,250,21,255,0,0,255,254,249,230,255,0,0,255,254,249,227,255,0,0,255,254,249,180,255,0,0,255,254,249,133,255,0,0,255,254,249,130,255,0,0,255,254,249,83,255,0,0,255,254,249,36,255,0,0,255,254,249,33,255,0,0,255,254,248,242,255,0,0,255,254,248,195,255,0,0,255,254,248,193,255,0,0,255,254,248,146,255,0,0,255,254,248,99,255,0,0,255,254,248,96,255,0,0,255,254,248,49,255,0,0,255,254,248,2,255,0,0,255,254,247,255,255,0,0,255,254,247,208,255,0,0,255,254,247,161,255,0,0,255,254,247,158,255,0,0,255,254,247,111,255,0,0,255,254,247,64,255,0,0,255,254,247,61,255,0,0,255,254,247,14,255,0,0,255,254,246,223,255,0,0,255,254,246,221,255,0,0,255,254,246,174,255,0,0,255,254,246,127,255,0,0,255,254,246,124,255,0,0,255,254,246,92,255,0,0,255,254,246,61,255,0,0,255,254,246,29,255,0,0,255,254,246,27,255,0,0,255,254,245,236,255,0,0,255,254,245,189,255,0,0,255,254,245,186,255,0,0,255,254,245,139,255,0,0,255,254,245,92,255,0,0,255,254,245,90,255,0,0,255,254,245,43,255,0,0,255,254,244,252,255,0,0,255,254,244,249,255,0,0,255,254,244,202,255,0,0,255,254,244,155,255,0,0,255,254,244,152,255,0,0,255,254,244,105,255,0,0,255,254,244,58,255,0,0,255,254,244,55,255,0,0,255,254,244,8,255,0,0,255,254,243,217,255,0,0,255,254,243,214,255,0,0,255,254,243,167,255,0,0,255,254,243,120,255,0,0,255,254,243,118,255,0,0,255,254,243,71,255,0,0,255,254,243,24,255,0,0,255,254,243,21,255,0,0,255,254,242,230,255,0,0,255,254,242,183,255,0,0,255,254,242,180,255,0,0,255,254,242,133,255,0,0,255,254,242,86,255,0,0,255,254,242,83,255,0,0,255,254,242,36,255,0,0,255,254,241,245,255,0,0,255,254,241,243,255,0,0,255,254,241,196,255,0,0,255,254,241,149,255,0,0,255,254,241,146,255,0,0,255,254,241,99,255,0,0,255,254,241,52,255,0,0,255,254,241,49,255,0,0,255,254,241,2,255,0,0,255,254,240,211,255,0,0,255,254,240,208,255,0,0,255,254,240,161,255,0,0,255,254,240,114,255,0,0,255,254,240,111,255,0,0,255,254,240,64,255,0,0,255,254,240,17,255,0,0,255,254,240,15,255,0,0,255,254,240,15,0,0,0,0,254,240,15,0,0,0,0,254,240,15,0,0,0,0,254,240,15,0,0,0,0,254,240,15,0,0,0,0,254,240,15,0,255,0,255,254,240,15,0,255,0,255,254,240,15,0,255,0,255,254,240,15,0,255,0,255,253,0,15,0,255,0,255,251,0,15,0,255,0,255,249,0,15,0,255,0,255,248,240,15,0,255,0,255,246,0,15,0,255,0,255,243,16,15,0,255,0,255,242,224,15,0,255,0,255,239,240,15,0,255,0,255,237,0,15,0,255,0,255,236,208,15,0,255,0,255,233,224,15,0,255,0,255,230,240,15,0,255,0,255,230,192,15,0,255,0,255,227,208,15,0,255,0,255,224,224,15,0,255,0,255,224,176,15,0,255,0,255,221,192,15,0,255,0,255,218,224,15,0,255,0,255,218,176,15,0,255,0,255,215,192,15,0,255,0,255,212,208,15,0,255,0,255,212,160,15,0,255,0,255,209,176,15,0,255,0,255,206,192,15,0,255,0,255,206,144,15,0,255,0,255,203,160,15,0,255,0,255,200,176,15,0,255,0,255,200,128,15,0,255,0,255,197,144,15,0,255,0,255,194,160,15,0,255,0,255,194,128,15,0,255,0,255,191,144,15,0,255,0,255,188,160,15,0,255,0,255,188,112,15,0,255,0,255,185,128,15,0,255,0,255,182,144,15,0,255,0,255,182,96,15,0,255,0,255,179,112,15,0,255,0,255,176,128,15,0,255,0,255,176,80,15,0,255,0,255,173,96,15,0,255,0,255,170,112,15,0,255,0,255,170,64,15,0,255,0,255,167,80,15,0,255,0,255,164,96,15,0,255,0,255,164,64,15,0,255,0,255,161,80,15,0,255,0,255,158,96,15,0,255,0,255,158,48,15,0,255,0,255,156,48,15,0,255,0,255,154,64,15,0,255,0,255,152,64,15,0,255,0,255,152,32,15,0,255,0,255,149,48,15,0,255,0,255,146,64,15,0,255,0,255,146,16,15,0,255,0,255,143,32,15,0,255,0,255,140,48,15,0,255,0,255,140,16,15,0,255,0,255,137,32,15,0,255,0,255,134,48,15,0,255,0,255,134,0,15,0,255,0,255,131,16,15,0,255,0,255,128,32,15,0,255,0,255,127,240,15,0,255,0,255,125,0,15,0,255,0,255,122,16,15,0,255,0,255,121,224,15,0,255,0,255,118,240,15,0,255,0,255,116,0,15,0,255,0,255,115,208,15,0,255,0,255,112,224,15,0,255,0,255,109,240,15,0,255,0,255,109,208,15,0,255,0,255,106,224,15,0,255,0,255,103,240,15,0,255,0,255,103,192,15,0,255,0,255,100,208,15,0,255,0,255,97,224,15,0,255,0,255,97,176,15,0,255,0,255,94,192,15,0,255,0,255,91,208,15,0,255,0,255,91,160,15,0,255,0,255,88,176,15,0,255,0,255,85,192,15,0,255,0,255,85,160,15,0,255,0,255,82,176,15,0,255,0,255,79,192,15,0,255,0,255,79,144,15,0,255,0,255,76,160,15,0,255,0,255,73,176,15,0,255,0,255,73,128,15,0,255,0,255,70,144,15,0,255,0,255,67,160,15,0,255,0,255,67,112,15,0,255,0,255,64,128,15,0,255,0,255,61,144,15,0,255,0,255,61,96,15,0,255,0,255,58,112,15,0,255,0,255,55,128,15,0,255,0,255,55,96,15,0,255,0,255,53,96,15,0,255,0,255,51,96,15,0,255,0,255,49,112,15,0,255,0,255,49,80,15,0,255,0,255,46,96,15,0,255,0,255,43,112,15,0,255,0,255,43,64,15,0,255,0,255,40,80,15,0,255,0,255,37,96,15,0,255,0,255,37,48,15,0,255,0,255,34,64,15,0,255,0,255,31,80,15,0,255,0,255,31,48,15,0,255,0,255,28,64,15,0,255,0,255,25,80,15,0,255,0,255,25,32,15,0,255,0,255,22,48,15,0,255,0,255,19,64,15,0,255,0,255,19,16,15,0,255,0,255,16,32,15,0,255,0,255,13,48,15,0,255,0,255,13,0,15,0,255,0,255,10,16,15,0,255,0,255,7,32,15,0,255,0,255,6,240,15,0,255,0,255,4,0,15,0,255,0,255,1,16,15,0,255,0,255,0,240,15,0,255,0,255,0,240,15,0,0,0,0,0,240,15,0,0,0,0,0,240,15,0,0,0,0,0,240,15,0,0,0,0,0,240,15,0,0,0,0,0,240,15,0,0,255,255,0,240,15,0,0,255,255,0,240,15,0,0,255,255,0,240,15,0,0,255,255,0,240,62,0,0,255,255,0,240,109,0,0,255,255,0,240,111,0,0,255,255,0,240,158,0,0,255,255,0,240,205,0,0,255,255,0,240,208,0,0,255,255,0,240,255,0,0,255,255,0,241,46,0,0,255,255,0,241,49,0,0,255,255,0,241,96,0,0,255,255,0,241,143,0,0,255,255,0,241,146,0,0,255,255,0,241,193,0,0,255,255,0,241,240,0,0,255,255,0,241,243,0,0,255,255,0,242,34,0,0,255,255,0,242,80,0,0,255,255,0,242,83,0,0,255,255,0,242,130,0,0,255,255,0,242,177,0,0,255,255,0,242,180,0,0,255,255,0,242,227,0,0,255,255,0,243,18,0,0,255,255,0,243,21,0,0,255,255,0,243,52,0,0,255,255,0,243,84,0,0,255,255,0,243,116,0,0,255,255,0,243,118,0,0,255,255,0,243,165,0,0,255,255,0,243,212,0,0,255,255,0,243,214,0,0,255,255,0,244,5,0,0,255,255,0,244,52,0,0,255,255,0,244,55,0,0,255,255,0,244,102,0,0,255,255,0,244,149,0,0,255,255,0,244,152,0,0,255,255,0,244,199,0,0,255,255,0,244,246,0,0,255,255,0,244,249,0,0,255,255,0,245,40,0,0,255,255,0,245,87,0,0,255,255,0,245,90,0,0,255,255,0,245,137,0,0,255,255,0,245,184,0,0,255,255,0,245,186,0,0,255,255,0,245,233,0,0,255,255,0,246,24,0,0,255,255,0,246,27,0,0,255,255,0,246,74,0,0,255,255,0,246,121,0,0,255,255,0,246,124,0,0,255,255,0,246,171,0,0,255,255,0,246,218,0,0,255,255,0,246,221,0,0,255,255,0,247,12,0,0,255,255,0,247,59,0,0,255,255,0,247,61,0,0,255,255,0,247,108,0,0,255,255,0,247,155,0,0,255,255,0,247,158,0,0,255,255,0,247,205,0,0,255,255,0,247,252,0,0,255,255,0,247,255,0,0,255,255,0,248,46,0,0,255,255,0,248,93,0,0,255,255,0,248,96,0,0,255,255,0,248,143,0,0,255,255,0,248,190,0,0,255,255,0,248,193,0,0,255,255,0,248,240,0,0,255,255,0,249,31,0,0,255,255,0,249,33,0,0,255,255,0,249,80,0,0,255,255,0,249,127,0,0,255,255,0,249,130,0,0,255,255,0,249,162,0,0,255,255,0,249,193,0,0,255,255,0,249,225,0,0,255,255,0,249,227,0,0,255,255,0,250,18,0,0,255,255,0,250,65,0,0,255,255,0,250,68,0,0,255,255,0,250,115,0,0,255,255,0,250,162,0,0,255,255,0,250,164,0,0,255,255,0,250,211,0,0,255,255,0,251,2,0,0,255,255,0,251,5,0,0,255,255,0,251,52,0,0,255,255,0,251,99,0,0,255,255,0,251,102,0,0,255,255,0,251,149,0,0,255,255,0,251,196,0,0,255,255,0,251,199,0,0,255,255,0,251,246,0,0,255,255,0,252,37,0,0,255,255,0,252,40,0,0,255,255,0,252,87,0,0,255,255,0,252,134,0,0,255,255,0,252,136,0,0,255,255,0,252,183,0,0,255,255,0,252,230,0,0,255,255,0,252,233,0,0,255,255,0,253,24,0,0,255,255,0,253,71,0,0,255,255,0,253,74,0,0,255,255,0,253,121,0,0,255,255,0,253,168,0,0,255,255,0,253,171,0,0,255,255,0,253,218,0,0,255,255,0,254,9,0,0,255,255,0,254,11,0,0,255,255,0,254,58,0,0,255,255,0,254,105,0,0,255,255,0,254,108,0,0,255,255,0,254,155,0,0,255,255,0,254,202,0,0,255,255,0,254,205,0,0,255,255,0,254,252,0,0,255,255,0,255,43,0,0,255,255,0,255,46,0,0,255,255,0,255,93,0,0,255,255,0,255,140,0,0,255,255,0,255,143,0,0,255,255,0,255,174,0,0,255,255,0,255,206,0,0,255,255,0,255,238,0,0,255,255,0,255,239,0,0,255,255,0,255,239,0,0,0,0,0,255,239,0,0,0,0,0,255,239,0,0,0,0,0,255,239,0,0,0,0,3,15,206,0,0,0,0,7,47,140,0,0,0,0,11,79,74,0,0,0,0,15,127,7,0,0,0,0,19,158,197,0,0,0,0,23,190,131,0,0,0,0,27,222,65,0,0,0,0,32,13,254,0,0,0,0,36,45,188,0,0,0,0,40,77,122,0,0,0,0,44,125,55,0,0,0,0,48,156,245,0,0,0,0,52,188,179,0,0,0,0,56,220,113,0,0,0,0,61,12,46,0,0,0,0,65,43,236,0,0,0,0,69,75,170,0,0,0,0,73,107,104,0,0,0,0,77,155,37,0,0,0,0,81,186,227,0,0,0,0,85,218,161,0,0,0,0,90,10,94,0,0,0,0,94,42,28,0,0,0,0,98,73,218,0,0,0,0,102,105,152,0,0,0,0,106,153,85,0,0,0,0,110,185,19,0,0,0,0,114,216,209,0,0,0,0,119,8,143,0,0,0,0,123,40,76,0,0,0,0,127,72,10,0,0,0,0,127,247,255,0,0,0,0,127,247,255,0,0,0,0,127,247,255,0,0,0,0,127,247,255,0,0,0,0,127,247,255,0,0,0,0,127,247,255,0,0,0,0,127,247,255,0,0,0,0,127,247,255,0,0,0,0,127,247,255,0,0,0,0,127,247,255,0,0,0,0};

void SysTick_Handler(void) //systick timer ISR
{
	if (playing) 
	{
		statusled_set(HIGH);
		//output point
		if (framePos > (frameSize - 7))
		{
			//frame finished
			if (newFrameReady)
			{
				//TODO load new frame
			}
			else
			{
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

void USB_control_placeholder(void)
{
	uint8_t data[512];
	//if (data[0] & FIRST_FRAME_MASK)
	{
		//first packet in frame
		
		if (newFrameReady)
		{
			newFrameReady = false;
		}
		
		if (frameAddress == &frame1[0])
			newFrameAddress = &frame2[0];
		else
			newFrameAddress = &frame1[0];
			
		newFramePos = 0;
		speed_set( (data[1] << 8) + data[2] );
		newFrameSize = ( (data[3] << 8) + data[4] );
		
		//TODO copy data from endpoint to newFrameAddress[newFramePos]
		
// 		if ()
// 		{
// 			if (playFlag)
// 			{
// 				newFrameReady = true;
// 			}
// 			else
// 			{
// 				framePos = 0;
// 				frameAddress = newFrameAddress;
// 				playFlag = true;
// 			}
// 		}
	}
// 	else if (/*last frame*/)
// 	{
// 		
// 	}
	
}

int main (void) //entry function
{
	sysclk_init();
	board_init();
	dac_init();
	spi_init();
	iopins_init();
	
	speed_set(outputSpeed);
	shutter_set(HIGH);
	statusled_set(LOW);
	errorled_set(LOW);
	blank_and_center();
	
	//testing
	memcpy(&frame1[0], &testFrame[0], 7000);
	frameAddress = &frame1[0];
	frameSize = 7000;
	playing = true;
}

void point_output(uint8_t *pointAddress) //sends point data to the DACs.
{
	//Argument is a pointer to an 8bit array with the following data in order:
	//8 MSB of x, 4 LSB of x + 4 MSB of y, 8 LSB of y, r, g, b, i
	
	if ((dacc_get_interrupt_status(DACC) & DACC_ISR_TXRDY) == DACC_ISR_TXRDY) //if DAC ready
	{
		dacc_set_channel_selection(DACC, 0);
		dacc_write_conversion_data(DACC, (pointAddress[0] << 4) + (pointAddress[1] >> 4) ); //X
		dacc_set_channel_selection(DACC, 1);
		dacc_write_conversion_data(DACC, ((pointAddress[1] & 0xF) << 8) + pointAddress[2]); //Y
	}
	spi_write(SPI0, (pointAddress[3] << 4) + (0b0001 << 12), 0, 0); //R
	spi_write(SPI0, (pointAddress[4] << 4) + (0b0101 << 12), 0, 0); //G
	spi_write(SPI0, (pointAddress[5] << 4) + (0b1001 << 12), 0, 0); //B
	spi_write(SPI0, (pointAddress[6] << 4) + (0b1101 << 12), 0, 0); //I
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
	SysTick_Config( ceil(sysclk_get_cpu_hz() / speed) );
}

void shutter_set(bool onoff) //set the shutter signal off or on
{
	ioport_set_pin_level(PIN_SHUTTER, onoff);
}

void statusled_set(bool onoff) //set the statusled on or off
{
	ioport_set_pin_level(PIN_STATUSLED, onoff);
}

void errorled_set(bool onoff) //set the error led on or off
{
	ioport_set_pin_level(PIN_ERRORLED, onoff);
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
	spi_set_baudrate_div(SPI0, 0, ceil(sysclk_get_cpu_hz() / 30000000)); //default for dac: 30000000
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
	statusled_set(LOW);
	shutter_set(HIGH);
}