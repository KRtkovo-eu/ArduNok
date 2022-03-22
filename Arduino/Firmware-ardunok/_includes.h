#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <avr/sleep.h>
#include <OneButton.h>
#include <PlayRtttl.h>
#include <StopWatch.h>
#include <TrueRandom.h>

// Bitmaps
#include "bitmaps_system.h"
#include "bitmaps_desktop.h"
#include "bitmaps_menu.h"

// Sounds
#include "rtttl_predefined.h"

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
#include "avrHelper.h"
#include "enums.h"
#include "_configuration.h"
#include "_system_info.h"

// Games
#include "game_dice.h"
