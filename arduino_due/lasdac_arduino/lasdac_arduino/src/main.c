/*
Lasdac main prosjekt (for Arduino Due)

*/

#include "asf.h"
#include <math.h>
//#include <setup.c>

//macros
#define MAXSPEED 50000
#define MINSPEED 1000
#define PIN_SHUTTER IOPORT_CREATE_PIN(PIOC,12)
#define PIN_STATUSLED IOPORT_CREATE_PIN(PIOC,13)
#define PIN_ERRORLED IOPORT_CREATE_PIN(PIOC,14)

//states
typedef enum {STATE_OFF, STATE_WAITING, STATE_OUTPUT, STATE_TEST} state_type;
state_type state = STATE_OFF;

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

//global variables
uint8_t *frameAddress = NULL; //start of current frame buffer
uint32_t frameSize = 0; //size of frame buffer in bytes
uint32_t framePos = 0; //current position in frame in byte number
bool loop = false;
uint32_t outputSpeed = 30000; //points per second
uint8_t testPoint[7] = {0xFF, 0xF0, 0x00, 0b10101010, 0b10101010, 0b10101010, 0b10101010};
uint8_t testFrame[7000] = {130,13,27,0,0,0,0,135,9,82,0,0,0,0,139,20,137,0,0,0,0,144,16,192,0,0,0,0,149,12,247,0,0,0,0,154,9,46,0,0,0,0,158,21,102,0,0,0,0,163,16,157,0,0,0,0,168,12,212,0,0,0,0,172,25,11,0,0,0,0,173,25,23,0,0,0,0,173,25,23,255,0,0,255,173,25,23,255,0,0,255,173,25,23,255,0,0,255,173,25,23,255,0,0,255,173,20,236,255,0,24,255,173,18,217,255,0,24,255,172,24,156,255,0,42,255,172,14,114,255,0,60,255,172,9,95,255,0,60,255,170,21,37,255,0,78,255,169,20,253,255,0,96,255,169,12,235,255,0,96,255,167,16,180,255,0,114,255,166,9,143,255,0,138,255,165,15,127,255,0,138,255,163,10,77,255,0,156,255,160,18,30,255,0,174,255,158,18,255,255,0,192,255,157,21,242,255,0,192,255,154,22,202,255,0,210,255,152,19,176,255,0,228,255,151,20,165,255,0,228,255,148,15,133,255,0,246,255,146,8,113,240,0,255,255,145,7,105,240,0,255,255,141,14,81,222,0,255,255,137,19,61,204,0,255,255,135,9,51,186,0,255,255,134,7,46,186,0,255,255,130,10,36,168,0,255,255,127,14,33,150,0,255,255,126,12,31,150,0,255,255,122,14,30,132,0,255,255,119,18,33,108,0,255,255,118,16,35,108,0,255,255,114,18,44,90,0,255,255,110,22,58,72,0,255,255,108,12,71,54,0,255,255,107,10,76,54,0,255,255,103,17,99,36,0,255,255,101,10,118,18,0,255,255,100,9,127,18,0,255,255,96,20,158,0,0,255,255,94,16,183,0,24,255,255,93,17,194,0,24,255,255,90,17,233,0,42,255,255,87,21,21,0,60,255,255,86,8,53,0,78,255,255,85,12,67,0,78,255,255,82,22,116,0,96,255,255,81,15,153,0,114,255,255,80,21,169,0,114,255,255,78,23,223,0,138,255,255,77,23,7,0,156,255,255,77,15,24,0,156,255,255,76,11,83,0,174,255,255,75,11,143,0,192,255,255,74,19,186,0,210,255,255,74,16,204,0,210,255,255,74,10,10,0,228,255,255,73,25,53,0,246,255,255,73,24,72,0,246,255,255,74,11,134,0,255,240,255,74,17,177,0,255,222,255,74,19,195,0,255,222,255,75,17,0,0,255,204,255,76,18,60,0,255,186,255,77,18,100,0,255,168,255,77,24,118,0,255,168,255,79,18,174,0,255,150,255,80,24,212,0,255,132,255,81,17,228,0,255,132,255,83,21,24,0,255,108,255,85,16,58,0,255,90,255,85,27,72,0,255,90,255,88,22,118,0,255,72,255,91,19,160,0,255,54,255,93,21,187,0,255,36,255,94,20,198,0,255,36,255,97,24,233,0,255,18,255,100,13,254,0,255,0,255,101,15,7,0,255,0,255,104,23,34,24,255,0,255,107,16,49,42,255,0,255,108,17,55,42,255,0,255,112,13,73,60,255,0,255,114,23,81,78,255,0,255,115,26,85,78,255,0,255,119,23,93,96,255,0,255,123,21,96,114,255,0,255,126,17,94,138,255,0,255,127,20,94,138,255,0,255,131,17,87,156,255,0,255,133,28,79,174,255,0,255,135,14,76,174,255,0,255,138,26,59,192,255,0,255,141,19,45,210,255,0,255,142,21,39,210,255,0,255,146,14,13,228,255,0,255,149,19,240,246,255,0,255,151,24,216,255,240,0,255,152,23,206,255,240,0,255,155,25,169,255,222,0,255,157,25,140,255,204,0,255,158,23,127,255,204,0,255,161,18,82,255,186,0,255,163,14,49,255,168,0,255,163,25,34,255,168,0,255,166,12,239,255,150,0,255,168,11,186,255,132,0,255,169,15,147,255,108,0,255,169,23,130,255,108,0,255,171,14,72,255,90,0,255,171,26,31,255,72,0,255,172,16,13,255,72,0,255,173,13,208,255,54,0,255,173,19,165,255,36,0,255,173,21,147,255,36,0,255,174,10,85,255,18,0,255,173,25,23,255,0,0,255,173,25,23,0,0,0,0,173,25,23,0,0,0,0,173,25,23,0,0,0,0,173,25,23,0,0,0,0,175,23,58,0,0,0,0,179,20,130,0,0,0,0,183,17,201,0,0,0,0,187,16,16,0,0,0,0,191,13,87,0,0,0,0,194,26,158,0,0,0,0,198,23,229,0,0,0,0,202,21,44,0,0,0,0,206,18,115,0,0,0,0,210,15,186,0,0,0,0,214,13,2,0,0,0,0,217,26,73,0,0,0,0,221,23,144,0,0,0,0,225,20,215,0,0,0,0,229,18,30,0,0,0,0,233,15,101,0,0,0,0,236,28,172,0,0,0,0,240,25,243,0,0,0,0,244,23,59,0,0,0,0,248,20,130,0,0,0,0,249,26,155,0,0,0,0,249,26,155,255,255,255,255,249,26,155,255,255,255,255,249,26,155,255,255,255,255,249,26,155,255,255,255,255,246,30,155,255,255,255,255,244,19,155,255,255,255,255,243,29,155,255,255,255,255,238,27,155,255,255,255,255,238,16,155,255,255,255,255,233,15,155,255,255,255,255,232,19,155,255,255,255,255,227,18,155,255,255,255,255,226,23,155,255,255,255,255,221,21,155,255,255,255,255,220,26,155,255,255,255,255,215,24,155,255,255,255,255,214,29,155,255,255,255,255,209,28,155,255,255,255,255,209,16,155,255,255,255,255,206,21,155,255,255,255,255,203,26,155,255,255,255,255,203,20,155,255,255,255,255,198,18,155,255,255,255,255,197,23,155,255,255,255,255,192,21,155,255,255,255,255,191,26,155,255,255,255,255,186,25,155,255,255,255,255,185,29,155,255,255,255,255,180,28,155,255,255,255,255,180,17,155,255,255,255,255,175,15,155,255,255,255,255,174,20,155,255,255,255,255,169,18,155,255,255,255,255,168,23,155,255,255,255,255,163,22,155,255,255,255,255,162,27,155,255,255,255,255,160,15,155,255,255,255,255,157,20,155,255,255,255,255,156,30,155,255,255,255,255,151,28,155,255,255,255,255,151,17,155,255,255,255,255,146,15,155,255,255,255,255,145,20,155,255,255,255,255,140,19,155,255,255,255,255,139,24,155,255,255,255,255,134,22,155,255,255,255,255,133,27,155,255,255,255,255,128,25,155,255,255,255,255,127,30,155,255,255,255,255,122,28,155,255,255,255,255,122,17,155,255,255,255,255,119,22,155,255,255,255,255,116,26,155,255,255,255,255,116,21,155,255,255,255,255,111,19,155,255,255,255,255,110,24,155,255,255,255,255,105,22,155,255,255,255,255,104,27,155,255,255,255,255,99,25,155,255,255,255,255,98,30,155,255,255,255,255,93,29,155,255,255,255,255,93,18,155,255,255,255,255,88,16,155,255,255,255,255,87,21,155,255,255,255,255,82,19,155,255,255,255,255,81,24,155,255,255,255,255,78,29,155,255,255,255,255,76,17,155,255,255,255,255,75,27,155,255,255,255,255,70,26,155,255,255,255,255,70,15,155,255,255,255,255,64,29,155,255,255,255,255,64,18,155,255,255,255,255,59,16,155,255,255,255,255,58,21,155,255,255,255,255,53,20,155,255,255,255,255,52,24,155,255,255,255,255,47,23,155,255,255,255,255,46,28,155,255,255,255,255,41,26,155,255,255,255,255,41,15,155,255,255,255,255,35,29,155,255,255,255,255,35,18,155,255,255,255,255,32,23,155,255,255,255,255,29,27,155,255,255,255,255,29,21,155,255,255,255,255,24,20,155,255,255,255,255,23,25,155,255,255,255,255,18,23,155,255,255,255,255,17,28,155,255,255,255,255,12,26,155,255,255,255,255,12,15,155,255,255,255,255,6,30,155,255,255,255,255,6,18,155,255,255,255,255,6,18,155,0,0,0,0,6,18,155,0,0,0,0,6,18,155,0,0,0,0,6,18,155,0,0,0,0,9,17,155,0,0,0,0,15,15,155,0,0,0,0,20,29,155,0,0,0,0,26,26,155,0,0,0,0,32,24,155,0,0,0,0,38,22,155,0,0,0,0,44,20,155,0,0,0,0,50,17,155,0,0,0,0,56,15,155,0,0,0,0,61,29,155,0,0,0,0,67,27,155,0,0,0,0,73,24,155,0,0,0,0,79,22,155,0,0,0,0,85,20,155,0,0,0,0,91,17,155,0,0,0,0,97,15,155,0,0,0,0,102,29,155,0,0,0,0,108,27,155,0,0,0,0,114,24,155,0,0,0,0,120,22,155,0,0,0,0,126,20,155,0,0,0,0,132,18,155,0,0,0,0,138,15,155,0,0,0,0,143,29,155,0,0,0,0,149,27,155,0,0,0,0,155,24,155,0,0,0,0,161,22,155,0,0,0,0,167,20,155,0,0,0,0,173,18,155,0,0,0,0,179,15,155,0,0,0,0,184,29,155,0,0,0,0,190,27,155,0,0,0,0,196,25,155,0,0,0,0,202,22,155,0,0,0,0,208,20,155,0,0,0,0,214,18,155,0,0,0,0,220,15,155,0,0,0,0,225,29,155,0,0,0,0,231,27,155,0,0,0,0,237,25,155,0,0,0,0,243,22,155,0,0,0,0,249,20,155,0,0,0,0,249,26,155,0,0,0,0,249,26,155,255,0,0,255,249,26,155,255,0,0,255,249,26,155,255,0,0,255,249,26,155,255,0,0,255,249,26,73,255,0,0,255,249,26,62,255,0,0,255,249,25,236,255,0,0,255,249,25,225,255,0,0,255,249,25,182,255,0,0,255,249,25,138,255,0,0,255,249,25,132,255,0,0,255,249,25,51,255,0,0,255,249,25,40,255,0,0,255,249,24,214,255,0,0,255,249,24,203,255,0,0,255,249,24,121,255,0,0,255,249,24,110,255,0,0,255,249,24,29,255,0,0,255,249,24,17,255,0,0,255,249,23,192,255,0,0,255,249,23,181,255,0,0,255,249,23,99,255,0,0,255,249,23,88,255,0,0,255,249,23,45,255,0,0,255,249,23,1,255,0,0,255,249,22,251,255,0,0,255,249,22,170,255,0,0,255,249,22,158,255,0,0,255,249,22,77,255,0,0,255,249,22,66,255,0,0,255,249,21,240,255,0,0,255,249,21,229,255,0,0,255,249,21,147,255,0,0,255,249,21,136,255,0,0,255,249,21,55,255,0,0,255,249,21,43,255,0,0,255,249,20,218,255,0,0,255,249,20,207,255,0,0,255,249,20,163,255,0,0,255,249,20,120,255,0,0,255,249,20,114,255,0,0,255,249,20,32,255,0,0,255,249,20,21,255,0,0,255,249,19,196,255,0,0,255,249,19,184,255,0,0,255,249,19,103,255,0,0,255,249,19,92,255,0,0,255,249,19,10,255,0,0,255,249,18,255,255,0,0,255,249,18,173,255,0,0,255,249,18,162,255,0,0,255,249,18,81,255,0,0,255,249,18,69,255,0,0,255,249,17,244,255,0,0,255,249,17,233,255,0,0,255,249,17,189,255,0,0,255,249,17,146,255,0,0,255,249,17,140,255,0,0,255,249,17,58,255,0,0,255,249,17,47,255,0,0,255,249,16,222,255,0,0,255,249,16,210,255,0,0,255,249,16,129,255,0,0,255,249,16,118,255,0,0,255,249,16,36,255,0,0,255,249,16,25,255,0,0,255,249,15,199,255,0,0,255,249,15,188,255,0,0,255,249,15,107,255,0,0,255,249,15,96,255,0,0,255,249,15,52,255,0,0,255,249,15,9,255,0,0,255,249,15,3,255,0,0,255,249,14,177,255,0,0,255,249,14,166,255,0,0,255,249,14,84,255,0,0,255,249,14,73,255,0,0,255,249,13,248,255,0,0,255,249,13,237,255,0,0,255,249,13,155,255,0,0,255,249,13,144,255,0,0,255,249,13,62,255,0,0,255,249,13,51,255,0,0,255,249,12,225,255,0,0,255,249,12,214,255,0,0,255,249,12,171,255,0,0,255,249,12,128,255,0,0,255,249,12,122,255,0,0,255,249,12,40,255,0,0,255,249,12,29,255,0,0,255,249,11,203,255,0,0,255,249,11,192,255,0,0,255,249,11,111,255,0,0,255,249,11,99,255,0,0,255,249,11,99,0,0,0,0,249,11,99,0,0,0,0,249,11,99,0,0,0,0,249,11,99,0,0,0,0,249,11,99,0,0,0,0,249,11,99,0,255,0,255,249,11,99,0,255,0,255,249,11,99,0,255,0,255,249,11,99,0,255,0,255,244,9,99,0,255,0,255,243,14,99,0,255,0,255,238,12,99,0,255,0,255,238,1,99,0,255,0,255,233,0,99,0,255,0,255,232,4,99,0,255,0,255,227,3,99,0,255,0,255,226,8,99,0,255,0,255,223,12,99,0,255,0,255,221,1,99,0,255,0,255,220,11,99,0,255,0,255,215,9,99,0,255,0,255,214,14,99,0,255,0,255,209,13,99,0,255,0,255,209,1,99,0,255,0,255,204,0,99,0,255,0,255,203,5,99,0,255,0,255,198,3,99,0,255,0,255,197,8,99,0,255,0,255,192,6,99,0,255,0,255,191,11,99,0,255,0,255,186,10,99,0,255,0,255,185,14,99,0,255,0,255,183,3,99,0,255,0,255,180,8,99,0,255,0,255,180,2,99,0,255,0,255,175,0,99,0,255,0,255,174,5,99,0,255,0,255,169,3,99,0,255,0,255,168,8,99,0,255,0,255,163,7,99,0,255,0,255,162,12,99,0,255,0,255,157,10,99,0,255,0,255,156,15,99,0,255,0,255,151,13,99,0,255,0,255,151,2,99,0,255,0,255,146,0,99,0,255,0,255,145,5,99,0,255,0,255,142,10,99,0,255,0,255,139,14,99,0,255,0,255,139,9,99,0,255,0,255,134,7,99,0,255,0,255,133,12,99,0,255,0,255,128,10,99,0,255,0,255,127,15,99,0,255,0,255,122,13,99,0,255,0,255,122,2,99,0,255,0,255,117,1,99,0,255,0,255,116,6,99,0,255,0,255,111,4,99,0,255,0,255,110,9,99,0,255,0,255,105,7,99,0,255,0,255,104,12,99,0,255,0,255,102,1,99,0,255,0,255,99,5,99,0,255,0,255,98,15,99,0,255,0,255,93,14,99,0,255,0,255,93,3,99,0,255,0,255,88,1,99,0,255,0,255,87,6,99,0,255,0,255,82,4,99,0,255,0,255,81,9,99,0,255,0,255,76,8,99,0,255,0,255,75,12,99,0,255,0,255,70,11,99,0,255,0,255,70,0,99,0,255,0,255,64,14,99,0,255,0,255,64,3,99,0,255,0,255,59,1,99,0,255,0,255,58,6,99,0,255,0,255,55,11,99,0,255,0,255,52,15,99,0,255,0,255,52,9,99,0,255,0,255,47,8,99,0,255,0,255,46,13,99,0,255,0,255,41,11,99,0,255,0,255,41,0,99,0,255,0,255,35,14,99,0,255,0,255,35,3,99,0,255,0,255,30,2,99,0,255,0,255,29,6,99,0,255,0,255,24,5,99,0,255,0,255,23,10,99,0,255,0,255,18,8,99,0,255,0,255,17,13,99,0,255,0,255,15,1,99,0,255,0,255,12,6,99,0,255,0,255,12,0,99,0,255,0,255,6,15,99,0,255,0,255,6,3,99,0,255,0,255,6,3,99,0,0,0,0,6,3,99,0,0,0,0,6,3,99,0,0,0,0,6,3,99,0,0,0,0,6,3,99,0,0,0,0,6,3,99,0,0,255,255,6,3,99,0,0,255,255,6,3,99,0,0,255,255,6,3,99,0,0,255,255,6,3,181,0,0,255,255,6,3,192,0,0,255,255,6,4,18,0,0,255,255,6,4,29,0,0,255,255,6,4,110,0,0,255,255,6,4,122,0,0,255,255,6,4,203,0,0,255,255,6,4,214,0,0,255,255,6,5,40,0,0,255,255,6,5,51,0,0,255,255,6,5,94,0,0,255,255,6,5,138,0,0,255,255,6,5,144,0,0,255,255,6,5,225,0,0,255,255,6,5,237,0,0,255,255,6,6,62,0,0,255,255,6,6,73,0,0,255,255,6,6,155,0,0,255,255,6,6,166,0,0,255,255,6,6,248,0,0,255,255,6,7,3,0,0,255,255,6,7,84,0,0,255,255,6,7,96,0,0,255,255,6,7,177,0,0,255,255,6,7,188,0,0,255,255,6,8,14,0,0,255,255,6,8,25,0,0,255,255,6,8,68,0,0,255,255,6,8,112,0,0,255,255,6,8,118,0,0,255,255,6,8,199,0,0,255,255,6,8,210,0,0,255,255,6,9,36,0,0,255,255,6,9,47,0,0,255,255,6,9,129,0,0,255,255,6,9,140,0,0,255,255,6,9,222,0,0,255,255,6,9,233,0,0,255,255,6,10,58,0,0,255,255,6,10,69,0,0,255,255,6,10,151,0,0,255,255,6,10,162,0,0,255,255,6,10,206,0,0,255,255,6,10,249,0,0,255,255,6,10,255,0,0,255,255,6,11,81,0,0,255,255,6,11,92,0,0,255,255,6,11,173,0,0,255,255,6,11,184,0,0,255,255,6,12,10,0,0,255,255,6,12,21,0,0,255,255,6,12,103,0,0,255,255,6,12,114,0,0,255,255,6,12,196,0,0,255,255,6,12,207,0,0,255,255,6,13,32,0,0,255,255,6,13,43,0,0,255,255,6,13,87,0,0,255,255,6,13,130,0,0,255,255,6,13,136,0,0,255,255,6,13,218,0,0,255,255,6,13,229,0,0,255,255,6,14,54,0,0,255,255,6,14,66,0,0,255,255,6,14,147,0,0,255,255,6,14,158,0,0,255,255,6,14,240,0,0,255,255,6,14,251,0,0,255,255,6,15,77,0,0,255,255,6,15,88,0,0,255,255,6,15,169,0,0,255,255,6,15,181,0,0,255,255,6,15,224,0,0,255,255,6,16,11,0,0,255,255,6,16,17,0,0,255,255,6,16,99,0,0,255,255,6,16,110,0,0,255,255,6,16,192,0,0,255,255,6,16,203,0,0,255,255,6,17,28,0,0,255,255,6,17,40,0,0,255,255,6,17,121,0,0,255,255,6,17,132,0,0,255,255,6,17,214,0,0,255,255,6,17,225,0,0,255,255,6,18,51,0,0,255,255,6,18,62,0,0,255,255,6,18,143,0,0,255,255,6,18,155,0,0,255,255,6,18,155,0,0,0,0,6,18,155,0,0,0,0,6,18,155,0,0,0,0,6,18,155,0,0,0,0,6,22,108,0,0,0,0,6,29,14,0,0,0,0,7,18,177,0,0,0,0,7,25,83,0,0,0,0,8,15,246,0,0,0,0,8,22,152,0,0,0,0,8,28,59,0,0,0,0,9,18,221,0,0,0,0,9,25,128,0,0,0,0,10,16,35,0,0,0,0,10,21,197,0,0,0,0,11,12,104,0,0,0,0,11,19,10,0,0,0,0,11,25,173,0,0,0,0,12,15,79,0,0,0,0,12,21,242,0,0,0,0,13,12,148,0,0,0,0,13,19,55,0,0,0,0,14,8,217,0,0,0,0,14,15,124,0,0,0,0,14,22,30,0,0,0,0,15,12,193,0,0,0,0,15,18,99,0,0,0,0,16,9,6,0,0,0,0,16,15,168,0,0,0,0,17,6,75,0,0,0,0,17,11,237,0,0,0,0,17,18,144,0,0,0,0,18,9,50,0,0,0,0,18,15,213,0,0,0,0,19,5,119,0,0,0,0,19,12,26,0,0,0,0,19,18,188,0,0,0,0,20,9,95,0,0,0,0,20,13,30,0,0,0,0,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,2,2,2,255,20,13,30,0,0,0,0,20,13,30,0,0,0,0,20,13,30,0,0,0,0,20,13,30,0,0,0,0,25,11,30,0,0,0,0,31,9,30,0,0,0,0,37,7,30,0,0,0,0,42,5,30,0,0,0,0,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,27,27,27,255,42,5,30,0,0,0,0,42,5,30,0,0,0,0,42,5,30,0,0,0,0,42,5,30,0,0,0,0,47,3,30,0,0,0,0,52,16,30,0,0,0,0,58,14,30,0,0,0,0,63,12,30,0,0,0,0,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,52,52,52,255,63,12,30,0,0,0,0,63,12,30,0,0,0,0,63,12,30,0,0,0,0,63,12,30,0,0,0,0,68,10,30,0,0,0,0,74,8,30,0,0,0,0,80,6,30,0,0,0,0,85,3,30,0,0,0,0,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,77,77,77,255,85,3,30,0,0,0,0,85,3,30,0,0,0,0,85,3,30,0,0,0,0,85,3,30,0,0,0,0,89,17,30,0,0,0,0,95,15,30,0,0,0,0,101,13,30,0,0,0,0,106,11,30,0,0,0,0,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,102,102,102,255,106,11,30,0,0,0,0,106,11,30,0,0,0,0,106,11,30,0,0,0,0,106,11,30,0,0,0,0,111,9,30,0,0,0,0,117,7,30,0,0,0,0,123,4,30,0,0,0,0,127,18,30,0,0,0,0,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,128,128,128,255,127,18,30,0,0,0,0,127,18,30,0,0,0,0,127,18,30,0,0,0,0,127,18,30,0,0,0,0,132,16,30,0,0,0,0,138,14,30,0,0,0,0,144,12,30,0,0,0,0,149,9,30,0,0,0,0,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,153,153,153,255,149,9,30,0,0,0,0,149,9,30,0,0,0,0,149,9,30,0,0,0,0,149,9,30,0,0,0,0,154,7,30,0,0,0,0,160,5,30,0,0,0,0,166,3,30,0,0,0,0,170,17,30,0,0,0,0,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,178,178,178,255,170,17,30,0,0,0,0,170,17,30,0,0,0,0,170,17,30,0,0,0,0,170,17,30,0,0,0,0,175,15,30,0,0,0,0,181,13,30,0,0,0,0,187,10,30,0,0,0,0,192,8,30,0,0,0,0,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,203,203,203,255,192,8,30,0,0,0,0,192,8,30,0,0,0,0,192,8,30,0,0,0,0,192,8,30,0,0,0,0,197,6,30,0,0,0,0,203,4,30,0,0,0,0,208,18,30,0,0,0,0,213,15,30,0,0,0,0,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,228,228,228,255,213,15,30,0,0,0,0,213,15,30,0,0,0,0,213,15,30,0,0,0,0,213,15,30,0,0,0,0,218,13,30,0,0,0,0,224,11,30,0,0,0,0,230,9,30,0,0,0,0,235,7,30,0,0,0,0,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,253,253,253,255,235,7,30,0,0,0,0,235,7,30,0,0,0,0,235,7,30,0,0,0,0,235,7,30,0,0,0,0,234,16,58,0,0,0,0,230,4,112,0,0,0,0,225,7,167,0,0,0,0,220,11,221,0,0,0,0,215,16,20,0,0,0,0,210,19,74,0,0,0,0,206,7,129,0,0,0,0,201,11,183,0,0,0,0,196,15,238,0,0,0,0,191,19,36,0,0,0,0,187,7,91,0,0,0,0,182,11,145,0,0,0,0,177,15,199,0,0,0,0,172,18,254,0,0,0,0,168,7,52,0,0,0,0,163,11,107,0,0,0,0,158,14,161,0,0,0,0,153,18,216,0,0,0,0,149,7,14,0,0,0,0,144,11,69,0,0,0,0,139,14,123,0,0,0,0,134,18,178,0,0,0,0,129,22,232,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0,127,22,255,0,0,0,0};
	

void SysTick_Handler(void) //systick timer ISR
	{
	switch (state)
	{
		case STATE_OFF: //inactive
			shutter_set(HIGH);
			statusled_set(LOW);
			break;
		case STATE_WAITING: //idle, waiting for command
			break;
		case STATE_OUTPUT: //output point
			if (framePos > (frameSize - 7))
			{
				//frame finished
				if (loop)
				{
					framePos = 0;
					point_output(frameAddress + framePos);
					framePos += 7;
				}
				else
				{
					blank_and_center();
					state = STATE_WAITING;
				}
			}
			else
			{
				//output current point
				point_output(frameAddress + framePos);
				framePos += 7;
			}
			break;
		case STATE_TEST:
			//point_output(&testPoint[0]);
			loop = true;
			frameSize = 7000;
			frameAddress = &testFrame[0];
			framePos = 0;
			state = STATE_OUTPUT;
			break;
		default: //unexpected
			state = STATE_WAITING;
			break;
	}
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
	
	state = STATE_TEST;
}

void point_output(uint8_t *pointAddress) //sends point data to the DACs.
{
	//Argument is a pointer to an 8bit array with the following data in order:
	//8 MSB of x, 4 LSB of x + 4 MSB of y, 8 LSB of y, r, g, b, (user?)
	
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
	spi_write(SPI0, (pointAddress[6] << 4) + (0b1101 << 12), 0, 0); //user ?
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
	ioport_set_pin_level(PIN_ERRORLED, onoff);
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
	state = STATE_WAITING;
	statusled_set(HIGH);
}

void stop(void) //shuts down the DAC, must be started again before output
{
	state = STATE_OFF;
	statusled_set(LOW);
	shutter_set(HIGH);
}