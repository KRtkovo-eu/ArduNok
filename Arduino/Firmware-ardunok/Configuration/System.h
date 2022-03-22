/*  Do not modify this file unless you are developing
 *  any features for the firmware.
 * 
 *  To customize the firmware defaults for your device
 *  visit Configuration/Defaults.h file.
 */

// firmware info
#define FWVERSION "v00.02"
#define FWDATE "21-03-2022"
#define FWMODEL "PSB-1"

// hardware info
#define HWMANUFACTURER "SPACE"
#define HWMODEL "2560"
#define DISPLAYRESX 84 // display used is 84*48 pixels, corresponds to the Nokia 5110/3310/etc. with 5 lines of text
#define DISPLAYRESY 48 // firmware is currently NOT designed for 96*65 pixels display from Nokia 3410/7110 etc.

// buzzer config
#define KEYPRESSTONEFREQUENCY 900
#define KEYPRESSTONEDURATION 75
#define FAILTONEFREQUENCYSHIFT -450
#define FAILTONEDURATIONSHIFT 225
#define SUCCTONEFREQUENCYSHIFT 450

// Arduino pins configuration
/* default values are for Space 2560 shield
 */
#define PINDISPCLK 5 //5
#define PINDISPDIN 7 //7
#define PINDISPDC 9 //9
#define PINDISPCE 15 //15
#define PINDISPRST 11 //11

#define PINBACKLIGHT 3 //3
#define PINSPEAKER 13 //13

#define PINBTNENTER 38 //38
#define PINBTNCANCEL 36 //36
#define PINBTNUP 32 //32
#define PINBTNDOWN 34 //34
