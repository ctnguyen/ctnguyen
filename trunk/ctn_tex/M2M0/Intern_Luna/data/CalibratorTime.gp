#
set xlabel "horizon(YR)"
set ylabel "time(s)"
set xrange[5:16]
set title "Time consuming of calibrator"
plot "CalibratorTime.dat" using 1:2 w lines title columnheader(2),\
     "CalibratorTime.dat" using 1:3 w lines title columnheader(3),\
     "CalibratorTime.dat" using 1:4 w lines title columnheader(4)
pause -1 "Hit return to continue"
set terminal postscript eps enhanced color font 'Helvetica,10'
set output 'CalibratorTime.eps'
replot