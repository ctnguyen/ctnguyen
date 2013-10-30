######################################################
######  m2mo Laure Elie TP6 Non Parametric   #########
######################################################

#!!! Set the PROJECT_ROOT_DIRECTORY as the working directory
## i.e ".." from this file

haar<-function(j,k,x)
{
  g=rep(0,length(x))
  ind=which( (x<=(k+1)/(2^j)) & (x>(k/(2^j)) ) )  ;
  g[ind] = 2^(j/2)                                ;
  return(g)                                       ;
}


whaar<-function(j,k,x)
{
  g=rep(0,length(x))
  ind=which( (x<=(k+0.5)/(2^j)) & (x>(k/(2^j)) ) )      ;
  g[ind] = 2^(j/2)                                      ;
  ind2=which( (x<=(k+1)/(2^j)) & (x>(k+0.5)/(2^j)) )    ;
  g[ind2] = -2^(j/2)                                    ;
  return(g)                                             ;  
}


