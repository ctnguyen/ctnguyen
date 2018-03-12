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
import DataImporter

# This script provide different way to extract the data from the original one
# to get a smaller and visialisable data
#

class DataViewer:
    def __init__(self,importeddata):
        self.importedData=importeddata

    def getCompanyData(self, companyName):
        companyData=[]
        if companyName not in self.importedData.mapCompanyCount:
            return companyData
        for dataRow in self.importedData.table:
            if dataRow.compName == companyName:
                companyData.append(dataRow)
        return companyData
