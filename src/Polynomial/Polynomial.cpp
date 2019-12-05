//
// Created by crazy_cloud on 2019/11/26.
//

#include "Polynomial.h"

//Warning: All operations here are considered to be in ring Z[P] !!!

static const int P = 998244353;
static const int G = 3;

int quick_power(int x , int y)
{
	int ret = 1;
	for (;y;y >>= 1 , x = 1ll * x * x % P) if (y & 1) ret = 1ll * ret * x % P;
	return ret;
}

void DFT(std::vector<int> &a , const int *omega , const int *trs , const int &len , const int &sig)
{
	std::vector<int> t(len , 0);
	for (int i = 0;i < len;++ i) t[trs[i]] = a[i];
	for (int l = 2;l <= len;l <<= 1)
		for (int h = l >> 1 , j = 0 , wn = omega[sig > 0 ? len / l : len - len / l];j < len;j += l)
			for (int i = 0 , w = 1;i < h;++ i , w = 1ll * w * wn % P)
			{
				int u = t[i + j] , v = 1ll * t [i + j + h] * w % P;
				t[i + j] = (u + v) % P , t[i + j + h] = (u - v + P)%P;
			}
	for (int i = 0;i < len;++ i) a[i] = t[i];
	if (sig < 0) for (int i = 0 , inv = quick_power(len , P - 2);i < len;++ i) a[i] = 1ll * a[i] * inv % P;
}

const int poly::operator[](const int &x) const {return coef[x];}

poly operator*(const poly &A , const poly &B)
{
	std::vector<int> a = A.coef , b = B.coef;
	int len = 1;
	for (;len <= A.deg + B.deg;len <<= 1);
	a.resize(len) , b.resize(len);
	int *trs = new int [len];
	for (int i = 0, ret;i < len;++ i)
	{
		ret = 0;
		for (int x = i , j = 1;j < len;j <<= 1 , x >>= 1) ret = (ret << 1) | (x & 1);
		trs[i] = ret;
	}
	int *omega = new int [len + 1] , g = quick_power(G , (P - 1) / len);
	omega[0] = 1;
	for (int i = 1;i <= len;++ i) omega[i] = 1ll * omega[i - 1] * g % P;
	DFT(a , omega , trs , len , 1) , DFT(b , omega , trs , len , 1);
	for (int i = 0;i < len;++ i) a[i] = 1ll * a[i] * b[i] % P;
	DFT(a , omega , trs , len , -1) , a.resize(A.deg + B.deg + 1);
	return delete [] trs , delete [] omega , poly(a , A.deg + B.deg);
}

poly operator+(const poly &A , const poly &B)
{
	std::vector<int> ret(std::max(A.deg , B.deg) + 1);
	for (int i = 0;i <= A.deg || i <= B.deg;++ i) ret[i] = ((i <= A.deg ? A[i] : 0) + (i <= B.deg ? B[i] : 0)) % P;
	return poly(ret , std::max(A.deg , B.deg));
}

poly operator-(const poly &A , const poly &B)
{
	std::vector<int> ret(std::max(A.deg , B.deg) + 1);
	for (int i = 0;i <= A.deg || i <= B.deg;++ i) ret[i] = ((i <= A.deg ? A[i] : 0) - (i <= B.deg ? B[i] : 0) + P) % P;
	return poly(ret , std::max(A.deg , B.deg));
}