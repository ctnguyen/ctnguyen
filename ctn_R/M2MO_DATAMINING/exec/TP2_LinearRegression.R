######################################################
#######  m2mo Laure Elie TP2 Applications   ##########
######################################################

#!!! Set the PROJECT_ROOT_DIRECTORY as the working directory
## i.e ".." from this file

tab=read.table("data/Icecreamdata.txt", header=TRUE, sep=";")

reg<-lm('cons~.',data=tab)

####### The Global Model ##########


## H_0 { \beta_2 = \beta_3 =... =  \beta_p  == 0  }
## H_1 { \exist \beta_j != zero}
##
## After summary(reg), we see that the p-value is very low,
## That say in the test global significativity will be easily rejected
## Then the model is significative

R2 = var(reg$fitted.values) / var(tab$cons)

# Manually compute the Fisher quantile
qFisher <- (R2 * (nrow(tab)-ncol(tab) ) ) /((1-R2) * (ncol(tab)-1))
# Manually compute the Fisher p-value
p_Ficher=pf( qFisher,ncol(tab)-1,nrow(tab)-ncol(tab),lower.tail=F )
## After comparing at the end of summary(reg), we see that these calculs
## corespond with the results computed by R


####### TEST FOR ONE COEFFICIENT ##########

## H_0 { \beta_j == 0 }
## H_1 { \beta_j != 0 }
##
## By looking at the summary(reg), we seee the coefficients 
## in the matrix form, indicating several informations for each coefficient.
## std.error, t-value (student statistics), p-value (4th column of coefficients matrix)
## of the student statistics,
## And we see that only the "temp" variable which is highly significative 

## the ***, **, * say when p-value is lesser then 1e-3, 1e-2, 1e-1


####### STUDY OF PREDICTED VALUES ##########
predict(reg);
## give just hat(Y)
predict(reg,interval="confidence",level=0.95)
## predict.lm
confint(object=reg, level=0.95)
## confidence intervalle



####### STUDY OF RESIDUAL ########## [very important ]

