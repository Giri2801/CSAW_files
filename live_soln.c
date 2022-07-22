#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../simpleserial/simpleserial.h"

// DUMMY VAL
uint8_t secret[] = {0, 255, 0, 1};

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
        isok = ~isok;
        isok += 1;
        perm[k] = perm[k]&(~isok) + j&isok;
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


uint8_t multiplier(uint8_t* data, uint8_t dlen)
{
  uint64_t user_data = 0;
  for (int i = 0; i < 4; i++) {
    user_data += ((uint64_t) data[i] << (8*(3-i)));
  }
  uint64_t prod = 0;

  trigger_high();
  // arr_i is used to index in first for loop
  // arr_j is used to index in second for loop
  uint8_t arr_i[4];
  uint8_t arr_j[8];
  for(uint8_t i = 0;i<4;i++){
    arr_i[i] = i;
  }
  for(uint8_t i = 0;i<8;i++){
    arr_j[i] = i;
  }
  // randomly permute arr_i
  permute(arr_i,4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      // randomly permute arr_j
      permute(arr_j,8);
      uint8_t secret_bit = (secret[i] >> j) & 1;
      secret_bit = ~secret_bit;
      secret_bit += 1;
//      if (secret_bit) {
//        prod += (user_data << (j+8*i));
//      }

      //replacing the leaking if condition with the assign statement in Line 95
      //Single instruction which executed each time doesn't reveal any extra information
      temp = prod + (user_data<<(j+8*i);
      prod = temp & secret_bit + prod & (~secret_bit);
    }
  }
  // the leaked secret bits cannnot be used to find the actual secet
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

