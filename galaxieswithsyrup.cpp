#include "vec.h"
#include "rk10.h"

#include <cmath>
#include <fstream>
#include <iostream>

#define SIMTIME 30

using namespace std;
using namespace eqm;


//I defined long double as T in rk10.h and vec.h.
nvector galaxy(nvector r, T t);	//function prototype for declaration.

T G = 10.;
T M1 = 1.;
T M2 = 1.;
T b  = 0.1;
T bb = b*b;

int main(int argc, char const *argv[])
{
	//open up our file to write to
	fstream file("syrupgalaxies.dat", fstream::out | fstream::app);

	//some initial positions.
	vector r1( 1,0,0);
	vector r2(-1,0,0);
	vector v1(0,1,0);
	vector v2(0,-1,0);

	nvector r;
	r = r << r1 << r2 << v1 << v2; //remember the order.

	rk10 simulation(galaxy, r); 

	// if we don't use .time, or .timestep, we can recover from a backup file.
	// simulation.time(0);
	// simulation.timestep(10);

	simulation.seterr(0,1e-10);	

	while( simulation.time() < SIMTIME ){
		simulation.step(simulation.time() + 0.1); //That way I record numbers at a decently coarse scale.

		simulation.R() >> r1 >> r2 >> v1 >> v2;
		// cerr << simulation.R() << endl;
		cout << "Time is " << simulation.time() << endl;
		file << simulation.time() << ' ' << vector(r1[0], r1[1],r2[0]) << ' ' << r2[1] << endl;
		// file << simulation.time() << ' ' << 1+(.5*M1*v1*v1 + .5*M2*v2*v2 - 1*G*M1*M2/(r1-r2).mag())/4 << endl;

	}
	return 0;
}

nvector galaxy(nvector r, T t){
	nvector drdt;      	//here's the vector that returns the derivative of r
	vector r1,r2,v1,v2;	//we break apart r for easier calculations
	vector F1,F2;
	r >> r1 >> r2 >> v1 >> v2;

	F1 = G*M1*M2/pow((r1-r2).mag(),2)*(r2-r1).uv() - b*v1;	//linear drag
	F2 = G*M1*M2/((r1-r2)*(r1-r2))*(r1-r2).uv() - b*v2;   	//quadratic drag
	//checkout how easy it is to compute our forces! Easy to error check and easy to write.

	//Now just return drdt;
	// drdt = drdt << v1 << v2 << F1/M1 << F2/M2;
	// and do return drdt;
	//or skipping the assignment, we can just do
	return drdt << v1 << v2 << F1/M1 << F2/M2;
}