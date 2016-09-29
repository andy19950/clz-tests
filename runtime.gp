set logscale x 10
set grid
set title "time_compare"
set term png  enhanced font 'Verdana,10'
set output "runtime.png"
set xlabel "N"
set ylabel "time(ms)"

plot "result_clock_gettime.csv" using 1:2 with lines title 'clz_recur', \
'' using 1:3 with lines title 'clz_itera', \
'' using 1:4 with lines title 'Harley'

