//
// Created by crazy_cloud on 2019/11/8.
//

#include "Integer.h"

integer operator+(const integer &A , const integer &B)
{
	integer ret;
	if (A.sig ^ B.sig ^ 1)
	{
		ret.num.resize(ret.len = std::max(A.len , B.len) + 1);
		for (int i = 0;i < ret.len;++ i) ret.num[i] = (i < A.len ? A.num[i] : 0) + (i < B.len ? B.num[i] : 0);
		for (int i = 0;i < ret.len;++ i) if (ret.num[i] >= 10) ret.num[i + 1] += ret.num[i] / 10 , ret.num[i] %= 10;
		ret.len -= !ret.num[ret.len - 1] , ret.num.resize(ret.len) , ret.sig = A.sig && B.sig;
	}
	else ret = A - (-B);
	if (!ret.sig && ret.is_zero()) ret.sig = 1;
	return ret;
}

integer operator-(const integer &A , const integer &B)
{
	integer ret;
	if (A >= B)
		if (A.sig && B.sig)
		{
			ret.num.resize(A.len) , ret.len = 1;
			for (int i = 0 , owe = 0;i < A.len;++ i)
			{
				ret.num[i] = A.num[i] - (i < B.len ? B.num[i] : 0) - owe , owe = 0;
				if (ret.num[i] < 0) ret.num[i] += 10 , ++ owe;
				if (ret.num[i]) ret.len = i + 1;
			}
			ret.num.resize(ret.len);
		}
		else ret = A.sig ? A + (-B) : (-B) - (-A);
	else ret = - (B - A);
	if (!ret.sig && ret.is_zero()) ret.sig = 1;
	return ret;
}

integer operator*(const integer &A , const integer &B)
{
	poly p(A.num , A.len - 1) , q(B.num , B.len - 1) , r = p * q;
	integer ret(r.deg + 2);
	for (int i = 0;i < ret.len - 1;++ i) ret.num[i] += r[i] , ret.num[i + 1] = ret.num[i] / 10 , ret.num[i] %= 10;
	for (;ret.len && !ret.num[ret.len - 1];) -- ret.len;
	ret.len += !ret.len , ret.num.resize(ret.len) , ret.sig = A.sig ^ B.sig ^ 1;
	if (!ret.sig && ret.is_zero()) ret.sig = 1;
	return ret;
}

integer operator/(const integer &A , const integer &B){return integer().divide(A , B , 1);}

integer operator%(const integer &A , const integer &B){return integer().divide(A , B , 0);}

bool operator<(const integer &A , const integer &B)
{
	if (A.sig != B.sig) return A.sig < B.sig;
	if (A.len != B.len) return A.len < B.len;
	for (int i = A.len - 1;i >= 0;-- i)
	{
		if (A.num[i] < B.num[i]) return A.sig;
		if (A.num[i] > B.num[i]) return !A.sig;
	}
	return 0;
}

bool operator>(const integer &A , const integer &B)
{
	if (A.sig != B.sig) return A.sig > B.sig;
	if (A.len != B.len) return A.len > B.len;
	for (int i = A.len - 1;i >= 0;-- i)
	{
		if (A.num[i] > B.num[i]) return A.sig;
		if (A.num[i] < B.num[i]) return !A.sig;
	}
	return 0;
}

bool operator<=(const integer &A , const integer &B)
{
	if (A.sig != B.sig) return A.sig < B.sig;
	if (A.len != B.len) return A.len < B.len;
	for (int i = A.len - 1;i >= 0;-- i)
	{
		if (A.num[i] < B.num[i]) return A.sig;
		if (A.num[i] > B.num[i]) return !A.sig;
	}
	return 1;
}

bool operator>=(const integer &A , const integer &B)
{
	if (A.sig != B.sig) return A.sig > B.sig;
	if (A.len != B.len) return A.len > B.len;
	for (int i = A.len - 1;i >= 0;-- i)
	{
		if (A.num[i] > B.num[i]) return A.sig;
		if (A.num[i] < B.num[i]) return !A.sig;
	}
	return 1;
}

bool operator!=(const integer &A , const integer &B)
{
	if (A.sig != B.sig) return 1;
	if (A.len != B.len) return 1;
	for (int i = 0;i < A.len;++ i) if (A.num[i] ^ B.num[i]) return 1;
	return 0;
}

bool operator==(const integer &A , const integer &B)
{
	if (A.sig != B.sig) return 0;
	if (A.len != B.len) return 0;
	for (int i = 0;i < A.len;++ i) if (A.num[i] ^ B.num[i]) return 0;
	return 1;
}

std::istream &operator>>(std::istream &ist , integer &x)
{
	std::string buf;
	return ist >> buf , x = integer(buf) , ist;
}

std::ostream &operator<<(std::ostream &ost , const integer &x){return ost << std::string(x);}

bool integer::is_zero() const {return len == 1 && !num[0];}

integer integer::operator*(const int &var) const
{
	integer ret(len + 1);ret.sig = sig ^ (var >= 0) ^ 1;
	for (int i = 0 , x = var >= 0 ? var : -var;i < len;++ i) ret.num[i] += num[i] * x , ret.num[i + 1] = ret.num[i] / 10 , ret.num[i] %= 10;
	for (;ret.len && !ret.num[ret.len - 1];-- ret.len);
	ret.len += !ret.len , ret.num.resize(ret.len) , ret.sig = sig;
	if (!ret.sig && ret.is_zero()) ret.sig = 1;
	return ret;
}

integer &integer::operator*=(const int &var){return (*this) = (*this) * var;}

integer integer::divide(const integer &A , const integer &B , const bool &tp)
{
	integer remainder(1) , quotient(A.len) , *tmp = new integer [10];
	quotient.sig = A.sig ^ B.sig ^ 1;
	tmp[0] = integer(1) , tmp[1] = abs(B);
	for (int i = 2;i < 10;++ i) tmp[i] = tmp[1] * i;
	for (int i = A.len - 1;i >= 0;-- i)
	{
		remainder *= 10 , remainder.num[0] = A.num[i];
		for (int d = 9;d >= 0;-- d)
		{
			if (remainder < tmp[d]) continue;
			quotient.num[i] = d , remainder -= tmp[d];
			break;
		}
	}
	for (;quotient.len && !quotient.num[quotient.len - 1];-- quotient.len);
	quotient.len += !quotient.len , quotient.num.resize(quotient.len);
	if (!quotient.sig && quotient.is_zero()) quotient.sig = 1;
	if (!quotient.sig && !remainder.is_zero()) -- quotient;
	if (!remainder.is_zero()) remainder = A.sig ? (B.sig ? remainder : remainder - tmp[1]) : (B.sig ? tmp[1] - remainder : -remainder);
	return delete [] tmp , tp ? quotient : remainder;
}

integer integer::abs(const integer &A)
{
	integer ret = A;
	return ret.sig = 1 , ret;
}

integer::integer(const double &var)
{
	std::string var_str = std::to_string(var);
	for (int i = 0;i < 7;++ i) var_str.pop_back();
	(*this) = integer(var_str);
}

integer::integer(const std::string &str)
{
	sig = str[0] != '-' , num.resize(len = str.length() + (int)sig - 1);
	for (int i = 0 , l = str.length();i < len;++ i) num[i] = str[l - 1 - i] - '0';
}


integer::operator double() const
{
	double base = sig ? 1. : -1., ret = 0.;
	for (int i = 0;i < len;++ i) ret += base * num[i] , base *= 10.;
	return ret;
}

integer::operator bool() const {return is_zero();}
integer::operator std::string() const
{
	char* buf = new char [len + (int)!sig];
	for (int i = (int)!sig;i < len + (int)!sig;++ i) *(buf + i) = '0' + num[i - (int)!sig];
	std::reverse(buf + (int)!sig , buf + len + (int)!sig);
	if (!sig) buf[0] = '-';
	std::string ret(buf , len + (int)!sig);
	return delete [] buf , ret;
}

integer integer::operator+() const {return *this;}

integer integer::operator-() const
{
	integer ret = *this;
	if (!ret.is_zero()) ret.sig ^= 1;
	return ret;
}

integer &integer::operator+=(const integer &var){return (*this) = (*this) + var;}

integer &integer::operator-=(const integer &var){return (*this) = (*this) - var;}

integer &integer::operator*=(const integer &var){return (*this) = (*this) * var;}

integer &integer::operator/=(const integer &var){return (*this) = (*this) / var;}

integer &integer::operator%=(const integer &var){return (*this) = (*this) % var;}

integer &integer::operator++(){return (*this) += integer(std::string("1"));}

integer integer::operator++(int x)
{
	integer ret(*this);
	return (*this) += integer(std::string("1")) , ret;
}

integer &integer::operator--(){return (*this) -= integer(std::string("1"));}

integer integer::operator--(int x)
{
	integer ret(*this);
	return (*this) -= integer(std::string("1")) , ret;
}