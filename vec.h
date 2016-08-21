#include <iostream>
#include <cmath>
#include <stdlib.h>  //has exit

#ifndef _VEC_H
#define _VEC_H

namespace eqm {
	typedef long double T;
	class vector;
	class nvector;

	vector operator*(const eqm::T&, const vector&); //multiplication by a scalar left hand side
	nvector operator*(const eqm::T&, const nvector&); //multiplication by a scalar left hand side
	std::ostream& operator<<(std::ostream&, const eqm::vector&);
	std::ostream& operator<<(std::ostream&, const eqm::nvector&);
	eqm::nvector operator<<(const eqm::nvector&, const eqm::vector&);
}


class eqm::nvector{
private:
	eqm::T* a;
	int dimension;
public:
	nvector();
	nvector(int dim);
	nvector(const eqm::nvector&);
	~nvector();

	int dim(){ return this->dimension; };

	//access
	eqm::T& operator[](int index);
	eqm::T  operator[](int index) const;

	//concatenating & disecting vectors
	friend eqm::nvector eqm::operator<<(const eqm::nvector&, const eqm::vector&);
	eqm::nvector operator>>(eqm::vector&) const;

	//arithmetic
	eqm::nvector operator+(const eqm::nvector& x) const;              	//addition
	eqm::nvector operator-(const eqm::nvector& x) const;              	//subtraction
	eqm::nvector operator/(const eqm::T x) const;                     	//division
	eqm::nvector operator*(const eqm::T x) const;                     	//scalar product
	friend eqm::nvector operator*(const eqm::T&, const eqm::nvector&);	//scalar product
	eqm::nvector operator-() const;                                   	//negation

	eqm::nvector operator=(const eqm::nvector& x);

	friend std::ostream& operator<<(std::ostream&, const eqm::nvector&);
};


class eqm::vector{
private:
	eqm::T x, y, z;
public:
	// constructor
	vector();
	vector(eqm::T x);
	vector(eqm::T x,eqm::T y);
	vector(eqm::T x,eqm::T y,eqm::T z);
	// copy constructor
	vector(const eqm::vector&);
	// destructor
	~vector();

	//access
	eqm::T& operator[](int index);
	eqm::T  operator[](int index) const;

	//arithmetic
	eqm::vector operator+(const eqm::vector& x) const;              	//addition
	eqm::vector operator-(const eqm::vector& x) const;              	//subtraction
	eqm::vector operator/(const eqm::T x) const;                    	//division
	eqm::vector operator*(const eqm::T x) const;                    	//scalar product
	friend eqm::vector operator*(const eqm::T&, const eqm::vector&);	//scalar product
	eqm::vector operator-() const;                                  	//negation
	eqm::vector operator^(const eqm::vector& x) const;              	//cross product
	eqm::T operator*(const eqm::vector& x) const;                   	//dot product

	//attributes
	eqm::T mag() const;    	//magnitude
	eqm::vector uv() const;	//unit vector
	//output
	friend std::ostream& operator<<(std::ostream&, const eqm::vector&);

	//nvector friendly
	friend eqm::nvector eqm::operator<<(const eqm::nvector&, const eqm::vector&);

	void printcontents();
};

#endif