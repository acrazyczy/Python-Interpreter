//
// Created by crazy_cloud on 2019/11/26.
//

#ifndef PYTHON_INTERPRETER_POLYNOMIAL_H
#define PYTHON_INTERPRETER_POLYNOMIAL_H

#include <algorithm>
#include <string>
#include <vector>

static int quick_power(int x , int y);

static void DFT(std::vector<int> &a , const int *omega , const int *trs , const int &len , const int &sig);

class poly
{
	friend poly operator*(const poly &A , const poly &B);
	friend poly operator+(const poly &A , const poly &B);
	friend poly operator-(const poly &A , const poly &B);
private:
	std::vector<int> coef;
public:
	int deg;
	poly(){}
	poly(const std::vector<int> &num , const int deg_){coef = num , deg = deg_;}

	const int operator[](const int &x) const;

	~poly(){}
};

#endif //PYTHON_INTERPRETER_POLYNOMIAL_H
