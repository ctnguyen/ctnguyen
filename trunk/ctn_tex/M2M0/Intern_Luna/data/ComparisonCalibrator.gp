#
set title "Calibrator Comparison with positive Constraint"
set datafile separator ","
set ylabel "absolute error (L1)"
set xdata time
set timefmt "%d/%m/%Y"
set format x "%b/%Y"
#unset xtics
set xtics rotate by -45 offset 0,-0.01
set xrange ["01/01/2008":"01/07/2014"]
set xtics "01/01/2008",7776000,"01/07/2014"
set xlabel "VCUB Date"

plot "ComparisonCalibrator_gPositive.dat" using 1:2 w lines title columnheader(2), \
     "ComparisonCalibrator_gPositive.dat" using 1:3 w lines title columnheader(3), \
     "ComparisonCalibrator_gPositive.dat" using 1:4 w lines title columnheader(4)

#set title "Calibrator Comparison without positive Constraint"
pause -1 "Hit return to continue"
#set terminal postscript eps enhanced color font 'Helvetica,10'
#set output 'Comparison_gNegative.eps'
#set output 'Comparison_gPositive.eps'
#replot