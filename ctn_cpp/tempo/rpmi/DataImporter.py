from collections import deque
import csv
import matplotlib.pyplot as plt
import os.path
import time
import math
import datetime

dataFileName='factorextract.csv'

class DataImporter:
    def __init__(self,datafilename):
        if os.path.isfile(datafilename):
            with open('factorextract.csv', 'r') as dataFile:
                reader = csv.reader(dataFile)
                next(reader,None)## skip header
                for line in reader:
                    compName = line[0]
                    dateStr  = line[1]
                    tradeId  = line[2]#
                    fValStr  = line[3]
                    fQtyStr  = line[4]
                    pyDate = datetime.datetime.strptime(dateStr, '%d/%m/%Y').date()
                    print('Comp[{}] date[{}] fVal[{}] fQty[{}]   dateStr[{}]   date[{}]'.format(compName,dateStr,fValStr,fQtyStr, dateStr, pyDate.isoformat()))


dataImporter = DataImporter(dataFileName)