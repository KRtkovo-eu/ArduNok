// All included files and libraries are specified in _includes.h file, except language file which is set in Configuration/Defaults.h
#include "_includes.h"

// Declare LCD object for software SPI
Adafruit_PCD8544 display = Adafruit_PCD8544(PINDISPCLK, PINDISPDIN, PINDISPDC, PINDISPCE, PINDISPRST);

OneButton btnEnter = OneButton(
  PINBTNENTER,  // Input pin for the button
  true,        // Button is active LOW
  true         // Enable internal pull-up resistor
);
OneButton btnCancel = OneButton(PINBTNCANCEL, true, true);
OneButton btnUp = OneButton(PINBTNUP, true, true);
OneButton btnDown = OneButton(PINBTNDOWN, true, true);

bool batteryThresholdTriggered = false;

void setup()   {
  // Check battery level to prevent complete discharge
  if(CheckBatteryThreshold()) {
    batteryThresholdTriggered = true;
    return;
  }
  
  // Initialize Display
  display.begin();
  display.setFont(&Nokia6ptBold);
  display.setContrast(0);

  // Show blank screen (to prevent show the Adafruit flower)
  display.clearDisplay();
  display.display();
  
  // Set pins
  pinMode(PINBACKLIGHT, OUTPUT);
  pinMode(PINSPEAKER, OUTPUT);

  // Turn off backlight
  digitalWrite(PINBACKLIGHT, HIGH);

  // Buttons click events attachment
  btnEnter.attachClick(HandleEnterClick);
  btnCancel.attachClick(HandleCancelClick);
  btnUp.attachClick(HandleUpClick);
  btnDown.attachClick(HandleDownClick);

  btnEnter.attachLongPressStart(HandleEnterLongPress);
  btnCancel.attachLongPressStart(HandleCancelLongPress);
  
  btnUp.attachDuringLongPress(HandleUpDuringLongPress);
  btnDown.attachDuringLongPress(HandleDownDuringLongPress);
}

ScreenType currentScreenType = BlankSleep;
byte desktopBatteryLevel = 0;
byte menuScreenShown = 0;
byte submenuEntered = 0;
byte submenuItemsCount = 0;
bool keyboardLocked = false;

StopWatch stopWatchClock;
byte runHours = 0;
byte runMinutes = 0;
byte runSeconds = 0;
byte runHoursShift = 0;
byte runMinutesShift = 0;
byte runHoursShiftInput = 0;
byte runMinutesShiftInput = 0;
byte currentHours = 0;
byte currentMinutes = 0;

long checkIndexCurrent = 0;
byte gameDiceValue = 0;

void loop() {
  if(!batteryThresholdTriggered) {
    // Cancel button is used to wake the device from sleep
    btnCancel.tick();
    
    if(currentScreenType != BlankSleep) {
      char currentTimeText[5];
      sprintf (currentTimeText, "%02d%s%02d",
            currentHours, ":", currentMinutes);
      
      // Buttons etc.
      btnEnter.tick();
      btnUp.tick();
      btnDown.tick();
      HandleBacklight();
  
      // Display screen section
      LoopChargingScreens();
      UpdateDeviceTime();
  
      // Handle screens which are updated realtime
      switch(currentScreenType) {
        case Menu:
          display.clearDisplay();
          DisplayBitmap(epd_bitmap_nokia_menu_header, 0, 0, 84, 6);
          DisplayBitmap((unsigned char*)pgm_read_word(&(bitmap_menu_array[menuScreenShown])), 0, 23, 84, 15);
          display.setFont(&Nokia12ptBold);
          DisplayCenterString((char*)pgm_read_word(&(LANG_MENUITEMS[menuScreenShown])), 10, 2);

          // Show slider
          DisplaySlider(menuScreenShown, 0, false, submenuItemsCount);

          DisplayKeyLabel(LANG_KEYSELECT);
          display.display();
          break;
        case NetMonitor:
          HandleSerialMonitor();
          break;
        case SerialLineMenu:
          switch(submenuEntered) {
            case 0:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_SERIALMONSHOW, LANG_VOID, LANG_KEYSELECT);
              break;
            case 1:
              char serialBaudrateSpeedText[13];
              String(String(SERIALBAUDRATE) + " baud").toCharArray(serialBaudrateSpeedText, 13);
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_SERIALSPEED, serialBaudrateSpeedText, LANG_KEYSELECT);
              break;
          }
          break;
        case SerialLineSpeedInput:
          char serialBaudrateSpeedText[8];
          String(checkIndexCurrent).toCharArray(serialBaudrateSpeedText, 8);
          DisplayRangeInputScreen(LANG_SERIALSPEEDINPUT, serialBaudrateSpeedText, LANG_KEYOK);
          break;
        case DateTime:
          switch(submenuEntered) {
            // Set clock submenu
            case 0:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_CLOCKSETTINGS, stopWatchClock.isRunning() ? currentTimeText : LANG_VOIDTIME, LANG_KEYSELECT);
              break;
            // Digital clock submenu
            case 1:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_CLOCKDIGITAL, LANG_VOID, LANG_KEYSHOW);
              break;
            // Analog clock submenu
            case 2:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_CLOCKANALOG, LANG_VOID, LANG_KEYSHOW);
              break;
            // Device uptime
            case 3:
              unsigned long uptimeSecondsMillis = millis()/1000;
              byte uptimeHours = uptimeSecondsMillis/3600;
              int secsRemaining = uptimeSecondsMillis%3600;
              byte uptimeMinutes = secsRemaining/60;
              byte uptimeSeconds = secsRemaining%60;
              char uptimeText[10];
              sprintf (uptimeText, "%02d%s%02d%s%02d",
                uptimeHours, ":", uptimeMinutes, ":", uptimeSeconds);
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_CLOCKUPTIME, uptimeText, LANG_VOID);
              break;
            }
            break;
        case SettingInputClock:
          sprintf (currentTimeText, "%02d%s%02d",
            runHoursShiftInput, ":", runMinutesShiftInput);
          DisplayInputScreen(LANG_CLOCKINPUTLABEL, currentTimeText, LANG_KEYOK);
          break;
        case AnalogClock:
        case DigitalClock:
          DrawCurrentClock();
          break;
        case Desktop:
          // show correct battery level or charging animation
          display.clearDisplay();
          DisplayBitmap((unsigned char*)pgm_read_word(&(bitmap_batteryLevel_array[desktopBatteryLevel])), 80, 1, 4, 38);
    
          // show volume level
          DisplayBitmap((unsigned char*)pgm_read_word(&(bitmap_volumeLevel_array[DEVICEVOLUME])), 0, 1, 5, 38);
    
          // if keyboard locked, show lock symbol
          if(keyboardLocked) {
            display.drawBitmap(7, 0, epd_bitmap_symbol_lock, 13, 6, BLACK);
          }
    
          display.setFont(&Nokia5ptBoldNumeric);
          display.setCursor(50,1);
          if(stopWatchClock.isRunning()) {
            display.println(currentTimeText);
          }
          display.setFont(&Nokia6ptBold);
          
          DisplayCenterString(HWMANUFACTURER, 10);
          DisplayKeyLabel(keyboardLocked ? LANG_KEYUNLOCK : LANG_KEYMENU);
          display.display();
          break;
        case Multimeter:
          display.clearDisplay();
          
          char currentInternalVccArray[8];
          String("+" + String(double(ReadInternalVccInt())/1000)).toCharArray(currentInternalVccArray, 8);
    
          DisplayCenterString(LANG_MULTIMETERINTVCC, 0);
          display.setFont(&segmentNumeric21);
          DisplayCenterString(currentInternalVccArray, 16);
          display.setFont(&Nokia6ptBold);
          
          display.display();
          delay(50);
          break;
        case Sounds:
          switch(submenuEntered) {
            // Keypad tones
            case 0:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_SOUNDSKEYTONES, (BEEPONKEYPRESS ? LANG_SETTINGON : LANG_SETTINGOFF), LANG_KEYSELECT);
              break;
            // Alert beeps
            case 1:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_SOUNDSALERTS, (ALERTBEEPS ? LANG_SETTINGON : LANG_SETTINGOFF), LANG_KEYSELECT);
              break;
            // Boot sound
            case 2:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_SOUNDSBOOTSOUND, (BOOTSOUND ? LANG_SETTINGON : LANG_SETTINGOFF), LANG_KEYSELECT);
              break;
            // Received serial monitor message tone
            case 3:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_SOUNDSSERIALMONMSG, (SERIALMONMSGSOUND ? LANG_SETTINGSDEFAULT : LANG_SETTINGOFF), LANG_KEYSELECT);
              break;
            // Open RTTTL gallery
            case 4:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_PLAYRTTTLCOLLECTION, LANG_VOID, LANG_KEYSHOW);
              break;
            // Open RTTTL composer
            case 5:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_RTTTLCOMPOSER, LANG_VOID, LANG_KEYSELECT);
              break;
          }        
          break;
        case PicturesGallery:
          display.clearDisplay();
          DisplayBitmap((unsigned char*)pgm_read_word(&(bitmap_gallery_array[submenuEntered])), 0, 0, 84, 48);
          display.display();
          break;
        case Games:
          switch(submenuEntered) {
            case 0:
              DisplaySubmenuScreen(menuScreenShown, submenuEntered, LANG_GAMEDICENAME, LANG_VOID, LANG_KEYSELECT);
              break;
          }
          break;
        case GameDice:
          display.clearDisplay();
          DisplayBitmap((unsigned char*)pgm_read_word(&(epd_bitmap_game_dice_array[gameDiceValue])), 35, 12, 18, 18);
          DisplayKeyLabel(LANG_KEYTHROW);
          display.display();
          break;
        default:
          //default = case BlankSleep
          break;
      }
    }
  }
}



static void KeyPressSound(int frequencyShift = 0, int toneDurationShift = 0) {
  if(BEEPONKEYPRESS && DEVICEVOLUME > 0) {
    tone(PINSPEAKER, KEYPRESSTONEFREQUENCY + frequencyShift, KEYPRESSTONEDURATION + toneDurationShift);
  }
}
static void AlertBeepSound(int frequencyShift, int toneDurationShift) {
  if(ALERTBEEPS && DEVICEVOLUME > 0) {
    tone(PINSPEAKER, KEYPRESSTONEFREQUENCY + frequencyShift, KEYPRESSTONEDURATION + toneDurationShift);
  }
}

#define SLIDER_MAXTOP 8
#define SLIDER_MAXBOTTOM 32
static byte CalculateSliderPosition(byte currentItem, byte allItemsCount) {
  // if only 1 item is in list return SLIDER_MAXTOP
  if(allItemsCount == 1) {
    return SLIDER_MAXTOP;
  }
  // if current item is the last in the list return SLIDER_MAXBOTTOM
  byte pos = SLIDER_MAXTOP + (((int)(SLIDER_MAXBOTTOM / allItemsCount) - (allItemsCount > 9 ? 0.5 : 0)) * currentItem);
  return (currentItem == (allItemsCount - 1)) ? SLIDER_MAXBOTTOM : pos;
}

// without this function I was not able to correctly show PROGMEM bitmaps stored in array
static void DisplayBitmap(const unsigned char* bitmap) {
  DisplayBitmap(bitmap, 0, 0, DISPLAYRESX, DISPLAYRESY);
}
static void DisplayBitmap(const unsigned char* bitmap, byte x, byte y, byte width, byte height) {
  display.drawBitmap(x, y, bitmap, width, height, BLACK);
}

static void DisplayCenterString(const char *buf, byte y) {
  DisplayCenterString(buf, y, 0);
}
static void DisplayCenterString(const char *buf, byte y, byte xMoveLeft) {
    byte x = DISPLAYRESX / 2;
    int16_t x1, y1;
    uint16_t w, h;
    display.setTextWrap(false);
    display.getTextBounds(buf, 0, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor((x - w / 2) - xMoveLeft, y);
    display.println(buf);
}
static void DisplayRightString(const char *buf, byte y) {
  DisplayRightString(buf, y, 0);
}
static void DisplayRightString(const char *buf, byte y, byte xMoveLeft)
{
    byte x = DISPLAYRESX;
    int16_t x1, y1;
    uint16_t w, h;
    display.setTextWrap(false);
    display.getTextBounds(buf, 0, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(x - w - xMoveLeft, y);
    display.print(buf);
}
static void DisplayRightString(const __FlashStringHelper *text, byte y, byte xMoveLeft) {
  const byte textLength = FSHlength(text);
  char buffer[textLength + 1];
  memcpy_P(buffer, text, textLength + 1);  //+1 for the null terminator
  DisplayRightString(buffer, y, xMoveLeft);
}

static void DisplayKeyLabel(const char* keyLabel) {
  display.setFont(&Nokia6ptBold);
  DisplayCenterString(keyLabel, 41);
}

static void DisplaySuccessScreen(const char* successMessage) {
  display.clearDisplay();
  display.setFont(&NokiaBigBold);
  display.setCursor(0,6);
  display.println(successMessage);
  display.drawBitmap(59, 7, epd_bitmap_success0, 21, 20, BLACK);
  display.display();
  
  delay(50);
  AlertBeepSound(SUCCTONEFREQUENCYSHIFT, FAILTONEDURATIONSHIFT);
  delay(200);
  
  display.drawBitmap(59, 7, epd_bitmap_success1, 21, 20, BLACK);
  display.display();
  delay(250);
  
  display.drawBitmap(59, 7, epd_bitmap_success2, 21, 20, BLACK);
  display.display();
  delay(1500);
  
  display.setFont(&Nokia6ptBold);
}

static void DisplayInfoScreen(const char* infoMessage, bool isInfo) {
  display.clearDisplay();
  display.setFont(&NokiaBigBold);
  display.setCursor(0,6);
  display.println(infoMessage);
  isInfo ? display.drawBitmap(60, 7, epd_bitmap_info, 19, 23, BLACK) : display.drawBitmap(59, 7, epd_bitmap_stop, 20, 20, BLACK);
  display.display();

  if(isInfo) {
    AlertBeepSound(SUCCTONEFREQUENCYSHIFT, FAILTONEDURATIONSHIFT);
  }
  else {
    AlertBeepSound(FAILTONEFREQUENCYSHIFT, FAILTONEDURATIONSHIFT);
  }
  
  delay(1500);
  display.setFont(&Nokia6ptBold);
}

static void DisplayStopScreen(const char* stopMessage) {
  DisplayInfoScreen(stopMessage, false);
}

static void DisplaySlider(byte sliderPosition, byte sliderItemsCount) {
  byte sliderY = CalculateSliderPosition(sliderPosition, sliderItemsCount);
  display.drawFastVLine(81, 7, sliderY -7, BLACK);
  display.drawBitmap(80, sliderY, epd_bitmap_slider, 3, 5, BLACK);
  display.drawFastVLine(81, sliderY + 5, 33 - sliderY, BLACK);
  display.setFont(&Nokia6ptBold);
}
static void DisplaySlider(byte menuPosition, byte submenuPosition, bool hasSubmenu, byte sliderItemsCount) {
  display.setFont(&Nokia5ptBoldNumeric);
  char submenuPositionText[5];
  if(hasSubmenu) {
    sprintf (submenuPositionText, "%d%s%d",
        (menuPosition + 1), "-", (submenuPosition + 1));
  }
  else {
    sprintf (submenuPositionText, "%d",
        (menuPosition + 1));
  }
  DisplayRightString(submenuPositionText, 0, 1);
  
  DisplaySlider(hasSubmenu ? submenuPosition : menuPosition, sliderItemsCount);
}

static void DisplaySubmenuScreen(byte menuPosition, byte submenuPosition, const char* submenuItemText, const char* submenuItemValueText, const char* submenuKeyLabel) {
  display.clearDisplay();
  
  // Slider and item position
  DisplaySlider(menuPosition, submenuPosition, true, submenuItemsCount);

  // Screen values
  display.setCursor(0,7);
  display.println(submenuItemText);

  display.setFont(&Nokia6ptRegular);
  DisplayRightString(submenuItemValueText, 30, 10);

  display.setFont(&Nokia6ptBold);
  DisplayKeyLabel(submenuKeyLabel);

  display.display();
}

static void DisplayListmenuScreen(byte menuPosition, byte menuItemsCount, const char* item_0_text, const char* item_1_text, const char* item_2_text) {
  display.clearDisplay();

  display.drawBitmap(1, 0, epd_bitmap_select, 16, 6, BLACK);
  
  // Slider and item position
  DisplaySlider(menuPosition, 0, false, menuItemsCount);

  // Screen values
  display.setCursor(1, menuPosition == 0 ? 9 : 8);
  display.setTextColor(menuPosition == 0 ? WHITE : BLACK);
  if(menuPosition == 0) display.fillRect(0, 7, 78, 11, BLACK);
  display.println(item_0_text);

  display.setCursor(1, (menuPosition == 1 || menuPosition == 0) ? 19 : 18);
  display.setTextColor(menuPosition == 1 ? WHITE : BLACK);
  if(menuPosition == 1) display.fillRect(0, 17, 78, 11, BLACK);
  display.println(item_1_text);

  display.setCursor(1, menuPosition == 2 ? 29 : 30);
  display.setTextColor(menuPosition == 2 ? WHITE : BLACK);
  if(menuPosition == 2) display.fillRect(0, 27, 78, 11, BLACK);
  display.println(item_2_text);

  display.setTextColor(BLACK);
  DisplayKeyLabel(LANG_KEYSELECT);

  display.display();
}

static void DisplayInputScreen(const char* inputHeaderLabel, const char* inputValue, const char* keyLabel, bool isRange) {
  display.clearDisplay();
  display.drawBitmap(0, 0, epd_bitmap_symbol_write, 13, 6, BLACK);
  if(isRange) {
    display.drawBitmap(0, 16, epd_bitmap_range, 9, 22, BLACK);
  }
  
  display.setCursor(0, 7);
  display.println(inputHeaderLabel);
  
  display.drawRect(0, 16, 84, 22, BLACK);
  
  display.setFont(&NokiaBigBold);
  DisplayRightString(inputValue, 24, 3);
  
  display.setFont(&Nokia6ptBold);
  DisplayKeyLabel(keyLabel);
  display.display();
}
static void DisplayInputScreen(const char* inputHeaderLabel, const char* inputValue, const char* keyLabel) {
  DisplayInputScreen(inputHeaderLabel, inputValue, keyLabel, false);
}
static void DisplayRangeInputScreen(const char* inputHeaderLabel, const char* inputValue, const char* keyLabel) {
  DisplayInputScreen(inputHeaderLabel, inputValue, keyLabel, true);
}




static byte SetBatterySymbolScreen() {
  double currentVcc = (double(ReadInternalVccInt())/1000);
  byte selectedScreen = 0;

  if(currentVcc > 4.0) {
    selectedScreen = 4;
  }
  else if(currentVcc > 3.8 && currentVcc <= 4.0) {
    selectedScreen = 3;
  }
  else if(currentVcc > 3.6 && currentVcc <= 3.8) {
    selectedScreen = 2;
  }
  else {
    selectedScreen = 1;
  }

  return selectedScreen;
}
unsigned long startMillisChargingScreen;
static void LoopChargingScreens() {
  // Loop between charging screens
  unsigned long currentMillisChargingScreen = millis();  //get the current "time" (actually the number of milliseconds since the program started)

  if (currentMillisChargingScreen - startMillisChargingScreen >= CHARGINGSCREENPERIOD)  //test whether the period has elapsed
  {
    if(LOOPCHARGING) {
      if(desktopBatteryLevel == 4) {
        desktopBatteryLevel = 0;
      }
      else {
        desktopBatteryLevel++;
      }
    }
    else {
      desktopBatteryLevel = SetBatterySymbolScreen();
    }
    startMillisChargingScreen = currentMillisChargingScreen;
  }
}



char incomingByte; // for incoming serial data
char serialIncomingWord[32];
byte cursorX = 0;
byte cursorY = 0;
unsigned long startMillisSerial;
bool forceClearSerialMonitor = true;
static void ClearSerialMonitor() {
    forceClearSerialMonitor = false;
    display.clearDisplay();
    //display.drawBitmap(0, 0, epd_bitmap_serial, DISPLAYRESX, 7, BLACK);
    display.fillRect(0, 0, 84, 7, BLACK);
    
    display.setFont(&Picopixel);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    
    char serialBaudrateSpeedText[19];
    String("<< " + String(SERIALBAUDRATE) + " BAUD >>").toCharArray(serialBaudrateSpeedText, 19);
    DisplayCenterString(serialBaudrateSpeedText, 5);

    display.setTextColor(BLACK);

    cursorX = 0;
    cursorY = 12;

    // print cursor
    display.setCursor(cursorX, cursorY);
    display.print(F("_"));
    display.setCursor(cursorX, cursorY);
    display.display();
    display.setFont(&Nokia6ptBold);
}
static void HandleSerialMonitor() {
  if(forceClearSerialMonitor) {
    ClearSerialMonitor();
  }
  
  // handle serial line incoming bytes
  if (Serial.available()) {  
    // read the incoming byte:
    incomingByte = Serial.read();
    BacklightTurnOnOff(true);

    // clear serial monitor if defined interval elapsed
    unsigned long currentMillisSerial = millis();
    if (currentMillisSerial - startMillisSerial >= SERIALMONITORDELAY) {
      ClearSerialMonitor();
    }
    
    // say what you got:
    Serial.print(incomingByte);

    display.setFont(&Picopixel);
    
    // erase cursor on current position
    display.setTextColor(WHITE);
    display.print(F("_"));
    display.setTextColor(BLACK);
    display.setCursor(cursorX, cursorY);

    // display incoming byte
    display.print(incomingByte);

    // move cursor to the next position
    if((cursorX >= 78 && cursorY < 43)) {
      cursorX = 0;
      cursorY = cursorY + 6;
    }
    else {
      cursorX = cursorX + 4;
      if(incomingByte == 'I' || incomingByte == 'i') {
        cursorX = cursorX - 2;
      }
      if(incomingByte == 'f' || incomingByte == 'j' || incomingByte == 'r' || incomingByte == 'r') {
        cursorX = cursorX - 1;
      }
      if(incomingByte == 'N') {
        cursorX = cursorX + 1;
      }
      if(incomingByte == 'M' || incomingByte == 'm' || incomingByte == 'W' || incomingByte == 'w') {
        cursorX = cursorX + 2;
      }
    }

    if(incomingByte == '\n' && SERIALMONMSGSOUND && DEVICEVOLUME > 0) {
      playRtttlBlockingPGM(PINSPEAKER, RtttlMessage);
    }

    // print cursor
    display.setCursor(cursorX, cursorY);
    display.print(F("_"));
    display.setCursor(cursorX, cursorY);
    display.display();
    display.setFont(&Nokia6ptBold);

    if(cursorY >= 43) {
      forceClearSerialMonitor = true;
    }

    startMillisSerial = currentMillisSerial;

    // Handle incoming words over serial line
    if(incomingByte == '\n') {
      if(strcmp(serialIncomingWord, "info") == 0) {
        Serial.println("");
        Serial.println(F("Device informations:"));
        Serial.println(F("--------------------"));
        
        Serial.print(F("HW manufacturer: "));
        Serial.println(HWMANUFACTURER);
        
        Serial.print(F("HW model: "));
        Serial.println(HWMODEL);

        Serial.print(F("Product number: "));
        Serial.println(F("PROTOTYPE"));

        Serial.println("");
        
        Serial.print(F("Firmware model: "));
        Serial.println(FWMODEL);
        
        Serial.print(F("Firmware version: "));
        Serial.println(FWVERSION);
        
        Serial.print(F("Firmware date: "));
        Serial.println(FWDATE);

        Serial.println("");
        
        Serial.print(F("Display resolution X: "));
        Serial.print(DISPLAYRESX);
        Serial.println(F(" pixels"));
        
        Serial.print(F("Display resolution Y: "));
        Serial.print(DISPLAYRESY);
        Serial.println(F(" pixels"));

        Serial.print(F("Display color depth: "));
        Serial.println(F("Monochrome graphic"));
        
        Serial.println("");

        Serial.print(F("Sound: "));
        Serial.println(F("1-bit square wave"));

        Serial.println("");

        Serial.print(F("Internal voltage: "));
        Serial.print(String("+" + String(double(ReadInternalVccInt())/1000)));
        Serial.println(F("V (volts)"));
        Serial.print(F("Serial line speed: "));
        Serial.print(SERIALBAUDRATE);
        Serial.println(F(" baud"));
      }

      // reset char array
      memset(serialIncomingWord, '\0', sizeof(serialIncomingWord));
      Serial.println("");
    }
    else {
      if(isAlpha(incomingByte)) {
        strncat(serialIncomingWord, &incomingByte, 1);
      }
    }
  }
}

static void DrawClock(Adafruit_PCD8544 display, byte h, byte m, byte s)
{
  const byte r = 23;
  const double rot = -M_PI / 2;
  double x, y, x0, y0, anglerad;

  const byte xShift = DISPLAYRESX / 2;
  const byte yShift = DISPLAYRESY / 2;
  
  display.clearDisplay();
  
  display.drawBitmap(0, 0, epd_bitmap_clock, 84, 48, BLACK);

  // hour
  anglerad = 2 * M_PI / 12 * (h%12) + 2 * M_PI / 12 / 60 * m + rot;
  x = (r-15) *cos(anglerad);
  y = (r-15) * sin(anglerad);
  x0 = 0;
  y0 = 0;
  display.drawLine(xShift + x0, yShift + y0, xShift + x, yShift + y, BLACK);
  
  // minute
  anglerad = 2 * M_PI / 60 * m + rot;
  x = (r - 10) * cos(anglerad);
  y = (r - 10) * sin(anglerad);
  x0 = 0;
  y0 = 0;
  display.drawLine(xShift + x0, yShift + y0, xShift + x, yShift + y, BLACK);

  // second
  anglerad = 2 * M_PI / 60 * s + rot;
  x = (r - 5) * cos(anglerad);
  y = (r - 5) * sin(anglerad);
  x0 = 0;
  y0 = 0;
  display.drawLine(xShift + x0, yShift + y0, xShift + x, yShift + y, BLACK);

  display.display();  
}

unsigned long startMillisClock;
static void UpdateDeviceTime() {
  unsigned long runMillis = stopWatchClock.elapsed();
  
  if(runMillis - startMillisClock >= 1000) {
    unsigned long allSeconds = runMillis/1000;
    runHours = allSeconds/3600;
    int secsRemaining = allSeconds%3600;
    runMinutes = secsRemaining/60;
    runSeconds = secsRemaining%60;

    // Handle time shift set by user
    currentHours = runHours + runHoursShift;
    currentMinutes = runMinutes + runMinutesShift;

    // Handle shifted time overflow
    if(currentMinutes >= 60) {
      currentMinutes = currentMinutes - 60;
      currentHours++;
    }
    currentHours = currentHours % 24;

    startMillisClock = runMillis;
  }
}
static void DrawCurrentClock() {
 
  if(currentScreenType == AnalogClock) {
    DrawClock(display, currentHours, currentMinutes, runSeconds);
  }
  else {
    display.clearDisplay();
  
    char currentTimeText[5];
    sprintf (currentTimeText, "%02d%s%02d",
          currentHours, (runSeconds % 2) ? " " : ":", currentMinutes);
    
    display.setFont(&segmentNumeric21);
    DisplayCenterString(currentTimeText, 12, 0);

    display.display();
    display.setFont(&Nokia6ptBold);
  }
}

static void DrawBorder() {
  display.drawLine(0,0,3,0,BLACK);
  display.drawLine(0,0,0,3,BLACK);
  display.drawLine(0,47,3,47,BLACK);
  display.drawLine(0,47,0,44,BLACK);
  display.drawLine(83,0,80,0,BLACK);
  display.drawLine(83,0,83,3,BLACK);
  display.drawLine(83,47,80,47,BLACK);
  display.drawLine(83,47,83,44,BLACK);
}




unsigned long startMillisBacklight;
static void BacklightTurnOnOff(bool turnOn) {
  if(turnOn) {
    startMillisBacklight = millis();
  }
  digitalWrite(PINBACKLIGHT, turnOn ? LOW : HIGH);
}

static void HandleBacklight() {
  unsigned long currentMillisBacklight = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillisBacklight - startMillisBacklight >= BACKLIGHTPERIOD)  //test whether the period has elapsed
  {
    BacklightTurnOnOff(false);
    startMillisBacklight = currentMillisBacklight;
  }
}

//Handler function for a button click:
static bool HandleEveryClick(bool skipKeyboardLockCheck = false) {
  if(keyboardLocked && !skipKeyboardLockCheck) {
    display.clearDisplay();
    display.drawBitmap(65, 8, epd_bitmap_keyboard, 17, 21, BLACK);
    display.setFont(&NokiaBigBold);
    display.setCursor(0,6);
    display.println(LANG_KEYBOARDUNLOCK);
    display.display();
    display.setFont(&Nokia6ptBold);
    delay(2000);
    return true;
  }

  BacklightTurnOnOff(true);
  KeyPressSound();
  return false;
}

bool playRtttlForceBreak = false;
bool playRtttlRunning = false;
static void PlayPreviousRtttl() {
  if(checkIndexCurrent - 2 >= 0) {
    checkIndexCurrent = checkIndexCurrent - 2;
  }
  else {
    checkIndexCurrent = RTTTLPREDEFCOUNT - 2;
  }
  stopPlayRtttl();
}
static void PlayNextRtttl() {
  if(checkIndexCurrent == RTTTLPREDEFCOUNT - 1) {
    checkIndexCurrent = 0;
  }
  stopPlayRtttl();
}

static void HandleEnterClick() {
  if(HandleEveryClick()) {
    return;
  }
  
  Serial.println(F("Enter - OK!"));

  switch(currentScreenType) {
    case Desktop:
      currentScreenType = Menu;
      menuScreenShown = 0;
      submenuEntered = 0;
      submenuItemsCount = MENUITEMSCOUNT;
      break;
    case Menu:
      switch(menuScreenShown) {
        case 0:
          currentScreenType = SerialLineMenu;
          submenuItemsCount = 2;
          break;
        case 1:
          currentScreenType = DateTime;
          submenuItemsCount = 4;
          break;
        case 2:
          currentScreenType = Multimeter;
          break;
        case 3:
          currentScreenType = Sounds;
          submenuItemsCount = 6;
          break;
        case 4:
          currentScreenType = PicturesGallery;
          submenuItemsCount = BITMAPSGALLERYITEMSCOUNT;
          break;
        case 5:
          currentScreenType = Games;
          //submenuItemsCount = 1;
          break;
        case 9:
          display.clearDisplay();
          display.setFont(&Nokia12ptBold);
          display.setCursor(0,2);
          display.println(FWVERSION);
          display.setCursor(0,15);
          display.println(FWDATE);
          display.setCursor(0,28);
          display.println(FWMODEL);
          display.setFont();
          display.setCursor(0,40);
          display.println(F("(c)KRtkovo.eu"));
          display.setFont(&Nokia6ptBold);
          display.display();
          currentScreenType = FwInfo;
          break;
        default:
          DisplayStopScreen(LANG_INPROGRESS);
          break;
      }
      break;
    case SerialLineMenu:
      switch(submenuEntered) {
        case 0:
          currentScreenType = NetMonitor;
          break;
        case 1:
          checkIndexCurrent = SERIALBAUDRATE;
          currentScreenType = SerialLineSpeedInput;
          break;
      }
      break;
    case SerialLineSpeedInput:
      SERIALBAUDRATE = checkIndexCurrent;
      checkIndexCurrent = 0;
      currentScreenType = SerialLineMenu;
      
      Serial.end();
      Serial.begin(SERIALBAUDRATE);

      DisplaySuccessScreen(LANG_SETTINGSDONE);
      break;
    case DateTime:
      switch(submenuEntered) {
        case 0:
          runHoursShiftInput = currentHours;
          runMinutesShiftInput = currentMinutes;
          currentScreenType = SettingInputClock;
          break;
        case 1:
          currentScreenType = DigitalClock;
          if(!stopWatchClock.isRunning()) {
            DisplayInfoScreen(LANG_CLOCKISNOTSET, true);
          }
          break;
        case 2:
          currentScreenType = AnalogClock;
          if(!stopWatchClock.isRunning()) {
            DisplayInfoScreen(LANG_CLOCKISNOTSET, true);
          }
          break;
      }
      break;
    case Sounds:
      switch(submenuEntered) {
        case 0:
          BEEPONKEYPRESS = !BEEPONKEYPRESS;
          DisplaySuccessScreen(LANG_SETTINGSDONE);
          break;
        case 1:
          ALERTBEEPS = !ALERTBEEPS;
          DisplaySuccessScreen(LANG_SETTINGSDONE);
          break;
        case 2:
          BOOTSOUND = !BOOTSOUND;
          DisplaySuccessScreen(LANG_SETTINGSDONE);
          break;
        case 3:
          SERIALMONMSGSOUND = !SERIALMONMSGSOUND;
          DisplaySuccessScreen(LANG_SETTINGSDONE);
          break;
        case 4:
          if(DEVICEVOLUME == 0) {
            DisplayStopScreen(LANG_SILENTMODE);
          }
          else {
            currentScreenType = RTTTL;
            
            for(checkIndexCurrent = 0; checkIndexCurrent < RTTTLPREDEFCOUNT; checkIndexCurrent++) {
              if(playRtttlForceBreak) {
                playRtttlForceBreak = false;
                break;
              }
              playRtttlRunning = true;
              
              display.clearDisplay();
              display.drawBitmap(19, 12, epd_bitmap_playRtttl, 46, 27, BLACK);
              
              DisplaySlider(checkIndexCurrent, RTTTLPREDEFCOUNT);
      
              // Get ringtone name from RTTTL string
              char rtttlStringStart[32];
              strncpy_P(rtttlStringStart, (char*)pgm_read_word(&(RtttlPredefined[checkIndexCurrent])), 31);
              char* rtttlName = strtok(rtttlStringStart, ":");
      
              display.setFont(&Picopixel);
              display.setCursor(0,5);
              display.println(String(checkIndexCurrent == 0 ? 1 : checkIndexCurrent) + F(":"));
              
              display.setFont(&Nokia6ptBold);
              DisplayCenterString(rtttlName, 0);
              
              DisplayKeyLabel(LANG_KEYNEXT);
              
              display.display();
              
              startPlayRtttlPGM(PINSPEAKER, (char*)pgm_read_word(&(RtttlPredefined[checkIndexCurrent])));

              // While playing (non-blocking) RTTTL melody, check for buttons
              while (updatePlayRtttl()) {
                btnEnter.tick();
                btnCancel.tick();
                btnUp.tick();
                btnDown.tick();
              }

              // At the end of the collection, play again
              if(checkIndexCurrent == RTTTLPREDEFCOUNT - 1) {
                checkIndexCurrent = 0;
              }
            }
            playRtttlRunning = false;
          }
          break;
        case 5:
          DisplayStopScreen(LANG_INPROGRESS);
          break;
      }
      break;
    case RTTTL:
      PlayNextRtttl();
      break;
    case SettingInputClock:
      currentScreenType = DateTime;
      submenuItemsCount = 4;
      submenuEntered = 0;
      
      if(stopWatchClock.isRunning()) {
        stopWatchClock.reset();
      }
      stopWatchClock.start();

      runHoursShift = runHoursShiftInput;
      runMinutesShift = runMinutesShiftInput;
      
      DisplaySuccessScreen(LANG_CLOCKSETTINGSDONE);
      break;
    case Games:
      switch(submenuEntered) {
        // Throw dice game
        case 0:
          display.clearDisplay();
          DisplayBitmap(epd_bitmap_game_dice_intro_a);
          display.display();
          if(DEVICEVOLUME > 0 && ALERTBEEPS) {
            playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
          }
          delay(100);
          display.clearDisplay();
          DisplayBitmap(epd_bitmap_game_dice_intro_b);
          display.display();
          if(DEVICEVOLUME > 0 && ALERTBEEPS) {
            playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
          }
          delay(100);
          display.clearDisplay();
          DisplayBitmap(epd_bitmap_game_dice_intro_a);
          display.display();
          if(DEVICEVOLUME > 0 && ALERTBEEPS) {
            playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
          }
          delay(100);
          display.clearDisplay();
          DisplayBitmap(epd_bitmap_game_dice_intro_b);
          display.display();
          if(DEVICEVOLUME > 0 && ALERTBEEPS) {
            playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
          }
          delay(100);
          display.clearDisplay();
          DisplayBitmap(epd_bitmap_game_dice_intro_a);
          display.display();
          if(DEVICEVOLUME > 0 && ALERTBEEPS) {
            playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
            playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
            playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
          }
          delay(100);
          currentScreenType = GameDice;
          break;
      }
      break;
    case GameDice:
      display.clearDisplay();
      DisplayBitmap(epd_bitmap_game_dice_wait_a);
      display.display();
      if(DEVICEVOLUME > 0 && ALERTBEEPS) {
        playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
      }
      delay(150);
      display.invertDisplay(1);
      if(DEVICEVOLUME > 0 && ALERTBEEPS) {
        playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
      }
      delay(150);
      display.invertDisplay(0);
      if(DEVICEVOLUME > 0 && ALERTBEEPS) {
        playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
      }
      delay(150);
      display.invertDisplay(1);
      if(DEVICEVOLUME > 0 && ALERTBEEPS) {
        playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
      }
      delay(150);
      display.invertDisplay(0);
      if(DEVICEVOLUME > 0 && ALERTBEEPS) {
        playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
        playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
        playRtttlBlockingPGM(PINSPEAKER, GameDiceSound);
      }
    
      gameDiceValue = TrueRandom.random(1,7);
      break;
  }
}

static void HandleEnterLongPress() {
  HandleEveryClick(true);

  Serial.println(F("Long Enter - OK!"));
  switch(currentScreenType) {
    case Desktop:
      keyboardLocked = !keyboardLocked;
      Serial.println(keyboardLocked ? F("Keyboard locked") : F("Keyboard unlocked"));
      
      if(keyboardLocked) {
        display.clearDisplay();
        display.setFont(&NokiaBigBold);
        display.setCursor(0,6);
        display.println(LANG_KEYBOARDLOCKED);
        display.drawBitmap(58, 5, epd_bitmap_keyboard_locked0, 22, 26, BLACK);
        display.display();
        
        delay(50);
        AlertBeepSound(SUCCTONEFREQUENCYSHIFT, FAILTONEDURATIONSHIFT);
        delay(200);
        
        display.clearDisplay();
        display.setCursor(0,6);
        display.println(LANG_KEYBOARDLOCKED);
        display.drawBitmap(58, 5, epd_bitmap_keyboard_locked1, 22, 26, BLACK);
        display.display();
        
        delay(250);
        
        display.clearDisplay();
        display.setCursor(0,6);
        display.println(LANG_KEYBOARDLOCKED);
        display.drawBitmap(58, 5, epd_bitmap_keyboard_locked2, 22, 26, BLACK);
        display.display();
        
        delay(1500);
        
        display.setFont(&Nokia6ptBold);
        BacklightTurnOnOff(false);
      }
      else {
        DisplaySuccessScreen(LANG_KEYBOARDUNLOCKED);
      }
      break;
  }
}

static void HandleCancelClick() {
  if(currentScreenType != BlankSleep) {
    if(HandleEveryClick()) {
      return;
    }
    
    Serial.println(F("Cancel - OK!"));
    switch(currentScreenType) {
      case Menu:
        currentScreenType = Desktop;
        menuScreenShown = 0;
        break;
      case FwInfo:
      case DateTime:
      case Multimeter:
      case Sounds:
      case PicturesGallery:
      case Games:
      case SerialLineMenu:
        currentScreenType = Menu;
        submenuEntered = 0;
        submenuItemsCount = MENUITEMSCOUNT;
        break;
      case SerialLineSpeedInput:
        currentScreenType = SerialLineMenu;
        checkIndexCurrent = 0;
        break;
      case NetMonitor:
        currentScreenType = SerialLineMenu;
        forceClearSerialMonitor = true;
        break;
      case RTTTL:
        if(playRtttlRunning) {
          playRtttlForceBreak = true;
          stopPlayRtttl();
        }
        currentScreenType = Sounds;
        break;
      case SettingInputClock:
      case DigitalClock:
      case AnalogClock:
        currentScreenType = DateTime;
        break;
      case GameDice:
        currentScreenType = Games;
        gameDiceValue = 0;
        break;
    } 
  }
}

static void HandleCancelLongPress() {
  if(HandleEveryClick()) {
    return;
  }
  
  Serial.println(F("Long Cancel - OK!"));
  switch(currentScreenType) {
    // Wake the device from sleep - make the waking procedure
    case BlankSleep:
      BacklightTurnOnOff(true);
      
      // Begin the serial line communication
      Serial.begin(SERIALBAUDRATE);
      Serial.println(F("Device WakeUp OK!"));
      
      // Set correct contrast
      display.setContrast(DISPLAYCONTRAST);

      display.clearDisplay();
      display.fillScreen(BLACK);
      display.display();
      delay(750);

      display.clearDisplay();
      display.display();
      delay(750);
      
      // Show splash screen
      display.clearDisplay();
      DisplayBitmap((unsigned char*)pgm_read_word(&(bitmap_batteryLevel_array[SetBatterySymbolScreen()])), 80, 1, 4, 38);
      display.display();
      delay(1500);
      CheckBatteryThreshold();
      
      display.clearDisplay();
      DisplayBitmap(epd_bitmap_boot);
      display.display();

      // Play boot sound
      if(BOOTSOUND && DEVICEVOLUME > 0) {
        // Initial delay
        delay(250);
        playRtttlBlockingPGM(PINSPEAKER, RtttlBoot);  
      }
      else {
        delay(4000);
      }
      
      currentScreenType = Desktop;
      break;
    default:
      KeyPressSound();

      // Reset current menu positions
      menuScreenShown = 0;
      submenuEntered = 0;
      submenuItemsCount = 0;

      currentScreenType = BlankSleep;

      // Sleep device procedure
      display.setContrast(0);
      display.clearDisplay();
      display.display();
      BacklightTurnOnOff(false);

      // End serial line communication
      Serial.println(F("Device Sleep OK!"));
      Serial.end();
      break;
  }
}

static void HandleUpClick() {
  if(HandleEveryClick()) {
    return;
  }

  Serial.println(F("Up - OK!"));
  switch(currentScreenType) {
    case RTTTL:
      PlayPreviousRtttl();
      break;
    case Menu:
      // Cycle through menu
      (menuScreenShown == 0) ? menuScreenShown = (MENUITEMSCOUNT - 1) : menuScreenShown--;
      break;
    case DateTime:
    case Sounds:
    case PicturesGallery:
    case SerialLineMenu:
      (submenuEntered > 0) ? submenuEntered-- : submenuEntered = (submenuItemsCount - 1);
      break;
    case SerialLineSpeedInput:
      switch(checkIndexCurrent) {
        case 300:
          checkIndexCurrent = 1200;
          break;
        case 1200:
          checkIndexCurrent = 2400;
          break;
        case 2400:
          checkIndexCurrent = 4800;
          break;
        case 4800:
          checkIndexCurrent = 9600;
          break;
        case 9600:
          checkIndexCurrent = 19200;
          break;
        case 19200:
          checkIndexCurrent = 38400;
          break;
        case 38400:
          checkIndexCurrent = 57600;
          break;
        case 57600:
          checkIndexCurrent = 74880;
          break;
        case 74880:
          checkIndexCurrent = 115200;
          break;
        case 115200:
          checkIndexCurrent = 230400;
          break;
        case 230400:
          checkIndexCurrent = 250000;
          break;
        case 250000:
          checkIndexCurrent = 500000;
          break;
        case 500000:
          checkIndexCurrent = 1000000;
          break;
        case 1000000:
          checkIndexCurrent = 2000000;
          break;
        default:
          AlertBeepSound(FAILTONEFREQUENCYSHIFT, FAILTONEDURATIONSHIFT);
          break;
      }
      break;
    case SettingInputClock:
      if(runMinutesShiftInput < 59) {
        runMinutesShiftInput++;
      }
      else {
        runMinutesShiftInput = 0;
      }
      break;
    case Desktop:
      // TODO: Volume on buzzer or speaker
      //(DEVICEVOLUME < 3) ? DEVICEVOLUME++ : DEVICEVOLUME = 4;
      DEVICEVOLUME = 4;
      break;
  }
}

static void HandleUpDuringLongPress() {
  if(HandleEveryClick()) {
    return;
  }

  Serial.println(F("Long Up - OK!"));
  switch(currentScreenType) {
    
  }

  delay(500);
}

static void HandleDownClick() {
  if(HandleEveryClick()) {
    return;
  }
  
  Serial.println(F("Down - OK!"));
  switch(currentScreenType) {
    case RTTTL:
      PlayNextRtttl();
      break;
    case Menu:
      // Cycle through menu
      (menuScreenShown == MENUITEMSCOUNT - 1) ? menuScreenShown = 0 : menuScreenShown++;
      break;
    case DateTime:
    case Sounds:
    case PicturesGallery:
    case SerialLineMenu:
      (submenuEntered < (submenuItemsCount - 1)) ? submenuEntered++ : submenuEntered = 0;
      break;
    case SerialLineSpeedInput:
      switch(checkIndexCurrent) {
        case 1200:
          checkIndexCurrent = 300;
          break;
        case 2400:
          checkIndexCurrent = 1200;
          break;
        case 4800:
          checkIndexCurrent = 2400;
          break;
        case 9600:
          checkIndexCurrent = 4800;
          break;
        case 19200:
          checkIndexCurrent = 9600;
          break;
        case 38400:
          checkIndexCurrent = 19200;
          break;
        case 57600:
          checkIndexCurrent = 38400;
          break;
        case 74880:
          checkIndexCurrent = 57600;
          break;
        case 115200:
          checkIndexCurrent = 74880;
          break;
        case 230400:
          checkIndexCurrent = 115200;
          break;
        case 250000:
          checkIndexCurrent = 230400;
          break;
        case 500000:
          checkIndexCurrent = 250000;
          break;
        case 1000000:
          checkIndexCurrent = 500000;
          break;
        case 2000000:
          checkIndexCurrent = 1000000;
          break;
        default:
          AlertBeepSound(FAILTONEFREQUENCYSHIFT, FAILTONEDURATIONSHIFT);
          break;
      }
      break;
    case SettingInputClock:
      if(runHoursShiftInput < 23) {
        runHoursShiftInput++;
      }
      else {
        runHoursShiftInput = 0;
      }
      break;
    case Desktop:
      // TODO: Volume on buzzer or speaker
      //if(DEVICEVOLUME > 1) {
      //  DEVICEVOLUME--;
      //}
      //else {
        if(DEVICEVOLUME > 0) {
          // Set volume to 0
          DEVICEVOLUME = 0;
          // Then show success screen (fix bug with sound playing when silent mode is entered)
          DisplaySuccessScreen(LANG_SILENTMODE);
        }
      //}
      
      break;
  }
}

static void HandleDownDuringLongPress() {
  if(HandleEveryClick()) {
    return;
  }

  Serial.println(F("Long Down - OK!"));
  switch(currentScreenType) {
    
  }

  delay(500);
}
