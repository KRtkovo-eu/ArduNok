/*  Do not modify this file unless you are developing
 *  any features for the firmware.
 */

// Source: https://forum.arduino.cc/t/read-internal-voltage-referance/130996
long ReadInternalVccInt() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0) ;
  #else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif
  #if defined(__AVR_ATmega2560__)
    ADCSRB &= ~_BV(MUX5); // Without this the function always returns -1 on the ATmega2560
  #endif
  
  delay(3); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring
  
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both
  
  long result = (high<<8) | low;
  
  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}

unsigned int FSHlength(const __FlashStringHelper * FSHinput) {
  PGM_P FSHinputPointer = reinterpret_cast<PGM_P>(FSHinput);
  unsigned int stringLength = 0;
  while (pgm_read_byte(FSHinputPointer++)) {
    stringLength++;
  }
  return stringLength;
}

static bool CheckBatteryThreshold() {
  if(ReadInternalVccInt() <= 3600) {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_cpu();
    return true;
  }
  return false;
}