from __future__ import division
import numpy as np
#from random import choice, uniform, randint
import pandas as pd
import sys
import os
import matplotlib.pyplot as plt


mydir = os.path.expanduser('~/GitHub/Dine-College-ASCEND/python')
df = pd.read_csv(mydir + '/Allyssa_Data/TEST.TXT')

# 'T1, mV1, C1'
fs = 6

fig = plt.figure()

# CH4 vs. time
fig.add_subplot(1, 1, 1)
clr = ['0.2']
plt.plot(df['mV1'], color = clr[0], linewidth=0.1, alpha=1.0)
plt.xlabel("Time", fontsize=fs)
plt.ylabel("Concentration", fontsize=fs)
#plt.yscale('log')
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

#plt.subplots_adjust(wspace=0.5, hspace=0.5)
#plt.savefig(mydir + '/figures/Fig1.png', dpi=400, bbox_inches = "tight")
#plt.close()
plt.show()
