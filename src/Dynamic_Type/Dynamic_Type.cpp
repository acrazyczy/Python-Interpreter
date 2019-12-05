//
// Created by crazy_cloud on 2019/12/1.
//

#include "Dynamic_Type.h"

dtype operator+(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	return mxt == dtype::is_str ? dtype(A.str_var + B.str_var) : (mxt == dtype::is_float ? dtype((double)A + (double)B) : dtype((integer)A + (integer)B));
}

dtype operator-(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	return mxt == dtype::is_float ? dtype((double)A - (double)B) : dtype((integer)A - (integer)B);
}

dtype operator*(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	if (mxt == dtype::is_str)
	{
		dtype ret(std::string(""));
		if (A.current_type == mxt) for (integer i(std::string("1")) , lim = (integer)B;i <= lim;i += integer(std::string("1"))) ret.str_var += A.str_var;
		else for (integer i(std::string("1")) , lim = (integer)A;i <= lim;++ i) ret.str_var += B.str_var;
		return ret;
	}
	else return mxt == dtype::is_float ? dtype((double)A * (double)B) : dtype((integer)A * (integer)B);
}

dtype operator/(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	return mxt == dtype::is_float ? dtype((double)A / (double)B) : dtype((integer)A / (integer)B);
}

dtype operator%(const dtype &A , const dtype &B){return dtype((integer)A % (integer)B);}

dtype operator<(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	return mxt == dtype::is_str ? dtype(A.str_var < B.str_var) : (mxt == dtype::is_float ? dtype((double)A < (double)B) : dtype((integer)A < (integer)B));
}

dtype operator>(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	return mxt == dtype::is_str ? dtype(A.str_var > B.str_var) : (mxt == dtype::is_float ? dtype((double)A > (double)B) : dtype((integer)A > (integer)B));
}

dtype operator<=(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	return mxt == dtype::is_str ? dtype(A.str_var <= B.str_var) : (mxt == dtype::is_float ? dtype((double)A <= (double)B): dtype((integer)A <= (integer)B));
}

dtype operator>=(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	return mxt == dtype::is_str ? dtype(A.str_var >= B.str_var) : (mxt == dtype::is_float ? dtype((double)A >= (double)B) : dtype((integer)A >= (integer)B));
}

dtype operator!=(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	return mxt == dtype::is_str ? dtype(A.str_var != B.str_var) : (mxt == dtype::is_float ? dtype((double)A != (double)B) : dtype((integer)A != (integer)B));
}

dtype operator==(const dtype &A , const dtype &B)
{
	int mxt = std::max(A.current_type , B.current_type);
	return mxt == dtype::is_str ? dtype(A.str_var == B.str_var) : (mxt == dtype::is_float ? dtype((double)A == (double)B) : dtype((integer)A == (integer)B));
}

dtype operator&&(const dtype &A , const dtype &B){return dtype((bool)A && (bool)B);}

dtype operator||(const dtype &A , const dtype &B){return dtype((bool)A || (bool)B);}

std::ostream &operator<<(std::ostream &ost , const dtype &x){return ost << std::string(x);}

dtype dtype::operator+() const {return current_type == is_float ? dtype(+float_var) : dtype(+int_var);}

dtype dtype::operator-() const {return current_type == is_float ? dtype(-float_var) : dtype(-int_var);}

dtype dtype::operator!() const {return dtype(!operator bool());}

dtype &dtype::operator+=(const dtype &var){return (*this) = (*this) + var;}

dtype &dtype::operator-=(const dtype &var){return (*this) = (*this) - var;}

dtype &dtype::operator*=(const dtype &var){return (*this) = (*this) * var;}

dtype &dtype::operator/=(const dtype &var){return (*this) = (*this) / var;}

dtype &dtype::operator%=(const dtype &var){return (*this) = (*this) % var;}

dtype &dtype::operator&=(const dtype &var){return (*this) = (*this) && var;}

dtype &dtype::operator|=(const dtype &var){return (*this) = (*this) || var;}

dtype::operator bool() const
{
	bool ret;
	if (current_type == is_str) ret = str_var.length();
	else if (current_type == is_float) ret = float_var;
	else if (current_type == is_int) ret = (bool) int_var;
	else ret = bool_var;
	return ret;
}

dtype::operator integer() const
{
	integer ret;
	if (current_type == is_str) ret = integer(str_var);
	else if (current_type == is_float) ret = integer(float_var);
	else if (current_type == is_int) ret = int_var;
	else ret = integer(bool_var);
	return ret;
}

dtype::operator double() const
{
	double ret;
	if (current_type == is_str)
	{
		std::stringstream sst(str_var);
		sst >> ret;
	}
	else if (current_type == is_float) ret = float_var;
	else if (current_type == is_int) ret = (double)int_var;
	else ret = bool_var;
	return ret;
}

dtype::operator std::string() const {return current_type == is_null ? std::string() : (current_type == is_str ? str_var : (current_type == is_float ? std::to_string(float_var) : (current_type == is_int ? std::string(int_var) : (bool_var ? std::string("True") : std::string("False")))));}

dtype &dtype::to_bool(){return (*this) = dtype((bool)(*this));}

dtype &dtype::to_int(){return (*this) = dtype((integer)(*this));}

dtype &dtype::to_float(){return (*this) = dtype((double)(*this));}

dtype &dtype::to_str(){return (*this) = dtype((std::string)(*this));}