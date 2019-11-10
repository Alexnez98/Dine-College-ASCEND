from __future__ import division
import numpy as np
import pandas as pd
import sys
import os
import matplotlib.pyplot as plt
from statsmodels.nonparametric.smoothers_lowess import lowess


mydir = os.path.expanduser('~/GitHub/Dine-College-ASCEND/python')
df = pd.read_csv(mydir + '/Samson_Data/TEST-SO2.csv')

# 'T1, mV1, C1'
fs = 10

fig = plt.figure()

# Gas concentration figure
fig.add_subplot(2, 2, 1)
y1 = df['mV1']
x = range(len(y1)) # a list representing time
filtered = lowess(y1, x, is_sorted=True, frac=0.025, it=0)

plt.plot(df['mV1'], color = '0.3', linewidth=0.1, alpha=1.0)
plt.plot(filtered[:,0], filtered[:,1], color = 'r', linewidth=1.0, alpha=1.0)
plt.xlabel("Seconds", fontsize=fs)
plt.ylabel('SO'+r'$_{2}$' + " concentration", fontsize=fs)
plt.tick_params(axis='both', which='major', labelsize=fs-1)


fig.add_subplot(2, 2, 2)
y1 = df['T1']
x = range(len(y1)) # a list representing time
filtered = lowess(y1, x, is_sorted=True, frac=0.025, it=0)

clr = ['m']
plt.plot(df['T1'], color = '0.3', linewidth=0.1, alpha=1.0)
plt.plot(filtered[:,0], filtered[:,1], color = 'r', linewidth=1.0, alpha=1.0)
plt.xlabel("Seconds", fontsize=fs)
plt.ylabel("Temperature, F", fontsize=fs)
plt.tick_params(axis='both', which='major', labelsize=fs-1)

'''
fig.add_subplot(3, 3, 3)
y1 = df['C1']
x = range(len(y1)) # a list representing time
filtered = lowess(y1, x, is_sorted=True, frac=0.025, it=0)

clr = ['c']
plt.plot(df['C1'], color = '0.3', linewidth=0.1, alpha=1.0)
plt.plot(filtered[:,0], filtered[:,1], color = 'r', linewidth=1.0, alpha=1.0)
plt.xlabel("Time", fontsize=fs)
plt.ylabel("Temp. corrected\nconcentration", fontsize=fs)
plt.tick_params(axis='both', which='major', labelsize=fs-1)
'''


plt.subplots_adjust(wspace=0.5, hspace=0.5)
plt.savefig(mydir + '/Samson_Data/figures/Fig1.png', dpi=400, bbox_inches = "tight")
plt.close()
#plt.show()
