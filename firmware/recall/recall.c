#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../simpleserial/simpleserial.h"

// DUMMY VAL
uint8_t correct_mem[] = {158, 103, 80, 74, 112, 89, 140, 29, 192, 139, 103, 171, 25, 182, 68, 244};

uint8_t verify(uint8_t* data, uint8_t dlen) {
  uint8_t mem_different = 0;
  uint8_t zero = 0, one = 1;

  trigger_high();

  // mask data with a random value
  uint32_t seed = HAL_GetTick();
  srand(seed);
  uint8_t r = rand() & 0xFF;
  for(uint8_t i=0;i<sizeof(correct_mem); i++){
    correct_mem[i] ^= r;
    data[i]^=r;
  }
  for (uint8_t i = 0; i < sizeof(correct_mem); i++) {

    // if (correct_mem[i] != data[i]) {
    //   mem_different = 1;
    //   break;
    // }

    // counter measure: remove if else block
    mem_different |= (correct_mem[i] != data[i]); //2 2 3 4
  }
  // unmask data 
  for(uint8_t i=0;i<sizeof(correct_mem); i++){
    correct_mem[i] ^= r;
    data[i]^=r;
  }
  trigger_low();

  if (mem_different) {
    simpleserial_put('r', 1, &zero);
  } else {
    simpleserial_put('r', 1, &one); // GOAL
  }
}

int main(void) {
  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();

  simpleserial_addcmd('a', 16, verify);

  while(1) {
    simpleserial_get();
  }

  return 0;
}
