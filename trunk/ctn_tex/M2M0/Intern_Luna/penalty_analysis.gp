#gnuplot file
set xlabel "Time Homogeneity coeff"
set ylabel "Libor Penalty Coeff"
set zlabel "Error(%)"
#set style data lines
set pm3d; set palette
set log x
set log y
#set cntrparam levels 10
#set contour surface
set hidden3d
##set title "Quotation Error Virtual Regularized Calib" 
##splot "penalty_analysis_quoteVirtual_error.dat"
set title "Param Error Virtual Regularized Calib" 
splot "penalty_analysis_gVirtual_error.dat"

pause -1 " Hit return to save image" 
#set terminal postscript eps
#set output "penalty_analysis_quoteVirtual_error.eps"
#set output "penalty_analysis_gVirtual_error.eps"
#replot

#set pm3d map
#set palette gray