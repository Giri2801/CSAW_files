#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../simpleserial/simpleserial.h"

#define ARR_LEN  5

int org_arr[ARR_LEN] = {-2,-1,0,1,2};
int arr[ARR_LEN] = {-2,-1,0,1,2};

uint8_t verify(uint8_t* data, uint8_t dlen) {
  uint8_t zero = 0, one = 1, err = -1;
  bool allmatch = true;
  int* data_int = (int*) data;

  if (dlen != sizeof(org_arr)) {
    simpleserial_put('r', 1, &err);
  }
  for (int i = 0; i < ARR_LEN; i++) {
    bool onematch = false;
    for (int j = 0; j < ARR_LEN; j++) {
      if (org_arr[i+j] == data_int[i]) {
        onematch = true;
      }
    }
    if (!onematch) {
      allmatch = false;
    }
  }
  if (allmatch) {
    simpleserial_put('r', 1, &one); // GOAL
  } else {
    simpleserial_put('r', 1, &zero);
  }
  return allmatch ? 0x01 : 0x00 ;
}

uint8_t init_arr(uint8_t* data, uint8_t dlen) {
  for (uint8_t t = 0; t < ARR_LEN; t++) {
    // org_arr[t] = t+1;
    arr[t] = org_arr[t];
  }
  return 0;
}

// void init_arr(void) {
//   for (uint8_t t = 0; t < ARR_LEN; t++) {
//     org_arr[t] = rand() * 987654321;
//     arr[t] = org_arr[t];
//   }
// }

uint8_t add(uint8_t* data, uint8_t dlen) {
  uint8_t scalar = 0;
  trigger_high();
  if (dlen == 1) {
    scalar = *data;
  }
  for (uint8_t i = 0; i < ARR_LEN; i++) {
    arr[i] += scalar;
  }
  trigger_low();
  return 0;
}

uint8_t sub(uint8_t* data, uint8_t dlen) {
  uint8_t scalar = 0;
  trigger_high();
  
  if (dlen == 1) {
    scalar = *data;
  }
  for (uint8_t i = 0; i < ARR_LEN; i++) {
    arr[i] -= scalar;
  }
  trigger_low();
  simpleserial_put('r', ARR_LEN, &arr);
  return 0;
}

uint8_t mult(uint8_t* data, uint8_t dlen) {
  uint8_t scalar = 1;
  trigger_high();
  if (dlen == 1) {
    scalar = *data;
  }
  for (uint8_t i=0; i<ARR_LEN; i++) {
    arr[i] *= scalar;
  }
  trigger_low();
  return 0;
}

uint8_t divisor(uint8_t* data, uint8_t dlen) {
  uint8_t scalar = 1;
  trigger_high();
  if (dlen == 1) {
    scalar = *data;
  }
  for (uint8_t i = 0; i < ARR_LEN; i++) {
    if (scalar != 0) {
      arr[i] /= scalar;
    }
  }
  trigger_low();
  return 0;
}



uint8_t dividend(uint8_t* data, uint8_t dlen) {


  uint8_t scalar = 1;

  trigger_high();
  
  if (dlen == 1) {
    scalar = *data;
  }
  for (uint8_t i = 0; i < ARR_LEN; i++) {
    int r = rand();
    
    if (arr[i] != 0) {
      int temp = r*arr[i];
      scalar*=r;
      arr[i]= scalar/temp;
    }
    else {
      int temp = r;
      scalar *= r;
      arr[i]*=scalar/temp;
    }
  }

  trigger_low();
  return 0;
}


uint8_t dividend_m(uint8_t* data, uint8_t dlen) {


  uint8_t scalar = 1;
  trigger_high();


  if (dlen == 1) {
    scalar = *data;
  }
  for (uint8_t i = 0; i < ARR_LEN; i++) {
    
    
    if (arr[i] != 0) {
      arr[i]= scalar/arr[i];
    }
    for (uint8_t i = 0; i < 10; i++)
      *data*=123;
  }


  trigger_low();
  return scalar;
}



int main(void) {
  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();

  int key = 0; // DUMMY VAL
  srand(key);
  // init_arr();

  simpleserial_addcmd('a', 12, verify);

  simpleserial_addcmd('q', 1, init_arr);
  simpleserial_addcmd('p', 1, add);
  simpleserial_addcmd('s', 1, sub);
  simpleserial_addcmd('m', 1, mult);
  simpleserial_addcmd('d', 1, divisor);
  simpleserial_addcmd('i', 1, dividend);
  simpleserial_addcmd('n', 1, dividend_m);
  while(1) {
    simpleserial_get();
  }
  return 0;
}
