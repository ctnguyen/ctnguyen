############################################################
### La californie
############################################################
### donnees
calif <- read.table("californie.txt",header=T,sep=";")
n <- nrow(calif)
X <- cbind(rep(1,n),data.matrix(calif[,-1]))
y <- data.matrix(calif[,1])
### dependance spatiale
M <- t(data.matrix(read.table("wijcalifornie_isolationisland.txt",sep=";")))
apply(M,1,sum) # ok
vpr <- as.real(eigen(M,only=T)$values)

### vraisemblance concentree
concentree <- function(rho,MM,nn,yy,XX) {
  AA <- diag(nn)-rho*MM
  PP <- AA%*%(diag(nn)-XX%*%solve(crossprod(AA%*%XX))%*%t(XX)%*%crossprod(AA))%*%yy
  res <- 0.5*nn*log(crossprod(PP))-0.5*(log(det(crossprod(AA))))
  return(res)
}
resconc <- optimize(concentree,c(-1,1),MM=M,nn=n,yy=y,XX=X)

### estimation
rhoconc <- resconc$minimum
A <- diag(n)-rhoconc*M
betaconc <- solve(crossprod(A%*%X))%*%t(X)%*%crossprod(A)%*%(as.matrix(calif[,"nbe.plante"]))
sigmaconc <- sqrt(as.vector(crossprod(A%*%(as.matrix(calif[,"nbe.plante"])-X%*%betaconc)))/n)

### ecart type
ecarttype <- function(rhoo,sigmaa,XX,MM,vprr) {
  AA <- diag(nrow(MM))-rhoo*MM
  V <- sigmaa^2*solve(rbind(cbind(matrix(c(2*nrow(MM),2*sigmaa*
  sum(diag(MM%*%solve(AA))),2*sigmaa*sum(diag(MM%*%solve(AA))),
  sigmaa^2*sum(diag(t(MM%*%solve(AA))%*%MM%*%solve(AA)))+sigmaa^2*
  sum(vprr^2/(1-rhoo*vprr)^2)),2,2),matrix(0,2,4)),
  cbind(matrix(0,4,2),crossprod(AA%*%XX))))
  return(sqrt(diag(V)))
       }
ecarttype(rhoconc,sigmaconc,X,M,vpr)

