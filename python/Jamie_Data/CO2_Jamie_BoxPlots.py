from __future__ import division
import numpy as np
#from random import choice, uniform, randint
import pandas as pd
import sys
import os
import matplotlib.pyplot as plt
from statsmodels.nonparametric.smoothers_lowess import lowess

mydir = os.path.expanduser('~/GitHub/Dine-College-ASCEND/python/Jamie_Data/')
df1 = pd.read_csv(mydir+'/Data_Results/Tsaile.TXT')
df2 = pd.read_csv(mydir+'/Data_Results/Shiprock.TXT')
df3 = pd.read_csv(mydir+'/Data_Results/Buffalo_Pass.TXT')


# 'Co2_ppm'
fs = 13

fig = plt.figure()

y1 = df1['v2']
y2 = df2['v2']
y3 = df3['v2']

x = range(len(y1)) # a list representing time


# CH4 vs. time
clr = ['0.2']

ax = fig.add_subplot(111)

# Create the boxplot
bp = ax.boxplot([y1,y2,y3], labels=['Tsaile', 'Shiprock', 'Buffalo pass'], showfliers=False, patch_artist=True)


## add patch_artist=True option to ax.boxplot()
## to get fill color

## change outline color, fill color and linewidth of the boxes
clrs = ['r', 'b', 'g']

for i, box in enumerate(bp['boxes']):
    # change outline color
    box.set( color=clrs[i], linewidth=2)
    # change fill color
    box.set( facecolor = clrs[i], alpha=0.5 )


## change color and linewidth of the whiskers

clrs1 = ['r', 'r', 'b', 'b', 'g', 'g']
for i, whisker in enumerate(bp['whiskers']):
    whisker.set(color=clrs1[i], linewidth=2)


## change color and linewidth of the caps
for i, cap in enumerate(bp['caps']):
    cap.set(color=clrs1[i], linewidth=2)


## change color and linewidth of the medians
for i, median in enumerate(bp['medians']):
    median.set(color=clrs[i], linewidth=2)

'''
## change the style of fliers and their fill
for i, flier in enumerate(bp['fliers']):
    flier.set(marker='.', color=clrs1[i], alpha=0.5)
'''



#plt.xlabel("Time", fontsize=fs)
#plt.ylabel("Concentration", fontsize=fs)
#plt.tick_params(axis='both', which='major', labelsize=fs-1)

plt.subplots_adjust(wspace=0.5, hspace=0.5)
plt.savefig(mydir + 'figures/BoxPlots_DataColumn2.png', dpi=200, bbox_inches = "tight")
plt.close()
