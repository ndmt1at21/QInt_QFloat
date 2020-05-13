/*
	Author:		Nguyen Duc Minh Tri
	Date:		09/05/2020
	Function:	create new data type QFloat (Float 128 bits) (IEEE)
*/

#pragma once
#include <iostream>
#include "BitArray.h"
#include "StringMath.h"
#include "Convert.h"
#include "Mode.h"
#include <string>

#define BIT_LENGTH 128
#define NUM_BIT_SIGN 1
#define NUM_BIT_EXP 15
#define NUM_BIT_FRAC 112
#define BIAS pow(2, NUM_BIT_EXP - 1) - 1
#define PRECISION (NUM_BIT_FRAC + 1) * log10(2)
#define LIMIT_NUM 4965

class QFloat
{
private:
	BitArray m_data;

public:
	// Default Contructor, init = 0
	QFloat();

	// Init QFloat by string number with mode input
	QFloat(const std::string& strNum, MODE mode = MODE::dec);

	// Copy constructor 
	QFloat(const QFloat& qFloat);

	//	Assign operator
	QFloat& operator=(const QFloat& qFloat);

	// Convert QFloat to decimal to show
	std::string to_dec(int precision = -1) const;

	// Convert QFloat to binary to show
	std::string to_bin() const;

	// Convert QFloat to string (decimal)
	std::string to_string() const;

	// Check QFloat < 0
	bool isNegative() const;

	// Check QFloat >= 0
	bool isPositive() const;

protected:
	// Check QFLoat = 0
	bool isZero() const;

	// Check QFloat is denormalize
	bool isDenormalize() const;

	// Check QFloat Infinite 
	bool isInf() const;

	// Check QFloat NaN
	bool isNaN() const;

	// Get, set bit sign (msb bit in bit array)
	void setBitSign();
	Bit getBitSign() const;

	// Set, get bit exponent in position index in exponent part
	// idx = [0, exp.size() - 1]
	void setBitExp(uint idx);
	Bit getBitExp(uint idx) const;

	// Set, get bit exponent in position index in fraction part
	// idx = [0, exp.size() - 1]
	void setBitFrac(uint idx);
	Bit getBitFrac(uint idx) const;

	// Get all bits in fraction part
	std::string getFraction() const;

	// Get all bits in exponent part
	std::string getExp() const;

	friend std::istream& operator>>(std::istream& in, QFloat& qFloat);
	friend std::ostream& operator<<(std::ostream& out, const QFloat& qFloat);
private:
	/*
		- Function:		Normalize string decimal
		- Return:		vector<string> have 3 elements
							vct[0] = sign
							vct[1] = exponent (decimal)
							vct[2] = mantassia
	*/
	std::vector<std::string> normalize(const std::string dec);
};

