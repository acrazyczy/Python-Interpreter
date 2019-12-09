def quick_power(x , y , p) :
	ret = 1
	while y != 0 :
		if y % 2 == 1 :
			ret *= x
			ret %= p
		x *= x
		x %= p
		y //= 2
	return ret

def miller_rabin(x , n) :
	cnt = 0
	m = n - 1
	while m % 2 == 0 :
		cnt += 1
		m //= 2
	x = quick_power(x , m , n)
	if x == 1 : return True
	while cnt :
		cnt -= 1
		if x == 1 : return False
		if x == n - 1 : return True
		x *= x
		x %= n
	return x == 1

def is_prime(x) :
	if x == 2 or x == 3 or x == 5 or x == 7 or x == 11 or x == 13 or x == 17 or x == 19 or x == 23 or x == 29 or x == 31 or x == 37 : return True
	if x == 1 or x % 2 == 0 : return False
	i = 2
	while i <= 37 :
		if not miller_rabin(i , x) : return False
		i += 1
	return True

def gcd(x , y) :
	if y == 0 : return x
	return gcd(y , x % y)

def F(n , p , c) : return (n * n + c) % p

seed = 0x125E591

def rand() :
	seed += seed * 131072
	seed += seed // 32
	seed += seed * 4096
	seed %= 4294967296
	return seed

def random(n) : return rand() % n

def iabs(x) :
	if x >= 0 : return x
	else : return -x

def pollard_rho(n) :
	#print ("try" , n)
	if n == 1 : return
	if is_prime(n) :
		print(n)
		return
	while True :
		c , p = random(n - 1) + 1 , random(n - 1) + 1
		q = F(p , n , c)
		while p != q :
			g = gcd(iabs(p - q) , n)
			if g != 1 and g != n :
				pollard_rho(g)
				pollard_rho(n // g)
				return
			p , q = F(p , n , c) , F(F(q , n , c) , n , c)

pollard_rho(30)
print()
pollard_rho(998244352)
print()
pollard_rho(809172)
print()
