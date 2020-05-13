#include "QInt.h"


QInt::QInt() :m_data(BIT_LENGTH)
{
	
}

QInt::QInt(int n)
{
	std::string temp;
	char dau='+';
	if (n == 0)
		temp.push_back('0');
	if (n < 0) {
		dau = '-';
		n = -n;
	}
	while (n > 0)
	{
		char c = n % 10 + 48;
		temp = c + temp;
		n /= 10;
	}
	if (dau == '-') //Neu so am thi gan bit dau vao dau chuoi
		temp = dau + temp;
	*this=QInt(temp,MODE::dec); // Goi lai ham khoi tao voi chuoi
}
QInt::QInt(long n)
{
	std::string temp;
	char dau='+';
	if (n == 0)
		temp.push_back('0');
	if (n < 0) {
		dau = '-';
		n = -n;
	}
	while (n > 0)
	{
		char c = n % 10 + 48;
		temp = c + temp;
		n /= 10;
	}
	if (dau == '-')
		temp = dau + temp;
	*this = QInt(temp, MODE::dec);
}
QInt::QInt(char n)
{
	std::string temp;
	temp += n;
	*this = QInt(temp, MODE::dec);
}


QInt::QInt(const std::string& num, MODE mode )
{
	
	std::string temp = num;
	if (mode == MODE::bin)
	{
		if (num.length() == 128)		//Neu duu 128 bit tien hanh gan truc tiep vao m_data
		{
			for (int i = 0; i < 128; i++)
			{
				Bit b = num[127 - i]-48;
				m_data.setBit(i, b);
			}
		}
		else 					
		{					
			m_data = BitArray(num);		// Neu khong thi goi ham tao Bitarray(string) de khoi tao
			m_data.resize(128);		// Sau do resize de chen bit 0 vao du 128 bit
		}
	}
	else if (mode == MODE::dec)
	{
		temp = Convert::DecToBin(num, 0);  			
		std::string abstemp = StringMath(temp).abs().to_string();	// Lay gia tri tuyet doi cua chuoi so thap phan dua vao
		m_data = BitArray(abstemp);
		
		if (temp[0] == '-') 						//Neu so am
		{
			BitArray tmp("1");					//Tien hanh cong cho 1 xong dao bit
			tmp.resize(128);
			m_data.resize(128);
			m_data = ~m_data+tmp;
		
		}
		m_data.resize(128);
	}
	else if (mode == MODE::hex)
	{
		temp = Convert::HexToBin(num);
		m_data = BitArray(temp);
		m_data.resize(128);
	}
}

QInt::~QInt(){}

QInt QInt::operator=(const QInt& rhs)
{
	this->m_data = rhs.m_data;
	return *this;
}

QInt QInt::operator-() {
	QInt temp = *this;		
	if (m_data.getMSB().isBit0()) 		//Neu la duong tien hanh dao bit xong cong 1
	{
		temp = ~temp;
		temp += QInt("1");
	}
	else 					//Neu la am tien hanh cong cho -1 xong dao bit
	{
		temp +=QInt("-1");
		temp = ~temp;

	}

	return temp;
}

QInt QInt::operator+(QInt rhs)
{
	QInt result;
	result.m_data = this->m_data + rhs.m_data;
	return result;
}

QInt QInt::operator-( QInt rhs)
{
	QInt result;
	QInt tmp = -rhs;
	result = *this + tmp;
	return result;
}
	
QInt QInt::operator*(QInt rhs)
{

	Bit Q0 = 0;                //dong vai tro bit nho
	QInt A;						//dong vai tro 1 phan ket qua nhan
	QInt M = *this;
	QInt Q = rhs;
	int k = 127;
	while (k >= 0)
	{
		if (Q.m_data.getBit(0).isBit1() && Q0.isBit0())            //Neu 2 bit cuoi Q=1 va Q0=0
		{
			A = A - M;
		}
		else if (Q.m_data.getBit(0).isBit0() && Q0.isBit1())       ////Neu 2 bit cuoi Q=0 va Q0=1
		{
			A = A + M;
		}
		//Shift right [A,Q,Q0]
		Q0 = Q.m_data.getBit(0);
		Q = Q >> 1;
		Q.m_data.setBit(127, A.m_data.getBit(0));
		A = A >> 1;
		k--;
	}
	return Q;
}

QInt QInt::operator/( QInt rhs)
{
	QInt A;  //khoi tao A
	QInt M = rhs;
	QInt Q = *this;
	
	int k = 128;
	
	if (M == QInt(0) || Q == QInt(0))
		return QInt(0);
	
	if (Q.m_data.getBit(127).isBit1())// Q < 0
	{
		A = QInt("-1"); 
	}

	while (k > 0)
	{
		//Shift left [A,Q]
		Bit Qtemp = Q.m_data.getBit(127);
		Q.m_data = Q.m_data << 1;
		A.m_data = A.m_data << 1;
		A.m_data.setBit(0, Qtemp);
		
		A = A - M;
		
		if (A.m_data.getBit(127).isBit1())        //A<0 
		{
			Q.m_data.setBit(0, 0);
			A = A + M;
			
		}
		else  //A>=0
		{
			Q.m_data.setBit(0, 1);
		}
		k--;
	}
	
	return Q;
}


QInt QInt::operator%(QInt rhs)
{
	QInt remainder = *this - (*this / rhs) * rhs;
	return remainder;
}

QInt QInt::operator+=(QInt rhs)
{
	this->m_data=this->m_data+rhs.m_data;
	return *this;
}

QInt QInt::operator-=(QInt rhs)
{
	this->m_data=this->m_data-rhs.m_data;
	return *this;
}

QInt QInt::operator*=(QInt rhs)
{
	*this = *this*rhs;
	return *this;
}

QInt QInt::operator/=(QInt rhs)
{
	*this = *this / rhs;
	return *this;
}
QInt QInt::operator|( QInt rhs)
{	
	QInt result;
	result.m_data = this->m_data | rhs.m_data;
	return result;
}

QInt QInt::operator&( QInt rhs)
{	
	QInt result;
	result.m_data = this->m_data & rhs.m_data;
	return result;
}

QInt QInt::operator^( QInt rhs)
{	
	QInt result;
	result.m_data=this->m_data^rhs.m_data;
	return result;
}

QInt QInt::operator~()const
{	
	QInt result;
	result.m_data = ~this->m_data;
	return result;
}

QInt QInt::operator<<(uint nBits )
{
	QInt temp = *this;
	temp.m_data = temp.m_data << nBits;
	return temp;
}

QInt QInt::operator>>(uint nBits)
{	
	QInt temp = *this;
	for (int i = 0; i < nBits; i++) {
		temp.m_data = temp.m_data >> 1;
		temp.m_data.resize(128);
	}
	
	return temp;
}

std::istream& operator>>(std::istream& in, QInt& qInt)
{
	std::string dec;
	std::getline(in, dec, '\n');

	qInt = QInt(dec);

	return in;
}

std::ostream& operator<<(std::ostream& out, QInt& qInt)
{
	out << qInt.to_dec();
	return out;
}

bool QInt::isNegative() const {
	if (m_data.getMSB().isBit1())
		return 1;
	return 0;
}

bool QInt::isPositive() const {
	if (m_data.getMSB().isBit0())
		return 0;
	return 1;
}

std::string QInt::to_string() {
	return m_data.to_string();
}
std::string QInt::to_bin()const {

	return m_data.to_string();
}
std::string QInt::to_dec()
{
	QInt res = *this;
	if(m_data.getMSB().isBit1())
	{
		std::string temp;
		QInt tmp =std::string("-1");
		res = res+ tmp;
		res = ~res;
		temp = Convert::BinToDec(res.m_data.to_string(), 0);
		temp='-'+temp;
		return temp;
	}
	return Convert::BinToDec(m_data.to_string(), 0);
}

std::string QInt::to_hex() const
{

	return Convert::BinToHex(m_data.to_string());

}

QInt QInt::RoL(uint n) const
{
	QInt temp = *this;
	for (int i = 0; i < n; i++) {
		temp = temp << 1;
		temp.m_data.setBit(0, this->m_data.getBit(127));
	}
	return temp;
}
QInt QInt::RoR(uint n) const {
	QInt temp = *this;
	for (int i = 0; i < n; i++)
	{
		temp = temp >> 1;
		temp.m_data.setBit(127, this->m_data.getBit(0));
	}
	return temp;
}
bool QInt::operator>(QInt rhs)
{
	QInt temp = *this; 
	int s1 = temp.m_data.getBit(127);
	int s2 = rhs.m_data.getBit(127);
	if (s1 < s2)
		return true;
	for (int i = 126; i >= 0; i--)
	{
		s1 = temp.m_data.getBit(i);
		s2 = rhs.m_data.getBit(i);
		if (s1 > s2)
			return true;
		if (s2 > s1)
			return false;
	}
	return false;
}
bool QInt::operator==(QInt rhs) {
	QInt temp = *this;
	int s1 ;
	int s2 ;
	
	for (int i = 127; i >= 0; i--)
	{
		s1 = temp.m_data.getBit(i);
		s2 = rhs.m_data.getBit(i);
		if (s1 != s2)
			return false;
	}
	return true;
}
bool QInt::operator!=(QInt rhs) 
{
	QInt temp = *this;
	return !(temp == rhs);
}
bool QInt::operator<=(QInt rhs)
{
	QInt temp = *this;
	return !(temp > rhs);
}
bool QInt::operator>=(QInt rhs)
{
	QInt temp = *this;
	return (temp > rhs)||temp==rhs;
}

bool QInt::operator<(QInt rhs) {
	QInt temp = *this;
	return !(temp >=rhs);
}
