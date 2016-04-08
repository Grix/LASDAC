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
Sheet 7 7
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
L TL084_v U?
U 1 1 56D5917F
P 3500 1300
F 0 "U?" H 3750 1100 60  0000 C CNN
F 1 "TL084_v" H 3850 1600 60  0000 C CNN
F 2 "" H 3500 1300 60  0000 C CNN
F 3 "" H 3500 1300 60  0000 C CNN
	1    3500 1300
	1    0    0    -1  
$EndComp
$Comp
L TL084_v U?
U 2 1 56D591BE
P 5500 1350
F 0 "U?" H 5750 1150 60  0000 C CNN
F 1 "TL084_v" H 5850 1650 60  0000 C CNN
F 2 "" H 5500 1350 60  0000 C CNN
F 3 "" H 5500 1350 60  0000 C CNN
	2    5500 1350
	1    0    0    -1  
$EndComp
$Comp
L TL084_v U?
U 3 1 56D5921B
P 3500 3050
F 0 "U?" H 3750 2850 60  0000 C CNN
F 1 "TL084_v" H 3850 3350 60  0000 C CNN
F 2 "" H 3500 3050 60  0000 C CNN
F 3 "" H 3500 3050 60  0000 C CNN
	3    3500 3050
	1    0    0    -1  
$EndComp
$Comp
L TL084_v U?
U 4 1 56D59252
P 5500 3050
F 0 "U?" H 5750 2850 60  0000 C CNN
F 1 "TL084_v" H 5850 3350 60  0000 C CNN
F 2 "" H 5500 3050 60  0000 C CNN
F 3 "" H 5500 3050 60  0000 C CNN
	4    5500 3050
	1    0    0    -1  
$EndComp
Text HLabel 3550 850  1    39   UnSpc ~ 0
+12V
Text HLabel 5550 900  1    39   UnSpc ~ 0
+12V
Text HLabel 5550 2600 1    39   UnSpc ~ 0
+12V
Text HLabel 3550 2600 1    39   UnSpc ~ 0
+12V
Text HLabel 3550 3500 3    39   UnSpc ~ 0
-12V
Text HLabel 5550 3500 3    39   UnSpc ~ 0
-12V
Text HLabel 5550 1800 3    39   UnSpc ~ 0
-12V
Text HLabel 3550 1750 3    39   UnSpc ~ 0
-12V
$Comp
L R R?
U 1 1 56D59A3D
P 950 1650
F 0 "R?" V 1030 1650 50  0000 C CNN
F 1 "6.6k" V 950 1650 50  0000 C CNN
F 2 "" V 880 1650 50  0000 C CNN
F 3 "" H 950 1650 50  0000 C CNN
	1    950  1650
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 56D59AA1
P 950 2150
F 0 "R?" V 1030 2150 50  0000 C CNN
F 1 "10k" V 950 2150 50  0000 C CNN
F 2 "" V 880 2150 50  0000 C CNN
F 3 "" H 950 2150 50  0000 C CNN
	1    950  2150
	1    0    0    -1  
$EndComp
Text HLabel 950  1400 1    60   UnSpc ~ 0
Offset
$Comp
L GND #PWR?
U 1 1 56D59B5F
P 950 2400
F 0 "#PWR?" H 950 2150 50  0001 C CNN
F 1 "GND" H 950 2250 50  0000 C CNN
F 2 "" H 950 2400 50  0000 C CNN
F 3 "" H 950 2400 50  0000 C CNN
	1    950  2400
	1    0    0    -1  
$EndComp
Text HLabel 2350 1400 0    60   Input ~ 0
R
$Comp
L R R?
U 1 1 56D5AEA9
P 2650 1400
F 0 "R?" V 2730 1400 50  0000 C CNN
F 1 "4.32k" V 2650 1400 50  0000 C CNN
F 2 "" V 2580 1400 50  0000 C CNN
F 3 "" H 2650 1400 50  0000 C CNN
	1    2650 1400
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5B08B
P 2650 3150
F 0 "R?" V 2730 3150 50  0000 C CNN
F 1 "4.32k" V 2650 3150 50  0000 C CNN
F 2 "" V 2580 3150 50  0000 C CNN
F 3 "" H 2650 3150 50  0000 C CNN
	1    2650 3150
	0    1    1    0   
$EndComp
Text HLabel 2350 3150 0    60   Input ~ 0
G
$Comp
L R R?
U 1 1 56D5B2F1
P 3550 2150
F 0 "R?" V 3630 2150 50  0000 C CNN
F 1 "6.6k" V 3550 2150 50  0000 C CNN
F 2 "" V 3480 2150 50  0000 C CNN
F 3 "" H 3550 2150 50  0000 C CNN
	1    3550 2150
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5B5EC
P 4750 1450
F 0 "R?" V 4830 1450 50  0000 C CNN
F 1 "10k" V 4750 1450 50  0000 C CNN
F 2 "" V 4680 1450 50  0000 C CNN
F 3 "" H 4750 1450 50  0000 C CNN
	1    4750 1450
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5B654
P 5550 2200
F 0 "R?" V 5630 2200 50  0000 C CNN
F 1 "10k" V 5550 2200 50  0000 C CNN
F 2 "" V 5480 2200 50  0000 C CNN
F 3 "" H 5550 2200 50  0000 C CNN
	1    5550 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 850  3550 900 
Wire Wire Line
	3550 1700 3550 1750
Wire Wire Line
	5550 1750 5550 1800
Wire Wire Line
	5550 900  5550 950 
Wire Wire Line
	5550 3450 5550 3500
Wire Wire Line
	5550 2600 5550 2650
Wire Wire Line
	3550 2650 3550 2600
Wire Wire Line
	3550 3450 3550 3500
Wire Wire Line
	950  1400 950  1500
Wire Wire Line
	950  1800 950  2000
Wire Wire Line
	950  2300 950  2400
Wire Wire Line
	1800 1200 3150 1200
Wire Wire Line
	1800 2950 3150 2950
Connection ~ 1800 2950
Wire Wire Line
	950  1900 1800 1900
Connection ~ 1800 1900
Connection ~ 950  1900
Wire Wire Line
	1800 1200 1800 6250
Wire Wire Line
	2800 1400 3150 1400
Wire Wire Line
	2500 1400 2350 1400
Wire Wire Line
	2800 3150 3150 3150
Wire Wire Line
	2500 3150 2350 3150
Wire Wire Line
	3000 1400 3000 2150
Wire Wire Line
	3000 2150 3400 2150
Connection ~ 3000 1400
Wire Wire Line
	3700 2150 4250 2150
Wire Wire Line
	4250 2150 4250 1300
Wire Wire Line
	4150 1300 4400 1300
Wire Wire Line
	4600 1450 4250 1450
Connection ~ 4250 1450
Text HLabel 4400 1300 2    60   Output ~ 0
-R
Connection ~ 4250 1300
Wire Wire Line
	4900 1450 5150 1450
Wire Wire Line
	5000 1450 5000 2200
Wire Wire Line
	5000 2200 5400 2200
Connection ~ 5000 1450
Wire Wire Line
	6350 2200 6350 1350
Wire Wire Line
	6150 1350 6500 1350
Text HLabel 6500 1350 2    60   Output ~ 0
+R
Connection ~ 6350 1350
$Comp
L GND #PWR?
U 1 1 56D5B915
P 5050 1250
F 0 "#PWR?" H 5050 1000 50  0001 C CNN
F 1 "GND" H 5050 1100 50  0000 C CNN
F 2 "" H 5050 1250 50  0000 C CNN
F 3 "" H 5050 1250 50  0000 C CNN
	1    5050 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 1250 5150 1250
$Comp
L R R?
U 1 1 56D5C684
P 3550 3800
F 0 "R?" V 3630 3800 50  0000 C CNN
F 1 "6.6k" V 3550 3800 50  0000 C CNN
F 2 "" V 3480 3800 50  0000 C CNN
F 3 "" H 3550 3800 50  0000 C CNN
	1    3550 3800
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5C6D6
P 4750 3150
F 0 "R?" V 4830 3150 50  0000 C CNN
F 1 "10k" V 4750 3150 50  0000 C CNN
F 2 "" V 4680 3150 50  0000 C CNN
F 3 "" H 4750 3150 50  0000 C CNN
	1    4750 3150
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5C72B
P 5550 3800
F 0 "R?" V 5630 3800 50  0000 C CNN
F 1 "10k" V 5550 3800 50  0000 C CNN
F 2 "" V 5480 3800 50  0000 C CNN
F 3 "" H 5550 3800 50  0000 C CNN
	1    5550 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 3800 3400 3800
Wire Wire Line
	3000 3800 3000 3150
Connection ~ 3000 3150
Wire Wire Line
	4300 3800 4300 3050
Wire Wire Line
	4150 3050 4400 3050
Wire Wire Line
	4300 3150 4600 3150
Connection ~ 4300 3150
Wire Wire Line
	4900 3150 5150 3150
Wire Wire Line
	5050 3150 5050 3800
Wire Wire Line
	5050 3800 5400 3800
Connection ~ 5050 3150
Wire Wire Line
	5700 3800 6350 3800
Wire Wire Line
	6350 3800 6350 3050
Wire Wire Line
	6150 3050 6450 3050
Text HLabel 4400 3050 2    60   Output ~ 0
-G
Text HLabel 6450 3050 2    60   Output ~ 0
+G
Connection ~ 6350 3050
Connection ~ 4300 3050
$Comp
L GND #PWR?
U 1 1 56D5CA8B
P 5050 2950
F 0 "#PWR?" H 5050 2700 50  0001 C CNN
F 1 "GND" H 5050 2800 50  0000 C CNN
F 2 "" H 5050 2950 50  0000 C CNN
F 3 "" H 5050 2950 50  0000 C CNN
	1    5050 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2950 5150 2950
Wire Wire Line
	5700 2200 6350 2200
Wire Wire Line
	3700 3800 4300 3800
$Comp
L TL084_v U?
U 1 1 56D5D360
P 3500 4600
F 0 "U?" H 3750 4400 60  0000 C CNN
F 1 "TL084_v" H 3850 4900 60  0000 C CNN
F 2 "" H 3500 4600 60  0000 C CNN
F 3 "" H 3500 4600 60  0000 C CNN
	1    3500 4600
	1    0    0    -1  
$EndComp
$Comp
L TL084_v U?
U 1 1 56D5D366
P 5500 4650
F 0 "U?" H 5750 4450 60  0000 C CNN
F 1 "TL084_v" H 5850 4950 60  0000 C CNN
F 2 "" H 5500 4650 60  0000 C CNN
F 3 "" H 5500 4650 60  0000 C CNN
	1    5500 4650
	1    0    0    -1  
$EndComp
$Comp
L TL084_v U?
U 1 1 56D5D36C
P 3500 6350
F 0 "U?" H 3750 6150 60  0000 C CNN
F 1 "TL084_v" H 3850 6650 60  0000 C CNN
F 2 "" H 3500 6350 60  0000 C CNN
F 3 "" H 3500 6350 60  0000 C CNN
	1    3500 6350
	1    0    0    -1  
$EndComp
$Comp
L TL084_v U?
U 1 1 56D5D372
P 5500 6350
F 0 "U?" H 5750 6150 60  0000 C CNN
F 1 "TL084_v" H 5850 6650 60  0000 C CNN
F 2 "" H 5500 6350 60  0000 C CNN
F 3 "" H 5500 6350 60  0000 C CNN
	1    5500 6350
	1    0    0    -1  
$EndComp
Text HLabel 3550 4150 1    39   UnSpc ~ 0
+12V
Text HLabel 5550 4200 1    39   UnSpc ~ 0
+12V
Text HLabel 5550 5900 1    39   UnSpc ~ 0
+12V
Text HLabel 3550 5900 1    39   UnSpc ~ 0
+12V
Text HLabel 3550 6800 3    39   UnSpc ~ 0
-12V
Text HLabel 5550 6800 3    39   UnSpc ~ 0
-12V
Text HLabel 5550 5100 3    39   UnSpc ~ 0
-12V
Text HLabel 3550 5050 3    39   UnSpc ~ 0
-12V
Text HLabel 2350 4700 0    60   Input ~ 0
B
$Comp
L R R?
U 1 1 56D5D381
P 2650 4700
F 0 "R?" V 2730 4700 50  0000 C CNN
F 1 "4.32k" V 2650 4700 50  0000 C CNN
F 2 "" V 2580 4700 50  0000 C CNN
F 3 "" H 2650 4700 50  0000 C CNN
	1    2650 4700
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5D387
P 2650 6450
F 0 "R?" V 2730 6450 50  0000 C CNN
F 1 "4.32k" V 2650 6450 50  0000 C CNN
F 2 "" V 2580 6450 50  0000 C CNN
F 3 "" H 2650 6450 50  0000 C CNN
	1    2650 6450
	0    1    1    0   
$EndComp
Text HLabel 2350 6450 0    60   Input ~ 0
Intensity
$Comp
L R R?
U 1 1 56D5D38E
P 3550 5450
F 0 "R?" V 3630 5450 50  0000 C CNN
F 1 "6.6k" V 3550 5450 50  0000 C CNN
F 2 "" V 3480 5450 50  0000 C CNN
F 3 "" H 3550 5450 50  0000 C CNN
	1    3550 5450
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5D394
P 4750 4750
F 0 "R?" V 4830 4750 50  0000 C CNN
F 1 "10k" V 4750 4750 50  0000 C CNN
F 2 "" V 4680 4750 50  0000 C CNN
F 3 "" H 4750 4750 50  0000 C CNN
	1    4750 4750
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5D39A
P 5550 5500
F 0 "R?" V 5630 5500 50  0000 C CNN
F 1 "10k" V 5550 5500 50  0000 C CNN
F 2 "" V 5480 5500 50  0000 C CNN
F 3 "" H 5550 5500 50  0000 C CNN
	1    5550 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 4150 3550 4200
Wire Wire Line
	3550 5000 3550 5050
Wire Wire Line
	5550 5050 5550 5100
Wire Wire Line
	5550 4200 5550 4250
Wire Wire Line
	5550 6750 5550 6800
Wire Wire Line
	5550 5900 5550 5950
Wire Wire Line
	3550 5950 3550 5900
Wire Wire Line
	3550 6750 3550 6800
Wire Wire Line
	1800 4500 3150 4500
Wire Wire Line
	1800 6250 3150 6250
Connection ~ 1800 6250
Connection ~ 1800 5200
Wire Wire Line
	2800 4700 3150 4700
Wire Wire Line
	2500 4700 2350 4700
Wire Wire Line
	2800 6450 3150 6450
Wire Wire Line
	2500 6450 2350 6450
Wire Wire Line
	3000 4700 3000 5450
Wire Wire Line
	3000 5450 3400 5450
Connection ~ 3000 4700
Wire Wire Line
	3700 5450 4250 5450
Wire Wire Line
	4250 5450 4250 4600
Wire Wire Line
	4150 4600 4400 4600
Wire Wire Line
	4600 4750 4250 4750
Connection ~ 4250 4750
Text HLabel 4400 4600 2    60   Output ~ 0
-B
Connection ~ 4250 4600
Wire Wire Line
	4900 4750 5150 4750
Wire Wire Line
	5000 4750 5000 5500
Wire Wire Line
	5000 5500 5400 5500
Connection ~ 5000 4750
Wire Wire Line
	6350 5500 6350 4650
Wire Wire Line
	6150 4650 6500 4650
Text HLabel 6500 4650 2    60   Output ~ 0
+B
Connection ~ 6350 4650
$Comp
L GND #PWR?
U 1 1 56D5D3C4
P 5050 4550
F 0 "#PWR?" H 5050 4300 50  0001 C CNN
F 1 "GND" H 5050 4400 50  0000 C CNN
F 2 "" H 5050 4550 50  0000 C CNN
F 3 "" H 5050 4550 50  0000 C CNN
	1    5050 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4550 5150 4550
$Comp
L R R?
U 1 1 56D5D3CB
P 3550 7100
F 0 "R?" V 3630 7100 50  0000 C CNN
F 1 "6.6k" V 3550 7100 50  0000 C CNN
F 2 "" V 3480 7100 50  0000 C CNN
F 3 "" H 3550 7100 50  0000 C CNN
	1    3550 7100
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5D3D1
P 4750 6450
F 0 "R?" V 4830 6450 50  0000 C CNN
F 1 "10k" V 4750 6450 50  0000 C CNN
F 2 "" V 4680 6450 50  0000 C CNN
F 3 "" H 4750 6450 50  0000 C CNN
	1    4750 6450
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 56D5D3D7
P 5550 7100
F 0 "R?" V 5630 7100 50  0000 C CNN
F 1 "10k" V 5550 7100 50  0000 C CNN
F 2 "" V 5480 7100 50  0000 C CNN
F 3 "" H 5550 7100 50  0000 C CNN
	1    5550 7100
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 7100 3400 7100
Wire Wire Line
	3000 7100 3000 6450
Connection ~ 3000 6450
Wire Wire Line
	4300 7100 4300 6350
Wire Wire Line
	4150 6350 4400 6350
Wire Wire Line
	4300 6450 4600 6450
Connection ~ 4300 6450
Wire Wire Line
	4900 6450 5150 6450
Wire Wire Line
	5050 6450 5050 7100
Wire Wire Line
	5050 7100 5400 7100
Connection ~ 5050 6450
Wire Wire Line
	5700 7100 6350 7100
Wire Wire Line
	6350 7100 6350 6350
Wire Wire Line
	6150 6350 6450 6350
Text HLabel 4400 6350 2    60   Output ~ 0
-Intensity
Text HLabel 6450 6350 2    60   Output ~ 0
+Intensity
Connection ~ 6350 6350
Connection ~ 4300 6350
$Comp
L GND #PWR?
U 1 1 56D5D3EF
P 5050 6250
F 0 "#PWR?" H 5050 6000 50  0001 C CNN
F 1 "GND" H 5050 6100 50  0000 C CNN
F 2 "" H 5050 6250 50  0000 C CNN
F 3 "" H 5050 6250 50  0000 C CNN
	1    5050 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 6250 5150 6250
Wire Wire Line
	5700 5500 6350 5500
Wire Wire Line
	3700 7100 4300 7100
Connection ~ 1800 4500
$EndSCHEMATC
