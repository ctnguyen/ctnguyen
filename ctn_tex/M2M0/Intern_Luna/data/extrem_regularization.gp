#gnuplot file
set xlabel "Libor"
set ylabel "Time"
set title "Highly Regularized Calibration Result"
#set style data lines
set hidden3d
set pm3d ; set palette
#set cntrparam levels 10
#set contour base
splot "extrem_regularization.dat"
#pause -1 " Hit return to save image" 
#set terminal postscript eps
#set output "extrem_regularization.eps"
#replot
