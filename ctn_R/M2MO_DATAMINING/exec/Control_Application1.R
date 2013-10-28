######################################################
#######  m2mo Laure Elie TP2 Applications   ##########
######################################################

#!!! Set the PROJECT_ROOT_DIRECTORY as the working directory
## i.e ".." from this file


### Application 1 
data_crime=read.table("data/UsCrime.txt", header=TRUE, sep="")
dim_data<-dim(data_crime)
## by looking to the dim_data, we see there are 13 explanator variable and 47 observations

#postscript('output/figure/control_DataCrime_Cov.ps');
plot(data_crime)
#dev.off();

data_corr<-cor(data_crime)
## Question about how to interpret the correlation matrix??