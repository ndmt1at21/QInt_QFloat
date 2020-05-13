/*
	Author:		Tran Ngoc Tinh
	Date:
	Function:
*/

#pragma once
#include <vector>
#include <string>
#include "Bit.h"

typedef unsigned char uchar;
typedef unsigned int uint;

class BitArray
{
private:
	std::vector<uint> m_vBlockbit;

public:
	// Default Constructor, 8 bit 0 
	BitArray();

	// Init BitArray have length = bitLength, all bit 0
	BitArray(uint bitLength );

	// Init BitArray with string bits
	BitArray(const std::string& bits);

	// Init BitArray with n block
	BitArray(const uint* bytes, uint nBytes);

	// Init BitArray with string Bit
	BitArray(const Bit* bits, uint bitLength);

	// Copy constructor 
	BitArray(const BitArray& bitArr);

	// Destructor 
	~BitArray();

	// Set bit with Bit value in position index
	void setBit(uint index, Bit bit);   

	// Set bit 1 in position index
	void setBit(uint index);

	// Get bit in position index 
	Bit getBit(uint index) const;   
	
	// Set block (4 bytes) in position index
	void setBlock(uint index, uint value); 

	// Get block value (4 bytes) in position index
	uint getBlock(uint index) const; 
	
	// Get Least Signficant Bit
	Bit getLSB() const;

	// Get Most Signficant Bit
	Bit getMSB() const;

	// Set Least Signficant Bit = 1
	void setLSB();

	// Set Most Signficant Bit = 1
	void setMSB();

	// Get number block (each block 4 byte)
	uint getNumBlock() const;  

	// Get length of bit array
	uint getBitLength() const;

	// Resize length bit array
	void resize(uint NewBitLength);

	// Set all bit in bit array = 0
	void clear();

	// Assign operator 
	BitArray& operator=(const BitArray& rhs);

	// Binary operator
	BitArray operator+(const BitArray& rhs) const;
	BitArray operator-(const BitArray& rhs) const;
	BitArray& operator+=(const BitArray& rhs);
	BitArray& operator-=(const BitArray& rhs);

	// Bitwise operator
	BitArray operator|(const BitArray& rhs) const;
	BitArray operator&(const BitArray& rhs) const;
	BitArray operator^(const BitArray& rhs) const;
	BitArray operator~() const;
	BitArray operator>>(uint nBits) const;
	BitArray operator<<(uint nBits) const;

	// Convert bit array to string
	// Delete all bit 0 in head 
	std::string to_string() const;

protected:
	// Normalize bitLength
	// Ex: bitLength = 5 -> normal: bitLength = 8
	void normalizeBitLength(uint& bitLength);
};

