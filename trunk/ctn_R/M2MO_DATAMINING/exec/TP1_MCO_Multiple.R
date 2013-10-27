######################################################
#######  m2mo Laure Elie TP1 Applications   ##########
######################################################

#!!! Set the PROJECT_ROOT_DIRECTORY as the working directory
## i.e ".." from this file

tab=read.table("data/immo.txt", header=TRUE, sep=";") # Read the data file from the data folder

## start by plotting data
## Plotting multiple figures in a single page by using layout mechanisme
layout(rbind(c(1,2))) 
plot(tab$valeur,tab$transaction,xlab="valeur",ylab="transaction")
plot(tab$surface,tab$transaction,xlab="surface",ylab="transaction")


X<-tab[c("surface","valeur")]; # Assign the X variable
Y<-tab[c("transaction")]     ; # Assign the Y variable
resmco=lsfit(X,Y)            ; # Least Squares Fit
summary(resmco)              ;
## Reponse : see help(lsfit) for result explaination

## Printout the transposed_beta vector (it is coefficients truncated the intercept value)
resmco$coefficients[c(2,3)]
## After the lsfit result, if surface increase 1m2, the transaction increase 2.63439962, i.e resmco$coefficients["surface"]

## Computation residual sum, verify if it is null
sum_residual<-sum(resmco$residuals)

## Computation Mean Square Error
MSE<- (1./length(resmco$residuals))*(resmco$residuals %*% resmco$residuals)
sqrt_MSE<-sqrt(MSE)

## Computation Relative Errors
relative_error<- resmco$residuals / tab$transaction
max_rel_error<-max(abs(relative_error))
plot(relative_error)
plot(abs(relative_error))
## The max relative error is about 8% which is relatively acceptable

## analyse residuals
mean_transaction<-mean(tab$transaction)
fitted_transaction<-as.matrix(tab[c("surface","valeur")]) %*% resmco$coefficients[c("surface","valeur")] + resmco$coefficients["Intercept"]
plot(fitted_transaction, resmco$residuals, xlab="fitted transaction",ylab="residuals")
plot(fitted_transaction, abs(resmco$residuals), xlab="fitted transaction",ylab="abs residuals")
## By plotting the residual and absolute value of residual in function of fitted data,
## We verify if the residuals badly variate in function of magnitude of data
## In the case of this exercice, non, residual behave seemingly good
##
## By computing the mean transaction, supposing that the mean residual is zero
## then plotting graphic of residual and transaction, we see that the these two variables are correlated


plot(fitted_transaction, tab$transaction, ylim=c( max(tab$transaction),min(tab$transaction) ),xlim=c( max(fitted_transaction),min(fitted_transaction) ), ylab="transaction",xlab="fitted transaction")
abline(0,pi/4)

