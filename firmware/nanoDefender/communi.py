import chipwhisperer as cw
import matplotlib.pyplot as plt
import numpy as np

scope = cw.scope()
target = cw.target(scope)
scope.default_setup()
scope.adc.clk_freq = 20000000

cw.program_target(scope, cw.programmers.STM32FProgrammer, "trace-CWNANO.hex")
scope.adc.samples = 2000
msg = bytearray([])
scope.arm()
target.simpleserial_write('s',msg)
ret = scope.capture(poll_done=True)
trace = scope.get_last_trace(as_int=True)
print(scope.adc.clk_freq)
# print(f"adc rate: {scope.clock.adc_rate}")
scope.dis()
target.dis()


# scope = cw.scope()
# target = cw.target(scope)
# scope.default_setup()
# scope.adc.clk_freq *=2
# cw.program_target(scope, cw.programmers.STM32FProgrammer, "trace-CWNANO1.hex")
# scope.adc.samples = 700
# msg = bytearray([])
# scope.arm()
# target.simpleserial_write('s',msg)
# ret = scope.capture()
# trace2 = scope.get_last_trace(as_int=True)
# scope.dis()
# target.dis()

# scope = cw.scope()
# target = cw.target(scope)
# scope.default_setup()
# scope.adc.clk_freq *=2
# cw.program_target(scope, cw.programmers.STM32FProgrammer, "trace-CWNANO2.hex")
# scope.adc.samples = 700
# msg = bytearray([])
# scope.arm()
# target.simpleserial_write('s',msg)
# ret = scope.capture()
# trace3 = scope.get_last_trace(as_int=True)
# scope.dis()
# target.dis()

# lis1 = []
# for i in range(200):
#     lis1.append(trace[i+1]-trace[i])

# lis2 = []
# for i in range(200):    
#     lis2.append(trace2[i+1]-trace2[i])

# lis3 = []
# for i in range(200):   
#     lis3.append(trace3[i+1]-trace3[i])

# print(lis1)
# print(lis2)
# print(lis3)

# fig, ax = plt.subplots(3, sharex=True, sharey=True)
# # plt.ylim(0,250)

# ax[0].plot(trace)
# ax[0].set_ylim(0,250)

# ax[1].plot(trace2)
# ax[1].set_ylim(0,250)


# ax[2].plot(trace3)
# ax[2].set_ylim(0,250)




plt.figure(figsize=(20,5))
plt.plot(trace, '.-')
# plt.plot(trace2, '.-')
# plt.plot(trace3, '.-')
# np.savetxt('fizzy/trace_2108976_2.csv', trace, delimiter=',')
# plt.savefig('Traces3.svg', format='svg', dpi=1200)
plt.show()
