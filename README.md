# comp-phys
A set of C++ libraries for doing numerical physics!!!

#Things to note.
Everything is in the eqm namespace, so to access everything you either need
to add `eqm::` or `using namespace eqm`

# vec.h
Contains two classes, `eqm::nvector` and `eqm::vector`.

For `eqm::vector`, all the arithmetic operations are supported.
```c++
eqm::vector u;       	//declare a vector with no argument u == vector(0,0,0);
eqm::vector v(2);    	//declare a vector with 1 argument  v == vector(2,0,0);
eqm::vector w(2,1);  	//w == vector(2,1,0);
eqm::vector v(3,1,2);	//v == vector(3,1,2);

double a,b;
//All possible 3D operations.
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