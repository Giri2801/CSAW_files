import chipwhisperer as cw
import matplotlib.pyplot as plt
import numpy as np

n = 1
scope = cw.scope()
target = cw.target(scope)
scope.default_setup()
cw.program_target(scope, cw.programmers.STM32FProgrammer, "NotSoAccessible/NotSoAccessible-CWNANO-true.hex")
scope.adc.samples = 3000


msg = bytearray([0x14,0x8d])
scope.arm()
target.simpleserial_write('a',msg)
# ret = scope.capture()
# trace = scope.get_last_trace(as_int=True)
reply = target.simpleserial_read('r',n)
lis = [int(b) for b in reply]
print(lis)
print(scope.adc.clk_freq)
scope.dis()
target.dis()

