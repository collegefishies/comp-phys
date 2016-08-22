set terminal pngcairo
set output "logdiff.png"
plot for [i = 2:16] "accuracy.dat" u 1:i w l t ''
set output 