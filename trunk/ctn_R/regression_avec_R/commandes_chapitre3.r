############################################################
### L'ozone
############################################################
### modele a 3 variables
modele3 <- lm(O3~T12+Vx+Ne12,data=ozone)
resume3 <- summary(modele3)

### coefficients et intervalle de confiance
coef3 <- coef(resume3)
IC3 <- confint(modele3,level=0.95)
IC3


### IC et ellipse de confiance
library(ellipse)
par(mfrow=c(3,2))
for(i in 1:3){
 for(j in (i+1):4){
   plot(ellipse(modele3,c(i,j),level=0.95),type="l",
    xlab=paste("beta",i,sep=""),ylab=paste("beta",j,sep=""))
   points(coef(modele3)[i], coef(modele3)[j],pch=3)
   lines(c(IC3[1,i],IC3[1,i],IC3[2,i],IC3[2,i],IC3[1,i]),
         c(IC3[1,j],IC3[2,j],IC3[2,j],IC3[1,j],IC3[1,j]),lty=2)
 }}

### IC variance
c(resume3$sigma^2*modele3$df.res/qchisq(0.975,modele3$df.res),resume3$sigma^2*modele3$df.res/qchisq(0.025,modele3$df.res))


### Effet de la Nebulosite
#### Test entre le modele a 3 variables et celui a 2 variables
modele2 <- lm(O3~T12+Vx,data=ozone)
anova(modele2,modele3)

############################################################
### La hauteur des eucalyptus
############################################################
### modele regression simple
regsimple <- lm(ht~circ,data=eucalypt)
### modele avec la racine carree
regM <- lm(ht~circ+I(sqrt(circ)),data=eucalypt)
### Test de comparaison entre les 2 modeles emboites
anova(regsimple,regM)
### Test T de nullite d'un coefficient
summary(regM)


circ <- seq(min(eucalypt[,"circ"]),max(eucalypt[,"circ"]),len=100)
grille <- data.frame(circ)
ICdte <- predict(regM,new=grille,interval="confidence",level=0.95)
ICpre <- predict(regM,new=grille,interval="prediction",level=0.95)
plot(ht~circ,data=eucalypt,pch="+",col="grey60")
matlines(circ,cbind(ICdte,ICpre[,-1]),lty=c(1,2,2,3,3),col=1)
legend("topleft",lty=2:3,c("E(y)","prev"))

############################################################
### Bootstrap sur l'ozone
############################################################
modele3 <- lm(O3~T12+Vx+Ne12,data=ozone)
resume3 <- summary(modele3)
coef3[,1:2]
res <- residuals(modele3)
ychap <- predict(modele3)
COEFF <- matrix(0,ncol=4,nrow=1000)
colnames(COEFF) <- names(coef(modele3))
ozone.boot <- ozone

### echantillon "bootstrappes"
for(i in 1:nrow(COEFF)){
  resetoile <- sample(res,length(res),replace=T)
  O3etoile <- ychap + resetoile
  ozone.boot[,"O3"] <- O3etoile
  regboot <- lm(formula(modele3),data=ozone.boot)
  COEFF[i,] <- coef(regboot)
}

### IC
apply(COEFF,2,quantile,probs=c(0.025,0.975))

### histogramme
hist(COEFF[,"T12"],main="",xlab="Coefficient de T12")
