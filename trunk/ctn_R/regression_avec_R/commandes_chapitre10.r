############################################################
### ozone et regression polynomiale
############################################################
ozone <- read.table("ozone_simple.txt",header=T,sep=";")
### la fonction de l'exercice
polyreg <- function(donnee,d=3){
  sigmax <- sd(donnee[,"T12"])
  grillex <- seq(min(donnee[,"T12"])-sigmax,max(donnee[,"T12"])+sigmax,length=100)
  aprevoir <- data.frame(T12=grillex)
  regpol <- lm(O3~poly(T12,degree=d,raw=TRUE),data=donnee)
  prev <- predict(regpol,aprevoir)
  return(list(grillex=grillex,grilley=prev))
}
### donnees
plot(O3~T12,xlim=c(0,35),ylim=c(0,150),data=ozone)
iter <- 1
for(ii in c(1,2,3,9)){
 tmp <- polyreg(ozone,d=ii)
 lines(tmp$grillex,tmp$grilley,col=iter,lty=iter)
 iter <- iter+1
}
legend(15,150,c("d=1","d=2","d=3","d=9"),col=1:4,lty=1:4)



############################################################
### ozone et regression par morceaux
############################################################
ind <- which(ozone[,2]<23)
regd <- lm(O3~T12,data=ozone[ind,])
regf <- lm(O3~T12,data=ozone[-ind,])
gxd <- seq(3,23,length=50)
gyd <- regd$coef[1]+gxd*regd$coef[2]
gxf <- seq(23,35,length=50)
gyf <- regf$coef[1]+gxf*regf$coef[2]
plot(O3~T12,data=ozone)
lines(gxd,gyd,col=2,lty=2,lwd=2)
lines(gxf,gyf,col=2,lty=3,lwd=2)
abline(v=23)

############################################################
### ozone et regression splines
############################################################
library(splines)
### base spline
BX <- bs(ozone[,2],knots=c(15,23),degre=2,Boundary.knots=c(5,32))
### regression spline
regs <- lm(ozone[,"O3"]~BX)
regs$coef

### representation graphique
grillex <- seq(5,32,length=100)
bgrillex <- bs(grillex,knots=c(15,23),degre=2,Boundary.knots=c(5,32))
prev <- bgrillex%*%as.matrix(regs$coeff[-1])+regs$coeff[1]
plot(O3~T12,data=ozone)
lines(grillex,prev,col=2)
abline(v=c(15,23))


############################################################
### ozone et regression a noyau
############################################################

ind <- order(ozone[,"T12"])
T12o <- ozone[ind,"T12"]
O3o <- ozone[ind,"O3"]
### regression constante par morceaux
reg1 <- lm(O3o~1,weight=c(rep(1,10),rep(0,40)))
reg2 <- lm(O3o~1,weight=c(rep(0,10),rep(1,10),rep(0,30)))
reg3 <- lm(O3o~1,weight=c(rep(0,20),rep(1,10),rep(0,20)))
reg4 <- lm(O3o~1,weight=c(rep(0,30),rep(1,10),rep(0,10)))
reg5 <- lm(O3o~1,weight=c(rep(0,40),rep(1,10)))
### graphique 
plot(T12o,O3o,xlab="T12",ylab="O3",col=rep(1:5,each=10),pch=rep(c(15:18,20),each=10))
lines(c(T12o[1],T12o[10]),c(reg1$coef,reg1$coef),col=1)
lines(c(T12o[11],T12o[20]),c(reg2$coef,reg2$coef),col=2)
lines(c(T12o[21],T12o[30]),c(reg3$coef,reg3$coef),col=3)
lines(c(T12o[31],T12o[40]),c(reg4$coef,reg4$coef),col=4)
lines(c(T12o[41],T12o[50]),c(reg5$coef,reg5$coef),col=5)


### regression a noyau
library(ibr)
### fenetres choisies par l'utilisateur
plot(O3~T12,data=ozone,xlab="T12",ylab="O3")
iter <- 1
for(i in c(1,3,5,10)){
  tmp <- npregression(ozone[,2],ozone[,1],bandwidth=i)
  lines(ozone[,"T12"],predict(tmp),col=iter,lty=iter)
  iter <- iter+1
}
legend(10,140,c("h=1","h=3","h=5","h=10"),col=1:4,lty=1:4)


### fenetres choisies par validation croisee
regnp <- npregression(ozone[,2],ozone[,1])
plot(O3~T12,data=ozone,xlab="T12",ylab="O3")
lines(ozone[,"T12"],predict(regnp),col=2,lty=2)

############################################################
### ozone et splines de lissage
############################################################
### smoothing spline
regsspline <- smooth.spline(ozone[,2],ozone[,1])
### representation graphique
prev <- predict(regsspline,grillex)
plot(O3~T12,data=ozone)
lines(prev$x,prev$y,col=2)
regsspline
