/*  Do not modify this file unless you are developing
 *  any features for the firmware.
 */

// Libraries
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <avr/sleep.h>
#include <OneButton.h>
#include <PlayRtttl.h>
#include <StopWatch.h>
#include <TrueRandom.h>

// Bitmaps
#include "Bitmaps/System.h"
#include "Bitmaps/Desktop.h"
#include "Bitmaps/Menu.h"

// Sounds
#include "Sounds/RTTTL_predefined.h"

// Used AdafruitGFX fonts
#include "Fonts/Picopixel.h"

// Used AdafruitGFX custom fonts
#include "Fonts/Nokia5ptBoldNumeric.h"
#include "Fonts/Nokia6ptBold.h"
#include "Fonts/Nokia6ptRegular.h"
#include "Fonts/Nokia12ptBold.h"
#include "Fonts/NokiaBigBold.h"
#include "Fonts/SegmentNumeric11.h"
#include "Fonts/SegmentNumeric21.h"

// Project files
#include "Helpers/avrHelper.h"
#include "Helpers/enums.h"
#include "Configuration/Defaults.h"
#include "Configuration/System.h"

// Games
#include "Games/ThrowDice.h"
