#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../simpleserial/simpleserial.h"

// DUMMY VAL
uint8_t secret[] = {85, 255, 0, 1};

uint8_t multiplier(uint8_t* data, uint8_t dlen)
{
  uint64_t user_data = 0;
  for (int i = 0; i < 4; i++) {
    user_data += ((uint64_t) data[i] << (8*(3-i)));
  }
  uint64_t prod = 0;

  trigger_high();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      uint8_t secret_bit = (secret[i] >> j) & 1;
      if (secret_bit) {
        prod += (user_data << (j+8*i));
      }
    }
  }
  trigger_low();

  uint8_t done[] = {'o','k'};
  simpleserial_put('r', 2, done);

  return 0x00;
}

uint8_t verify(uint8_t* data, uint8_t dlen) {
  uint8_t result = 1;
  for (int i = 0; i < dlen; i++) {
    result *= (secret[i] == data[i]);
  }
  simpleserial_put('r', 1, &result); // GOAL is to output 1
  return result;
}

int main(void) {

  // RESEARCH TEAMS: Do not use the '*' operator outside of index calculations
  
  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();

  simpleserial_addcmd('m', 4, multiplier);
  simpleserial_addcmd('a', 4, verify);

  while(1) simpleserial_get();

  return 0;
}

