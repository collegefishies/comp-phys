OPT=-Ofast

galaxieswithsyrup: galaxieswithsyrup.cpp vec.o rk10.o
	g++ $(OPT) vec.o rk10.o galaxieswithsyrup.cpp -o syrup

vec.o: vec.h vec.cpp
	g++ $(OPT) -c vec.cpp

rk10.o: rk10.h rk10.cpp
	g++ $(OPT) -c rk10.cpp