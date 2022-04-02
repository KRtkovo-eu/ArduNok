/*  Do not modify this file unless you are developing
 *  any features for the firmware.
 */

//
// Ring Tone Text Transfer Language (RTTTL) was developed by Nokia to be used to transfer ringtones to cellphone by Nokia.
// The RTTTL format is a string divided into three sections: name, default value, and data.
//
// The jintu section consists of a string describing the name of the ringtone. It can be no longer than 10 characters, and cannot contain a colon ":" character. (However, since the Smart Messaging specification allows names up to 15 characters in length, some applications processing RTTTL also do so.)
//
// The default value section is a set of values separated by commas, where each value contains a key and a value separated by an = character, which describes certain defaults which should be adhered to during the execution of the ringtone. Possible names are
//
// d - duration
// o - octave
// b - beat, tempo
// The data section consists of a set of character strings separated by commas, where each string contains a duration, pitch, octave and optional dotting (which increases the duration of the note by one half).
//
// Example:
// HauntHouse: d=4,o=5,b=108: 2a4,2e,2d#,2b4,2a4,2c,2d,2a#4,2e.,e,1f4,1a4,1d#,2e.,d,2c.,b4,1a4,1p,2a4,2e,2d#,2b4,2a4,2c,2d,2a#4,2e.,e,1f4,1a4,1d#,2e.,d,2c.,b4,1a4
//
// Part 1: name of the ringtone (here: "HauntHouse"), a string of characters represents the name of the ringtone
// Part 2: settings (here: d=4,o=5,b=108), where "d=" is the default duration of a note. In this case, the "4" means that each note with no duration specifier (see below) is by default considered a quarter note. "8" would mean an eighth note, and so on. Accordingly, "o=" is the default octave. There are four octaves in the Nokring/RTTTL format. And "b=" is the tempo, in "beats per minute".
// Part 3: the notes. Each note is separated by a comma and includes, in sequence: a duration specifier, a standard music note, either a, b, c, d, e, f or g, and an octave specifier. If no duration or octave specifier are present, the default applies.
//
// https://en.wikipedia.org/wiki/Ring_Tone_Text_Transfer_Language
//

static const char RtttlGameOver[] PROGMEM = "Game Over:d=32,o=4,b=320:8d,p,2a,p,8d,p,2a";
static const char RtttlGameWin[] PROGMEM = "Game Win:d=32,o=4,b=320:8d,4p,8d,p,8d,p,8d,p,2a,p,8d,p,2a";
static const char RtttlMessage[] PROGMEM = "Message:d=32,o=5,b=100:32c,32e,32g";
static const char RtttlBoot[] PROGMEM = "Scifi:d=32,o=4,b=245:4a#5,8a3.,8a5.,8a#3,8g#5,16b3.,16g5.,16c.,16f#5,16c#,16f5,16d,e5,d#,d#5,e,d5,f,c#5,f#,c5,g,b,g#,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,a#,a,1p.,1p.";

static const char Rtttl_0[] PROGMEM = "Grande valse:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a";
static const char Rtttl_1[] PROGMEM = "Ring ring:d=32,o=4,b=137:e,c5,e,c5,e,c5,e,c5,e,c5,16p.,e,c5,e,c5,e,c5,e,c5,e,c5,2p,2p,8p,e,c5,e,c5,e,c5,e,c5,e,c5,16p.,e,c5,e,c5,e,c5,e,c5,e,c5,2p,2p";
static const char Rtttl_2[] PROGMEM = "Low:d=32,o=3,b=240:a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,1p.,1p.,1p.,4p,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,a#,d#4,1p.,1p.,1p.";
static const char Rtttl_3[] PROGMEM = "Intro:d=32,o=5,b=137:g#,b,d#6,g#,b,d#6,g#,b,d#6,g#,b,d#6,g#,b,d#6,16p.,d#,g,a#,d#,g,a#,d#,g,a#,d#,g,a#,d#,g,a#,2p,2p,2p,8p,g#,b,d#6,g#,b,d#6,g#,b,d#6,g#,b,d#6,g#,b,d#6,16p.,d#,g,a#,d#,g,a#,d#,g,a#,d#,g,a#,d#,g,a#,2p,2p,2p";
static const char Rtttl_4[] PROGMEM = "Kick:d=32,o=6,b=193:8f4,p,f,16p,f,16p,8d#4,p,f,8p,8c#4,p,f,16p,f,16p,8c4,8p.,f,16p,f,16p,8f4,p,8d#4,p,f,8p,8c#4,p,f,16p,f,16p,4c4,2p,1p.,8p.,8f4,p,f,16p,f,16p,8d#4,p,f,8p,8c#4,p,f,16p,f,16p,8c4,8p.,f,16p,f,16p,8f4,p,8d#4,p,f,8p,8c#4,p,f,16p,f,16p,4c4,2p,1p.";
static const char Rtttl_5[] PROGMEM = "That's it!:d=32,o=5,b=106:b,16p.,f#,p,f#,p,g#,16p.,f#,8p.,a#,16p.,16b,p,4p,e6,16p.,b,p,b,p,c#6,16p.,b,8p.,d#6,16p.,16e6,p,4p.,2p,8p,b,16p.,f#,p,f#,p,g#,16p.,f#,8p.,a#,16p.,16b,p,4p,e6,16p.,b,p,b,p,c#6,16p.,b,8p.,d#6,16p.,16e6,p,4p.,2p";
static const char Rtttl_6[] PROGMEM = "Mozart 40:d=8,o=4,b=320:e,16d#.,32p,d#,p,e,16d#.,32p,d#,p,e,16d#.,32p,d#,p,4b,4p,b,a#,g#,p,g#,f#,e,p,e,d#,c#,p,4c#,4p,d#,16c#.,32p,c#,p,d#,16c#.,32p,c#,p,d#,16c#.,32p,c#,p,4a#,4p,a#,g#,g,p,g,e,d#,p,d#,c#,b3,p,4b3,4p,b,16a#.,32p,4a#,4c#5,4g,4a#,4g#,4d#,4p,b,16a#.,32p,4a#,4c#5,4g,4a#,4g#,4b,a#,g#,f#,e,4d#,4g,4g#,4a#,4b,c#5,b,4a#,4g#,4d#5,4p,2e5,4d#5,4p,2e5,4d#5,4p,2e5,4d#5,4e5,4d#5,4e5,16d#5,16e5,16d#5,16e5,16d#5,16e5,16d#5,16e5,16d#5,16e5,16d#5,16e5,16d#5,16e5,d#5,2p,1p.,2p";
static const char Rtttl_7[] PROGMEM = "Transylvania:d=8,o=5,b=614:32g4,g.,g#.,g.,d#.,c.,4p.,32g4,g.,g#.,g.,d#.,32d,c.,4p.,32g6,g.,g#.,g.,32f#,32f,32e,d#.,c.,32c#,32d,d#.,32d#6,g.,g#.,c6.,32d6,d#6.,32g,g6.,32f#4,f#.,g.,f#.,d.,b4.,4p.,32f#4,f#.,g.,f#.,d.,32c#,b4.,4p.,32f#6,f#.,g.,f#.,32f,32e,32d#,d.,b4.,32c,32c#,d.,32d6,f#.,g.,b.,32c#6,d6.,32f#,f#6.,32e4,d.,e.,c.,b4.,g4.,4p.,32e4,e.,g.,c.,b4.,32a4,g4.,4p.,32e6,e.,g.,c.,b4.,g4.,32a4,32a#4,b4.,32a6,c.,e.,a.,32a#,b.,32e,c6.,32f4,d.,e.,c.,a4.,f4.,4p.,32f4,c.,d.,b4.,a4.,32g4,f4.,4p.,32f6,b4.,d.,b4.,a4.,f4.,32g4,32g#4,a4.,32c6,b4.,d.,f.,32g,a.,d6.,1p.,1p.,1p.,1p.,32g4,g.,g#.,g.,d#.,c.,4p.,32g4,g.,g#.,g.,d#.,32d,c.,4p.,32g6,g.,g#.,g.,32f#,32f,32e,d#.,c.,32c#,32d,d#.,32d#6,g.,g#.,c6.,32d6,d#6.,32g,g6.,32f#4,f#.,g.,f#.,d.,b4.,4p.,32f#4,f#.,g.,f#.,d.,32c#,b4.,4p.,32f#6,f#.,g.,f#.,32f,32e,32d#,d.,b4.,32c,32c#,d.,32d6,f#.,g.,b.,32c#6,d6.,32f#,f#6.,32e4,d.,e.,c.,b4.,g4.,4p.,32e4,e.,g.,c.,b4.,32a4,g4.,4p.,32e6,e.,g.,c.,b4.,g4.,32a4,32a#4,b4.,32a6,c.,e.,a.,32a#,b.,32e,c6.,32f4,d.,e.,c.,a4.,f4.,4p.,32f4,c.,d.,b4.,a4.,32g4,f4.,4p.,32f6,b4.,d.,b4.,a4.,f4.,32g4,32g#4,a4.,32c6,b4.,d.,f.,32g,a.,d6.,1p.";
static const char Rtttl_8[] PROGMEM = "Toreador:d=16,o=4,b=80:8c5,d5.,32c5,a.,32p,a.,32p,a.,32g,a.,32a#,8a.,p,8a#,g.,32c5,8a.,p,8f,d.,32g,8c.,p,4g,g,d5,c5,a#,a,g,a,a#,8a.,p,8e,a.,32p,8a,g#.,32b,8e5.,e5,8e5,8e5,p,d5,c#5,d5,g,a,8a#,p,a,f,d5,4c5,p,f,c,a#,8a,8g,8f.,p,4p";
static const char Rtttl_9[] PROGMEM = "Hurdy-gurdy:d=32,o=4,b=137:16a#3,16p,f,c#,16p,a#,f#,16p,f,c#,8p.,f,c#,16p,a#,f#,16p,f,c#,8p.,f,c#,16p,a#,f#,16p,f,c#,p,e6,8f6,f,c#,16p,a#,f#,16c#6,f,c#,16c6,8a#5,f,c#,16p,a#,f#,16p,f,c#,16c6,8c#6,f,c#,16f6,a#,f#,16g#6,f,c#,16g6,8f6,f,c#,16p,a#,f#,16p,f,c#,p,g#6,8a#6,f,c#,16p,a#5,f#5,16g#6,f,c#,f6,e6,8d#6,f,c#,16p,a#,f#,16p,f,c#,16e6,8f6,f,c#,16a#5,a#,f#,16c#6,f,c#,16c6,8a#5,f,c#,16p,a#,f#,16p,f,c#,8a#3.,4p,2p,8p.";
static const char Rtttl_10[] PROGMEM = "Orient:d=32,o=5,b=80:16e.,a,b,c6,16e6.,d#6,e6,d#6,16c6.,b,c6,b,16a.,4p.,4p.,8p,16e.,a,b,c6,16d#6.,c6,d#6,c6,16b.,a,b,a,16g#.,4p.,4p.,16e.,f,g,a,16a#.,a,a#,a,16g.,f,g,f,16d#6.,c6,d#6,c6,16a#.,a,a#,a,16e6.,4p.,4p.,16e.,a,b,c6,16e6.,d#6,e6,d#6,16c6.,b,c6,b,16a.,4p.,4p.";
static const char Rtttl_11[] PROGMEM = "William Tell:d=8,o=4,b=320:16c.,32p,16c.,32p,c,p,16c.,32p,16c.,32p,c,p,16c.,32p,c,f,p,g,p,a,p,16c.,32p,16c.,32p,c,p,16c.,32p,16c.,32p,c,p,16a.,32p,a,g,p,e,p,c,p,16c.,32p,16c.,32p,c,p,16c.,32p,16c.,32p,c,p,16c.,32p,c,f,p,g,p,a,p,f,a,2c5,a#,a,g,f,p,a,p,f,1p.,1p.,4p.";

#define RTTTLPREDEFCOUNT 13
//Rtttl_0 is there twice because btnEnter.tick() while RTTTL collection playing is triggering the first melody too early so it skips to next - this is the cheapest fix
static const char* const RtttlPredefined[RTTTLPREDEFCOUNT] PROGMEM = {
  Rtttl_0, Rtttl_0, Rtttl_1, Rtttl_2, Rtttl_3, Rtttl_4, Rtttl_5, Rtttl_6, Rtttl_7, Rtttl_8, Rtttl_9,
  Rtttl_10, Rtttl_11
};
