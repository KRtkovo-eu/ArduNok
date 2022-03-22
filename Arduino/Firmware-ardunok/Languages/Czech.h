// Labels for MENU screen (corresponding bitmap from Bitmaps/Menu.h will be shown)
static const char* const LANG_MENUITEMS[10] PROGMEM = {
  (const char*) "Seriova kom.",
  (const char*) "Hodiny",
  (const char*) "Multimetr",
  (const char*) "Zvuky",
  (const char*) "Obrazky",
  (const char*) "Hry",
  (const char*) "Sluzby",
  (const char*) "Nastroje",
  (const char*) "Nastaveni",
  (const char*) "O zarizeni"
};

// Label for ENTER key - INFO: bottom border of the display is also baseline for this label - character descenders will not be shown
#define LANG_KEYSELECT "Zvolit"
#define LANG_KEYMENU "Menu"
#define LANG_KEYUNLOCK "Odemknout"
#define LANG_KEYNEXT "Dalsi"
#define LANG_KEYSHOW "Zobrazit"
#define LANG_KEYOK "OK"

// Labels for LOCK screen
#define LANG_KEYBOARDUNLOCK "Drzte Enter\npro odemknuti"
#define LANG_KEYBOARDLOCKED "Klavesnice\nuzamcena"
#define LANG_KEYBOARDUNLOCKED "Klavesnice\nodemcena"

// Labels for DESKTOP screen
#define LANG_SILENTMODE "Profil\ntichy"

// Labels for SERIAL LINE screens
#define LANG_SERIALSPEED "Rychlost\nseriove linky"
#define LANG_SERIALSPEEDINPUT "Rychlost (baud):"
#define LANG_SERIALMONSHOW "Sledovat\nseriovou linku"

// Labels for MULTIMETER screen
#define LANG_MULTIMETERINTVCC "interni napeti"
#define LANG_MULTIMETERVOLTUNITS "V"

// Labels for CLOCK screen
#define LANG_CLOCKSETTINGS "Nastaveni\nhodin"
#define LANG_CLOCKDIGITAL "Digitalni\nhodiny"
#define LANG_CLOCKANALOG "Analogove\nhodiny"
#define LANG_CLOCKINPUTLABEL "Cas:"
#define LANG_CLOCKSETTINGSDONE "Cas\nnastaven"
#define LANG_CLOCKISNOTSET "Cas\nneni\nnastaven"
#define LANG_CLOCKUPTIME "Doba\nzapnuti"

// Labels for SOUNDS screen
#define LANG_SOUNDSKEYTONES "Zvuk\ntlacitek"
#define LANG_SOUNDSALERTS "Zvuky vystrahy\na her"
#define LANG_SOUNDSBOOTSOUND "Prehrat zvuk\npri zapnuti"
#define LANG_SOUNDSSERIALMONMSG "Zvuk prichozi\nseriove komunikace"
#define LANG_PLAYRTTTLCOLLECTION "Galerie\nmelodii"
#define LANG_RTTTLCOMPOSER "Skladatel\nmelodii"

// Labels for DICE GAME screen
#define LANG_GAMEDICENAME "Hod\nkostkou"
#define LANG_KEYTHROW "Hod"

// Labels for Settings
#define LANG_SETTINGON "zapnuto"
#define LANG_SETTINGOFF "vypnuto"
#define LANG_SETTINGSDONE "Hotovo"
#define LANG_SETTINGSDEFAULT "Standardni"

// Other system labels
#define LANG_INPROGRESS "Neni\nhotovo"
#define LANG_VOID ""
#define LANG_VOIDTIME "--:--"
