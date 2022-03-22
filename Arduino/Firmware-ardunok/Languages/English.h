// Labels for MENU screen (corresponding bitmap from Bitmaps/Menu.h will be shown)
static const char* const LANG_MENUITEMS[10] PROGMEM = {
  (const char*) "Serial line",
  (const char*) "Clock",
  (const char*) "Multimeter",
  (const char*) "Sounds",
  (const char*) "Pictures",
  (const char*) "Games",
  (const char*) "Services",
  (const char*) "Tools",
  (const char*) "Settings",
  (const char*) "About"
};

// Label for ENTER key - INFO: bottom border of the display is also baseline for this label - character descenders will not be shown
#define LANG_KEYSELECT "Select"
#define LANG_KEYMENU "Menu"
#define LANG_KEYUNLOCK "Unlock"
#define LANG_KEYNEXT "Next"
#define LANG_KEYSHOW "Show"
#define LANG_KEYOK "OK"

// Labels for LOCK screen
#define LANG_KEYBOARDUNLOCK "Hold Enter\nto unlock"
#define LANG_KEYBOARDLOCKED "Keypad\nlocked"
#define LANG_KEYBOARDUNLOCKED "Keypad\nactive"

// Labels for DESKTOP screen
#define LANG_SILENTMODE "Profile\nsilent"

// Labels for SERIAL LINE screens
#define LANG_SERIALSPEED "Serial line\nbaudrate"
#define LANG_SERIALSPEEDINPUT "Baudrate:"
#define LANG_SERIALMONSHOW "Monitor\nserial line"

// Labels for MULTIMETER screen
#define LANG_MULTIMETERINTVCC "internal Vcc"
#define LANG_MULTIMETERVOLTUNITS "V"

// Labels for CLOCK screen
#define LANG_CLOCKSETTINGS "Clock\nsettings"
#define LANG_CLOCKDIGITAL "Digital\nclock"
#define LANG_CLOCKANALOG "Analog\nclock"
#define LANG_CLOCKINPUTLABEL "Time:"
#define LANG_CLOCKSETTINGSDONE "Time\nis set"
#define LANG_CLOCKISNOTSET "Time\nnot set"
#define LANG_CLOCKUPTIME "Device\nuptime"

// Labels for SOUNDS screen
#define LANG_SOUNDSKEYTONES "Keypad\ntones"
#define LANG_SOUNDSALERTS "Warning and\ngame tones"
#define LANG_SOUNDSBOOTSOUND "Play sound\non boot"
#define LANG_SOUNDSSERIALMONMSG "Serial line\nalert tone"
#define LANG_PLAYRTTTLCOLLECTION "Ringtones\ngallery"
#define LANG_RTTTLCOMPOSER "Ringtone\ncomposer"

// Labels for DICE GAME screen
#define LANG_GAMEDICENAME "Throw\nhexagonal\ndice"
#define LANG_KEYTHROW "Throw"

// Labels for Settings
#define LANG_SETTINGON "On"
#define LANG_SETTINGOFF "Off"
#define LANG_SETTINGSDONE "Done"
#define LANG_SETTINGSDEFAULT "Standard"

// Other system labels
#define LANG_INPROGRESS "In\nprogress"
#define LANG_VOID ""
#define LANG_VOIDTIME "--:--"
