import numpy as np
import matplotlib.pyplot as plt

def read_csv(file_path):
    return np.genfromtxt(file_path, delimiter=',')

def save_csv(file, file_path):
    np.savetxt(file_path, file, delimiter=',')

trace = read_csv('live.csv')


# pat_e = read_csv('end_pat_v4.csv')
# pat_0 = read_csv('pat0_v4.csv')
# pat_1 = read_csv('pat1_v4.csv')
# len(pat_e),len(pat_0),len(pat_1)
trace = trace*256 + 128

print(len(trace))

plt.figure(figsize=(20,10))
plt.plot(trace)
plt.show()

trace = trace[16:520]

# from tqdm.notebook import tqdm

# window_size = 15

# patterns = []
# matches = []
# count = 0
# is_pass = False

# for i in tqdm(range(len(trace)-window_size)):
#     if is_pass:
#         count -= 1
#         if count == 0:
#             is_pass = False
#         continue
#     window = trace[i:i+window_size]
#     done = False
#     temp_matches = []
#     is_pass2 = False
#     count2 = 0
#     for j in patterns:
#         if is_pass2:
#             count2 -= 1
#             if count2 == 0:
#                 is_pass2 = False
#             continue
#         if np.corrcoef(trace[j:j+window_size], window)[0,1] > 0.95:
#             done= True
#             is_pass2 = True
#             count2 = window_size
#             break
#     if done:
#         continue
#     for j in range(i+1,len(trace)-window_size):
#         window_2 = trace[j:j+window_size]
#         if np.corrcoef(window, window_2)[0,1] > 0.95 and i!=j:
#             temp_matches.append(j)
#     if len(temp_matches) > 0:
#         patterns.append(i)
#         matches.append(temp_matches)
#         is_pass = True
#         count = window_size
            



from tqdm.notebook import tqdm
import random
window_size = 13

patterns = []
matches = []
count = 0
is_pass = False

trace1 = trace.copy()
done1 = np.zeros(len(trace1))
for i in tqdm(range(len(trace)-window_size)):
    if done1[i] == 1 or done1[i+window_size-1] == 1:
        continue
    window = trace[i:i+window_size]
    done = False
    temp_matches = []
    
    for j in patterns:  
        if np.corrcoef(trace[j:j+window_size], window)[0,1] > 0.95:
            done= True
            
            break
    if done:
        continue
    for j in range(i+1,len(trace)-window_size):
        if done1[j] == 1 or done1[j+window_size-1] == 1:
            continue
        window_2 = trace[j:j+window_size]
        if np.corrcoef(window, window_2)[0,1] > 0.95 and i!=j:
            temp_matches.append(j)
            for k in range(j,j+window_size):
                done1[k] = 1
    if len(temp_matches) > 0:
        patterns.append(i)
        for j in temp_matches:
            for k in range(j,j+window_size):
                done1[k] = 1
        for k in range(i,i+window_size):
            done1[k] = 1
        matches.append(temp_matches)
            
trace = trace1

print(len(patterns))

data = [(i,j) for i, j in zip(patterns, matches)]
data = sorted(data, key=lambda x: len(x[1]), reverse=True)
data1 = data.copy()

for i in data1:
    print(i[0],len(i[1]))

# process the found patterns, remove unnecessary patterns
for i in data1:
    if len(i[1]) < 2 or i[0] > 2300:
        data.remove(i)

print(len(data))
for i in data:
    print(i[0],len(i[1]))

figs = 4
fig,ax = plt.subplots(figs,sharex=True)
for i in range(figs):
    ax[i].plot(trace)
    a = data[i][0]
    ax[i].plot(np.arange(a, a+window_size), trace[a:a+window_size],color='orange',)
    for a in data[i][1]:
        ax[i].plot(np.arange(a, a+window_size), trace[a:a+window_size], color='lime',alpha=0.75)
plt.show()

val = 37
print(np.corrcoef(trace[val:val+window_size], trace[val+window_size:val+2*window_size])[0,1])

# mapping to code :


# void super_efficient_sort(uint8_t* arr, int n) {
#   for (int i = 0; i < n-1; i++) {
#     for (int j = 0; j < n-i-1; j++) {
#       if (arr[j] > arr[j+1]) {
#         swap(&arr[j], &arr[j+1]);
#       }
#     }
#   }
# }

# outer for loop runs for n-1 = 6 times. => corresponding pattern can be data[6]
# inner for loop runs for sum(n-i-1) = 21 times. => corresponding pattern can be data[2]
# number of swaps = 8, so the pattern can be data[4] or data[5], or data[0]/10

# hidden secret part is arr
# so these patterns can be used to find the array

# plot the correct patterns again:

pattern1 = 6
pattern2 = 2
pattern3 = 4
plt.plot(trace)
for val,col in zip([pattern1,pattern2,pattern3],['orange','lime','salmon']):
    pat = data[val][0]
    plt.plot(np.arange(pat, pat+window_size), trace[pat:pat+window_size], color=col,)
    for a in data[val][1]:
        plt.plot(np.arange(a, a+window_size), trace[a:a+window_size], color=col,alpha=0.75)

plt.show()

figs = 3
fig,ax = plt.subplots(figs,sharex=True)
for i,val in enumerate([0,2]):
    ax[i].plot(trace)
    a = data[val][0]
    ax[i].plot(np.arange(a, a+window_size), trace[a:a+window_size],color='orange',)
    for a in data[val][1]:
        ax[i].plot(np.arange(a, a+window_size), trace[a:a+window_size], color='lime',alpha=0.75)

ax[4].plot(trace)
ax[0].set_title('For loop in swap')
ax[1].set_title('Inner for loop')
ax[2].set_title('One swap call')
ax[3].set_title('Outer for loop')
ax[4].set_title('Original trace')
plt.show()

# fig = plt.figure(figsize=(15,8))
# val = 6
# a = data[val][0]
# plt.plot(trace)
# plt.plot(np.arange(a, a+window_size), trace[a:a+window_size],color='orange',)
# for a in data[val][1]:
#     plt.plot(np.arange(a, a+window_size), trace[a:a+window_size], color='lime',alpha=0.75)
# plt.title('Outer for loop')

plt.plot(trace)


