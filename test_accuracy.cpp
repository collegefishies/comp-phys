#include "rk10.h"
#include <iomanip>
#include <fstream>
#include <cmath>


using namespace std;

double k = 1/100.;

eqm::nvector yp(eqm::nvector y, eqm::T t){
	for (int i = 0; i < 15; ++i)
	{
		y[i] = k*(i+1)*y[i];
	}
	return y;
}

eqm::nvector yexact(long double t){
	eqm::nvector y(15);
	for (int i = 0; i < 15; ++i)
	{
		y[i] = std::exp(k*(i+1)*t);
	}
	return y;
}
int main(int argc, char const *argv[])
{
	eqm::nvector y(15);
	for (int i = 0; i < 15; ++i)
	{
		y[i] = 1;
	}

	eqm::rk10 integrator(yp, y, false); //no backup.
	integrator.timestep(0.0001);
	integrator.seterr(0,1e-20);
	std::fstream f("accuracy.dat", std::fstream::out);
	// integrator.time(1);
	f << std::setprecision(20);
	while(integrator.time() < 2){
		// std::cout << "dt is: " << integrator.timestep() << std::endl; 
		std::cout << "t is: " << integrator.time() << std::endl; 
		double t = integrator.time();
		integrator.step(t+0.1);
		f << t << ' ';
		y = yexact(t) - integrator.R();
		for (int i = 0; i < 15; ++i)
		{
			// f << log(abs(y[i]))-log(abs(yexact(t)[i]))<< ' ';
			f << log(abs(y[i]))  << ' ';
			// f << log(1 - y[i]/yexact(t)[i])  << ' ';
		}
		f << std::endl;
		f.flush();
	}
	return 0;
}