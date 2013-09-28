######################################################
#######  m2mo Laure Elie TP1 Applications   ##########
######################################################

#!!! Set the PROJECT_ROOT_DIRECTORY as the working directory
## i.e ".." from this file

tab=read.table("data/immo.txt", header=TRUE, sep=";") # Read the data file from the data folder
tab[,1];
tab$surface;
tab[,c(1,3)];
tab$transaction;
## Reponse 1 : the data containing in the immo.txt file composed of 3 variables, 20 observations

#postscript('figure/my_plot_tab.ps');
plot(tab);
#dev.off();

## Reponse 2 : Because there are 3 variables, the plot function of the data frame plot
##             each variable in function of other, then there are 6 graphics.

cor(tab);
## Reponse  : the variable "valeur" is hightly correlated to the variable "surface"

rm(tab); # remove the tab object at the end of the program