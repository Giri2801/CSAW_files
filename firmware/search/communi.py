import chipwhisperer as cw
import matplotlib.pyplot as plt

n = 6
scope = cw.scope()
target = cw.target(scope)
scope.default_setup()
cw.program_target(scope, cw.programmers.STM32FProgrammer, "search/search-CWNANO.hex")
scope.adc.samples = 1000


'''msg = bytearray([128])
scope.arm()
target.simpleserial_write('s',msg)
ret = scope.capture()
trace = scope.get_last_trace(as_int=True)'''
msg1 = bytearray([113, 126, 52, 205, 204, 3])
target.simpleserial_write('a',msg1)
print(target.simpleserial_read('r',1))
msg_1 = bytearray([127])
scope.arm()
target.simpleserial_write('s',msg_1)
ret = scope.capture()
trace = scope.get_last_trace(as_int=True)

# reply = target.simpleserial_read('r',n)
# print(reply)
# lis = [int(b) for b in reply]
# print(lis)
# msg2 = bytearray([113, 126, 52, 205, 204, 3])
# target.simpleserial_write('a',msg2)
# print(target.simpleserial_read('r',1))
msg = bytearray([0])
scope.arm()
target.simpleserial_write('s',msg)
ret = scope.capture()
trace1 = scope.get_last_trace(as_int=True)
# reply = target.simpleserial_read('r',n)
print(scope.adc.clk_freq)
scope.dis()
target.dis()

fig, axs = plt.subplots(2, sharex=True, gridspec_kw={'hspace': 0})
axs[0].plot(trace)
axs[1].plot(trace1)
plt.show()
