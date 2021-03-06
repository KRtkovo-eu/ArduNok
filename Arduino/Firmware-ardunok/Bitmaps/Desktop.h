/*  Do not modify this file unless you are developing
 *  any features for the firmware.
 */

#define INDICATORSLEVELCOUNT 5

// 'B0', 4x38px
static const unsigned char epd_bitmap_B0 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x60, 0xf0, 0x90, 0x90, 0x90, 0xf0
};
// 'B1', 4x38px
static const unsigned char epd_bitmap_B1 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 
  0x60, 0xf0, 0x90, 0x90, 0x90, 0xf0
};
// 'B2', 4x38px
static const unsigned char epd_bitmap_B2 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 
  0x60, 0xf0, 0x90, 0x90, 0x90, 0xf0
};
// 'B3', 4x38px
static const unsigned char epd_bitmap_B3 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 
  0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 
  0x60, 0xf0, 0x90, 0x90, 0x90, 0xf0
};
// 'B4', 4x38px
static const unsigned char epd_bitmap_B4 [] PROGMEM = {
  0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 
  0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 
  0x60, 0xf0, 0x90, 0x90, 0x90, 0xf0
};

static const unsigned char* const bitmap_batteryLevel_array[INDICATORSLEVELCOUNT] PROGMEM = {
	epd_bitmap_B0,
	epd_bitmap_B1,
	epd_bitmap_B2,
	epd_bitmap_B3,
	epd_bitmap_B4
};

// 'S0', 5x38px
static const unsigned char epd_bitmap_S0 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x48, 0x90, 0x48, 0x90, 0x48, 0x90
};
// 'S1', 5x38px
static const unsigned char epd_bitmap_S1 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 
  0x30, 0x50, 0x98, 0x98, 0x50, 0x30
};
// 'S2', 5x38px
static const unsigned char epd_bitmap_S2 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 
  0x30, 0x50, 0x98, 0x98, 0x50, 0x30
};
// 'S3', 5x38px
static const unsigned char epd_bitmap_S3 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
  0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 
  0x30, 0x50, 0x98, 0x98, 0x50, 0x30
};
// 'S4', 5x38px
static const unsigned char epd_bitmap_S4 [] PROGMEM = {
  0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
  0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 
  0x30, 0x50, 0x98, 0x98, 0x50, 0x30
};

static const unsigned char* const bitmap_volumeLevel_array[INDICATORSLEVELCOUNT] PROGMEM = {
  epd_bitmap_S0,
  epd_bitmap_S1,
  epd_bitmap_S2,
  epd_bitmap_S3,
  epd_bitmap_S4
};
