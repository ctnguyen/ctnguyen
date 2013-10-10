############################################################
### L'ozone
############################################################
### representation des donnees
ozone <- read.table("ozone_simple.txt",header=T,sep=";")
plot(O3~T12,data=ozone,xlab="T12",ylab="O3")

### estimation
reg <- lm(O3~T12,data=ozone)

### affichage
summary(reg)

### qualite du modele et des observations
### graphique regression complet (points, modele et IC Xb)
plot(O3~T12,data=ozone) 
T12 <- seq(min(ozone[,"T12"]),max(ozone[,"T12"]),length=100)
grille <- data.frame(T12)
ICdte <- predict(reg,new=grille,interval="confidence",level=0.95)
matlines(grille$T12,cbind(ICdte),lty=c(1,2,2),col=1)


### qualite du modele et des observations (prevision)
### graphique regression complet (points, modele et 2 IC)
plot(O3~T12,data=ozone,ylim=c(0,150))
T12 <- seq(min(ozone[,"T12"]),max(ozone[,"T12"]),length=100)
grille <- data.frame(T12)
ICdte <- predict(reg,new=grille,interval="conf",level=0.95)
ICprev <- predict(reg,new=grille,interval="pred",level=0.95)
matlines(T12,cbind(ICdte,ICprev[,-1]),lty=c(1,2,2,3,3),col=1)
legend("topleft",lty=2:3,c("Y","E(Y)"))

## IC coefficients
IC <- confint(reg,level=0.95)
IC

## RC ellipse coefficients + IC rectangle
library(ellipse)
plot(ellipse(reg,level=0.95),type="l",xlab="",ylab="")
points(coef(reg)[1], coef(reg)[2],pch=3)
lines(IC[1,c(1,1,2,2,1)],IC[2,c(1,2,2,1,1)],lty=2)

############################################################
### La hauteur des eucalyptus
############################################################
### representation des donnees
eucalypt <- read.table("eucalyptus.txt",header=T,sep=";")
plot(ht~circ,data=eucalypt,xlab="circ",ylab="ht")

### estimation + affichage
reg <- lm(ht~circ,data=eucalypt)
summary(reg)

### qualite du modele et des observations
plot(ht~circ,data=eucalypt,pch="+",col="grey60")
grille <- data.frame(circ=seq(min(eucalypt[,"circ"]),max(eucalypt[,"circ"]),length=100))
ICdte <- predict(reg,new=grille,interval="confi",level=0.95)
matlines(grille$circ,ICdte, lty=c(1,2,2),col=1)

### qualite du modele et des observations (prevision)
plot(ht~circ,data=eucalypt,pch="+",col="grey60")
circ <- seq(min(eucalypt[,"circ"]),max(eucalypt[,"circ"]),len=100)
grille <- data.frame(circ)
ICdte <- predict(reg,new=grille,interval="conf",level=0.95)
ICprev <- predict(reg,new=grille,interval="pred",level=0.95)
matlines(circ,cbind(ICdte,ICprev[,-1]),lty=c(1,2,2,3,3),col=1)
