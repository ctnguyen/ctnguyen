#
set xlabel "Indices on Diag"
set ylabel "g diag value"

set title "Regularized Diagonal Example"

plot "diag_compare.dat" using 1:2 w lines title columnheader(2), "diag_compare.dat" using 1:3 w lines title columnheader(3)
	 
pause -1 "Hit return to continue"
set terminal postscript eps enhanced color font 'Helvetica,10'
set output 'diag_compare.eps'
replot