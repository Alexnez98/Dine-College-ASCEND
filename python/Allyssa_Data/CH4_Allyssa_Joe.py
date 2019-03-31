from __future__ import division
import numpy as np
#from random import choice, uniform, randint
import pandas as pd
import sys
import os
import matplotlib.pyplot as plt
from statsmodels.nonparametric.smoothers_lowess import lowess

mydir = os.path.expanduser('~/GitHub/Dine-College-ASCEND/python/Allyssa_Data')
df = pd.read_csv(mydir+'/TEST.TXT')

# using regular expression to remove blank lines in dataframe
df = df.replace(r'^\s+$', np.nan, regex=True)
df = df.replace(r'^\t+$', np.nan, regex=True)
df = df.dropna()

# 'T1, mV1, C1'
fs = 13

fig = plt.figure()

y1 = df['sensor_voltage']
x = range(len(y1)) # a list representing time

filtered = lowess(y1, x, is_sorted=True, frac=0.025, it=0)

# CH4 vs. time
fig.add_subplot(1, 1, 1)
clr = ['0.2']

plt.plot(df['sensor_voltage'], color = '0.3', linewidth=2.5, alpha=1.0)
plt.plot(filtered[:,0], filtered[:,1], color = 'lime', linewidth=1.0, alpha=1.0)
plt.axvspan(2600, 3800,alpha=0.5,color='red')

plt.xlabel("Seconds", fontsize=fs)
plt.ylabel("Concentration", fontsize=fs)
plt.tick_params(axis='both', which='major', labelsize=fs-1)

'''
fig.add_subplot(3, 3, 2)
clr = ['m']
plt.plot(df['T1'], color = clr[0], linewidth=0.1, alpha=1.0)
plt.xlabel("Time", fontsize=fs)
plt.ylabel("Temperature, F", fontsize=fs)
#plt.yscale('log')
plt.tick_params(axis='both', which='major', labelsize=fs-1)


fig.add_subplot(3, 3, 3)
clr = ['c']
plt.plot(df['C1'], color = clr[0], linewidth=0.1, alpha=1.0)
plt.xlabel("Time", fontsize=fs)
plt.ylabel("Temp. corrected\nconcentration", fontsize=fs)
#plt.yscale('log')
plt.tick_params(axis='both', which='major', labelsize=fs-1)
'''

plt.subplots_adjust(wspace=0.5, hspace=0.5)
plt.savefig(mydir + '/figures/Fig5.png', dpi=400, bbox_inches = "tight")
plt.close()
#plt.show()
