#include <stdio.h>
#include <cmath>
#include "vec.h"


// ****************************************
// *******    eqm Namespace     ********
// ****************************************
eqm::vector eqm::operator*(const eqm::T& l, const eqm::vector& u){
	return u*l;
}

std::ostream& eqm::operator<<(std::ostream& stream, const eqm::vector& u){
	stream << u.x << ' ' << u.y << ' ' << u.z;
	return stream;
}

std::ostream& eqm::operator<<(std::ostream& stream, const eqm::nvector& u){
	if(u.dimension == 0){
		stream << "empty";
		return stream;
	}
	for (int i = 0; i < u.dimension-1; ++i)
	{
		stream << u.a[i] << ' ';
	}
	stream << u.a[u.dimension-1];

	return stream;
}

void eqm::vector::printcontents(){
	// printf("(%.3f, %.3f, %.3f)\n",x,y,z);
}



// ****************************************
// *********     Constructors       *******
// ****************************************

//-----------eqm::vector-------------------
eqm::vector::vector(){
	x = 0; y = 0; z = 0;
}

eqm::vector::vector(eqm::T x){
	this->x = x; y = 0; z = 0;
}

eqm::vector::vector(eqm::T x, eqm::T y){
	this->x = x; this->y = y; z = 0;
}

eqm::vector::vector(eqm::T x, eqm::T y, eqm::T z){
	this->x = x; this->y = y; this->z = z;
}

eqm::vector::vector(const eqm::vector& w){
	this->x = w.x;
	this->y = w.y;
	this->z = w.z;
};

eqm::vector::~vector(){
	//null
}

//-----------eqm::nvector-------------------
eqm::nvector::nvector(int dim){
	this->dimension = dim;
	a = new eqm::T[dim];
	for (int i = 0; i < dim; ++i)
	{
		a[i] = 0;
	}
}

eqm::nvector::nvector(){
	this->dimension = 0;
	a = new eqm::T;
	*a= 0;
}

eqm::nvector::nvector(const eqm::nvector& uu){
	this->dimension = uu.dimension;
	this->a = new eqm::T[this->dimension];
	for (int i = 0; i < this->dimension; ++i)
	{
		(this->a)[i] = uu.a[i];
	}
}

eqm::nvector::~nvector(){
	delete[] a;
}

// ****************************************
// ********       Operators        ********
// ****************************************

//-----------eqm::vector-------------------
//addition
eqm::vector eqm::vector::operator+(const eqm::vector& w) const{
	eqm::vector temp;
	temp.x = this->x + w.x;
	temp.y = this->y + w.y;
	temp.z = this->z + w.z;
	return temp;
}

//subtraction
eqm::vector eqm::vector::operator-(const eqm::vector& w) const{
	eqm::vector temp;
	temp.x = this->x - w.x;
	temp.y = this->y - w.y;
	temp.z = this->z - w.z;
	return temp;
}

//negation
eqm::vector eqm::vector::operator-() const{
	eqm::vector temp;
	temp.x = -this->x;
	temp.y = -this->y;
	temp.z = -this->z;
	return temp;
}
// the dot product
eqm::T eqm::vector::operator*(const eqm::vector& w) const{
	return this->x * w.x + this->y * w.y + this->z * w.z;
}

// the scalar product
eqm::vector eqm::vector::operator*(const eqm::T w) const{
	eqm::vector temp;
	temp.x = this->x * w;
	temp.y = this->y * w;
	temp.z = this->z * w;
	return temp ;
}

// the cross product
eqm::vector eqm::vector::operator^(const eqm::vector& w) const{
	eqm::vector temp;
	temp.x = (this->y * w.z - this->z*w.y);
	temp.y = (this->z * w.x - this->x*w.z);
	temp.z = (this->x * w.y - this->y*w.x);
	return temp;
}

//division by scalar
eqm::vector eqm::vector::operator/(const eqm::T w) const{
	eqm::vector temp;
	temp.x = this->x / w;
	temp.y = this->y / w;
	temp.z = this->z / w;
	return temp;
}

eqm::T eqm::vector::mag() const{
	return pow( (*this)*(*this),.5);
}

eqm::vector eqm::vector::uv() const{
	return (*this)/abs(this->mag());
}

//-----------eqm::nvector-------------------
eqm::nvector eqm::nvector::operator=(const eqm::nvector& x){
	delete[] a;
	a = new eqm::T[x.dimension];
	dimension = x.dimension;

	for (int i = 0; i < dimension; ++i)
	{
		a[i] = x[i];
	}

	return *this;
}

eqm::nvector eqm::nvector::operator+(const eqm::nvector& x) const{	//addition

	if (x.dimension != this->dimension){
		std::cerr << "Incorrect dimension: Addition: Quitting!\n";
		std::cerr << "Dimensions: " << this->dimension << " vs. " << x.dimension << std::endl;
		exit(1);
	}

	nvector temp(dimension);

	for (int i = 0; i < dimension; ++i)
	{
		temp[i] = a[i] + x.a[i];
	}

	return temp;
}

eqm::nvector eqm::nvector::operator-(const eqm::nvector& x) const{	//subtraction

	if (x.dimension != this->dimension){
		std::cerr << "Incorrect dimension: Subtraction: Quitting!\n";
		std::cerr << "Dimensions: " << this->dimension << " vs. " << x.dimension << std::endl;
		exit(1);
	}

	nvector temp(dimension);

	for (int i = 0; i < dimension; ++i)
	{
		temp[i] = a[i] - x.a[i];
	}

	return temp;
}

eqm::nvector eqm::nvector::operator/(eqm::T x) const{	//division

	nvector temp(dimension);

	for (int i = 0; i < dimension; ++i)
	{
		temp[i] = a[i]/x;
	}

	return temp;
}

eqm::nvector eqm::nvector::operator*(eqm::T x) const{	//multiplication

	nvector temp(dimension);

	for (int i = 0; i < dimension; ++i)
	{
		temp[i] = a[i]*x;
	}

	return temp;
}

eqm::nvector eqm::operator*(const eqm::T& x,const eqm::nvector& v){ //left multiplication
	return v*x;
}

eqm::nvector eqm::nvector::operator-() const{ //negation
	return -1*(*this);
}



//*****************************************
//*******      Element Accesss      *******
//*****************************************

eqm::T& eqm::vector::operator[](int index){
	switch(index){
		case 0:
			return this->x;
			break;
		case 1:
			return this->y;
			break;
		case 2:
			return this->z;
			break;
		default:
			std::cout << "vector::index" << index << "not valid" << std::endl;
			exit(1);
	}
}

eqm::T eqm::vector::operator[](int index) const{
	switch(index){
		case 0:
			return this->x; 
			break;
		case 1:
			return this->y;
			break;
		case 2:
			return this->z;
			break;
		default:
			std::cout << "vector::index" << index << "not valid" << std::endl;
			exit(1);
	}
}

eqm::T& eqm::nvector::operator[](int index){
	if ((index >= 0 ) && index < this->dimension){
		return a[index];
	} else {
		std::cout << "Error: Accessing element beyond dimension!!\n";
		std::cout << "Dimension is " << this->dimension << std::endl;
		std::cout << "index passed was " << index << std::endl;
		std::cout << "Quitting!!" << std::endl;
		exit(1);
	}
}

eqm::T eqm::nvector::operator[](int index) const{
	if ((index >= 0 ) && index < this->dimension){
		return a[index];
	} else {
		std::cout << "Error: Accessing element beyond dimension!!\n";
		std::cout << "Dimension is " << this->dimension << std::endl;
		std::cout << "index passed was " << index << std::endl;
		std::cout << "Quitting!!" << std::endl;
		exit(1);
	}
}


//****************************************
//****     Concat// Disect nvector *******
//****************************************


eqm::nvector eqm::operator<<(const eqm::nvector& nv, const eqm::vector& newer){
	eqm::nvector temp(nv.dimension + 3);

	for (int i = 0; i < nv.dimension; ++i)
	{
		temp[i] = nv.a[i];
	}

	for (int i = 0; i < 3; ++i)
	{
		temp[i+nv.dimension] = newer[i];
	}
	return temp;
}

eqm::nvector eqm::nvector::operator>>(eqm::vector& newer) const{
	if(dimension < 3){
		std::cout << "nvector too short, can't pull out 3 elements for vector." << std::endl;
		std::cout << "Quitting!!" << std::endl;
		exit(1);
	}
	eqm::nvector temp(dimension - 3);
	for (int i = 0; i < 3; ++i)
	{
		newer[i] = a[i];
	}
	for (int i = 0; i < dimension - 3; ++i)
	{
		temp[i] = a[3 + i];
	}
	return temp;
}