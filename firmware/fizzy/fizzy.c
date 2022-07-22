#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include "../simpleserial/simpleserial.h"

// DUMMY VAL
uint8_t arr[] = {2,1,0,8,9,7,6};
uint8_t n = 7;
uint8_t permute();
uint8_t verify(uint8_t* data, uint8_t dlen) {
  uint8_t zero = 0;
  uint8_t one = 1;
  for (int i = 0; i < n; i++) {
    if (arr[i] != data[i]) {
      simpleserial_put('r', 1, &zero);
      return 0x00;
    }
  }
  simpleserial_put('r', 1, &one); // GOAL
  return 0x01;
}

void swap(uint8_t *xp, uint8_t *yp) {
  uint8_t temp = *xp;
  *xp = *yp;
  *yp = temp;
}

uint8_t verify1(uint8_t* data, uint8_t dlen,uint8_t val) {
  uint8_t is_present = 0x0;
  for (int i = 0; i < dlen; i++) {
      is_present |= (data[i]==val);
  }
  return !is_present;
}

uint8_t permute(){
    srand(HAL_GetTick());
    uint8_t n = sizeof(arr)/sizeof(arr[0]);
    uint8_t perm[256];
    for (int i = 0; i<n ; i++ )
        perm[i] = n;
        
    int k = 0;
    while(k<n){
        int m = rand();
        uint8_t j = m%n;
        uint8_t isok = verify1(perm,n,j);
        perm[k] = perm[k]*(1-isok) + j*isok;
        k = k + isok;
    }
    uint8_t temp[256];
    for(int i=0;i<n;i++){
        temp[i] = arr[i];
    }
    for(int i=0;i<n;i++){
        arr[i]=temp[perm[i]];
    }
    return 0;
}



void super_efficient_sort(uint8_t* arr, int n) {
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
      if (arr[j] > arr[j+1]) {
        swap(&arr[j], &arr[j+1]);
      }
      // else {
      //   //dummy swap
      //   swap(&arr[j], &arr[j]);
      // }
    }
  }
}

uint8_t sort(uint8_t* data, uint8_t dlen) {
  trigger_high();
  // random wait to protect against the glitch that can
  // skip the permute or sort call
  // srand(HAL_GetTick());
  // uint32_t wait = rand()%100;
  // for( volatile uint32_t i = 0; i< wait;i++);

  // randomly permute the array before calling sort
  // permute();

  int n = sizeof(arr)/sizeof(arr[0]);
  super_efficient_sort(arr, n);

  // random wait to protect against the glitch that can
  // skip if condition
  wait = rand()%100;
  for( volatile uint32_t i = 0; i< wait;i++);
  if(!isSorted(arr, n)) return 0;
  
  simpleserial_put('r', n, arr);
  trigger_low();
  return 0;
}

int main(void) {

  // WARNING: Do not call verify and sort from the same python process
  // Just call one at a time

  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();
  simpleserial_addcmd('a', n, verify);
  simpleserial_addcmd('s', 0, sort);

  while(1) {
		simpleserial_get();
  }

  return 0;
}
