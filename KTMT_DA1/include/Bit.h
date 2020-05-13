/*
	Author:		Tran Ngoc Tinh
	Date:		
	Function:	
*/

#pragma once
class Bit
{
private:
	bool m_bit;

public:
	Bit();
	Bit(bool bit);
	Bit(const Bit& bit);
	~Bit();

	// Asign operator
	Bit& operator=(const Bit& bit);

	// Compare operator
	bool operator==(const Bit& bit) const;
	bool operator!=(const Bit& bit) const;

	// Bitwise operator
	Bit operator|(const Bit& bit);
	Bit operator&(const Bit& bit);
	Bit operator^(const Bit& bit);
	Bit operator~();

	// Type cast operator
	operator bool() const;
	operator int() const;
	operator char() const;

	// Check bit 1 or bit 0-
	bool isBit0()const;
	bool isBit1()const;
};
