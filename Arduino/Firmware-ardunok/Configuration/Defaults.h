/*  In this file, you can modify any system default values.
 *   
 *  Those will be loaded when power is plugged into the device,
 *  and will be resetted (when changed from the device) on any
 *  device reset or power loss (as they are saved just in RAM).
 */

// Language settings
#include "../Languages/English.h"
/*  Select different language file only if that file is present.
 *  Currently only english is supported by the official firmware.
 *  Feel free to create your own translation and send us Pull Request!
 *  
 *  Be aware! Used custom fonts support ASCII characters only (not all of them) and do NOT support
 *  any special characters. Feel free to update the fonts which are included in the project
 *  with their source file for ArduinoFontCreator.exe (also included in Tools folder).
 */

// Intervals
#define BACKLIGHTPERIOD 10000  // backlight on after keypress in miliseconds
#define CHARGINGSCREENPERIOD 650  // loop between charging symbol on desktop in milliseconds
#define SERIALMONITORDELAY 10000 // if new incoming byte over serial after this delay in miliseconds elapsed, clear serial monitor

// Display settings
#define DISPLAYCONTRAST 65 
/*  65 is maximum value to have usable display, larger values are too dim (quality of new chinese "Nokia" displays varies so it could be completely different in your case).
 *  You can use original Nokia display which is better in backlight and visible pixels.
 */

// Default system settings
bool BEEPONKEYPRESS = true; // for beep on key press set on true
bool ALERTBEEPS = true; // for alert and game beeps set on true
bool BOOTSOUND = true; // for boot sound set on true
bool SERIALMONMSGSOUND = true; // for received message sound in serial monitor set on true
bool LOOPCHARGING = true; // true = desktop is looping charging animation, false = show current battery level // TODO detect charging
byte DEVICEVOLUME = 4; // volume MAX = 4, MIN = 0

long SERIALBAUDRATE = 9600;
/* 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 
 * 74880, 115200, 230400, 250000, 500000, 1000000, 2000000   
 */
  
