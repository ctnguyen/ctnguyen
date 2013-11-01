

rm(list=ls())
####   Question 1   #####
crime.data=read.table("data/UsCrime.txt", header=TRUE, sep="")
data.dim<-dim(crime.data)
plot(crime.data)


###   Question 2    ####
library("corrplot")
data.cor<-cor(crime.data)
postscript('output/figure/TP4_crime_correlations.ps');
corrplot(data.cor)
dev.off();


###   Question 3   ###
crime.lm<-lm("R~.", data=crime.data)
summary(crime.lm)
par(mfrow=c(2,2))
plot(crime.lm)
## The model is globally significant by the p-value of the Fisher test p-value=3.686-07
## By the coefficient table of results only five of explanatory variables who are significant
## Age, Ed, U2, X where their p-value of the student test are very low
#lm.designmatrix <- cbind(rep(1,data.dim[1]), crime.data[-1] )
#fitted.data<- as.matrix(lm.designmatrix) %*% crime.lm$coefficients
lm.RSS<- sum(crime.lm$residuals^2)
lm.AIC<-extractAIC(crime.lm)
n<-data.dim[1]
#lm.logLikelihood<- -(n/2)*log(lm.RSS/n ) - (n/2)*(1+ log(2/pi))
lm.AIC.manual_calcul<- n*log(lm.RSS/n ) + 2*14
lm.BIC<-extractAIC(crime.lm,k=2*log(n))


######################
###   Question 4  ####
## a- backward regression
lm.regbackward<-step(crime.lm,direction="backward")
#lm.regbackward<-step(crime.lm,direction="backward", k=log(n))
summary(lm.regbackward)
## by looking step by step of the backward selection process, we see the comparison table of AIC 
## in each case of elimination a variable. The elimination with the lowest AIC will be chosen and 
## the next step will process without the variable eliminated
## After several backward steps, we finally find a submodel with only 6 explanatory variables, among of which
## there are 4 highly significant variables found by the Student test at the beginning in the complete model

## b- forward regression
lm.regforward=step(lm(R~1,data=crime.data),list(upper=crime.lm),direction='forward');
summary(lm.regforward);
summary(lm.regbackward)

## c - stepwise regression
lm.regstepwise<-step(lm(R~U1+M+Ed,data=crime.data),list(upper=crime.lm),direction="both")
summary(lm.regstepwise)
summary(lm.regforward)
summary(lm.regbackward)