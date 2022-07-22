import chipwhisperer as cw
import matplotlib.pyplot as plt
import numpy as np

n = 15
scope = cw.scope()
target = cw.target(scope)
scope.default_setup()
cw.program_target(scope, cw.programmers.STM32FProgrammer, "casino-CWNANO.hex")
scope.adc.samples = 50000


msg = bytearray([])
scope.arm()
target.simpleserial_write('s',msg)
ret = scope.capture()
trace = scope.get_last_trace(as_int=True)
reply = target.simpleserial_read('r',n)
lis = [int(b) for b in reply]
print(lis)
print(scope.adc.clk_freq)
scope.dis()
target.dis()
trace1 = trace
trace = np.array(trace)
trace = trace>250

thresh = 30
prev=-1
count = 1
for i in range(len(trace)):
    if trace[i] == 1:
        if i-prev >= thresh:
            if count>1:
                print(count)
            count=0
        prev=i
        count+=1

plt.figure(figsize=(20,5))
plt.plot(trace1)
plt.savefig('Traces3.svg', format='svg', dpi=1200)
plt.show()
