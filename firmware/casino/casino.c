#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include "../simpleserial/simpleserial.h"

// Correct values but random permutation.
uint8_t arr[] = {10,20,30,40,50,60,70,80,90,100,110,120,130,140,150};

uint8_t verify(uint8_t* data, uint8_t dlen) {
  uint8_t result = 1;
  for (int i = 0; i < 15; i++) {
    result *= (arr[i] == data[i]);
  }
  simpleserial_put('r', 1, &result); // GOAL is to output 1
  return result;
}

// verify if val is present in data array
uint8_t verify1(uint8_t* data, uint8_t dlen,uint8_t val) {
  uint8_t is_present = 0x0;
  //generate a random number and use it mask the data
  uint8_t r = rand() & 0xFF;
  for(int i=0;i<dlen;i++){
    data[i]^=r;
  }
  val ^= r;
  for (int i = 0; i < dlen; i++) {
      is_present |= (data[i]==val); 
  }
  // unmask data
  for(int i=0;i<dlen;i++){
    data[i]^=r;
  }
  return !is_present;
}

uint8_t permute(uint8_t* array,int n){
    srand(HAL_GetTick());
    uint8_t perm[256];
    for (int i = 0; i<n ; i++ )
        perm[i] = n;
        
    int k = 0;
    while(k<n){
        // generate a random number
        // if already present, skip
        // else add it to perm
        int m = rand();
        uint8_t j = m%n;
        uint8_t isok = verify1(perm,n,j);
        perm[k] = perm[k]*(1-isok) + j*isok;
        k = k + isok;
    }
    uint8_t temp[256];
    for(int i=0;i<n;i++){
        temp[i] = array[i];
    }
    // permute arr according to perm
    for(int i=0;i<n;i++){
        array[i]=temp[perm[i]];
    }
    return 0;
}

void draw(uint8_t* arr, int n) {
  volatile int x = 1234;
  // countermeasure
  // store a random permutation in arr_i
  // use that to index into arr
  uint8_t arr_i[256];
  for(int i=0;i<n;i++){
    arr_i[i] = i;
  }
  permute(arr_i,n);
  for (int i = 0; i < n; i++) {
    int i_ = arr_i[i];
    for (volatile int j = 0; j < arr[i_]; j++) {
      x = x * j;
    }
  }
}

// void draw(uint8_t* arr, int n) {
//   volatile int x = 1234;
//   for (int i = 0; i < n; i++) {
//     for (volatile int j = 0; j < arr[i]; j++) {
//       x = x * j;
//     }
//   }
// }

uint8_t casino(uint8_t* data, uint8_t dlen) {
  trigger_high();
  int n = sizeof(arr)/sizeof(arr[0]);
  draw(arr, n);
  simpleserial_put('r', n, arr);
  trigger_low();
  return 0;
}

int main(void) {

  // WARNING: Do not call verify and casino from the same python process
  // Just call one at a time

  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();
  simpleserial_addcmd('a', 16, verify);
  simpleserial_addcmd('s', 0, casino);
  while(1) {
		simpleserial_get();
  }

  return 0;
}
