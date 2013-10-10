############################################################
### L'ozone
############################################################
### 
ozone <- read.table("ozone.txt",header=T,sep=";")
library(leaps)
recherche.ex <- regsubsets(O3~T12+T15+Ne12+N12+S12+E12+W12+Vx+O3v,int=T,nbest=1,nvmax=10,method="exhaustive",really.big=T,data=ozone)
plot(recherche.ex,scale="bic")
plot(recherche.ex,scale="Cp")
plot(recherche.ex,scale="adjr2")
plot(recherche.ex,scale="r2")
