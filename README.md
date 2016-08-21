# comp-phys
A set of C++ libraries for doing numerical physics!!! It includes
a vector class, and tenth order Runge-Kutta method with adaptive step and
error checking.
- [Things to note.](#)
- [vec.h](#)
	- [vector](#)
	- [nvector](#)
		- [The Cool Extra Thing about nvector](#)
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
can remember the order easily as you do this.

# rk10.h