/*
	Author:		Nguyen Duc Minh Tri
	Date:		06/05/2020
	Function:	Math operator with huge number
*/

#pragma once
#include <string>
#include <iostream>

#define NO_POINT 0

typedef unsigned int uint;

class StringMath
{
private:
	std::string m_sLongNumber;

public:
	// Default Constructor
	StringMath();

	// Init StringMath with string dec number
	StringMath(const std::string& decimalNumber);
	StringMath(const char* decimalNumber);

	// Init StringMath with base data type
	StringMath(int number);
	StringMath(long number);
	StringMath(float number);
	StringMath(double number);

	// Copy Constructor
	StringMath(const StringMath& strMath);

	// Assign operator
	StringMath& operator=(const StringMath& rhs);

	// Binary operator
	StringMath operator*(const StringMath& rhs);
	StringMath div(long divisor, uint precision);
	StringMath operator%(long divisor);
	StringMath operator+(const StringMath& rhs);
	StringMath operator-(const StringMath& rhs);
	
	// Unary operator -
	StringMath operator-();

	// Compare operator
	bool operator>(const StringMath& rhs) const;
	bool operator==(const StringMath& rhs) const;
	bool operator!=(const StringMath& rhs) const;

	// Get number in position index
	char operator[](long index);

	// Get abs
	StringMath abs() const;

	// Check < 0
	bool isNegative() const;

	// Check > 0
	bool isPositive() const;

	// Get int part
	StringMath getInt() const;

	// Get fraction part
	StringMath getFraction() const;

	// Get position point
	// Return:	if no point return NO_POINT
	//			if have point return pos point
	uint getPosPoint() const;
	
	uint getNumDigitFractional() const;
	uint getNumDigitInt() const;

	// Get length string dec number
	uint length() const;

	// Convert to string
	std::string to_string() const;

protected:
	// Valid data
	// Example:
	//	"125x" -> return false;
	//	"1...25" -> return false;
	bool validData(const std::string& decimalNumber);

	// Format data, delete element not need
	// Example: 
	//	"0001" -> "1"
	//	"01.5000 -> "1.5"			
	void normalize(std::string& decimalNumber);
};

