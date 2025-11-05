#include "Arduino.h"
#include "wrappers.h"

/**
 * Wrapper for Arduino tone() function
 */
void w_tone(unsigned char pin, unsigned int frequency) {
  tone(pin, frequency);
}

/**
 * Wrapper for Arduino noTone() function
 */
 void w_noTone(unsigned char pin) {
  noTone(pin);
}
