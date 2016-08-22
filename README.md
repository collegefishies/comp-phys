# comp-phys
A set of C++ libraries for doing numerical physics!!! It includes
a vector class, and tenth order (unconfirmed) Runge-Kutta method with adaptive step and
error checking, and calculation back up!!!
The paper used for implementing RK10 can be found [here](https://web.archive.org/web/20160821182327/http://sce.uhcl.edu/feagin/courses/rk10.pdf)
- [Things to note.](#things-to-note)
- [vec.h](#vech)
	- [vector](#vector)
	- [nvector](#nvector)
		- [The Cool Extra Thing about nvector](#the-cool-extra-thing-about-nvector)
- [rk10.h](#rk10h)
	- [Checking out the source code](#checking-out-the-source-code)
	- [Using rk10 without backup](#using-rk10-without-backup)
		- [How to use F](#how-to-use-f)
		- [How to initialize the rk10 class](#how-to-initialize-the-rk10-class)
			- [Changing Simulation Parameters](#changing-simulation-parameters)
			- [Running rk10!](#running-rk10)
	- [Backup](#backup)
	- [Changing rk10](#changing-rk10)

		**(made with doctoc.herokuapp.com)**

#Things to note.
Everything is in the eqm namespace, so to access everything you either need
to add `eqm::` or `using namespace eqm`

If you're a primo-coder who doesn't want to read through my verbosity, just check out
`vec.h` and `rk10.h` for almost everything you need to know. Be warned that `rk10.h`
is verbose too.

# vec.h
Contains two classes, `eqm::nvector` and `eqm::vector`.
## vector
For `eqm::vector`, all the arithmetic operations are supported.
```c++
eqm::vector u;       	//declare a vector with no argument u == vector(0,0,0);
eqm::vector v(2);    	//declare a vector with 1 argument  v == vector(2,0,0);
eqm::vector w(2,1);  	//w == vector(2,1,0);
eqm::vector v(3,1,2);	//v == vector(3,1,2);

double a,b;
//All possible arithmetical 3D operations.
u = a*v;	//multiplication by a scalar
u = v*a;	
u = v/a;	// division by a scalar!!
u = v+w;	//addition and subtraction
u = v-w;
u = -v + w; //negation

a = v*w;    	//the dot product.
u = v^w;    	//the cross product.
a = u*(v^w);	//the scalar triple product! Y(*o*)Y~~~~

a = v.mag();	//magnitude
u = v.uv(); 	//and unit vector.

//You can also define certain elements
v[0] = 1;
v[1] = 2;
v[2] = 3;

//and print it out to the terminal/file
cout << v << endl; //is defined!!
```
## nvector
`nvector` extends the functionality of `vector` to n-dimensions! Plus a little extra.
This extra, is the ability to concatenate `vector`s to an `nvector` as well as rip it 
apart again.
It only has a vector space structure. That is only the operations in the following block
are defined.
```c++
eqm::nvector u(17);	//a 17 dimensional vector
eqm::nvector v(17);	//a 17 dimensional vector
eqm::nvector w(17);	//a 17 dimensional vector
double a,b;
v[13] = 3;
w[13] = .1L;

u = a*(-v) - (w/b) + a;
```

Zero dimensional vectors are also possible!! (This *is* useful btw cus I've got **more** features!!)
For `eqm::nvector` the following operations are 

```c++
//All possible arithmetical 3D operations.
u = a*v;	//multiplication by a scalar
u = v*a;	
u = v/a;	// division by a scalar!!
u = v+w;	//addition and subtraction
u = v-w;
u = -v; //negation

//*********************
//nvector specifics!!
//*********************

u.dim() //returns the dimension of u!!!
u[i]    //also works!!

// u,v are of different dimension, the program quits!!! (and gives an error message.)
// Hooray error checking!!
```

### The Cool Extra Thing about `nvector`
Suppose you have an arbitrary number of vectors, that you want to pass to a function,
and still preserve the vector space structure, you can with `nvector`s!!!

```c++
using namespace eqm;
using namespace std;
vector x(1,2,3);
vector v(-1,-1,0);

vector u,v;
nvector r;	//note that it's of zero dimension (for now).

r = r << x << v; // r is unchanged until we do assignment
r >> u >> v;	// note that r is still 6 dimensional and unchanged.

cout << r << endl;
cout << "u is: " << u << endl;
cout << "v is: " << v << endl;
```

This prints out
```
1 2 3 -1 -1 0
u is: 1 2 3
v is: -1 -1 0
```

Some interesting things about `<<` and `>>`, if we instead did
```c++
r >> u;
r >> v;
```
Both `u` and `v` would be the same. If we wanted the behavior of v being the rest of r such as in
`r >> u >> v;` then we could do
```c++
r = r >> u;
r = r >> v;
```
As would be useful in a loop. Also note that `>>` pulls the first three elements out of `r`. So you
if you remember the order in which you put vectors, you know which way they'll come out, i.e, 
```c++
r = r << x << y << z;
r = r >> x >> y >> z;
```
does (in effect) nothing.

# rk10.h

Oooo! This is a cool puppy, it makes implementing a runge-kutta method painless!
It also has backup functionality!! So if your code takes a dip, you can pick up from
the same spot!!

## Checking out the source code

For those who are interested in how rk10 works, I kind of started commenting it heavily,
it isn't completely done. But there is stuff in there.

## Using rk10 without backup
To define a system that you want to integrate, you need to define first and foremost,
the first order differential equations that define it, and the starting point.
The format of these are
```c++
nvector F(nvector r, long double t);	//the function that calculates our first derivatives
nvector r;                          	//defines all our initial positions.
```

### How to use F
If you want to see why I did it this way, we can begin to see the full generality of F
by considering a two particle system with quadratic drag. Let's suppose they're like
planets and they orbit around each other with a 1/r^2 force between them. We can define they're initial
position like so
```c++
using namespace eqm;

//some initial positions.
vector r1( 1,0,0);
vector r2(-1,0,0);
vector v1(0,1,0);
vector v2(0,-1,0);

nvector r;
r = r << r1 << r2 << v1 << v2; //remember the order.
```

In our function definition just before, or after `main`
```c++
using namespace eqm;

nvector galaxy(nvector r, long double t){
	nvector drdt;      	//here's the vector that returns the derivative of r
	vector r1,r2,v1,v2;	//we break apart r for easier calculations
	vector F1,F2;
	r >> r1 >> r2 >> v1 >> v2;

	F1 = -G*M1*M2/pow((r1-r2).mag(),2)*(r2-r1).uv() - b*v1;       	//linear drag
	F2 = -G*M1*M2/((r1-r2)*(r1-r2))*(r1-r2).uv() - bb*v1.mag()*v1;	//quadratic drag
	//checkout how easy it is to compute our forces! Easy to error check and easy to write.

	//Now just return drdt;
	drdt = drdt << v1 << v2 << F1/M1 << F2/M2;
	// and do return drdt;
	//or skipping the assignment, we can just do
	return drdt << v1 << v2 << F1/M1 << F2/M2;
}
```

Note that this was relatively simple to write and can be easily extended to N particles!
Finite element analysis for a 305 project anyone??

### How to initialize the rk10 class

To initialize the rk10 class we just need to have our initial position vector ready,
and our derivatives function ready. Using what we have from the previous section,

```c++

int main(){
	eqm::rk10 simulation(galaxy, r, false); //the false turns off the backup functionality.
// ...
```
Note that by definition of rk10 constructor, we should really pass `&galaxy`: the *address* 
to the galaxy function, but g++ doesn't seem to have problems dealing with ambiguity
between functions and pointers to functions.

Now, **by default**, t = 0, and dt = 0.01. If you don't want that, there are member functions
of rk10, that let you change that.

#### Changing Simulation Parameters
Here are useful rk10 member functions
```c++
void seterr(T minerr, T maxerr);      	//sets error bounds, so you're accurate enough, but not too accurate.
void setalpha(T x){alpha = x;};       	//Everytime you're not accurate enough rk10, changes dt by a factor 
                                      	//alpha. You can set alpha with this function.
void settrials(int x){errcounts = x;};	//Sometimes your simulation is hopeless and for no dt will your
                                      	//simulation ever have the desired error. This is the max attempts
                                      	//that the simulation will try decreasing dt by alpha. For a given
                                      	//step calculation.

T time(){return t;};        	//This returns the time of the simulation
T time(T x){t=x; return t;};	//This returns the time of the simulation as well as sets it.
T timestep(){return dt;};  
T timestep(T x){dt = x; return dt;};	// You can set and read dt with this function.
nvector R(){return r;};             	// This returns the configuration space vector that describes
                                    	// your system.
```

#### Running rk10!
You can find a sample rk10 simulation in `galaxieswithsyrup.cpp`.
You can use the makefile to run it and plot it, provided you have `gnuplot.`

 If you don't want hints though and just want
to make your own, the function that actually proceeds with the integration is 
```c++
step([t]);
```
It belongs to rk10, and it simulates until time `t`, so if you don't need to record the integration details 
in between 0 and 10 seconds, you can ignore them if you wish. If you call it with no argument, it integrates
for one step. 

To record, the position after it is finished calculating you can call `R()` which returns
the current position `nvector`. 
## Backup

Using backup functionality requires some finesse, which is nothing more than a couple if statements.
However note that the `rk10.bak` will get destroyed at the end of the simulation, so if you would like
to save data for extension, remove the `remove` statement in the `rk10` deconstructor `~rk10()`.
```c++
using namespace std;

ifstream isbackup("rk10.bak");	//attempt to open the .bak file
fstream  datafile("some.dat")
if(!isbackup){
	datafile.open(fstream::out | fstream::trunc);
} else {
	datafile.open(fstream::out | fstream::app);	//append if there is existing data
}

rk10 simulation(F,r0);
simulation.seterr(0,1e-6);

if(!isbackup){  //only set initial time if we're not picking off from previous data.
	simulation.time(0);
	simulation.timestep(0.001);
}

while(simulation.time() < T){
	//....
```



## Changing rk10
You can make it a twentieth order method (and they *do* exist) if you want! All you need to do is change
the matricies `ak`, `ck`, and `bkj` and the appropriate dimensions all throughout the code,
as well as the calculation for the error nvector which will then be different.

The key to making implementing Runge-Kutta painless, is remember that at the heart of RK methods
is the incremental guess of what our approximation derivative is is, if y' = f(t,x) is our differential
equation, we make first guess `y' ~ k[0] = f(t,x)`, then we make another guess based on our 
last guess, `k[1] = f(t + a*dt, x + dt*b*k[0])` and then make yet another guess based on all our previous
guesses yet again (usually in some new way. Then after that, we choose our ultimate final guess to be some
 weighted sum of our previous guesses. 
