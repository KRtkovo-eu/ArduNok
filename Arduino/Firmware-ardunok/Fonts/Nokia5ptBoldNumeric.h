const uint8_t Nokia5ptBoldNumericBitmaps[] PROGMEM =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x4E, 0x54, 0x40, 0x00, 0x00, 0x01, 
  0x0E, 0x10, 0x00, 0x00, 0x00, 0x00, 0x5A, 0x00, 0x30, 0x00, 0x00, 0x00, 
  0xD8, 0x11, 0x32, 0x64, 0x40, 0x39, 0xB6, 0xDB, 0x6C, 0xE0, 0x18, 0xE1, 
  0x86, 0x18, 0x60, 0x78, 0x30, 0xCE, 0x61, 0xF0, 0x78, 0x33, 0x83, 0x0D, 
  0xE0, 0x0C, 0x72, 0xDF, 0x0C, 0x30, 0x79, 0x07, 0x83, 0x0D, 0xE0, 0x39, 
  0x87, 0x9B, 0x6C, 0xE0, 0x7C, 0x31, 0x86, 0x30, 0xC0, 0x39, 0xB3, 0x9B, 
  0x6C, 0xE0, 0x39, 0xB6, 0xCF, 0x0C, 0xE0, 0x0D, 0x86, 0xC0, 0x0D, 0x82, 
  0xD0
};

const GFXglyph Nokia5ptBoldNumericGlyphs[] PROGMEM =
{
  { 0, 4, 7, 4, 0, 0 },  // 0x20 ' '
  { 0, 0, 0, 0, 0, 0 },  // 0x21 '!'
  { 0, 0, 0, 0, 0, 0 },  // 0x22 '"'
  { 0, 0, 0, 0, 0, 0 },  // 0x23 '#'
  { 0, 0, 0, 0, 0, 0 },  // 0x24 '$'
  { 0, 0, 0, 0, 0, 0 },  // 0x25 '%'
  { 0, 0, 0, 0, 0, 0 },  // 0x26 '&'
  { 0, 0, 0, 0, 0, 0 },  // 0x27 '''
  { 0, 0, 0, 0, 0, 0 },  // 0x28 '('
  { 0, 0, 0, 0, 0, 0 },  // 0x29 ')'
  { 4, 6, 7, 6, 0, 0 },  // 0x2A '*'
  { 10, 6, 7, 6, 0, 0 },  // 0x2B '+'
  { 16, 3, 8, 3, 0, 0 },  // 0x2C ','
  { 19, 3, 7, 3, 0, 0 },  // 0x2D '-'
  { 22, 3, 7, 3, 0, 0 },  // 0x2E '.'
  { 25, 4, 7, 4, 0, 0 },  // 0x2F '/'
  { 29, 6, 6, 6, 0, 0 },  // 0x30 '0'
  { 34, 6, 6, 6, 0, 0 },  // 0x31 '1'
  { 39, 6, 6, 6, 0, 0 },  // 0x32 '2'
  { 44, 6, 6, 6, 0, 0 },  // 0x33 '3'
  { 49, 6, 6, 6, 0, 0 },  // 0x34 '4'
  { 54, 6, 6, 6, 0, 0 },  // 0x35 '5'
  { 59, 6, 6, 6, 0, 0 },  // 0x36 '6'
  { 64, 6, 6, 6, 0, 0 },  // 0x37 '7'
  { 69, 6, 6, 6, 0, 0 },  // 0x38 '8'
  { 74, 6, 6, 6, 0, 0 },  // 0x39 '9'
  { 79, 3, 6, 3, 0, 0 },  // 0x3A ':'
  { 82, 3, 7, 3, 0, 0 }  // 0x3B ';'
};

const GFXfont Nokia5ptBoldNumeric PROGMEM =
{
  (uint8_t*) Nokia5ptBoldNumericBitmaps,
  (GFXglyph*) Nokia5ptBoldNumericGlyphs,
  0x20, 0x3B, 9
};

// Approx. 85 bytes
