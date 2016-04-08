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
Sheet 1 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 2700 2100 1100 800 
U 56B1E50F
F0 "Power Regulation" 60
F1 "Power.sch" 60
F2 "5V" U L 2700 2300 60 
F3 "GND" U L 2700 2650 60 
F4 "+9V" U R 3800 2250 60 
F5 "-9V" U R 3800 2400 60 
F6 "3.3V" U R 3800 2550 60 
F7 "2.5V" U R 3800 2700 60 
$EndSheet
$Comp
L USB_B P1
U 1 1 56B1FF91
P 950 2300
F 0 "P1" H 1150 2100 50  0000 C CNN
F 1 "USB_B" H 900 2500 50  0000 C CNN
F 2 "Connect:USB_B" V 900 2200 50  0001 C CNN
F 3 "" V 900 2200 50  0000 C CNN
	1    950  2300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X25 P2
U 1 1 56B205F7
P 11100 2800
F 0 "P2" H 11100 4100 50  0000 C CNN
F 1 "CONN_01X25" V 11200 2800 50  0000 C CNN
F 2 "Connect:DB25FC" H 11100 2800 50  0001 C CNN
F 3 "" H 11100 2800 50  0000 C CNN
	1    11100 2800
	1    0    0    -1  
$EndComp
$Sheet
S 4600 1700 1150 2850
U 56B20B20
F0 "Microcontroller" 60
F1 "Microcontroller.sch" 60
F2 "3.3V" U L 4600 1950 60 
F3 "GND" U L 4600 2250 60 
F4 "D-" B L 4600 3500 60 
F5 "D+" B L 4600 3350 60 
F6 "X" O R 5750 3350 60 
F7 "Y" O R 5750 3450 60 
F8 "MOSI" O R 5750 2950 60 
F9 "!SYNC" O R 5750 2850 60 
F10 "SCLK" O R 5750 2750 60 
F11 "Shutter" O R 5750 3750 60 
F12 "2.5V" U L 4600 2450 39 
$EndSheet
$Sheet
S 6300 1750 1400 900 
U 56B20B34
F0 "DAC" 60
F1 "DAC.sch" 60
F2 "2.5V" U L 6300 1900 60 
F3 "SCLK" I L 6300 2150 60 
F4 "!SYNC" I L 6300 2250 60 
F5 "DIN" I L 6300 2350 60 
F6 "R" O R 7700 1900 60 
F7 "G" O R 7700 2000 60 
F8 "B" O R 7700 2100 60 
F9 "Intensity" O R 7700 2200 60 
F10 "3.3V" U L 6300 2000 60 
$EndSheet
$Sheet
S 8350 1850 1000 1350
U 56B20B6E
F0 "Amplifiers" 60
F1 "Amplifiers.sch" 60
F2 "+9V" U L 8350 2050 60 
F3 "-9V" U L 8350 2150 60 
F4 "GND" U L 8350 1950 60 
F5 "X" I L 8350 2650 60 
F6 "Y" I L 8350 2750 60 
F7 "R" I L 8350 2250 60 
F8 "G" I L 8350 2350 60 
F9 "B" I L 8350 2450 60 
F10 "+X" O R 9350 1900 60 
F11 "+Y" O R 9350 2000 60 
F12 "-X" O R 9350 2500 60 
F13 "-Y" O R 9350 2600 60 
F14 "+R" O R 9350 2100 60 
F15 "+G" O R 9350 2200 60 
F16 "+B" O R 9350 2300 60 
F17 "-R" O R 9350 2700 60 
F18 "-G" O R 9350 2800 60 
F19 "-B" O R 9350 2900 60 
F20 "Intensity" I L 8350 2550 60 
F21 "+Intensity" O R 9350 2400 60 
F22 "-Intensity" O R 9350 3000 60 
F23 "2.5V" U L 8350 2850 60 
F24 "Shutter" I L 8350 2950 60 
F25 "Shutter_Out" O R 9350 3100 60 
$EndSheet
$Comp
L GND #PWR01
U 1 1 56B2C915
P 2700 2650
F 0 "#PWR01" H 2700 2400 50  0001 C CNN
F 1 "GND" H 2700 2500 50  0000 C CNN
F 2 "" H 2700 2650 50  0000 C CNN
F 3 "" H 2700 2650 50  0000 C CNN
	1    2700 2650
	0    1    1    0   
$EndComp
$Comp
L GND #PWR02
U 1 1 56B317A1
P 8200 1950
F 0 "#PWR02" H 8200 1700 50  0001 C CNN
F 1 "GND" H 8200 1800 50  0000 C CNN
F 2 "" H 8200 1950 50  0000 C CNN
F 3 "" H 8200 1950 50  0000 C CNN
	1    8200 1950
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR03
U 1 1 56B34131
P 10750 4000
F 0 "#PWR03" H 10750 3750 50  0001 C CNN
F 1 "GND" H 10750 3850 50  0000 C CNN
F 2 "" H 10750 4000 50  0000 C CNN
F 3 "" H 10750 4000 50  0000 C CNN
	1    10750 4000
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 56B410A0
P 4350 3350
F 0 "R1" V 4430 3350 50  0000 C CNN
F 1 "27R" V 4350 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 4280 3350 50  0001 C CNN
F 3 "" H 4350 3350 50  0000 C CNN
	1    4350 3350
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 56B411F0
P 4350 3500
F 0 "R2" V 4430 3500 50  0000 C CNN
F 1 "27R" V 4350 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 4280 3500 50  0001 C CNN
F 3 "" H 4350 3500 50  0000 C CNN
	1    4350 3500
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 56C38472
P 10600 1600
F 0 "R3" V 10550 1450 50  0000 C CNN
F 1 "150" V 10600 1600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 1600 50  0001 C CNN
F 3 "" H 10600 1600 50  0000 C CNN
	1    10600 1600
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 56C39BBD
P 10600 1700
F 0 "R4" V 10550 1550 50  0000 C CNN
F 1 "150" V 10600 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 1700 50  0001 C CNN
F 3 "" H 10600 1700 50  0000 C CNN
	1    10600 1700
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 56C39CF9
P 10600 2000
F 0 "R6" V 10550 1850 50  0000 C CNN
F 1 "150" V 10600 2000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 2000 50  0001 C CNN
F 3 "" H 10600 2000 50  0000 C CNN
	1    10600 2000
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 56C3B39A
P 10600 2100
F 0 "R7" V 10550 1950 50  0000 C CNN
F 1 "150" V 10600 2100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 2100 50  0001 C CNN
F 3 "" H 10600 2100 50  0000 C CNN
	1    10600 2100
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 56C3B4DC
P 10600 2200
F 0 "R8" V 10550 2050 50  0000 C CNN
F 1 "150" V 10600 2200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 2200 50  0001 C CNN
F 3 "" H 10600 2200 50  0000 C CNN
	1    10600 2200
	0    1    1    0   
$EndComp
$Comp
L R R10
U 1 1 56C3BB53
P 10600 2900
F 0 "R10" V 10550 2750 50  0000 C CNN
F 1 "150" V 10600 2900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 2900 50  0001 C CNN
F 3 "" H 10600 2900 50  0000 C CNN
	1    10600 2900
	0    1    1    0   
$EndComp
$Comp
L R R11
U 1 1 56C3BCAF
P 10600 3000
F 0 "R11" V 10550 2850 50  0000 C CNN
F 1 "150" V 10600 3000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 3000 50  0001 C CNN
F 3 "" H 10600 3000 50  0000 C CNN
	1    10600 3000
	0    1    1    0   
$EndComp
$Comp
L R R13
U 1 1 56C3C072
P 10600 3300
F 0 "R13" V 10550 3150 50  0000 C CNN
F 1 "150" V 10600 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 3300 50  0001 C CNN
F 3 "" H 10600 3300 50  0000 C CNN
	1    10600 3300
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 56C3C1D4
P 10600 3400
F 0 "R14" V 10550 3250 50  0000 C CNN
F 1 "150" V 10600 3400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 3400 50  0001 C CNN
F 3 "" H 10600 3400 50  0000 C CNN
	1    10600 3400
	0    1    1    0   
$EndComp
$Comp
L R R15
U 1 1 56C3C331
P 10600 3500
F 0 "R15" V 10550 3350 50  0000 C CNN
F 1 "150" V 10600 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 3500 50  0001 C CNN
F 3 "" H 10600 3500 50  0000 C CNN
	1    10600 3500
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 56C33D0E
P 10600 1800
F 0 "R5" V 10550 1650 50  0000 C CNN
F 1 "150" V 10600 1800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 1800 50  0001 C CNN
F 3 "" H 10600 1800 50  0000 C CNN
	1    10600 1800
	0    1    1    0   
$EndComp
$Comp
L R R12
U 1 1 56C341ED
P 10600 3100
F 0 "R12" V 10550 2950 50  0000 C CNN
F 1 "150" V 10600 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 3100 50  0001 C CNN
F 3 "" H 10600 3100 50  0000 C CNN
	1    10600 3100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR04
U 1 1 56C4FEF7
P 10750 2400
F 0 "#PWR04" H 10750 2150 50  0001 C CNN
F 1 "GND" H 10750 2250 50  0000 C CNN
F 2 "" H 10750 2400 50  0000 C CNN
F 3 "" H 10750 2400 50  0000 C CNN
	1    10750 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	1050 2600 1050 2650
Wire Wire Line
	4400 1950 4600 1950
Wire Wire Line
	8350 2050 8200 2050
Wire Wire Line
	10750 3900 10900 3900
Wire Wire Line
	10750 3800 10900 3800
Wire Wire Line
	10750 3700 10900 3700
Wire Wire Line
	10900 3600 10750 3600
Wire Wire Line
	10750 3500 10900 3500
Wire Wire Line
	10900 3400 10750 3400
Wire Wire Line
	10750 3300 10900 3300
Wire Wire Line
	10900 3000 10750 3000
Wire Wire Line
	10750 2900 10900 2900
Wire Wire Line
	10750 2500 10900 2500
Wire Wire Line
	10900 2400 10750 2400
Wire Wire Line
	10750 2300 10900 2300
Wire Wire Line
	10900 2200 10750 2200
Wire Wire Line
	10750 2100 10900 2100
Wire Wire Line
	10900 2000 10750 2000
Wire Wire Line
	10750 1700 10900 1700
Wire Wire Line
	10900 1600 10750 1600
Wire Wire Line
	10300 1900 10900 1900
Wire Wire Line
	10300 3200 10900 3200
Wire Wire Line
	10750 1800 10900 1800
Wire Wire Line
	10900 3100 10750 3100
Wire Wire Line
	10750 3600 10750 4000
Connection ~ 10750 3700
Connection ~ 10750 3800
Connection ~ 10750 4000
Connection ~ 10750 3900
Wire Wire Line
	10750 2300 10750 2600
Connection ~ 10750 2600
Connection ~ 10750 2500
Connection ~ 10750 2400
Wire Wire Line
	5750 3350 5900 3350
Text Label 5900 3350 0    39   ~ 0
X
Wire Wire Line
	5750 3450 5900 3450
Text Label 5900 3450 0    39   ~ 0
Y
Wire Wire Line
	8350 2650 8200 2650
Text Label 8200 2650 0    39   ~ 0
X
Wire Wire Line
	8350 2750 8200 2750
Text Label 8200 2750 0    39   ~ 0
Y
Wire Wire Line
	8350 2250 8200 2250
Text Label 8200 2250 0    39   ~ 0
R
Wire Wire Line
	8350 2350 8200 2350
Text Label 8200 2350 0    39   ~ 0
G
Wire Wire Line
	8350 2450 8200 2450
Text Label 8200 2450 0    39   ~ 0
B
Wire Wire Line
	8350 2550 8200 2550
Text Label 8200 2550 0    39   ~ 0
Int
Wire Wire Line
	7700 1900 7850 1900
Text Label 7850 1900 0    39   ~ 0
R
Wire Wire Line
	7700 2000 7850 2000
Text Label 7850 2000 0    39   ~ 0
G
Wire Wire Line
	7700 2100 7850 2100
Text Label 7850 2100 0    39   ~ 0
B
Wire Wire Line
	7700 2200 7850 2200
Text Label 7850 2200 0    39   ~ 0
Int
Wire Wire Line
	5750 2750 5900 2750
Text Label 5900 2750 0    39   ~ 0
SCLK
Wire Wire Line
	5750 2850 5900 2850
Text Label 5900 2850 0    39   ~ 0
!SYNC
Wire Wire Line
	5900 2950 5750 2950
Text Label 5900 2950 0    39   ~ 0
MOSI
Wire Wire Line
	6300 2150 6150 2150
Text Label 6150 2150 0    39   ~ 0
SCLK
Wire Wire Line
	6300 2250 6150 2250
Text Label 6150 2250 0    39   ~ 0
!SYNC
Wire Wire Line
	6300 2350 6150 2350
Text Label 6150 2350 0    39   ~ 0
MOSI
Wire Wire Line
	10450 1600 10300 1600
Text Label 10300 1600 0    39   ~ 0
+X
Wire Wire Line
	10450 1700 10300 1700
Text Label 10300 1700 0    39   ~ 0
+Y
Wire Wire Line
	10450 1800 10300 1800
Text Label 10300 1800 0    39   ~ 0
+Int
Wire Wire Line
	10450 2000 10300 2000
Text Label 10300 2000 0    39   ~ 0
+R
Wire Wire Line
	10450 2100 10300 2100
Text Label 10300 2100 0    39   ~ 0
+G
Wire Wire Line
	10450 2200 10300 2200
Text Label 10300 2200 0    39   ~ 0
+B
Wire Wire Line
	10450 2900 10300 2900
Text Label 10300 2900 0    39   ~ 0
-X
Wire Wire Line
	10450 3000 10300 3000
Text Label 10300 3000 0    39   ~ 0
-Y
Wire Wire Line
	10450 3100 10300 3100
Text Label 10300 3100 0    39   ~ 0
-Int
Wire Wire Line
	10450 3300 10300 3300
Text Label 10300 3300 0    39   ~ 0
-R
Wire Wire Line
	10450 3400 10300 3400
Text Label 10300 3400 0    39   ~ 0
-G
Wire Wire Line
	10450 3500 10300 3500
Text Label 10300 3500 0    39   ~ 0
-B
Wire Wire Line
	9350 1900 9500 1900
Text Label 9500 1900 0    39   ~ 0
+X
Wire Wire Line
	9350 2000 9500 2000
Text Label 9500 2000 0    39   ~ 0
+Y
Wire Wire Line
	9350 2100 9500 2100
Text Label 9500 2100 0    39   ~ 0
+R
Wire Wire Line
	9500 2200 9350 2200
Text Label 9500 2200 0    39   ~ 0
+G
Wire Wire Line
	9350 2300 9500 2300
Text Label 9500 2300 0    39   ~ 0
+B
Wire Wire Line
	9350 2400 9500 2400
Text Label 9500 2400 0    39   ~ 0
+Int
Wire Wire Line
	9350 2500 9500 2500
Text Label 9500 2500 0    39   ~ 0
-X
Wire Wire Line
	9350 2600 9500 2600
Text Label 9500 2600 0    39   ~ 0
-Y
Wire Wire Line
	9350 2700 9500 2700
Text Label 9500 2700 0    39   ~ 0
-R
Wire Wire Line
	9350 2800 9500 2800
Text Label 9500 2800 0    39   ~ 0
-G
Wire Wire Line
	9350 2900 9500 2900
Text Label 9500 2900 0    39   ~ 0
-B
Wire Wire Line
	9350 3000 9500 3000
Text Label 9500 3000 0    39   ~ 0
-Int
Text Label 10300 3200 0    39   ~ 0
Interlock
Text Label 10300 1900 0    39   ~ 0
Interlock
Wire Wire Line
	10750 4000 10900 4000
Wire Wire Line
	10750 2600 10900 2600
Text Label 10300 2800 0    39   ~ 0
Shutter_Out
Wire Wire Line
	3800 2250 3950 2250
Text Label 3950 2250 0    39   ~ 0
+9V
Wire Wire Line
	3800 2400 3950 2400
Text Label 3950 2400 0    39   ~ 0
-9V
Wire Wire Line
	3800 2550 3950 2550
Text Label 3950 2550 0    39   ~ 0
3.3V
Wire Wire Line
	3800 2700 3950 2700
Text Label 3950 2700 0    39   ~ 0
2.5V
Wire Wire Line
	750  2600 750  3350
Text Label 750  3350 0    39   ~ 0
VCC
Wire Wire Line
	4500 3350 4600 3350
Wire Wire Line
	4600 3500 4500 3500
Wire Wire Line
	2700 2300 2550 2300
Text Label 2550 2300 0    39   ~ 0
VCC
Wire Wire Line
	850  2600 850  2800
Text Label 850  2800 0    39   ~ 0
D-
Wire Wire Line
	950  2600 950  2750
Text Label 950  2750 0    39   ~ 0
D+
$Comp
L GND #PWR05
U 1 1 56ED04E3
P 1050 2650
F 0 "#PWR05" H 1050 2400 50  0001 C CNN
F 1 "GND" H 1050 2500 50  0000 C CNN
F 2 "" H 1050 2650 50  0000 C CNN
F 3 "" H 1050 2650 50  0000 C CNN
	1    1050 2650
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR06
U 1 1 56ED0A89
P 4600 2250
F 0 "#PWR06" H 4600 2000 50  0001 C CNN
F 1 "GND" H 4600 2100 50  0000 C CNN
F 2 "" H 4600 2250 50  0000 C CNN
F 3 "" H 4600 2250 50  0000 C CNN
	1    4600 2250
	0    1    1    0   
$EndComp
Text Label 4400 1950 0    60   ~ 0
3.3V
Wire Wire Line
	6300 1900 6150 1900
Text Label 6150 1900 0    39   ~ 0
2.5V
Wire Wire Line
	8350 1950 8200 1950
Wire Wire Line
	8350 2150 8200 2150
Text Label 8200 2150 0    39   ~ 0
-9V
Text Label 8200 2050 0    39   ~ 0
+9V
Wire Wire Line
	4200 3350 4100 3350
Text Label 4100 3350 0    39   ~ 0
D+
Wire Wire Line
	4200 3500 4100 3500
Text Label 4100 3500 0    39   ~ 0
D-
Wire Wire Line
	9350 3100 9500 3100
Text Label 9500 3100 0    39   ~ 0
Shutter_Out
Wire Wire Line
	6300 2000 6150 2000
Text Label 6150 2000 0    39   ~ 0
3.3V
Wire Wire Line
	5750 3750 5900 3750
Text Label 5900 3750 0    39   ~ 0
Shutter
Wire Wire Line
	8350 2950 8200 2950
Text Label 8200 2950 0    39   ~ 0
Shutter
Wire Wire Line
	8350 2850 8200 2850
Text Label 8200 2850 0    39   ~ 0
2.5V
Wire Wire Line
	4600 2450 4400 2450
Text Label 4400 2450 0    39   ~ 0
2.5V
$Comp
L Mounting_Hole U1
U 1 1 56FCCEBD
P 1650 850
F 0 "U1" H 1650 1100 60  0001 C CNN
F 1 "Mounting_Hole" H 1700 1000 60  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 1700 850 60  0001 C CNN
F 3 "" H 1700 850 60  0000 C CNN
	1    1650 850 
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole U3
U 1 1 56FCD90A
P 1900 850
F 0 "U3" H 1900 1100 60  0001 C CNN
F 1 "Mounting_Hole" H 1950 1000 60  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 1950 850 60  0001 C CNN
F 3 "" H 1950 850 60  0000 C CNN
	1    1900 850 
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole U4
U 1 1 56FCDA71
P 1900 1100
F 0 "U4" H 1900 1350 60  0001 C CNN
F 1 "Mounting_Hole" H 1950 1250 60  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 1950 1100 60  0001 C CNN
F 3 "" H 1950 1100 60  0000 C CNN
	1    1900 1100
	1    0    0    -1  
$EndComp
$Comp
L Mounting_Hole U2
U 1 1 56FCDBD8
P 1650 1100
F 0 "U2" H 1650 1350 60  0001 C CNN
F 1 "Mounting_Hole" H 1700 1250 60  0001 C CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3" H 1700 1100 60  0001 C CNN
F 3 "" H 1700 1100 60  0000 C CNN
	1    1650 1100
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 56FE8927
P 10600 2800
F 0 "R9" V 10550 2650 50  0000 C CNN
F 1 "150" V 10600 2800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10530 2800 50  0001 C CNN
F 3 "" H 10600 2800 50  0000 C CNN
	1    10600 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	10750 2800 10900 2800
Wire Wire Line
	10450 2800 10300 2800
$EndSCHEMATC
