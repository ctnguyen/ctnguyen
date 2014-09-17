#gnuplot file
set xlabel "Time Homogeneity coeff"
set ylabel "Libor Penalty Coeff"
set zlabel "Error(%)"

set pm3d; set palette
set log x
set log y
#set contour base
#set cntrparam levels 10

set title "Param Error Regularized Calib" 
splot "penalty_analysis_gVirtual_error.dat"

#set title "Quoted Error Regularized Calib" 
#splot "penalty_analysis_quoteVirtual_error.dat"

#pause -1 " Hit return to save image" 
#set terminal postscript eps
#set output "penalty_analysis_gVirtual_error.eps"
#set output "penalty_analysis_quoteVirtual_error.eps"
#replot