//
// Created by crazy_cloud on 2019/11/8.
//

#ifndef PYTHON_INTERPRETER_INTEGER_H
#define PYTHON_INTERPRETER_INTEGER_H

#include "Polynomial.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

class integer
{
	friend integer operator+(const integer &A , const integer &B);
	friend integer operator-(const integer &A , const integer &B);
	friend integer operator*(const integer &A , const integer &B);
	friend integer operator/(const integer &A , const integer &B);
	friend integer operator%(const integer &A , const integer &B);

	friend bool operator<(const integer &A , const integer &B);
	friend bool operator>(const integer &A , const integer &B);
	friend bool operator<=(const integer &A , const integer &B);
	friend bool operator>=(const integer &A , const integer &B);
	friend bool operator!=(const integer &A , const integer &B);
	friend bool operator==(const integer &A , const integer &B);

	friend std::istream &operator>>(std::istream &ist , integer &x);
	friend std::ostream &operator<<(std::ostream &ost , const integer &x);
private:

	std::vector<int> num;
	bool sig;//+ 1; - 0
	int len;

	bool is_zero() const;

	integer operator*(const int &var) const;
	integer &operator*=(const int &var);

	integer divide(const integer &A , const integer &B , const bool &tp);//tp : 0 - rem : 1 - quo

public:
	explicit integer(int length = 0){num = std::vector<int>(len = length , 0) , sig = 1;}
	explicit integer(const bool &val){sig = 1 , num.resize(len = 1) , num[0] = val;}
	explicit integer(const double &val);
	explicit integer(const std::string &str);

	explicit operator double() const;
	explicit operator bool() const;
	explicit operator std::string() const;

	//integer &operator=(const integer &var);
	//integer &operator=(integer &&var);

	integer operator+() const;
	integer operator-() const;

	integer &operator+=(const integer &var);
	integer &operator-=(const integer &var);
	integer &operator*=(const integer &var);
	integer &operator/=(const integer &var);
	integer &operator%=(const integer &var);

	integer &operator--();
	integer operator--(int x);

	integer &operator++();
	integer operator++(int x);

	integer abs(const integer &A);

	~integer(){}
};

#endif //PYTHON_INTERPRETER_INTEGER_H