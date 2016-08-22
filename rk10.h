#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include "vec.h"

//this preprocessor directive checks to see whether our parent source file
//has already defined rk10 or not. If so, it does nothing. Note how the source
//code is entirely contained in the #ifndef ... #endif block
#ifndef _RK10_H
#define _RK10_H

/*	Remember how you have to use std::cout whenever you want to use 
  	 cout? Either that or declare that you're "using namespace std"?
  	 Well we can make our own. In this case I named mine "eqm". This 
  	 is particularly useful since I'm naming things that are already 
  	 defined out there in the world. Like "vector" which if you're using
  	 vector.h would be a conflict. However with name spaces! (if you don't
  	 do 'using namespace std' AND 'using namespace eqm'; but maybe there are
  	 work arounds for this....) you won't run into conflicts by using
  	 eqm::vector VS. std::vector. You can also rename my namespace to something
  	 you want, you'll need to look up how you can use the namespace keyword.

	 As long as I'm in eqm, everything I define is in the eqm namespace, and I'll 
	 need to say that when I'm accessing it in my main.cpp.
*/
namespace eqm{
	//Here I'm defining a new type! "hamilton". Which is a 
	// pointer to a function! That's write you can use function
	// pointers so you can pass you're custom function to different
	// places! In this case, the function in your main, to this rk10
	// class. To define new function pointers (discussed on line 54) 
	// you need only do
	//			hamilton f;
	//
	typedef long double T; //because long double is annoying to write.
	typedef nvector (*hamilton)(nvector x, T t);
	//here I'm declaring rk10. I'm just saying it exists.
	class rk10;

	//here I'm defining rk10. I'm giving it meat.
	class rk10{
	private:
		//here, I'm declaring that I have some constant matricies I would like 
		//define later. I define them in rk10.cpp. Once I define them I can't define
		//them again, thats why they're const. The static part says that whenever you 
		//see the workds, bkj, ak, ck, they each resp. point to the SAME array. That is
		//if I have 5 runge-kutta methods, they'll all refer to the same constants in 
		//memory. This saves some space. It doesn't hurt to do so as far as I know.
		const static T bkj[17][17];
		const static T ak[17];
		const static T ck[17];

		//declare variables to be used by our class,
		std::ofstream backup;
		T dt, t;
		T errmax; //our desired error bound.
		T errmin; //our desired error bound.
		int errs,errcounts;	//the number of times we tried to change dt to reduce/increase error 
		                   	//and the most amount of times we can do that.
		T alpha; //the factor by which we change our timestep.
		hamilton F;	//our force function POINTER
		//if you don't know what a pointer is, its a variable that holds the address of
		//other data types in C++. Everything in the computer has an address. It's how
		//it navigates from file to file, and from C++ from variable to function to array.
		//You can access the address of something with &, that is if you define
		//		double x; 
		//	 &x; is the address of x.
		// This goes for any type. Not just doubles or integers.
		//Passing addresses are especially useful when the things you want to transfer are
		//massive. Like files. Normally function calls f(x) copy x. If you instead transferred
		// the address of x in a function g(&x), it would only copy the address of x, which is
		// smaller. Now once you have the address how do you access the data? with a unary (one-argument)
		// operator *. That is given the address &x of x. You can call for its value using *,
		//		*&x == x
		// Isn't that cool?? Now that's how you manipulate an address, and read an address. If you wan't
		// to declare variables that HOLD addresses specifically (as opposed to data), you can
		// use double* a; or double *a; they're the same. Guess what this code does
		//		a = &x;
		//		y = *a;
		//We can do similar stuff for functions. We can get their address using &, &f.
		//and access their contents using *(&f), however DEFINING variables to hold their addresses
		//is actually more complicated! It's not like you can do
		//		double ()(double x)* a;
		//although that's close. What you have to do is this.
		//		double (*a)(double x); and that declares a variable a which will hold
		//addresses to functions that take one double and return one double.
		//Its very picky but so is everything else in C++. (Until you use templates! Then the world becomes
		//so much brighter...)

		nvector  r;	//our position vector. also defined in the eqm namespace in vec.h
	public:
		//constructor! this says whenever we define a member of the class rk10, we need to 
		//pass two arguments, a function address, hamilton G, and a pointer to r0.
		rk10(hamilton G, nvector r0, bool backup=true);
		rk10(const rk10&){ std::cout << "Error! You shouldn't be calling the rk10 copy constructor.\n";
			std::cout << "If you really believe you should. Change rk10.h. Quitting!" << std::endl;
			exit(1);
		};
		~rk10();
		void seterr(T minerr, T maxerr);
		void setalpha(T x){alpha = x;};
		void settrials(int x){errcounts = x;};
		T time(){return t;};
		T time(T x){t=x; return t;};
		T timestep(){return dt;};
		T timestep(T x){
			x = std::abs(x);
			if(x < 1e-200)
			{
				dt = 0.01; 
				std::cerr << "dt == " << abs(x) << std::endl;
				std::cerr << "Warning! rk10.timestep() detected dt == 0! Setting dt = 0.01" << std::endl;
			} else {
				dt = x;
			}
			return dt;
		};

		T step();   	//returns the error of the ultimate calculation
		T step(T t);	//returns the error of the ultimate calculation
		nvector R(){return r;};
	};

}//done with eqm
#endif