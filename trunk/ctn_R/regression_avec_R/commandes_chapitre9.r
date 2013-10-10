############################################################
### PCR biscuits
############################################################
library(pls)
### separation en 4 parties de l'apprentissage
set.seed(87)
cvseg <- cvsegments(nrow(cookie.app),k=4,type="random")
n.app <- nrow(cookie.app)
stdX.app <- sqrt(apply(cookie.app[,-1],2,var)*(n.app-1)/n.app)

### modeles
modele.pcr <- pcr(sucres~.,ncomp=28,data = cookie.app,scale=stdX.app,validation = "CV",segments=cvseg)
msepcv.pcr <- MSEP(modele.pcr ,estimate=c("train","CV")) 
plot(explvar(modele.pcr),type="l",main="")
### choix du nombre de composantes
ncomp.pcr <- which.min(msepcv.pcr$val["CV",,])-1

### modele final
modele.pcr.fin <- pcr(sucres~.,ncomp=ncomp.pcr,data = cookie.app,scale=stdX.app)
### prevision sur le jeu de validation
ychap <- predict(modele.pcr.fin,newdata=cookie.val)[,1,ncomp.pcr]
res.pcr <-cookie.val[,"sucres"]-ychap 
mean(res.pcr^2)

############################################################
### PLS biscuits
############################################################
### modeles
modele.pls <- plsr(sucres~.,ncomp=28,data = cookie.app,scale=stdX.app,validation = "CV",segments=cvseg)

msepcv.pls <- MSEP(modele.pls ,estimate=c("train","CV")) 
plot(msepcv.pls,col=1,type="l")
plot(explvar(modele.pls),type="l",main="")

### choix du nombre de composantes
ncomp.pls <- which.min(msepcv.pls$val["CV",,])-1
### modele final
modele.pls.fin <- plsr(sucres~.,ncomp=ncomp.pls,data=cookie.app,scale=stdX.app)
### prevision sur le jeu de validation
ychap <- predict(modele.pls.fin,newdata=cookie.val)[,1,5]
res.pls <- cookie.val[,"sucres"]-ychap
mean(res.pls^2)

