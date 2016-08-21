#include "vec.h"
#include "rk10.h"

#include <cmath>
#include <fstream>
#include <iostream>

#define SIMTIME 100

using namespace std;
using namespace eqm;


//I defined long double as T in rk10.h and vec.h.
nvector galaxy(nvector r, T t);	//function prototype for declaration.

T G = 1;
T M1 = 1;
T M2 = 1;
T b  = 0.2;
T bb = b*b;

int main(int argc, char const *argv[])
{
	//open up our file to write to
	fstream file("syrupgalaxies.dat", fstream::out | fstream::trunc);

	//some initial positions.
	vector r1( 1,0,0);
	vector r2(-1,0,0);
	vector v1(0,1,0);
	vector v2(0,-1,0);

	nvector r;
	r = r << r1 << r2 << v1 << v2; //remember the order.

	rk10 simulation(galaxy, r);

	simulation.time(0);
	simulation.timestep(0.001);
	simulation.seterr(0,1e-6);	//to within one micron plz.

	while( simulation.time() < SIMTIME ){
		simulation.step(simulation.time() + 1); //That way I record numbers at a decently coarse scale.

		simulation.R() >> r1 >> r2;

		file << simulation.time() << ' ' << vector(r1[0], r1[1],r2[0]) << ' ' << r2[1] << endl;
	}
	return 0;
}

nvector galaxy(nvector r, T t){
	nvector drdt;      	//here's the vector that returns the derivative of r
	vector r1,r2,v1,v2;	//we break apart r for easier calculations
	vector F1,F2;
	r >> r1 >> r2 >> v1 >> v2;

	F1 = -G*M1*M2/pow((r1-r2).mag(),2)*(r2-r1).uv() - b*v1;       	//linear drag
	F2 = -G*M1*M2/((r1-r2)*(r1-r2))*(r1-r2).uv() - bb*v1.mag()*v1;	//quadratic drag
	//checkout how easy it is to compute our forces! Easy to error check and easy to write.

	//Now just return drdt;
	// drdt = drdt << v1 << v2 << F1/M1 << F2/M2;
	// and do return drdt;
	//or skipping the assignment, we can just do
	return drdt << v1 << v2 << F1/M1 << F2/M2;
}