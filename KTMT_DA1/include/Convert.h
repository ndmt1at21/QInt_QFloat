/* 
	Author:		Nguyen Duc Minh Tri
	Date:		08/05/2020
	Function:	Convert between base system
*/

#pragma once
#include "StringMath.h"
#include "BitArray.h"

class Convert
{
public:
	/* - Function: Convert decimal to binary number (normal, not 2's complement)
	   - Parameter:
	  		.decimal:	string decimal (can have point)
	  		.precision:	precision after point
	   - Example:
	  		(5, 0)	->	101
	  		(-5, 0)	->	-101
	  		(5.1, 5)->	101.00011
	*/
	static std::string DecToBin(const std::string& decimal, uint precision);




	/* - Function: Convert binary (normal, not 2's complement) to decimal number
	   - Parameter:
			.binary:	string binary (can have point)
			.precision:	precision after point
	   - Example:
			(101, 0)		->	5
			(-101, 0	)	->	-5
			(101.00011), 5)	->	5.09375
	*/
	static std::string BinToDec(const std::string& bits, uint precision);




	/* - Function: Convert binary (normal, no point) to hex number
	   - Parameter:
			.binary:	string binary
	   - Example:
			101		->	5
			1010	->	10
			1110	->	D
	*/
	static std::string BinToHex(const std::string& bits);




	/* - Function: Convert hex to binary (normal) number
	   - Parameter:
			.hex:	hex (no point)
	*/
	static std::string HexToBin(const std::string& hex);
};
