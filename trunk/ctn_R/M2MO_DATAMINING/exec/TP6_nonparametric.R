######################################################
######  m2mo Laure Elie TP6 Non Parametric   #########
######################################################

#!!! Set the PROJECT_ROOT_DIRECTORY as the working directory
## i.e ".." from this file


### Question 1 - Tendance terms  ####
source(file="lib/nonparametric_lib.R")
t<-seq(from=0, to=1, length.out=16)
phi_10<-haar(1,0,t)
phi_11<-haar(1,1,t)
xbound<-c(0,1)
maxy<-max(max(phi_10),max(phi_11))
ybound<-c(0, maxy*1.2)
plot(0,0, xlim=xbound, ylim=ybound)
matlines(t,cbind(phi_10,phi_11), lty=c(2,3) )
legend(0.02, maxy*1.2, lty=c(2,3), c("phi_10","phi_11"))
rm(phi_10,phi_11,xbound,maxy,ybound)


### Question 2 - Detail terms  ####
phi_10<-whaar(1,0,t)
phi_21<-whaar(1,1,t)
xbound<-c(0,1)
maxy<-max(max(phi_10),max(phi_11))
ybound<-c(-maxy*1.5, maxy*1.5)
plot(0,0, xlim=xbound, ylim=ybound)
matlines(t,cbind(phi_10,phi_21), lty=c(2,3) )
legend(0.02, maxy*1.4, lty=c(2,3), c("phi_10","phi_11"))




