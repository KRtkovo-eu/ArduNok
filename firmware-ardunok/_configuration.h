// Language settings
#include "lang_english.h"

// Intervals
#define BACKLIGHTPERIOD 10000  // backlight on after keypress in miliseconds
#define CHARGINGSCREENPERIOD 650  // loop between charging symbol on desktop in milliseconds
#define SERIALMONITORDELAY 10000 // if new incoming byte over serial after this delay in miliseconds elapsed, clear serial monitor

// Display settings
#define DISPLAYCONTRAST 65

// Default system settings
bool BEEPONKEYPRESS = true; // for beep on key press set on true
bool BOOTSOUND = true; // for boot sound set on true
bool SERIALMONMSGSOUND = true; // for received message sound in serial monitor set on true
bool LOOPCHARGING = true; // true = desktop is looping charging animation, false = show current battery level // TODO detect charging
byte DEVICEVOLUME = 4; // volume MAX = 4, MIN = 0
