#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static const uint16_t round_keys[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
  18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

// masked implementation of and
uint16_t and_with_mask(uint16_t x, uint16_t y){
    
    uint16_t xdd,ydd,xd,yd,zd,rz;
    uint16_t r0 = rand() & 0xFFFF;
    uint16_t r1 = rand() & 0xFFFF;

    xdd = x & r0;
    ydd = y & r1;

    xd = x ^ r0 ^ xdd;
    yd = y ^ r1 ^ ydd;

    zd = xd & yd;
    rz = (xdd ^ r0) & (yd ^ ydd) ^ xd & (r1 ^ ydd) ^ r1 & (xdd ^ r0);

    return zd ^ rz;

}

void simon_encrypt(uint16_t* ctxt) {
  const uint8_t rounds = 32;
  const uint16_t word_size = 16;

  for(uint8_t i = 0; i < rounds; i++) {
    if (i == 25) {
      trigger_high();
    }
    uint16_t r0 = rand() & 0xFFFF;
    uint16_t r1 = rand() & 0xFFFF;

    // mask the value of ctxt with random values
    ctxt[0] ^= r0;
    ctxt[1] ^= r1; 

    uint16_t rol_1 = (ctxt[1] << 1) | (ctxt[1] >> (word_size - 1));
    uint16_t rol_2 = (ctxt[1] << 2) | (ctxt[1] >> (word_size - 2));
    uint16_t rol_8 = (ctxt[1] << 8) | (ctxt[1] >> (word_size - 8));

    uint16_t rol1_r1 = (r1 << 1) | (r1 >> (word_size - 1));
    uint16_t rol1_r2 = (r1 << 2) | (r1 >> (word_size - 2));
    uint16_t rol1_r8 = (r1 << 8) | (r1 >> (word_size - 8));


    uint16_t temp = and_with_mask(rol_1,rol_8) ^ (ctxt[0]) ^ rol_2 ;
    uint16_t temp_mask = rol1_r2^r0^(rol1_r1 & rol1_r8)^(rol_1 & rol1_r8)^(rol_8 & rol1_r1);


    ctxt[0] = ctxt[1] ^ r1;
    ctxt[1] = temp ^ round_keys[i] ^ temp_mask;

    if (i == 25) {
      trigger_low();
    }
  }
}

void simon_encrypt2(uint16_t* ctxt) {
  const uint8_t rounds = 32;
  const uint16_t word_size = 16;

  for(uint8_t i = 0; i < rounds; i++) {
    uint16_t rol_1 = (ctxt[1] << 1) | (ctxt[1] >> (word_size - 1));
    uint16_t rol_2 = (ctxt[1] << 2) | (ctxt[1] >> (word_size - 2));
    uint16_t rol_8 = (ctxt[1] << 8) | (ctxt[1] >> (word_size - 8));

    uint16_t temp = (rol_1 & rol_8) ^ ctxt[0] ^ rol_2;
    ctxt[0] = ctxt[1];
    ctxt[1] = temp ^ round_keys[i];
  }
}

int main(){
    srand(time(NULL));
    uint16_t a = 5764;
    uint16_t b = 9365;
    printf("%d\n",a&b);
    
    printf("%d\n",and_with_mask(a,b));
}