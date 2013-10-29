######################################################
#####        m2mo Laure Elie Control LIB      ########
######################################################


### In the case of multivariate regression (where there are more than 2 explanatory variable X)
### After regressing, it is difficult to plot the regression line
### This function give the normalize of all X_i variables into a unique X variable
### That allows one to plot Y in function of normedX
###
### Assuming the whole dataframe contain X and Y
### The function take 2 arguments 
### 1, the data frame, 
### 2, and the column index of Y variable
### return the normed X
normedX<-function(wholedata, yIndex)
{
  wholedata.dim<-dim(wholedata)
  nbObs<-as.integer(wholedata.dim[1])
  nbXVariables<-as.integer(wholedata.dim[2]-1)
  returnX <- rep(0,nbObs)
  
  for(i in 1:nbObs) {
    ## Compute the L2 norm of ith observations
    ## Divide it to the number of Explanatory Variables to remove the dimension effect
    returnX[i]= sqrt(sum(wholedata[i,-yIndex]^2))
  }
  
  return(returnX)
}