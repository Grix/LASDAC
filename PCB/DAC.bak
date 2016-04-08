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
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DAC084S085C U9
U 1 1 56B20C0A
P 4400 2650
F 0 "U9" H 4400 3350 60  0000 C CNN
F 1 "DAC084S085C" V 4400 2950 60  0000 C CNN
F 2 "Housings_SSOP:MSOP-10_3x3mm_Pitch0.5mm" H 4400 2650 60  0001 C CNN
F 3 "" H 4400 2650 60  0000 C CNN
	1    4400 2650
	1    0    0    -1  
$EndComp
Text HLabel 3700 2100 0    60   UnSpc ~ 0
3.3V
Text HLabel 5050 2100 2    60   Input ~ 0
SCLK
Text HLabel 5050 2200 2    60   Input ~ 0
!SYNC
Text HLabel 5050 2300 2    60   Input ~ 0
Din
Text HLabel 5050 2500 2    60   UnSpc ~ 0
GND
Text HLabel 3700 2200 0    60   Output ~ 0
R
Text HLabel 3700 2300 0    60   Output ~ 0
G
Text HLabel 3700 2400 0    60   Output ~ 0
B
$Comp
L C C14
U 1 1 56B32431
P 5650 2700
F 0 "C14" H 5675 2800 50  0000 L CNN
F 1 "0.1uF" H 5675 2600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 5688 2550 50  0001 C CNN
F 3 "" H 5650 2700 50  0000 C CNN
	1    5650 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 56B32486
P 5650 2950
F 0 "#PWR025" H 5650 2700 50  0001 C CNN
F 1 "GND" H 5650 2800 50  0000 C CNN
F 2 "" H 5650 2950 50  0000 C CNN
F 3 "" H 5650 2950 50  0000 C CNN
	1    5650 2950
	1    0    0    -1  
$EndComp
Text HLabel 5800 2400 2    60   UnSpc ~ 0
2.5V
Wire Wire Line
	3700 2100 3800 2100
Wire Wire Line
	3700 2200 3800 2200
Wire Wire Line
	3700 2300 3800 2300
Wire Wire Line
	3700 2400 3800 2400
Wire Wire Line
	4950 2100 5050 2100
Wire Wire Line
	4950 2200 5050 2200
Wire Wire Line
	4950 2300 5050 2300
Wire Wire Line
	4950 2500 5050 2500
Wire Wire Line
	4950 2400 5800 2400
Wire Wire Line
	5650 2400 5650 2550
Wire Wire Line
	5650 2950 5650 2850
Connection ~ 5650 2400
$Comp
L CP1 CP1
U 1 1 56B4306D
P 3750 1800
F 0 "CP1" H 3775 1900 50  0000 L CNN
F 1 "10uF" H 3775 1700 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeA_EIA-3216_HandSoldering" H 3750 1800 50  0001 C CNN
F 3 "" H 3750 1800 50  0000 C CNN
	1    3750 1800
	-1   0    0    1   
$EndComp
Wire Wire Line
	3750 1950 3750 2100
Connection ~ 3750 2100
$Comp
L GND #PWR026
U 1 1 56B430BD
P 3750 1450
F 0 "#PWR026" H 3750 1200 50  0001 C CNN
F 1 "GND" H 3750 1300 50  0000 C CNN
F 2 "" H 3750 1450 50  0000 C CNN
F 3 "" H 3750 1450 50  0000 C CNN
	1    3750 1450
	-1   0    0    1   
$EndComp
Wire Wire Line
	3750 1450 3750 1650
Text Notes 3500 1900 2    60   ~ 0
CP1 should be a tantalum cap\n\n
Text Notes 6600 2750 2    60   ~ 0
Low ESR low ESL\n
Text HLabel 3700 2500 0    60   Output ~ 0
Intensity
Wire Wire Line
	3700 2500 3800 2500
$EndSCHEMATC
