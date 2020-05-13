/*
	Author:		Nguyen Ngoc Nang Toan
	Date:		
	Function:	Create new data type QInt (Integer 128 bits) (IEEE)
*/

#pragma once
#include <iostream>
#include "Convert.h"
#include "BitArray.h"
#include "Mode.h"

#define BIT_LENGTH 128

class QInt
{
public:
	BitArray m_data;

public:
	//Default constructor
	QInt();
	//Constructor with string number and mode of num
	QInt(const std::string& num, MODE mode = MODE::dec);
	//Constructor with char n
	QInt(char n);
	//Constructor with int n
	QInt(int n);
	//Constructor with long n
	QInt(long n);
	//Destructor
	~QInt();

public:
	//Operator =
	QInt operator=(const QInt& rhs);
	//Operator +
	QInt operator+(QInt rhs);
	//Operator -
	QInt operator-( QInt rhs);
	//Operator - , change a number  to the opposite number
	QInt operator-();
	//Operator *
	QInt operator*( QInt rhs);
	//Operator /
	QInt operator/( QInt rhs);
	// Operator mod
	QInt operator%(QInt rhs);
	//Operator +=
	QInt operator+=( QInt rhs);
	//Operator -=
	QInt operator-=(QInt rhs);
	//Operator *=
	QInt operator*=(QInt rhs);
	//Operator /=
	QInt operator/=(QInt rhs);
	//Operator | , OR
	QInt operator|( QInt rhs);
	//Operator & , AND
	QInt operator&(QInt rhs);
	//Operator ^ , XOR
	QInt operator^(QInt rhs);
	//Operator ~ , NOT
	QInt operator~()const;
	//Operator << , shift left
	QInt operator<<(uint nBits);
	//Operator >> , shift right
	QInt operator>>(uint nBits);
	
	//Compare 2 QInt
	bool operator>(QInt rhs);
	bool operator==(QInt rhs);
	bool operator!=(QInt rhs);
	bool operator<=(QInt rhs);
	bool operator>=(QInt rhs);
	bool operator<(QInt rhs);
	
	//Rotate left
	QInt RoL(uint n) const;
	//Rotate right
	QInt RoR(uint n) const;
	
	//Input
	friend std::istream& operator>>(std::istream& in, QInt& qInt);
	//Output
	friend std::ostream& operator<<(std::ostream& out, const QInt& qInt);
	
	//Convert QInt to string
	std::string to_string() ;
	//Convert QInt to Binary number
	std::string to_bin() const;
	//Convert QInt to Decimal number
	std::string to_dec();
	//Convert QInt to hexadecimal number
	std::string to_hex() const;
	
	//Check if QInt is negative
	bool isNegative() const;
	//Check if QInt is Positive
	bool isPositive() const;
};
