#
# gnuplot for Rebonato curve
#
#set samples 50
set xlabel "Time to maturity"
set yrange[0:0.6]
set title "abcd function"
a1=-0.02 ; b1=2.6 ; c1=2.2 ; d1=0.07
a2=0.07 ; b2=0.2 ; c2=0.6 ; d2=0.075
a3=0.3 ; b3=1.5 ; c3=5 ; d3=0.15
plot [0:10] (a1+b1*(x))*exp(-c1*(x))+d1 title "a=-0.02;b=2.6;c=2.2;d=0.07", \
            (a2+b2*(x))*exp(-c2*(x))+d2 title "a=0.07;b=0.2;c=0.6;d=0.075", \
			(a3+b3*(x))*exp(-c3*(x))+d3 title "a=0.3;b=1.5;c=5;d=0.15"
pause -1 "Hit return to continue"
set terminal latex
set output "gnuplot_abcdFunction.tex"
replot