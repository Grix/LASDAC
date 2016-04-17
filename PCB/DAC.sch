EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Personal library
LIBS:LASDAC-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title "Digital to Analog Converter"
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DAC084S085C U5
U 1 1 56B20C0A
P 5650 4050
F 0 "U5" H 5650 4750 60  0000 C CNN
F 1 "DAC084S085C" V 5650 4350 60  0000 C CNN
F 2 "Housings_SSOP:MSOP-10_3x3mm_Pitch0.5mm" H 5650 4050 60  0001 C CNN
F 3 "" H 5650 4050 60  0000 C CNN
	1    5650 4050
	1    0    0    -1  
$EndComp
Text HLabel 4950 3500 0    60   UnSpc ~ 0
3.3V
Text HLabel 6300 3500 2    60   Input ~ 0
SCLK
Text HLabel 6300 3600 2    60   Input ~ 0
!SYNC
Text HLabel 6300 3700 2    60   Input ~ 0
Din
Text HLabel 6300 3900 2    60   UnSpc ~ 0
GND
Text HLabel 4950 3900 0    60   Output ~ 0
R
Text HLabel 4950 3600 0    60   Output ~ 0
G
Text HLabel 4950 3700 0    60   Output ~ 0
B
$Comp
L C C16
U 1 1 56B32431
P 5000 3200
F 0 "C16" H 5025 3300 50  0000 L CNN
F 1 "0.1uF" H 5025 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5038 3050 50  0001 C CNN
F 3 "" H 5000 3200 50  0000 C CNN
	1    5000 3200
	-1   0    0    1   
$EndComp
Text HLabel 7050 3800 2    60   UnSpc ~ 0
2.5V
Wire Wire Line
	4950 3500 5050 3500
Wire Wire Line
	4950 3600 5050 3600
Wire Wire Line
	4950 3700 5050 3700
Wire Wire Line
	4950 3800 5050 3800
Wire Wire Line
	6200 3500 6300 3500
Wire Wire Line
	6200 3600 6300 3600
Wire Wire Line
	6200 3700 6300 3700
Wire Wire Line
	6200 3900 6300 3900
Wire Wire Line
	6200 3800 7050 3800
Wire Wire Line
	5000 3350 5000 3500
Connection ~ 5000 3500
$Comp
L GND #PWR025
U 1 1 56B430BD
P 5000 2850
F 0 "#PWR025" H 5000 2600 50  0001 C CNN
F 1 "GND" H 5000 2700 50  0000 C CNN
F 2 "" H 5000 2850 50  0000 C CNN
F 3 "" H 5000 2850 50  0000 C CNN
	1    5000 2850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5000 2850 5000 3050
Text Notes 4750 3300 2    60   ~ 0
CP1 should be a tantalum cap\n\n
Text HLabel 4950 3800 0    60   Output ~ 0
Intensity
Wire Wire Line
	4950 3900 5050 3900
$EndSCHEMATC
