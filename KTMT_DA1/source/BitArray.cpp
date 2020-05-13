#include "BitArray.h"

BitArray::BitArray()//cho gia tri mac dinh gom 4 byte int=0
{
	for (int i = 0; i < 4; i++)
	{
		this->m_vBlockbit.push_back(0);
	}
}
BitArray::BitArray(uint bitLength )//khoi tao voi do dai n bit =0
{
	normalizeBitLength(bitLength);
	for (int i = 0; i < bitLength / 32;i++)
	{
		this->m_vBlockbit.push_back(0);
	}
}
BitArray::BitArray(const uint* bytes, uint nBytes)//khoi tao nBytes voi chuoi Bytes
{
	for (int i = 0; i < nBytes; i++)
	{
		this->m_vBlockbit[i]=bytes[i];
	}	
}
BitArray::BitArray(const Bit* bits, uint bitLength)//khoi tao n bit=bitLength voi chuoi bits voi do dai da biet
{
	uint temp = bitLength;
	normalizeBitLength(bitLength);
	for (int i = 0; i < bitLength / 32; i++)
	{
		this->m_vBlockbit.push_back(0);
	}

	for (int i = 0; i <temp; i++)
	{
		if (bits[bitLength - i - 1].isBit1())//kiem tra neu bang 1
		{
			this->setBit(i, 1);
		}
		else
		{
			this->setBit(i, 0);
		}
	}
}
BitArray::BitArray(const std::string& bits)//khoi tao bang 1 chuoi
{
	uint bitLength = bits.size();
	normalizeBitLength(bitLength);
	for (int i = 0; i < bitLength / 32; i++)
	{
		this->m_vBlockbit.push_back(0);
	}
	for (int i = 0; i <bits.size(); i++)
	{
		if (bits[bits.size()-i-1] == '1')
		{
			this->setBit(i,1);
		}
		else
		{
			this->setBit(i,0);
		}
	}
}
BitArray::BitArray(const BitArray& bitArr)//khoi tao bang doi so 
{
	for(int i=0;i<bitArr.getNumBlock();i++)
	{
		this->m_vBlockbit.push_back(bitArr.m_vBlockbit[i]);
	}
}
BitArray::~BitArray()//ham huy
{

}
void BitArray::setBit(uint index)//set bit 1 o vi tri index
{
	int byte = index / 32;
	this->m_vBlockbit[byte] = this->m_vBlockbit[byte] | (1 << (index % 32));
}


void BitArray::setBit(uint index, Bit bit)
{
		int byte = index / 32;
		if (bit.isBit1())
		{
			this->m_vBlockbit[byte] = this->m_vBlockbit[byte] | (1 << (index % 32));
		}
		if (bit.isBit0())
		{
			this->m_vBlockbit[byte] = this->m_vBlockbit[byte] & ~(1 << (index % 32));
		}
}
Bit BitArray::getBit(uint index) const//tra ve bit o vi tri index
{
	if ((index > 127) || (index < 0))
	{
		return 0;
	}
	uint byte = index / 32;
	return (this->m_vBlockbit[byte] >> (index % 32)) & 1;
}

void BitArray::setBlock(uint index, uint value)//set 1 byte co gia tri value o vi tri index
{
	this->m_vBlockbit[index] = value;
}

uint BitArray::getBlock(uint index) const//tra ve gia tri o vi tri index
{
	return this->m_vBlockbit[index];
}


Bit BitArray::getLSB() const
{
	return getBit(0);
}

Bit BitArray::getMSB() const
{
	return getBit(getBitLength() - 1);
}

void BitArray::setLSB()
{
	setBit(0);
}

void BitArray::setMSB()
{
	setBit(getBitLength() - 1);
}

uint BitArray::getNumBlock() const//tra ve tong so byte
{
	return this->m_vBlockbit.size();
}

uint BitArray::getBitLength() const//tra ve do dai bit
{
	return this->m_vBlockbit.size()*32;
}

void BitArray::resize(uint NewBitLength) //resize day bit
{
	normalizeBitLength(NewBitLength);
	if (NewBitLength > this->getBitLength())
	{
		BitArray temp(NewBitLength);
		for (int i = 0; i < this->getBitLength(); i++)
		{
			if (getBit(i).isBit0())
			{
				temp.setBit(i,0);
			}
			else
			{
				temp.setBit(i,1);
			}
		}
		for (uint i = this->getBitLength(); i < NewBitLength; i++)
		{
			temp.setBit(i, 0);
		}
		*this = temp;
	}
	else
	{
		BitArray temp(NewBitLength);
		for (uint i = 0; i < NewBitLength; i++)
		{
			if (getBit(i).isBit0())
			{
				temp.setBit(i, 0);
			}
			else
			{
				temp.setBit(i, 1);
			}
		}
		*this = temp;
	}
}

void BitArray::clear()//xoa du lieu tat ca cac bit
{
	this->m_vBlockbit.clear();
}

BitArray& BitArray::operator=(const BitArray& rhs)//toan tu gan
{
	if (this == &rhs)//neu trung return ve this
		return *this;

	this->clear();//xoa du lieu o this 
	for (int i = 0; i < rhs.getNumBlock(); i++)
	{
		this->m_vBlockbit.push_back(rhs.m_vBlockbit[i]); // gan rhs vao this
	}

	return *this;
}

BitArray BitArray::operator+(const BitArray& rhs) const//toan tu cong
{
	uint longer;
	if (this->getBitLength() > rhs.getBitLength()) //xac dinh day bit nao dai hon
	{
		longer = this->getBitLength();
		BitArray temp(rhs.to_string());
		temp.resize(longer);
		BitArray result(longer);  //tao 1 BitArray ket qua

		int remember = 0;//gia tri nho
		for (int i = 0; i < longer; i++)//cong giong nhu 2 so nguyen
		{
			if (remember == 0)//truong hop co gia tri remember =0
			{
				if (this->getBit(i).isBit0() && temp.getBit(i).isBit0())
					result.setBit(i, 0);
				else if (this->getBit(i).isBit1() && temp.getBit(i).isBit1())
				{
					remember = 1;
					result.setBit(i, 0);
				}
				else result.setBit(i, 1);
			}
			else //truong hop co gia tri remember =1
			{
				if (this->getBit(i).isBit0() && temp.getBit(i).isBit0())
				{
					result.setBit(i, 1);
					remember = 0;
				}
				else if (this->getBit(i).isBit1() && temp.getBit(i).isBit1())
				{
					result.setBit(i, 1);
					remember = 1;
				}
				else
				{
					result.setBit(i, 0);
					remember = 1;
				}
			}
		}
		return result;

	}
	else
	{
		longer = rhs.getBitLength();
		BitArray temp(this->to_string());
		temp.resize(longer);
		BitArray result(longer);  //tao 1 BitArray ket qua
		int remember = 0;//gia tri nho
		for (int i = 0; i < longer; i++)//cong giong nhu 2 so nguyen
		{
			if (remember == 0)//truong hop co gia tri remember =0
			{
				if (temp.getBit(i).isBit0() && rhs.getBit(i).isBit0())
					result.setBit(i, 0);
				else if (temp.getBit(i).isBit1() && rhs.getBit(i).isBit1())
				{
					remember = 1;
					result.setBit(i, 0);
				}
				else result.setBit(i, 1);
			}
			else //truong hop co gia tri remember =1
			{
				if (temp.getBit(i).isBit0() && rhs.getBit(i).isBit0())
				{
					result.setBit(i, 1);
					remember = 0;
				}
				else if (temp.getBit(i).isBit1() && rhs.getBit(i).isBit1())
				{
					result.setBit(i, 1);
					remember = 1;
				}
				else
				{
					result.setBit(i, 0);
					remember = 1;
				}
			}
		}
		return result;
	}
}

BitArray BitArray::operator-(const BitArray& rhs) const//toan tu tru
{
	return *this + (~rhs + BitArray("1")); //lay so dang xet cong voi Bu 2 cua so con lai
}

BitArray& BitArray::operator+=(const BitArray& rhs)
{
	*this = this->operator+(rhs);
	return *this;
}
BitArray& BitArray::operator-=(const BitArray& rhs)
{
	*this = this->operator-(rhs);
	return *this;
}
BitArray BitArray::operator|(const BitArray& rhs) const //toan tu or
{
	uint n;//chieu dai bit lon hon
	BitArray result;
	if (this->getBitLength() > rhs.getBitLength())
	{
		n = this->getBitLength();
		BitArray rhs1(rhs.to_string());//tao BitArray rhs1 =rhs.va co BitLength=n
		rhs1.resize(n);
		for (int i = 0; i < n; i++)
		{
			bool temp = this->getBit(i) | rhs1.getBit(i);
			result.setBit(i, temp);
		}
	}
	else
	{
		n = rhs.getBitLength();
		BitArray this1(this->to_string());
		this1.resize(n);
		for (int i = 0; i < n; i++)
		{
			bool temp = this1.getBit(i) | rhs.getBit(i);
			result.setBit(i, temp);
		}
	}
	return result;
}
BitArray BitArray::operator&(const BitArray& rhs) const   //toan tu &
{
	uint n;//chieu dai bit lon hon
	BitArray result;
	if (this->getBitLength() > rhs.getBitLength())
	{
		n = this->getBitLength();
		BitArray rhs1(rhs.to_string());//tao BitArray rhs1 =rhs.va co BitLength=n
		rhs1.resize(n);
		for (int i = 0; i < n; i++)
		{
			bool temp = this->getBit(i) & rhs1.getBit(i);
			result.setBit(i, temp);
		}
	}
	else
	{
		n = rhs.getBitLength();
		BitArray this1(this->to_string());
		this1.resize(n);
		for (int i = 0; i < n; i++)
		{
			bool temp = this1.getBit(i) & rhs.getBit(i);
			result.setBit(i, temp);
		}
	}
	return result;
}

BitArray BitArray::operator^(const BitArray& rhs) const        //toan tu xor
{
	uint n;//chieu dai bit lon hon
	BitArray result;
	if (this->getBitLength() > rhs.getBitLength())
	{
		n = this->getBitLength();
		BitArray rhs1(rhs.to_string());//tao BitArray rhs1 =rhs.va co BitLength=n
		rhs1.resize(n);
		for (int i = 0; i < n; i++)
		{
			bool temp = this->getBit(i) ^ rhs1.getBit(i);
			result.setBit(i, temp);
		}
	}
	else
	{
		n = rhs.getBitLength();
		BitArray this1(this->to_string());
		this1.resize(n);
		for (int i = 0; i < n; i++)
		{
			bool temp = this1.getBit(i) ^ rhs.getBit(i);
			result.setBit(i, temp);
		}
	}
	return result;
}

BitArray BitArray::operator~()const        //toan tu not
{
	BitArray result(this->getBitLength());
	for (int i = 0; i < this->getBitLength(); i++)
	{
		if (this->getBit(i).isBit1())
		{
			result.setBit(i, 0);
		}
		else
		{
			result.setBit(i, 1);
		}
	}
	return result;
}

BitArray BitArray::operator>>(uint nBits) const    //dich phai nBits
{
	uint n = this->getBitLength();
	BitArray temp(n);
	if (nBits >= n)
	{
		return temp;
	}
	if (nBits < 0)
	{
		return *this;
	}
	bool Bitdau = this->getBit(this->getBitLength()-1);//bit dau
	for (uint i = 0; i < n-nBits; i++)
	{
		temp.setBit(i, getBit(i + nBits));
		//setBit(temp, getBit(i - nBits).GetBit(), i);
	}
	temp.setBit(temp.getBitLength() - 1, Bitdau);   //cho bit dau vao vi tri dau tien
	return temp;
}

BitArray BitArray::operator<<(uint nBits) const  //dich trai nBits
{
	uint n = this->getBitLength();
	BitArray temp(n);
	if (nBits >= n)
	{
		return temp;
	}
	if (nBits < 0)
	{
		return *this;
	}
	for (uint i = n-1; i>=nBits; i--)
	{
		temp.setBit(i, getBit(i - nBits));
		//setBit(temp,getBit(i+nBits).GetBit(),i);
	}
	for (uint i = 0; i < nBits; i++)
	{
		temp.setBit(i,0);
	}
	//setBit(temp, 0,n-1);
	return temp;
}

void BitArray::normalizeBitLength(uint& bitLength)  //chuan hoa do dai Bit
{
	if (bitLength > 0 && bitLength < 32)
	{
		bitLength = 32;
	}
	if (bitLength > 32 && bitLength < 64)
	{
		bitLength = 64;
	}
	if (bitLength > 64 && bitLength < 96)
	{
		bitLength = 96;
	}
	if (bitLength > 96 && bitLength < 128)
	{
		bitLength = 128;
	}
}
std::string BitArray::to_string() const
{
	std::string result;
	result.reserve(getBitLength());

	long flag = getBitLength() - 1;
	while (getBit(flag).isBit0() && flag > 0)
		flag--;

	for (long i = flag; i >= 0; i--)
		result.push_back((char)getBit(i) + '0');

	if (result.size() == 0)
		result.push_back('0');

	return result;
}



