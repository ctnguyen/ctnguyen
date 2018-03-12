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

dataFileName='factorextract.csv' ## original file
#dataFileName='_goodData.csv' # run plot on this data after running PreprocessData.py to reproduce the '_goodData.csv'

dataImporter = DataImporter.DataImporter(dataFileName)
dataViewer = DataViewer.DataViewer(dataImporter)

companyname = 'Aflac Incorporated'
smallDataTable = dataViewer.getCompanyData(companyname)

vT=[]
vDate=[]
vFVal=[]
vFQty=[]
for rowData in smallDataTable:
    vDate.append(rowData.pyDate)
    vT.append(rowData.dateDouble())
    ## if not math.isnan(rowData.fVal):
    vFVal.append(rowData.fVal)
    vFQty.append(rowData.fQty)
    print(str(rowData))


fig, ax1 = plt.subplots()
ax2 = ax1.twinx()
plt.title(companyname, loc='left')
plt.title('From file[{}]'.format(dataFileName), loc='right')

ax1.set_xlabel('timeline')
ax1.set_ylabel('Value Factor (%)', color='b')
ax2.set_ylabel('Quality Factor (%)', color='r')

fValCurve, = ax1.plot(vDate,vFVal, 'b-', linewidth=0.5)
fQtyCurve, = ax2.plot(vDate,vFQty, 'r--_', linewidth=0.5)
plt.legend([fValCurve, fQtyCurve], ['[{}] Val'.format(companyname), '[{}] Qty'.format(companyname)])
show()