import matplotlib.pyplot as plt
import numpy as np

def plot(trace):
    plt.plot(trace)
    plt.show()
    
def sub_plot(trc_arrs):
    plt_no = len(trc_arrs)
    fig, ax = plt.subplots(plt_no,sharex=False)
    for i, obj in enumerate(ax):
        obj.plot(trc_arrs[i])
        obj.set_title(i)
    
        
    plt.show()


def read_csv(file_path):
    return np.genfromtxt(file_path, delimiter=',')

def save_csv(file, file_path):
    np.savetxt(file_path, file, delimiter=',')