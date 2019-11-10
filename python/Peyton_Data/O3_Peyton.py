from __future__ import division
import numpy as np
#from random import choice, uniform, randint
import pandas as pd
import sys
import os
import matplotlib.pyplot as plt
from statsmodels.nonparametric.smoothers_lowess import lowess

mydir = os.path.expanduser('~/GitHub/Dine-College-ASCEND/python/Peyton_Data/')
df = pd.read_csv(mydir+'/O3-Data.txt')

df = df[df['ozone'] > 0]
df = df[df['alt'] > 0]

# 'ozone'
fs = 8

fig = plt.figure()

# min,ozone,cell_temp,cell_pressure,photo_diode_v,p_suppV,lat,long,alt,gps-Qual,date,time


fig.add_subplot(3, 3, 1)
y = 'ozone'
x = 'min'
y1 = df[y]
#smoothed = lowess(y1, df[x], is_sorted=True, frac=0.05, it=0)

plt.plot(df[x], df[y], color = '0.3', linewidth=2.5, alpha=1.0)
#plt.plot(smoothed[:,0], smoothed[:,1], color = 'red', linewidth=1.0, alpha=1.0)
plt.xlabel('Minutes after launch', fontsize=fs)
plt.ylabel('Ozone, ppb', fontsize=fs)
plt.tick_params(axis='both', which='major', labelsize=fs-1)



fig.add_subplot(3, 3, 2)
y = 'ozone'
x = 'alt'
plt.scatter(df[x], df[y], color = 'c', s=5, alpha=1.0)
plt.xlabel('Altitude', fontsize=fs)
plt.ylabel('Ozone, ppb', fontsize=fs)
plt.tick_params(axis='both', which='major', labelsize=fs-1)


# min,ozone,cell_temp,cell_pressure,photo_diode_v,p_suppV,lat,long,alt,gps-Qual,date,time
fig.add_subplot(3, 3, 3)
x = 'cell_temp'
y = 'ozone'
plt.scatter(df[x], df[y], color = 'm', s=5, alpha=1.0)
#plt.plot(smoothed[:,0], smoothed[:,1], color = 'red', linewidth=1.0, alpha=1.0)
plt.xlabel('Temperature, K', fontsize=fs)
plt.ylabel('Ozone, ppb', fontsize=fs)
plt.tick_params(axis='both', which='major', labelsize=fs-1)



plt.subplots_adjust(wspace=0.7, hspace=0.5)
plt.savefig(mydir + 'figures/Fig2-O3.png', dpi=400, bbox_inches = "tight")
plt.close()
