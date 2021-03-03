// File:	poly.h
// Author:	Josh Watts
// Date:	1/23/20
// Description:
// Implementation of a polynomial ADT,  One term is stored in one array 
// element; each term contains an exponent and a coefficient. The array 
// element subscript is the exponent and the content of the element is 
// the coefficient value. A constructor receives at most two values, 
// the coefficient of the term and the largest exponent currently expected.
// Memory is to be allocated dynamically and tied to the largest exponent.
// Input is assumed to be inputted correctly and no exceptions need to be
// handled.
#ifndef POLYTEST_H
#define POLYTEST_H

#include <iostream>

class Poly
{
public:
	//Polynomial constuctors
	Poly();
	Poly(int);
	Poly(int, int);
	Poly(Poly &);

	//Polynomial descructor
	~Poly();

	//Overloaded arithmetic operators
	Poly operator+(const Poly &) const;
	Poly operator-(const Poly &) const;
	Poly operator*(const Poly &) const;

	//Overloaded combined arithmetic opertators
	Poly& operator+=(const Poly &);
	Poly& operator-=(const Poly &);
	Poly& operator*=(const Poly &);

	//Overloaded inequality/equality operators
	bool operator==(const Poly &);
	bool operator!=(const Poly &);

	//Overloaded assignment operator
	Poly& operator=(const Poly &);

	//Getters and Setters
	int getCoeff(int) const;
	void setCoeff(int,int);

	//Overloaded input/output operators
	friend std::ostream &operator<<(std::ostream&, const Poly&);
	friend std::istream &operator>>(std::istream&, Poly&);

private:
	int *coeffPtr;	//array of polynomial
	int size;		//size of array
};

#endif // !POLY_H