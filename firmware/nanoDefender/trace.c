#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include "../simpleserial/simpleserial.h"


uint8_t sort(uint8_t* data, uint8_t dlen) {
  // int a = 10, b = 20, c;  
   
  // asm {  
  //     mov ax,a  
  //     mov bx,b
  // };
       
  trigger_high();
  asm (  
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t"
"add r5,r1\n\t"
"NOP\n\t"
"NOP\n\t"
//"mul r5,r5,r1\n\t" 
  );
  // asm{
  //   add ax,bx 
  // };
  trigger_low();
  // asm{
  //   mov c,ax 
  // };
  return 0;
}

int main(void) {

  // WARNING: Do not call verify and sort from the same python process
  // Just call one at a time

  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();
  simpleserial_addcmd('s', 0, sort);

  while(1) {
		simpleserial_get();
  }

  return 0;
}
