#gnuplot file
set xlabel "Libor"
set ylabel "Time"
set title "Regularized Vol 01_aug_2014, pelT0.01, pelM=1e-4"
#set style data lines
set hidden3d
set pm3d at sb
#set cntrparam levels 10
#set contour base
splot "Regularized_calibrated_Vol_01_aug_2014.dat"
pause -1 " Hit return to save image" 
#set terminal postscript eps
#set output "Regularized_calibrated_Vol_01_aug_2014.eps"
#replot
