def haha(a):
	return 998244353

def quick_power(x , y , p = haha(3)):
	ret = 1
	while y != 0:
		if y % 2 == 1:
			ret *= x
			ret %= p
		x *= x
		x %= p
		y //= 2
	return ret
#print (quick_power(12,2,5))
print (quick_power(2,998244351))
print (1<3>2)