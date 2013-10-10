############################################################
### L'ozone
############################################################
### representation des donnees
ozone <- read.table("ozone.txt",header=T,sep=";")
library("scatterplot3d")
scatterplot3d(ozone[,"T12"],ozone[,"Vx"],ozone[,"O3"],type="h",pch=16,box=FALSE,xlab="T12",ylab="Vx",zlab="O3")

### estimation + affichage
regmulti <- lm(O3~T12+Vx,data=ozone)
summary(regmulti)






############################################################
### La hauteur des eucalyptus
############################################################
eucalypt <- read.table("eucalyptus.txt",header=T,sep=";")
regmult <- lm(ht~circ+I(sqrt(circ)),data=eucalypt)
resume.mult <- summary(regmult)
resume.mult

### qualite du modele et des observations
plot(ht~circ,data=eucalypt,pch="+",col="grey60")
circ <- seq(min(eucalypt[,"circ"]),max(eucalypt[,"circ"]),len=100)
grille <- data.frame(circ)
lines(grille[,"circ"],predict(regmult,grille))

