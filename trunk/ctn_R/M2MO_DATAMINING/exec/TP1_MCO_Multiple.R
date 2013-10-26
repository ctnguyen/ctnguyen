######################################################
#######  m2mo Laure Elie TP1 Applications   ##########
######################################################

#!!! Set the PROJECT_ROOT_DIRECTORY as the working directory
## i.e ".." from this file

tab=read.table("data/immo.txt", header=TRUE, sep=";") # Read the data file from the data folder

## start by plotting data
nb_obs = dim(tab)[2]-1
for(i in 1:nb_obs ) {
  plot(tab[,i],tab[,i+1],xlab=names(tab[i]),ylab=names(tab[nb_obs+1]))
}

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

mean_transaction<-mean(tab$transaction)
#plot(resmco$residuals,tab$transaction)
#plot(tab$transaction,resmco$residuals)
## By computing the mean transaction, supposing that the mean residual is zero
## then plotting graphic of residual and transaction, we see that the these two variables are correlated

estimated_transaction<-as.matrix(tab[c("surface","valeur")]) %*% resmco$coefficients[c("surface","valeur")]

plot(tab$transaction,estimated_transaction,xlim=c(0,1000),ylim=c(0,1000))
abline(0,pi/4)

