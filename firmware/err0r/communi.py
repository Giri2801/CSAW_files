import chipwhisperer as cw
import matplotlib.pyplot as plt

n = 4
scope = cw.scope()
target = cw.target(scope)
scope.default_setup()
cw.program_target(scope, cw.programmers.STM32FProgrammer, "err0r/err0r-CWNANO.hex")
scope.adc.samples = 2000


msg = bytearray([])
scope.arm()
target.simpleserial_write('s',msg)
ret = scope.capture()
trace = scope.get_last_trace(as_int=True)
reply = target.simpleserial_read('r',n)
print(reply)
print(reply.decode())
print(scope.adc.clk_freq)
scope.dis()
target.dis()

plt.figure(figsize=(20,5))
plt.plot(trace)
plt.savefig('Traces3.svg', format='svg', dpi=1200)
plt.show()
