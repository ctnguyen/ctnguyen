############################################################### #
#  Date             12/03/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          chithanhnguyen.math@gmail.com               #
#################################################################
from pylab import plot, show, grid, xlabel, ylabel
import matplotlib.pyplot as plt

import DataImporter
import DataViewer
import math
import datetime

MAX_NB_POINTS = 100 # set to -1 if don't want to use
dataFileName='factorextract.csv' ## original file
#dataFileName='_goodData.csv' # run plot on this data after running PreprocessData.py to reproduce the '_goodData.csv'

dataImporter = DataImporter.DataImporter(dataFileName)
dataViewer = DataViewer.DataViewer(dataImporter)

dateStr = '31/12/2015'

dateplot = datetime.datetime.strptime(dateStr, '%d/%m/%Y').date()
smallDataTable = dataViewer.getDateData(dateplot)

mapComNameToIndex = {}
vFVal=[]
vFQty=[]
indexCounter=0
for rowData in smallDataTable:
    if MAX_NB_POINTS<0 or indexCounter<MAX_NB_POINTS:
        mapComNameToIndex[rowData.compName]=indexCounter
        vFVal.append(rowData.fVal)
        vFQty.append(rowData.fQty)
        indexCounter+=1
        print(str(rowData))


plt.plot(vFQty,vFVal, 'bs')
plt.title(dateStr, loc='left')
plt.title('From file[{}]'.format(dataFileName), loc='right')
plt.xlabel('Quality Factor')
plt.ylabel('Value Factor')

for compname in mapComNameToIndex:
    compIndex = mapComNameToIndex[compname]
    x=vFQty[compIndex]
    y=vFVal[compIndex]
    plt.annotate(compname, xy=(x,y), xytext=(x,y) )
plt.show(block=True)