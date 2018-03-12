############################################################### #
#  Date             12/03/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          chithanhnguyen.math@gmail.com               #
#################################################################
import DataImporter

## This script preprocess the data and give out some rough information
## Filter out bad data and print to files
##

dataFileName='factorextract.csv' ## original file

dataImporter = DataImporter.DataImporter(dataFileName)

## Reproduce data file with marker of the bad row
with open('_factorextract_bad_marker.csv', 'w') as dataFile:
    dataFile.write(str(dataImporter))

## Print info of the bad data
with open('_badRowsInfo.csv', 'w') as dataFile:
    dataFile.write(dataImporter.getBadRowsInfo())

## Replicate data with good data only
with open('_goodData.csv', 'w') as dataFile:
    dataFile.write(dataImporter.getDataGoodOnlyStr())

## Reproduce csv file showing the number of data point by company
with open('_nbDataByCompany.csv', 'w') as dataFile:
    dataFile.write(dataImporter.getCompanyInfo())

## Reproduce csv file showing the number of data point by company
with open('_anonymizedData.csv', 'w') as dataFile:
    dataFile.write(dataImporter.getAnonymizedDataStr())

## Reproduce csv file of all time points
with open('_timepoints.csv', 'w') as dataFile:
    for pydate in dataImporter.timePoints:
        print(pydate.strftime('%d/%m/%Y'))
        dataFile.write('{}\n'.format(pydate.strftime('%d/%m/%Y')))