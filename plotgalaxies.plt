set size square 

set xrange [-1.5:1.5]
set yrange [-1.5:1.5]
# set yrange [-1:1]
set title "GMM = 10, b = 0.1"
set term pngcairo
set output "milkway.png"
plot "syrupgalaxies.dat" u 2:3 w l t "Planet Green", "" u 4:5 w l t "Planet Blue"
# plot "syrupgalaxies.dat" u 1:2 w l t "Energy"

# plot "syrupgalaxies.dat" u 1:2 w l t "Energy"
set output 