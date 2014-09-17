#gnuplot file
set xlabel "Libor"
set ylabel "Time"
set title "g Calibrated PelTime=1,PelMaturity=0.1"
#set style data lines
set hidden3d
set pm3d ; set palette
#set cntrparam levels 10
#set contour base
splot "TwoPenalty.dat"
pause -1 " Hit return to save image" 
set terminal postscript eps
set output "TwoPenalty.eps"
replot
