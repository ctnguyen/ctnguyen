############################################################
### L'ozone: ANCOVA
############################################################
### representation des donnees
ozone <- read.table("ozone.txt",header=T,sep=";")

### regression par secteur de vent
plot(ozone[,"T12"],ozone[,"O3"],pch=as.numeric(ozone[,"vent"]),col=as.numeric(ozone[,"vent"]))
a1 <- lm(O3~T12,data=ozone[ozone[,"vent"]=="EST",])
a2 <- lm(O3~T12,data=ozone[ozone[,"vent"]=="NORD",])
a3 <- lm(O3~T12,data=ozone[ozone[,"vent"]=="OUEST",])
a4 <- lm(O3~T12,data=ozone[ozone[,"vent"]=="SUD",])
abline(a1,col=1)
abline(a2,col=2)
abline(a3,col=3)
abline(a4,col=4)

### regression complet avec interaction
mod1b <- lm(formula = O3 ~ -1 + vent + T12:vent, data = ozone)
summary(mod1b)

### regression complet avec  constante + vent et interaction
mod1 <- lm(formula = O3 ~ vent + T12:vent, data = ozone)
summary(mod1)


### regression complet avec constante + vent et meme pente  (T12)
mod2 <- lm(formula = O3 ~ vent + T12, data = ozone)
### regression complet (sans constante) vent et meme pente (T12)
mod2b <- lm(formula = O3 ~ -1 + vent + T12, data = ozone)

### modèle avec une seule ordonnee à l'origine (pente differente: interaction)
mod3 <- lm(formula = O3 ~ vent:T12, data = ozone)

### test égalite des pentes
anova(mod2,mod1)

### test égalite des ordonnees à l'origine
anova(mod3,mod1)

### residus
plot(rstudent(mod2)~fitted(mod2),xlab="ychap",ylab="residus")
xyplot(rstudent(mod2)~fitted(mod2)|vent,data=ozone,ylab="residus")

############################################################
### La hauteur des eucalyptus ANCOVA
############################################################
eucalypt <- read.table("eucalyptus.txt",header=T,sep=";")
eucalypt[,"bloc"] <- as.factor(eucalypt[,"bloc"])
### modele complet
m.complet <- lm(ht~bloc-1+bloc:circ,data=eucalypt)

### modele avec meme pente
m.pente <- lm(ht~bloc-1+circ,data=eucalypt)


### modele avec meme ordonnee a l'origine
m.ordonne <- lm(ht~bloc:circ,data=eucalypt)

### egalite des pentes
anova(m.pente,m.complet)

### test égalite des ordonnees à l'origine
anova(m.ordonne,m.complet)

### modele avec meme ordonnee a l'origine et meme pente
m.simple <- lm(ht~circ,data=eucalypt)

### memes ordonnees a l'origine ou non ?
anova(m.simple,m.pente)

############################################################
### L'ozone: ANOVA 1
############################################################
plot(O3~vent,data=ozone)
### modele mi anova 1
mod1 <- lm(O3~vent-1,data=ozone)
summary(mod1)

### fonction anova
anova(mod1)

### modele avec contrainte
mod2 <- lm(O3~vent,data=ozone)
### tableau d'anova
anova(mod2)
### resume
summary(mod2)

### contraste treatment :
lm(O3~C(vent,treatment),data=ozone)
##ou 
lm(O3~vent,contrasts=list(vent="contr.treatment"), data = ozone)

### contraste treatment base 2e modalite
lm(O3~C(vent,base=2),data=ozone)

### contraste : orthogonalite
II <- length(levels(ozone$vent))
nI <- table(ozone$vent)
CONTRASTE<-matrix(rbind(diag(II-1),-nI[-II]/nI[II]),II,II-1)
mod3 <- lm(O3~C(vent,CONTRASTE),data=ozone)
anova(mod3)
summary(mod3)

### contraste : somme
mod4 <- lm(O3~C(vent,sum),data=ozone)
##ou
lm(O3~vent,contrasts=list(vent="contr.sum"), data = ozone)
anova(mod4)
summary(mod4)

### residus
library(lattice)
resid2 <- resid(mod2)
## boxplot par vent
plot(resid2~vent,data=ozone,ylab="residus")
## par secteur
plot(resid2~jitter(fitted(mod2)),xlab="ychap",ylab="residus")
xyplot(resid2~I(1:50)|vent,data=ozone,xlab="index",ylab="residus")
### qqplot
plot(mod2,which=2)


############################################################
### L'ozone: ANOVA 2
############################################################
###interaction ?
par(mfrow=c(2,1))
with(ozone,interaction.plot(vent,NEBU,O3,col=1:2))
with(ozone,interaction.plot(NEBU,vent,O3,col=1:4))

### effet nebulosite ?
mod1 <- lm(O3~vent+NEBU+vent:NEBU,data=ozone)
mod2 <- lm(O3~vent+NEBU,data=ozone)
anova(mod2,mod1)

### effet vent ?
mod3 <- lm(O3~vent,data=ozone)
anova(mod3,mod2)

## tout ensemble
anova(mod3,mod2,mod1)
