


rm(list=ls())
crime.data=read.table("data/UsCrime.txt", header=TRUE, sep="")
data.dim<-dim(crime.data)

### Question 1 ####
library(leaps);
X=crime.data[,2:ncol(crime.data)]; 
xnames=names(X); 
Y=crime.data[,"R"];


####################
### Question 2 ####
### a R2 criteria
reg.R2=leaps(X,Y,method="r2",nbest=1,names=xnames);
reg.R2
plot(reg.R2$r2,main='R2',ylab="R^2", xlab='id model',type="both");

### b ajusted R2 criteria
reg.adjR2=leaps(X,Y,method="adjr2",nbest=1,names=xnames);
reg.adjR2
plot(reg.adjR2$adjr2,main='ajusted R2',ylab="adj-R^2", xlab='id model',type="both");
## The best reduced following ajusted R2 criteria 
#     Age     S    Ed  Ex0   Ex1    LF     M     N    NW    U1    U2     W     X
##8   TRUE FALSE  TRUE TRUE FALSE FALSE  TRUE FALSE FALSE  TRUE  TRUE  TRUE  TRUE
m0=8; ind0=reg.adjR2$which[m0,];
fk=paste("R~",paste(xnames[ind0],collapse= "+"))
mes=sprintf('Reduced Model (Cp) -> %s ',fk); mes
reduced.lm<-lm(fk,data=crime.data)
summary(reduced.lm);
n=data.dim[1]
reduced.AIC<-extractAIC(reduced.lm)
reduced.BIC<-extractAIC(reduced.lm, k=log(n))

### c Cp (Mallows) criteria
reg.Cp=leaps(X,Y,method="Cp",nbest=1,names=xnames);
reg.Cp
plot(reg.Cp$Cp,main='Cp',ylab="Cp", xlab='id model');
##     Age     S    Ed  Ex0   Ex1    LF     M     N    NW    U1    U2     W     X
##6   TRUE FALSE  TRUE TRUE FALSE FALSE FALSE FALSE FALSE FALSE  TRUE  TRUE  TRUE
m0=which.min(reg.Cp$Cp);
ind0=reg.Cp$which[m0,]; 
fk=paste("R~",paste(xnames[ind0],collapse="+"))
mes=sprintf('Reduced Model (Cp) -> %s ',fk);
mes
reduced.lm<-lm(fk,data=crime.data)
summary(reduced.lm);
reduced.AIC<-extractAIC(reduced.lm)
reduced.BIC<-extractAIC(reduced.lm, k=log(n))



### Question 3
##reg.exh=regsubsets(X,Y,nbest=1,method="forward",nvmax=ncol(crime.data),names=xnames);
reg.exh=regsubsets(X,Y,nbest=1,method="exh",nvmax=ncol(crime.data),names=xnames);
summary(reg.exh);
mod=summary(reg.exh);
attributes(mod);
