######################################################
#######  m2mo Laure Elie TP2 Applications   ##########
######################################################

#!!! Set the PROJECT_ROOT_DIRECTORY as the working directory
## i.e ".." from this file

source(file="lib/control_lib.R")
#### MODEL REGRESSION LINEAIRE ####

## read the data of crimes
crime.data=read.table("data/UsCrime.txt", header=TRUE, sep="")
data.dim<-dim(crime.data)
## linear model fitting 
crime.lm<-lm("R~.", data=crime.data)

### Question 1
print(crime.lm)
summary(crime.lm)
attributes(crime.lm)
## The linear fitting has fitted the variable R in a linear model explained by all other variables on the data table
## the estimated parameters (hat_beta) is stored in the crime.lm$coefficients


### Question 2  -- Global Model
## The R^2, determination coefficient mesuring the goodness of fit
## Geometrically, it is the cos(\theta)^2, where \theta is the angle between |Y-\bar{Y}1_{n}| and the |\hat{Y}-\bar{Y}1_{n}|
## The more R^2 near 1, the more model is good
## In this case of study, by using command summary, at the and, we see that R-square value is 0.7692, which
## is quite not bad
## By using summary, we also see the global significance of model. The last line of summary indicate this.
## It give informations about the Fisher test : H0={\beta2 = ... = \betap = 0}, with the very small p-value
## That say if we test with a test level > p-value(3.686-07), the test reject H0 hypothesis. In the case here,
## We reject the H0 hypothesis


### Question 3 -- Model's Coefficients
## The significance test for ith parameter is H0 = {\beta_i = 0}
## Always by usiing summary to see the result detail
## We can see in the array of coefficients detail the p-value for significance test for each coefficients
## The table show that only the intercept, Age, Ed, U2, X that have the significance to the regressand
## *** <--> p-value < 1-03
##  ** <--> p-value < 1-02
##   * <--> p-value < 1-01
IC095<-confint(crime.lm, level=0.95)
IC099<-confint(crime.lm, level=0.99)
IC095
IC099

### Question 4  --  Prediction Studies
design_matrix<-as.matrix(cbind( rep(1,data.dim[1]), crime.data[,2:data.dim[2]]) )
fitted_regressand<-design_matrix%*%crime.lm$coefficients
#postscript('output/figure/control_fitted_observed_regressand.ps');
plot(fitted_regressand, crime.data[,1])
abline(0,pi/4)
#dev.off();
## By viewing the graphic of fitted data in function of measured data, and the bissect line, 
## we see that the fitted data are majority greater than measured data
crime.grid<-crime.data[,2:data.dim[2]]
ICconf<-predict(crime.lm,crime.grid,interval="confidence")
ICpred<-predict(crime.lm,crime.grid,interval="prediction")
## plotting every lines in fucntions of fitted reponses \hat{Y}
predictLines<-data.frame(fittedY=fitted_regressand, Y=fitted_regressand,
                         ConfLow=ICconf[,2],ConfUp=ICconf[,3],
                         PredLow=ICpred[,2],PredUp=ICpred[,3])
plot(predictLines[,1],crime.data[,1],xlab="fittedY",ylab="response")
predictLines<-predictLines[order(predictLines[,1]),]
matlines(predictLines[,1],predictLines[,-1],lty=c(1,2,2,3,3),col=1)
legend(min(predictLines[,1])+10, max(predictLines[,1])-10, lty=c(1,2,3), c("fitted","conf","pred"))


### Question 5 --  Residual studies
## RSS Residual sum of squares
rss<-sum(crime.lm$residuals^2)
## non biaised sigma estimator
hat_sigma<-rss/(data.dim[1]-data.dim[2])
## plot residuals in function of response
plot(crime.data[,1], crime.lm$residuals,xlab="Y",ylab="residual",main="residuals in function of response")
## It is better to plot the studendized residual in function of fitted data
## with this graphic of studentized, we can detect easyli the aberrant points
studentized_r<-rstudent(crime.lm)
plot(crime.data[,1],rstudent(crime.lm) ,xlab="Y",ylab="t*",main="studentized residuals in function of response")
abline(h=c(-2,2,0),lty=c(2,2,1))
## Study the normality of residual
## This graphic of qqnorm and qqline show that the residuals distribution is near to the normal distribution
qqnorm(crime.lm$residuals)
qqline(crime.lm$residuals)
residual.shapiro<-shapiro.test(crime.lm$residuals)
residual.shapiro$p.value
## The Shapiro-Wilk test in this case has a too high p-value, that mean we can not reject the H0 hypothesis
## H0 = { sample distributed normally }
## The test affirm that the residuals comes from a normal distribution

### Qestion 6  Prediction with new data
rm(list=ls())
crime.data=read.table("data/UsCrime.txt", header=TRUE, sep="")
data.dim<-dim(crime.data)
indTest<-seq(1,data.dim[1],by=2)
test.data<-crime.data[indTest,]
train.data<-crime.data[-indTest,]
train.lm<-lm("R~.", data=train.data);
ICconf<-predict(train.lm,newdata=test.data[,-1],interval="confidence")
ICpred<-predict(train.lm,newdata=test.data[,-1],interval="prediction")
M_SSE<-sum(ICconf[,1]-test.data[,1]) /nrow(test.data)  # Mean Sum Squares Errors
M_SSEP<-sum(ICpred[,1]-test.data[,1])/nrow(test.data)  # Mean Sum Squares Errors of Prediction
  


### Question 7 -- Graphics Analysis
rm(list=ls())
crime.data=read.table("data/UsCrime.txt", header=TRUE, sep="")
crime.lm<-lm("R~.", data=crime.data);
par(mfrow=c(2,2));
plot(crime.lm);