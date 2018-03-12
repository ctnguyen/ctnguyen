############################################################### #
#  Date             12/03/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          chithanhnguyen.math@gmail.com               #
#################################################################

import csv
import matplotlib.pyplot as plt
import os.path
import time
import math
import datetime

def parseDouble(vStr):
    value=math.nan
    try:
        value= float(vStr)
    except:
        return value
    return value

class DataRecord:
    def __init__(self, rowID, compname, pydate, fval=math.nan, fqty=math.nan, isbad=False, badreason=''):
        self.rowID    = rowID
        self.compName = compname
        self.pyDate   = pydate
        self.fVal     = fval
        self.fQty     = fqty
        self.isBad    = isbad
        self.badReason = badreason

class DataImporter:
    def __init__(self,datafilename, useFilter=True):
        self.useFilter=useFilter
        self.table   = []
        self.badRows = []

        if os.path.isfile(datafilename):
            with open('factorextract.csv', 'r') as dataFile:
                reader = csv.reader(dataFile)
                next(reader,None)## skip header
                rowCounter=0
                for line in reader:
                    compName = line[0]
                    dateStr  = line[1]
                    tradeId  = line[2]#
                    fValStr  = line[3]
                    fQtyStr  = line[4]
                    pyDate = datetime.datetime.strptime(dateStr, '%d/%m/%Y').date()
                    fVal = parseDouble(fValStr)
                    fQty = parseDouble(fQtyStr)
                    isBad=False
                    badReason = ''
                    if(fVal!=fVal):#isNaN
                        isBad=True
                        badReason+='Factor_VALUE is NULL.'
                    if(fQty!=fQty):#isNaN
                        isBad=True
                        badReason+='Factor_QUALITY is NULL.'

                    if(useFilter and fVal==fVal and fVal>1000):
                        isBad = True
                        badReason += 'Factor_VALUE is too big.'
                    dataRow=DataRecord(rowCounter, compName, pyDate, fVal,fQty,isBad,badReason)
                    #print('[{}] Comp[{}] date[{}] fVal[{}] fQty[{}]   dateStr[{}]   date[{}]'.format(rowCounter, compName, dateStr, fValStr, fQtyStr, dateStr, pyDate.isoformat()))
                    self.table.append(dataRow)

                    if(isBad):
                        self.badRows.append(rowCounter)

                    rowCounter += 1

    def getBadRowsInfo(self):
        dataInfo = 'Nb Of Rows = {}\n'.format(len(self.table))
        dataInfo = 'Nb Of Bad Rows = {}\n'.format(len(self.badRows))
        dataInfo = 'companyname,datadate,tradingitemid,Factor_VALUE,Factor_QUALITY\n'
        for badRowIndex in self.badRows:
            badRow = self.table[badRowIndex]
            dataInfo += '[{}][{}] {},{},,{},{}\n'.format(badRowIndex, badRow.badReason , badRow.compName, badRow.pyDate.strftime('%d/%m/%Y'), badRow.fVal, badRow.fQty)
        return dataInfo

    def getDataGoodOnlyStr(self):
        csvData = 'companyname,datadate,tradingitemid,Factor_VALUE,Factor_QUALITY\n'
        for row in self.table:
            if(not row.isBad):
                csvData += '"{}",{},,{},{}\n'.format(row.compName, row.pyDate.strftime('%d/%m/%Y'), row.fVal, row.fQty)
        return csvData

    def __str__(self):
        csvData = 'companyname,datadate,tradingitemid,Factor_VALUE,Factor_QUALITY\n'
        for row in self.table:
            if(row.isBad):
                csvData+='--------{}--------'.format(row.badReason)
            csvData += '"{}",{},,{},{}\n'.format(row.compName, row.pyDate.strftime('%d/%m/%Y'), row.fVal, row.fQty)
        return csvData