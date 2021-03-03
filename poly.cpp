// File:	poly.cpp
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

#include "poly.h"
using namespace std;

// ---------------------------------------------------------------------------
// Default constructor.
// Initilize the polynomial to 0x^0 when no values are provided.
Poly::Poly()
{
	//set array size 1 and value to 0
	this->size = 1;
	coeffPtr = new int[this->size];
	coeffPtr[0] = 0;
}

// ---------------------------------------------------------------------------
// Overloaded constructor (int).
// Initilize the polynomial to #x^0, array has only one element.
Poly::Poly(int coeff)
{
	//set array size 1 and value to coeff
	this->size = 1;
	coeffPtr = new int[this->size];
	coeffPtr[0] = coeff;
}

// ---------------------------------------------------------------------------
// Overloaded constructor (int, int).
// Initilize the polynomial to #x^#, array length set to power, coefficients
// set in their corresponding array element (power 5 goes in slot 5 (element 6)).
Poly::Poly(int coeff, int power)
{
	//set array size power and set element to coeff
	coeffPtr = new int[power + 1];
	this->size = power + 1; //+1 for zero based implementation
	for (int i = 0; i < this->size; i++)
	{
		coeffPtr[i] = 0;
	}
	coeffPtr[power] = coeff;
}

// ---------------------------------------------------------------------------
// Copy constructor (poly).
// Initilize a new polynomial to be the exact same as the one provided,
// create new memory allocation for the new one, not an address point.
Poly::Poly(Poly &polyToCopy)
{
	this->size = polyToCopy.size;
	coeffPtr = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		coeffPtr[i] = polyToCopy.coeffPtr[i];
	}
}

// ---------------------------------------------------------------------------
// Destructor
// Delete the polynomial array and recoup the memory
Poly::~Poly()
{
	delete[] coeffPtr;
	coeffPtr = NULL;
}

// ---------------------------------------------------------------------------
// Overloaded + Operator
// Add two polynomials together by adding each element from one poly to
// the other. Use the size of the larger array so that the range does not
// get busted by accessing an element out of range.
Poly Poly::operator+(const Poly &rightHandSide) const
{
	//check if the left side has the larger array (power)
	if (this->size > rightHandSide.size)
	{
		//create new poly to hold sum and return
		Poly addPoly(0, this->size - 1);

		for (int i = 0; i < this->size; i++)
		{
			//copy the left side into the new poly array
			addPoly.coeffPtr[i] = this->coeffPtr[i];
		}

		for (int i = 0; i < rightHandSide.size; i++)
		{
			//add each element to eachother (0 + 0 will result in 0 naturally)
			addPoly.coeffPtr[i] = addPoly.coeffPtr[i] + rightHandSide.coeffPtr[i];
		}

		return addPoly;
	}
	//right side is has larger array, size determined by right side
	else
	{
		//create new poly to hold sum and return
		Poly addPoly(0, rightHandSide.size - 1);

		for (int i = 0; i < rightHandSide.size; i++)
		{
			//copy the left side into the new poly array
			addPoly.coeffPtr[i] = rightHandSide.coeffPtr[i];
		}

		for (int i = 0; i < this->size; i++)
		{
			//add each element to eachother (0 + 0 will result in 0 naturally)
			addPoly.coeffPtr[i] = addPoly.coeffPtr[i] + this->coeffPtr[i];
		}

		return addPoly;
	}
}

// ---------------------------------------------------------------------------
// Overloaded - Operator
// Subtract two polynomials together by subtracting each element from one poly to
// the other. Use the size of the larger array so that the range does not
// get busted by accessing an element out of range. Fill the empty larger array
// with the values of the smaller array so that you may subtract without using
// memory location as the values.
Poly Poly::operator-(const Poly &rightHandSide) const
{
	//check if the left side has the larger array (power)
	if (this->size > rightHandSide.size)
	{
		//create new poly to hold diff and return
		Poly diffPoly(0, this->size - 1);

		for (int i = 0; i < rightHandSide.size; i++)
		{
			//copy the right side into the new poly array (smaller)
			diffPoly.coeffPtr[i] = rightHandSide.coeffPtr[i];
		}

		for (int i = 0; i < this->size; i++)
		{
			//subtract each element to eachother (0 - 0 will result in 0 naturally)
			diffPoly.coeffPtr[i] = this->coeffPtr[i] - diffPoly.coeffPtr[i];
		}

		return diffPoly;
	}
	//right side is has larger array, size determined by right side
	else
	{
		//create new poly to hold difference and return
		Poly diffPoly(0, rightHandSide.size - 1);

		for (int i = 0; i < this->size; i++)
		{
			//copy the left side into the new poly array (smaller)
			diffPoly.coeffPtr[i] = this->coeffPtr[i];
		}

		for (int i = 0; i < rightHandSide.size; i++)
		{
			//subtract each element to eachother (0 - 0 will result in 0 naturally)
			diffPoly.coeffPtr[i] = diffPoly.coeffPtr[i] - rightHandSide.coeffPtr[i];
		}

		return diffPoly;
	}
}

// ---------------------------------------------------------------------------
// Overloaded * Operator
// Multiply two polynomials together, size is determined by the highest 
// power that can be achieved. Each polynomial from the left side is 
// multiplied by each polynomial from the right side. The powers are added
// together and the coefficients are multiplied together.
// Assumption: Zero polynomials are to be treated as 0's. Poly * 0 = 0.
Poly Poly::operator*(const Poly &rightHandSide) const
{
	int power;
	//find max power to determine the size of the product array
	int maxVal;
	//holds the temporart product
	int tempVal;
	maxVal = this->size + rightHandSide.size - 2; //-2 because each one is 0 based

	//create new poly to hold product and return
	Poly prodPoly(0, maxVal);

	for (int i = 0; i < this->size; i++)
	{
		//for each polynomial that is not a zero, 
		//multiply it by each polynomial on the right side
		if (this->coeffPtr[i] != 0)
		{
			for (int j = 0; j < rightHandSide.size; j++)
			{
				if (rightHandSide.coeffPtr[j] != 0)
				{
					power = i + j;
					//if there is already a product, add the two
					if (prodPoly.coeffPtr[power] != 0)
					{
						tempVal = this->coeffPtr[i] * rightHandSide.coeffPtr[j];
						prodPoly.coeffPtr[power] = prodPoly.coeffPtr[power] + tempVal;
					}
					//new product entry
					else
					{
						//add the powers, insert the product at that element
						prodPoly.coeffPtr[power] = this->coeffPtr[i] * rightHandSide.coeffPtr[j];
					}
				}
			}
		}
	}

	return prodPoly;
}

// ---------------------------------------------------------------------------
// Overloaded + Operator
// Add two polynomials together by adding each element from one poly to
// the other. 
// This combined arithmetic utilized the overloaded + operator previously covered
// to produce results (See Overloaded + Operator).
Poly& Poly::operator+=(const Poly &rightHandSide)
{
	//use the overloaded + operator to perform the arithmatic
	*this = *this + rightHandSide;
	return *this;
}

// ---------------------------------------------------------------------------
// Overloaded -= Operator
// Subtract two polynomials together by subtracting each element from one poly to
// the other. 
// This combined arithmetic utilized the overloaded - operator previously covered
// to produce results (See Overloaded - Operator).
Poly& Poly::operator-=(const Poly &rightHandSide)
{
	//use the overloaded - operator to perform the arithmatic
	*this = *this - rightHandSide;
	return *this;
}

// ---------------------------------------------------------------------------
// Overloaded *= Operator
// Multiply two polynomials together. Each polynomial from the left side is 
// multiplied by each polynomial from the right side. The powers are added
// together and the coefficients are multiplied together.
// This combined arithmetic utilized the overloaded * operator previously
// covered to produce results (See Overloaded * Operator).
Poly& Poly::operator*=(const Poly &rightHandSide)
{
	//use the overloaded * operator to perform the arithmatic
	*this = *this * rightHandSide;
	return *this;
}

// ---------------------------------------------------------------------------
// Overloaded == Operator
// Determine if two polynomials are equal to eachother. Test each element
// against its corresponding right side to see if they are equivalent, if
// any do not match, they do not equal the same polynomial.
bool Poly::operator==(const Poly &rightHandSide)
{
	bool isSame = true;
	//check if both polynomial arrays have the same size
	if (this->size != rightHandSide.size)
		isSame = false;
	//check if the polynomials match
	for (int i = 0; isSame == true && i < this->size; i++)
	{
		if (this->coeffPtr[i] != rightHandSide.coeffPtr[i])
			isSame = false;
	}
	return isSame;
}

// ---------------------------------------------------------------------------
// Overloaded == Operator
// Determine if two polynomials are not equal to eachother. Utilize the
// overloaded == operator to determine if two polynomials equal eachother
// then reverse the logic (See Overloaded == Operator).
bool Poly::operator!=(const Poly &rightHandSide)
{
	//use the overloaded == operator and reverse the logic
	return !(*this == rightHandSide);
}

// ---------------------------------------------------------------------------
// Overloaded = Operator
// Assign the polynomial on the right hand side to the polynomial on the
// left hand side. If they are already the same polynomial, dont bother
// copying the information.
Poly& Poly::operator=(const Poly &rightHandSide)
{
	//if the two are already identical, dont mess with memory,  return left one
	if (this->coeffPtr == rightHandSide.coeffPtr)
	{
		return *this;
	}

	//not identical, delete left hand side and replace with right
	delete[] this->coeffPtr;

	this->coeffPtr = new int[rightHandSide.size];
	for (int i = 0; i < rightHandSide.size; i++)
	{
		this->coeffPtr[i] = rightHandSide.coeffPtr[i];
	}
	this->size = rightHandSide.size;

	//return the new left hand side
	return *this;
}

// ---------------------------------------------------------------------------
// getCoeff(int)
// Get the coeffieicnt at the element(power) .
int Poly::getCoeff(int power) const
{
	//check if the power is valid in the range
	if ((power >= 0) && (power < this->size))
	{
		//return the value at the location of the power
		return this->coeffPtr[power];
	}
	else
	{
		//not found, return 0 to avoid crashing
		return 0;
	}
}

// ---------------------------------------------------------------------------
// setCoeff(int,int)
// Set the element located at power to the coefficient provided by coeff. 
// Re-allocate memory for the array if the size is increased.
// Do not allow negative powers.
void Poly::setCoeff(int coeff, int power)
{
	//check if the power is positive
	if (power >= 0)
	{
		//power already has a spot, dont need to reallocate
		if (power < this->size)
		{
			coeffPtr[power] = coeff;
		}
		else
		{
			//make new array to hold new cap size
			int *tempPoly = new int[power + 1];

			//initilize temp to all 0 
			for (int i = 0; i < power + 1; i++)
			{
				tempPoly[i] = 0;
			}

			//fill in the values 
			for (int i = 0; i < this->size; i++)
			{
				//ignore redundant zeros
				if (coeffPtr[i] != 0)
				{
					tempPoly[i] = coeffPtr[i];
				}
			}
			//set the new coeff value
			tempPoly[power] = coeff;

			//set the temp poly to the current and remove the old one from memory
			delete[] coeffPtr;
			coeffPtr = NULL;
			coeffPtr = tempPoly;
			tempPoly = NULL;
			this->size = power + 1; //get size instance back to correct one
		}
	}
}

// ---------------------------------------------------------------------------
// Overloaded << Operator
// Format the output stream in the example format of (+5x^3 -2x^2 -4).
// Use the element index to determine if the output requires a space, x, or
// a caret. If no numbers are encountered, return the stream and 0.
ostream &operator<<(ostream &outStream, const Poly &outPolynomial)
{
	bool isNumber = false;
	outStream << " ";
	//loop through, starting at end for formatting
	for (int i = outPolynomial.size - 1; i >= 0; i--)
	{
		//if the poly is not blank
		if (outPolynomial.coeffPtr[i] != 0)
		{
			isNumber = true;
			//positive or negative sign in front of the poly
			if (outPolynomial.coeffPtr[i] > 0)
			{
				outStream << "+";
			}
			//if the coeff has no x, dont include one
			if (i == 0)
			{
				outStream << outPolynomial.coeffPtr[i];
			}
			else if(i == 1)
			{
				outStream << outPolynomial.coeffPtr[i] << "x" << " ";
			}
			else
			{
				outStream << outPolynomial.coeffPtr[i] << "x^" << i << " ";
			}
		}
	}
	//there is at least one non zero
	if (isNumber)
	{
		return outStream;
	}
	//there are only 0's
	else
	{
		return outStream << "0";
	}
}

// ---------------------------------------------------------------------------
// Overloaded >> Operator
// Read the input stream and take in two values at a time. The first value
// is the coefficient and the second is the power. If both = -1, terminate.
// Values are assumed to be valid integers.
istream &operator>> (istream &inStream, Poly &inPolynomial)
{
	int coeff;
	int power;
	//read the input from the user, first digit into coeff, second into power
	inStream >> coeff >> power;
	//break when both coeff and power are -1
	while (!((coeff == -1) && (power == -1)))
	{
		//set the coeff and read the next input
		inPolynomial.setCoeff(coeff, power);
		inStream >> coeff >> power;
	}
	return inStream;
}