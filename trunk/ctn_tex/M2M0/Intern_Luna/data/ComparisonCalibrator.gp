#
set title "Calibrator Comparison with positive Constraint"
set datafile separator ","
set ylabel "absolute error (L1)"
set xdata time
set timefmt "%d/%m/%Y"
set format x "%b/%Y"
#unset xtics
set xtics rotate by -45 offset 0,-0.01
set mxtics 1
set xlabel "VCUB Date"

plot "gPositive.dat" using 1:2 w lines title columnheader(2), \
     "gPositive.dat" using 1:3 w lines title columnheader(3), \
     "gPositive.dat" using 1:4 w lines title columnheader(4)

#set title "Calibrator Comparison without positive Constraint"
pause -1 "Hit return to continue"
#set terminal postscript eps enhanced color font 'Helvetica,10'
#set output 'Comparison_gNegative.eps'
#set output 'Comparison_gPositive.eps'
#replot