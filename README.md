# comp-phys
A set of C++ libraries for doing numerical physics!!! It includes
a vector class, and tenth order Runge-Kutta method with adaptive step and
error checking, and calculation back up!!!
- [Things to note.](#things-to-note)
- [vec.h](#vech)
	- [vector](#vector)
	- [nvector](#nvector)
		- [The Cool Extra Thing about nvector](#the-cool-extra-thing-about-nvector)
- [rk10.h](#rk10h)

#Things to note.
Everything is in the eqm namespace, so to access everything you either need
to add `eqm::` or `using namespace eqm`

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
`nvector` extends the functionality of `vector` to ndimensions! Plus a little extra.
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
r >> u >> v;	// note that r is still 6 dimensional an unchanged.

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



## Backup

## Changing rk10
You can make it a twentieth order method (and they *do* exist) if you want! All you need to do is change
the matricies `ak`, `ck`, and `bkj` and the appropriate dimensions all throughout the code,
as well as the calculation for the error nvector which will then be different.

The key to making implementing runge-kutta painless, is remember that at the heart of RK methods
is the incremental guess of what our approximation derivative is is, if y' = f(t,x) is our differential
equation, we make first guess `y' ~ k[0] = f(t,x)`, then we make another guess based on our 
last guess, `k[1] = f(t + a*dt, x + dt*b*k[0])` and then make yet another guess based on all our previous
guesses yet again (usually in some new way. Then after that, we choose our ultimate final guess to be some
 weighted sum of our previous guesses. 
