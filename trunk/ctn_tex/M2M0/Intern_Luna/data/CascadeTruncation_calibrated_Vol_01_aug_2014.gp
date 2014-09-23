#gnuplot file
set xlabel "Libor"
set ylabel "Time"
set title "Cascade Truncated 6,8,9,11 YR, calibrated Vol 01_aug_2014"
#set style data lines
set hidden3d
set pm3d at sb
#set cntrparam levels 10
#set contour base
splot "CascadeTruncation_calibrated_Vol_01_aug_2014.dat"
pause -1 " Hit return to save image" 
#set terminal postscript eps
#set output "CascadeTruncation_calibrated_Vol_01_aug_2014.eps"
#replot
