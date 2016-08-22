OPT=-Ofast

plt: syrupgalaxies.dat plotgalaxies.plt
	gnuplot plotgalaxies.plt
	echo "Made the png: milkway.png"

syrupgalaxies.dat: syrup
	./syrup.exe

syrup: galaxieswithsyrup.cpp vec.o rk10.o
	g++ $(OPT) vec.o rk10.o galaxieswithsyrup.cpp -o syrup

vec.o: vec.h vec.cpp
	g++ $(OPT) -c vec.cpp

rk10.o: rk10.h rk10.cpp
	g++ $(OPT) -c rk10.cpp

accuracy: test_accuracy.cpp rk10.o vec.o
	g++ $(OPT) vec.o rk10.o test_accuracy.cpp -o accuracy

accuracy.dat: accuracy
	./accuracy
pltacc: accuracy.dat
	gnuplot pltacc.plt

clean:
	rm *.o
