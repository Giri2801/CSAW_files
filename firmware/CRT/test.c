#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
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

// int main(){
//     uint64_t a = 96247659919005988;
//     uint64_t b = 108402426248885997;
//     uint64_t low,high;
//     mult64to128(a,b,&high,&low);
//     printf("%lu ,%lu\n",high,low);


// }


int main()
{
    __uint128_t p = *(__int128*) "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f";
    printf("HIGH %016llx\n", (uint64_t) (p >> 64));
    printf("LOW  %016llx\n", (uint64_t) p);
    return 0;
}