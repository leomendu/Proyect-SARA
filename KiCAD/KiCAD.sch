EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Device:Transformer_1P_1S T1
U 1 1 618E185A
P 2050 1300
F 0 "T1" H 2050 1800 50  0000 C CNN
F 1 "Transformer_1P_1S" H 2050 1650 50  0000 C CNN
F 2 "" H 2050 1300 50  0001 C CNN
F 3 "~" H 2050 1300 50  0001 C CNN
F 4 "X" H 2050 1300 50  0001 C CNN "Spice_Primitive"
F 5 "Transformer_1P_1S" H 2050 1300 50  0001 C CNN "Spice_Model"
F 6 "Y" H 2050 1300 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2050 1300
	1    0    0    -1  
$EndComp
$Comp
L Diode_Bridge:W04G D1
U 1 1 618E3D5C
P 2850 1300
F 0 "D1" H 2550 1100 50  0000 L CNN
F 1 "W04G" H 2550 1000 50  0000 L CNN
F 2 "Diode_THT:Diode_Bridge_Round_D9.8mm" H 3000 1425 50  0001 L CNN
F 3 "https://www.vishay.com/docs/88769/woo5g.pdf" H 2850 1300 50  0001 C CNN
	1    2850 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 618E8549
P 3250 1600
F 0 "C1" H 3368 1646 50  0000 L CNN
F 1 "2200u" H 3368 1555 50  0000 L CNN
F 2 "" H 3288 1450 50  0001 C CNN
F 3 "~" H 3250 1600 50  0001 C CNN
	1    3250 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 618E9314
P 3700 1750
F 0 "D2" V 3739 1632 50  0000 R CNN
F 1 "LED" V 3648 1632 50  0000 R CNN
F 2 "" H 3700 1750 50  0001 C CNN
F 3 "~" H 3700 1750 50  0001 C CNN
	1    3700 1750
	0    -1   -1   0   
$EndComp
$Comp
L pspice:VSOURCE V1
U 1 1 61905BA6
P 1150 1300
F 0 "V1" H 1378 1346 50  0000 L CNN
F 1 "311" H 1378 1255 50  0000 L CNN
F 2 "" H 1150 1300 50  0001 C CNN
F 3 "~" H 1150 1300 50  0001 C CNN
F 4 "V" H 1150 1300 50  0001 C CNN "Spice_Primitive"
F 5 "sin(0 311 50 0 0)" H 1150 1300 50  0001 C CNN "Spice_Model"
F 6 "Y" H 1150 1300 50  0001 C CNN "Spice_Netlist_Enabled"
	1    1150 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6190A455
P 1650 1650
F 0 "#PWR?" H 1650 1400 50  0001 C CNN
F 1 "GND" H 1655 1477 50  0000 C CNN
F 2 "" H 1650 1650 50  0001 C CNN
F 3 "" H 1650 1650 50  0001 C CNN
	1    1650 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6190BC5B
P 3700 1450
F 0 "R1" H 3770 1496 50  0000 L CNN
F 1 "1k" H 3770 1405 50  0000 L CNN
F 2 "" V 3630 1450 50  0001 C CNN
F 3 "~" H 3700 1450 50  0001 C CNN
	1    3700 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1100 1650 950 
Wire Wire Line
	1650 950  1150 950 
Wire Wire Line
	1150 950  1150 1000
Wire Wire Line
	1150 1600 1150 1650
Wire Wire Line
	1150 1650 1650 1650
Wire Wire Line
	1650 1650 1650 1500
Wire Wire Line
	2850 1600 2850 1650
Wire Wire Line
	2850 1650 2450 1650
Wire Wire Line
	2450 1650 2450 1500
Wire Wire Line
	2850 1000 2850 950 
Wire Wire Line
	2850 950  2450 950 
Wire Wire Line
	2450 950  2450 1100
Wire Wire Line
	3250 1900 3250 1750
Wire Wire Line
	3250 1900 2550 1900
Wire Wire Line
	2550 1900 2550 1300
Wire Wire Line
	3150 1300 3250 1300
Wire Wire Line
	3250 1300 3250 1450
Wire Wire Line
	3250 1300 3700 1300
Connection ~ 3250 1300
Wire Wire Line
	3700 1900 3250 1900
Connection ~ 3250 1900
Connection ~ 1650 1650
$Comp
L Converter_DCDC:Mini360 U1
U 1 1 619139E2
P 4450 1600
F 0 "U1" H 4450 1925 50  0000 C CNN
F 1 "Mini360" H 4450 1834 50  0000 C CNN
F 2 "" H 4400 1750 50  0001 C CNN
F 3 "" H 4400 1750 50  0001 C CNN
	1    4450 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1300 4100 1300
Wire Wire Line
	4100 1300 4100 1500
Connection ~ 3700 1300
Wire Wire Line
	3700 1900 4100 1900
Wire Wire Line
	4100 1900 4100 1700
Connection ~ 3700 1900
$Comp
L Driver_Motor:L298-shield U2
U 1 1 6191C1CA
P 6150 1950
F 0 "U2" H 6150 2575 50  0000 C CNN
F 1 "L298-shield" H 6150 2484 50  0000 C CNN
F 2 "" H 6150 2550 50  0001 C CNN
F 3 "" H 6150 2550 50  0001 C CNN
	1    6150 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1600 5700 1600
$Comp
L Device:R R3
U 1 1 61923C74
P 5450 1750
F 0 "R3" H 5520 1796 50  0000 L CNN
F 1 "2k2" H 5520 1705 50  0000 L CNN
F 2 "" V 5380 1750 50  0001 C CNN
F 3 "~" H 5450 1750 50  0001 C CNN
	1    5450 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 61924F5F
P 5200 1750
F 0 "R2" H 5270 1796 50  0000 L CNN
F 1 "2k2" H 5270 1705 50  0000 L CNN
F 2 "" V 5130 1750 50  0001 C CNN
F 3 "~" H 5200 1750 50  0001 C CNN
	1    5200 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 1600 5450 1600
Connection ~ 5700 1600
Connection ~ 5450 1600
Wire Wire Line
	5450 1600 5200 1600
Wire Wire Line
	5200 1900 5200 2000
Wire Wire Line
	5450 1900 5450 2100
Connection ~ 5450 1900
Wire Wire Line
	5200 2000 5200 2100
Connection ~ 5200 2000
$Comp
L Switch:SW_Push SW2
U 1 1 6192B779
P 5200 2300
F 0 "SW2" V 5100 2550 50  0000 R CNN
F 1 "SW_Push" V 5350 2650 50  0000 R CNN
F 2 "" H 5200 2500 50  0001 C CNN
F 3 "~" H 5200 2500 50  0001 C CNN
	1    5200 2300
	0    -1   1    0   
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 6192E7F3
P 5450 2300
F 0 "SW3" V 5350 2550 50  0000 R CNN
F 1 "SW_Push" V 5600 2650 50  0000 R CNN
F 2 "" H 5450 2500 50  0001 C CNN
F 3 "~" H 5450 2500 50  0001 C CNN
	1    5450 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 1500 5750 1500
Wire Wire Line
	4800 2600 5200 2600
Wire Wire Line
	5450 2500 5450 2600
Connection ~ 5450 2600
Wire Wire Line
	5450 2600 5750 2600
Wire Wire Line
	5200 2500 5200 2600
Connection ~ 5200 2600
Wire Wire Line
	5200 2600 5450 2600
Wire Wire Line
	4800 1700 4800 2600
$Comp
L power:GND1 #PWR?
U 1 1 61933951
P 3250 1900
F 0 "#PWR?" H 3250 1650 50  0001 C CNN
F 1 "GND1" H 3255 1727 50  0000 C CNN
F 2 "" H 3250 1900 50  0001 C CNN
F 3 "" H 3250 1900 50  0001 C CNN
	1    3250 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND2 #PWR?
U 1 1 61934A17
P 5450 2600
F 0 "#PWR?" H 5450 2350 50  0001 C CNN
F 1 "GND2" H 5455 2427 50  0000 C CNN
F 2 "" H 5450 2600 50  0001 C CNN
F 3 "" H 5450 2600 50  0001 C CNN
	1    5450 2600
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC_ALT M1
U 1 1 61937091
P 6950 1750
F 0 "M1" H 7097 1746 50  0000 L CNN
F 1 "Motor_DC_ALT" H 7097 1655 50  0000 L CNN
F 2 "" H 6950 1660 50  0001 C CNN
F 3 "~" H 6950 1660 50  0001 C CNN
	1    6950 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1850 6750 1850
Wire Wire Line
	6750 1850 6750 2050
Wire Wire Line
	6750 2050 6950 2050
Wire Wire Line
	6550 1750 6750 1750
Wire Wire Line
	6750 1750 6750 1550
Wire Wire Line
	6750 1550 6950 1550
Connection ~ 5750 2600
Wire Wire Line
	5750 2200 5750 2300
Wire Wire Line
	6550 2150 6550 2600
Wire Wire Line
	5750 2400 5750 2600
Wire Wire Line
	6550 2050 6550 2150
Connection ~ 6550 2150
Wire Wire Line
	5750 2600 6150 2600
Wire Wire Line
	5750 2300 5750 2400
Connection ~ 5750 2300
Connection ~ 5750 2400
Wire Wire Line
	5700 1800 5750 1800
Wire Wire Line
	5700 1600 5700 1800
Wire Wire Line
	5450 1900 5750 1900
Wire Wire Line
	5200 2000 5750 2000
Wire Wire Line
	6150 2550 6150 2600
Connection ~ 6150 2600
Wire Wire Line
	6150 2600 6550 2600
$EndSCHEMATC
