######################################################
#######  m2mo Laure Elie TP2 Applications   ##########
######################################################

#!!! Set the PROJECT_ROOT_DIRECTORY as the working directory
## i.e ".." from this file


### Application 1 
crime.data=read.table("data/UsCrime.txt", header=TRUE, sep="")
data.dim<-dim(crime.data)
## by looking to the dim_data, we see there are 13 explanator variable and 47 observations

#postscript('output/figure/control_DataCrime_Cov.ps');
plot(crime.data)
#dev.off();

data.corr<-cor(crime.data)
## Question about how to interpret the correlation matrix??