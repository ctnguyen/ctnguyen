############################################################
### RIDGE biscuits
############################################################
### donnees
Xbrut.app <- matrix(scan("nirc.asc"),ncol=700,byrow=T)
Ybrut.app <- matrix(scan("labc.asc"),ncol=4,byrow=T)
Xbrut.val <- matrix(scan("nirp.asc"),ncol=700,byrow=T)
Ybrut.val <- matrix(scan("labp.asc"),ncol=4,byrow=T)

Yselec <- 2
cookie.app <- cbind.data.frame(Ybrut.app[,Yselec],Xbrut.app)
names(cookie.app) <- c("sucres",paste("X",1:ncol(Xbrut.app),sep=""))
cookie.val <- cbind.data.frame(Ybrut.val[,Yselec],Xbrut.val)
names(cookie.val) <- c("sucres",paste("X",1:ncol(Xbrut.val),sep=""))
### separation en 4 parties de l'apprentissage
library(pls)
set.seed(87)
cvseg <- cvsegments(nrow(cookie.app),k=4,type="random")

library(MASS)
### fonction pour choisir (necessite cookie.app et une
### formule valide dans lm.ridge)
choix.kappa <- function(kappamax,cvseg,nbe=1000) {
  press <- rep(0,nbe)  
  for (i in 1:length(cvseg)) {
    valid <- cookie.app[unlist(cvseg[i]),]
    modele <- lm.ridge(sucres~.,data = cookie.app[unlist(cvseg[-i]),],lambda=seq(0,kappamax,length=nbe))
    coeff <- coef(modele)
    prediction <- matrix(coeff[,1],nrow(coeff),nrow(valid))+coeff[,-1]%*%t(data.matrix(valid[,-1]))
    press <- press+rowSums((matrix(valid[,1],nrow(coeff),nrow(valid),byrow=T)-prediction)^2)
  }
  kappaet <- seq(0,kappamax,length=nbe)[which.min(press)]
  return(list(kappaet=kappaet,press=press))
}

### modeles
plot(seq(0,1,length=nbe),res$press,type="l")
res <- choix.kappa(1,cvseg)


### modele final
coeff <- coef.lmridge(lm.ridge(sucres~.,data = cookie.app,lambda=kappaet))
### prevision sur le jeu de validation
prediction <- rep(coeff[1,1],n.val)+as.vector(coeff[,-1]%*%t(data.matrix(cookie.val[,-1])))
mean((cookie.val[,1]-prediction)^2)
modele.lm=lm(sucres~.,data = cookie.app)
mean((cookie.val[,1]-predict(modele.lm,newdata=cookie.val))^2)
### coefficients
coefflm <- coef.lmridge(lm.ridge(sucres~.,data = cookie.app,lambda=0))
matplot(t(rbind(coeff,coefflm)),type="l",col=1)


############################################################
### Lasso biscuits
############################################################
library(lars)

frac.delta <- seq(from = 0, to = 1, length = 1000)
### modeles
set.seed(87)
mse.cv <- cv.lars(data.matrix(cookie.app[,-1]),cookie.app[,1],K = 4,se=F,frac=frac.delta,use.Gram=F)
frac.delta.et <-frac.delta[ which.min(mse.cv$cv)]
plot(frac.delta,mse.cv$cv,xlab="delta",ylab="MSEP")
### modele final
modele.lasso <- lars(data.matrix(cookie.app[,-1]),cookie.app[,1],use.Gram=F)
### prevision sur le jeu de validation
prediction <- predict(modele.lasso,data.matrix(cookie.val[,-1]),s=frac.delta.et,mode="fraction")
mean((cookie.val[,1]-prediction$fit)^2)
### coefficients
plot(modele.lasso,breaks=F)
