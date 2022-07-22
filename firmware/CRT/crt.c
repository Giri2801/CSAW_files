#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include "../simpleserial/simpleserial.h"

void mult64to128(uint64_t op1, uint64_t op2, uint64_t *hi, uint64_t *lo)
{
    uint64_t u1 = (op1 & 0xffffffff);
    uint64_t v1 = (op2 & 0xffffffff);
    uint64_t t = (u1 * v1);
    uint64_t w3 = (t & 0xffffffff);
    uint64_t k = (t >> 32);

    op1 >>= 32;
    t = (op1 * v1) + k;
    k = (t & 0xffffffff);
    uint64_t w1 = (t >> 32);

    op2 >>= 32;
    t = (u1 * op2) + k;
    k = (t >> 32);

    *hi = (op1 * op2) + w1 + k;
    *lo = (t << 32) + w3;
}

uint64_t modular_mul(uint64_t a, uint64_t b, uint64_t mod) {
    uint64_t result = 0;
    for (uint64_t current_term = a; b; b >>= 1) {
        // if (b & 1) {
        //     result = (result + current_term) % mod;
        // }
        // if-else counter meausre
        // number of adds and mults no longer dependant on b&1
        uint64_t result1 = (result + current_term) % mod;
        uint64_t cnd = b & 1;
        result = result1*cnd + result*(1-cnd);
        current_term = 2 * current_term % mod;
    }
    return result;
}

// p = 137, q = 131, n = 137.131 = 17947, e = 3, d = 11787.
// m = 513
// c = 513**3 mod n = 8363.

// m = 8363**11787 mod 17947 = 513.

// dP = e**(-1) mod (p-1) = d mod (p-1) = 11787 mod 136 = 91
// dQ = e**(-1) mod (q-1) = d mod (q-1) = 11787 mod 130 = 87
// qInv = q-1 mod p = 131-1 mod 137 = 114
// m1 = c**dP mod p = 836391 mod 137 = 102
// m2 = c**dQ mod q = 836387 mod 131 = 120
// h = qInv.(m1 - m2) mod p = 114.(102-120+137) mod 137 = 3 [we add in an extra p here to keep the sum positive]
// m = m2 + h.q = 120 + 3.131 = 513.

uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    for (uint64_t current_factor = base; exp; exp >>= 1) {
        // if (exp & 1) {
        //     result = modular_mul(result, current_factor, mod);
        // }
        // if-else counter meausre
        // number of calls to modular_mul no longer dependant on exp&1
        uint64_t result1 = modular_mul(result, current_factor, mod);
        uint64_t cnd = exp & 1;
        result = result1*cnd + result*(1-cnd);
        current_factor = modular_mul(current_factor, current_factor, mod);
    }
    return result;
}

static void rsa(int x)
{
  // GOAL: Can you find P and Q?
  
  // ACTUAL VALUES HAVE BEEN REDACTED
  uint64_t p = 0x89;
  uint64_t q = 0x83;
  uint64_t dp = 0x5b;
  uint64_t dq = 0x57;

  /*********/
  uint64_t qinv = 0x72;
  /********/

  
  // // CRT Decryption
  uint64_t mp = mod_exp(x, dp, p);
  uint64_t mq = mod_exp(x, dq, q);


  // send only after full decryption
  /***************/
  uint64_t h = modular_mul(qinv,mp-mq+p,p);
  uint64_t low,high;
  //function to multiply 2 64 bit int
  mult64to128(h,q,&high,&low);
  if (mq + low < mq || mq + low < low ){
    high ++;
  }
  low = mq + low;
  /***************/


  uint8_t out[16];
  for (int i = 0; i < 8; i++) {
    out[i] = (low >> (8*i)) & 0xFF;
    out[i+8] = (high >> (8*i)) & 0xFF;
  }
  simpleserial_put('r', 16, out);
}

uint8_t rsa_init(uint8_t* data, uint8_t dlen)
{
  int ptxt = 0;
  for (int i = 0; i < dlen; i++) {
    ptxt += (data[i] << (i*8));
  }
  trigger_high();
  rsa(ptxt);
  trigger_low();

  return 0x00;
}

int main(void)
{
  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();

  simpleserial_addcmd('s', 4, rsa_init);

  while(1)
		simpleserial_get();
  return 0;
}
