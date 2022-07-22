import chipwhisperer as cw
import matplotlib.pyplot as plt
import numpy as np
import pickle
from matplotlib.patches import Rectangle
n = 16
analyse = False
if not analyse :
    scope = cw.scope()
    target = cw.target(scope)
    scope.default_setup()
    cw.program_target(scope, cw.programmers.STM32FProgrammer, "homebrew-CWNANO.hex")
    scope.adc.samples = 6000


    msg = bytearray([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])
    scope.arm()
    target.simpleserial_write('e',msg)
    ret = scope.capture()
    trace = scope.get_last_trace(as_int=True)
    reply = target.simpleserial_read('r',n)
    lis = [int(b) for b in reply]
    print(lis)

    cw.program_target(scope, cw.programmers.STM32FProgrammer, "homebrew-CWNANO0.hex")
    scope.arm()
    target.simpleserial_write('e',msg)
    ret = scope.capture()
    trace1 = scope.get_last_trace(as_int=True)
    reply = target.simpleserial_read('r',n)
    lis = [int(b) for b in reply]
    print(lis)

    cw.program_target(scope, cw.programmers.STM32FProgrammer, "homebrew-CWNANO1.hex")
    scope.arm()
    target.simpleserial_write('e',msg)
    ret = scope.capture()
    trace2 = scope.get_last_trace(as_int=True)
    reply = target.simpleserial_read('r',n)
    lis = [int(b) for b in reply]
    print(lis)

    print(scope.adc.clk_freq)
    scope.dis()
    target.dis()

    # plt.figure(figsize=(20,5))
    # plt.plot(trace)
    # plt.savefig('Traces3.svg', format='svg', dpi=1200)
    # plt.show()
    thresh = 240
    fig, axs = plt.subplots(3, sharex=True, gridspec_kw={'hspace': 0})
    temp_trace = np.array(trace)>thresh
    for i in range(len(trace)):
        if temp_trace[i] and trace[i-1]<120:
            # print(i)
            rect = Rectangle((i, 0), 34, 256, facecolor='lightgrey')
            axs[0].add_patch(rect)
    print(np.sum(temp_trace))
    axs[0].plot(trace)
    temp_trace = np.array(trace1)>thresh
    for i in range(len(trace)):
        if temp_trace[i]:
            # print(i)
            rect = Rectangle((i, 0), 34, 256, facecolor='lightgrey')
            axs[1].add_patch(rect)
    print(np.sum(temp_trace))
    axs[1].plot(trace1)
    temp_trace = np.array(trace2)>thresh
    for i in range(len(trace)):
        if temp_trace[i]:
            # print(i)
            rect = Rectangle((i, 0), 34, 256, facecolor='lightgrey')
            axs[2].add_patch(rect)
    print(np.sum(temp_trace))
    axs[2].plot(trace2)
    plt.show()

    # with open('Homebrew', 'wb') as fp:
    #     pickle.dump(trace, fp)

    # with open('Homebrew1', 'wb') as fp:
    #     pickle.dump(trace1, fp)

    # with open('Homebrew2', 'wb') as fp:
    #     pickle.dump(trace2, fp)

if analyse :
    with open('Homebrew', 'rb') as fp:
        trace = pickle.load(fp)

    with open('Homebrew1', 'rb') as fp:
        trace1 = pickle.load(fp)

    with open('Homebrew2', 'rb') as fp:
        trace2 = pickle.load(fp)




    def dist(l1,l2):
        l1 = np.array(l1)
        l2 = np.array(l2)
        l1 = l1 - np.min(l1)
        l2 = l2 - np.min(l2)
        l1 = l1/np.max(l1)*100
        l2 = l2/np.max(l2)*100
        return np.sum(np.reciprocal((l1-l2)*(l1-l2)+0.001))

    pt0_s = 53
    pt0_e = 80
    len1 = pt0_e - pt0_s

    pt1_s = 112
    pt1_e = 135
    len2 = pt1_e - pt1_s

    pattern1 = trace1[pt0_s:pt0_e]
    pattern2 = trace2[pt1_s:pt1_e]

    lis1 = []
    for i in range(len(trace)-len1):
        curr = trace[i:i+len1]
        lis1.append(dist(curr,pattern1)/len1)

    lis2 = []
    for i in range(len(trace)-len2):
        curr = trace[i:i+len2]
        lis2.append(dist(curr,pattern2)/len2)


    fig1, axs1 = plt.subplots(2, sharex=True, gridspec_kw={'hspace': 0})
    axs1[0].plot(pattern1)
    axs1[1].plot(pattern2)
    plt.show()


    fig, axs = plt.subplots(3, sharex=True, gridspec_kw={'hspace': 0})
    
    axs[0].plot(trace)
    axs[1].plot(lis1)
    axs[2].plot(lis2)
    plt.show()


