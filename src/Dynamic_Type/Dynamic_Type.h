//
// Created by crazy_cloud on 2019/12/1.
//

#ifndef CODE_DYNAMIC_TYPE_H
#define CODE_DYNAMIC_TYPE_H

#include <iostream>
#include <sstream>
#include <string>
#include "Integer.h"

class dtype
{
	friend dtype operator+(const dtype &A , const dtype &B);
	friend dtype operator-(const dtype &A , const dtype &B);
	friend dtype operator*(const dtype &A , const dtype &B);
	friend dtype operator/(const dtype &A , const dtype &B);
	friend dtype operator%(const dtype &A , const dtype &B);

	friend dtype operator<(const dtype &A , const dtype &B);
	friend dtype operator>(const dtype &A , const dtype &B);
	friend dtype operator<=(const dtype &A , const dtype &B);
	friend dtype operator>=(const dtype &A , const dtype &B);
	friend dtype operator!=(const dtype &A , const dtype &B);
	friend dtype operator==(const dtype &A , const dtype &B);

	friend dtype operator&&(const dtype &A , const dtype &B);
	friend dtype operator||(const dtype &A , const dtype &B);

	friend std::ostream &operator<<(std::ostream &ost , const dtype &x);
private:
	enum{is_null = 0 , is_bool = 1 , is_int = 2 , is_float = 3 , is_str = 4};

	bool bool_var;
	integer int_var;
	double float_var;
	std::string str_var;
	int current_type;

public:
	explicit dtype(){current_type = is_null;}
	explicit dtype(const bool &bool_var_){current_type = is_bool , bool_var = bool_var_;}
	explicit dtype(const integer &int_var_){current_type = is_int , int_var = int_var_;}
	explicit dtype(const double &float_var_){current_type = is_float , float_var = float_var_;}
	explicit dtype(const std::string &str_var_){current_type = is_str , str_var = str_var_;}

	dtype operator+() const;
	dtype operator-() const;

	dtype operator!() const;

	dtype &operator+=(const dtype &var);
	dtype &operator-=(const dtype &var);
	dtype &operator*=(const dtype &var);
	dtype &operator/=(const dtype &var);
	dtype &operator%=(const dtype &var);

	dtype &operator&=(const dtype &var);
	dtype &operator|=(const dtype &var);

	dtype &to_bool();
	dtype &to_int();
	dtype &to_float();
	dtype &to_str();

	explicit operator bool() const;
	explicit operator integer() const;
	explicit operator double() const;
	explicit operator std::string() const;

	~dtype(){}
};


#endif //CODE_DYNAMIC_TYPE_H
